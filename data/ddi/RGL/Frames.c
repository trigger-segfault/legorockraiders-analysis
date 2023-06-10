
#include "Standard.h"
#include "Lists.h"
#include "Maths.h"
#include "Mem.h"
#include "Errors.h"
#include "Utils.h"
#include "Lights.h"
#include "Frames.h"

struct FrameGlobs {

	struct List *list;

} frameGlobs = { 0 };

BOOL Frame_ShutdownCallback(lpFrame frame, LPVOID data) {

	Error_Warn(TRUE, Error_Format("Unremoved frame named \"%s\"", frame->name));

	Frame_Remove(frame, FALSE);

	return FALSE;
}

VOID Frame_Shutdown(VOID) {

	List_RunThrough(frameGlobs.list, Frame_ShutdownCallback, NULL);
	List_Remove(frameGlobs.list);
	frameGlobs.list = NULL;
}

VOID Frame_Initialise(VOID) {

	frameGlobs.list = List_Create(sizeof(struct Frame));
}

/*
__inline BOOL Frame_AllFlagsSet(lpFrame frame, ULONG flags) {

	return ((frame->flags & flags) == flags);
}

__inline BOOL Frame_AnyFlagsSet(lpFrame frame, ULONG flags) {

	return (frame->flags & flags)?TRUE:FALSE;
}
*/

__inline VOID Frame_SetFlags_Internal(lpFrame frame, ULONG flags, BOOL set) {

	if (set) frame->flags |= flags;
	else frame->flags &= ~flags;
}

__inline BOOL Frame_TestFlags_Internal(lpFrame frame, ULONG flags, BOOL all) {

	if (all) return ((frame->flags & flags) == flags);
	else return (frame->flags & flags) ? TRUE : FALSE;
}

__inline BOOL Frame_IsClipped(lpFrame frame) {

	return (frame->flags & (FRAME_FLAG_TERMINATE|FRAME_FLAG_CLIPTERMINATE))?TRUE:FALSE;
}

__inline VOID Frame_SetFlags_External(lpFrame frame, ULONG flags, BOOL set) {

	Error_Fatal(flags & FRAME_FLAG_INTERNALMASK, "Invalid flags");
	
	Frame_SetFlags_Internal(frame, flags, set);
}

__inline BOOL Frame_TestFlags_External(lpFrame frame, ULONG flags, BOOL all) {

	Error_Fatal(flags & FRAME_FLAG_INTERNALMASK, "Invalid flags");

	return Frame_TestFlags_Internal(frame, flags, all);
}

#ifdef _DEBUG
lpFrame Frame_Debug_Create(lpFrame parent, LPUCHAR file, ULONG line) {
#else // _DEBUG
lpFrame Frame_Create(lpFrame parent) {
#endif // _DEBUG

	lpFrame frame;

	frame = List_ObtainItem(frameGlobs.list);
	Maths_IdentityMatrix(frame->localMatrix);
	Maths_IdentityMatrix(frame->worldMatrix);
	Frame_Link(frame, parent);

#ifdef _DEBUG
	{
		UCHAR name[1024];
		sprintf(name, "%s(%d)", file, line);
		frame->name = Mem_Alloc(strlen(name) + 1);
		sprintf(frame->name, "%s", name);
	}
#endif // _DEBUG

//	frame->flags |= FRAME_FLAG_IDENTITY;
	return frame;
}

lpFrame Frame_Find(lpFrame frame, LPUCHAR name) {

	lpFrame child, found;

	if (frame->name && 0 == strcmp(name, frame->name)) return frame;
	for (child=frame->children ; child ; child=Frame_GetNextChild(child)) {
		if (found = Frame_Find(child, name)) return found;
	}
	return NULL;
}

__inline LPUCHAR Frame_GetName(lpFrame frame) {

	return frame->name;
}

VOID Frame_SetName(lpFrame frame, LPUCHAR name) {

	List_CheckItem(frameGlobs.list, frame);

	if (frame->name) Mem_Free(frame->name);
	if (name) frame->name = Mem_CopyString(name);
	else frame->name = NULL;
}

VOID Frame_Remove(lpFrame dead, BOOL recursive) {

	lpFrame child, next;

	List_CheckItem(frameGlobs.list, dead);
	Error_Fatal(NULL == dead, "NULL passed as frame to Frame_Remove()");

	for (child=dead->children ; child ; child=next) {
		next = child->nextSibling;
		if (recursive) Frame_Remove(child, TRUE);
		else child->parent = NULL;
	}

	Frame_SetName(dead, NULL);
	Frame_Unlink(dead);

	List_ReturnItem(frameGlobs.list, dead);
}

static VOID Frame_CalculateLocalTransform(lpFrame frame, MATRIX4D worldMatrix) {

	MATRIX4D invParentWorld;

	List_CheckItem(frameGlobs.list, frame);
	Error_Fatal(NULL==frame->parent, "Pointless applying transformations to an unparented frame");

	Frame_UpdateWorldMatrix(frame->parent);
	Maths_InvertMatrixQuick(invParentWorld, frame->parent->worldMatrix);
	Maths_MultiplyMatrix(frame->localMatrix, invParentWorld, worldMatrix);
}

VOID Frame_SetPriority(lpFrame frame, SWORD priority, BOOL absolute) {

	List_CheckItem(frameGlobs.list, frame);

	frame->priority = priority;

	if (absolute) frame->flags |= FRAME_FLAG_ABSOLUTEPRIORITY;
	else frame->flags &= ~FRAME_FLAG_ABSOLUTEPRIORITY;
}

VOID Frame_MakeIdentity(lpFrame frame) {

	List_CheckItem(frameGlobs.list, frame);

	Maths_IdentityMatrix(frame->localMatrix);
	Frame_MarkDirty(frame, TRUE);
}

VOID Frame_SetWorldPosition(lpFrame frame, LPVECTOR3D pos) {

	List_CheckItem(frameGlobs.list, frame);
	Error_Fatal(NULL==frame->parent, "Pointless setting the position of an unparented frame");

	frame->worldMatrix[3][0] = pos->x;
	frame->worldMatrix[3][1] = pos->y;
	frame->worldMatrix[3][2] = pos->z;

	Frame_CalculateLocalTransform(frame, frame->worldMatrix);
	Frame_MarkDirty(frame, TRUE);
	frame->flags &= ~FRAME_FLAG_DIRTY;
}

VOID Frame_SetPosition(lpFrame frame, LPVECTOR3D pos) {

	List_CheckItem(frameGlobs.list, frame);
	Error_Fatal(NULL==frame->parent, "Pointless setting the position of an unparented frame");

	frame->localMatrix[3][0] = pos->x;
	frame->localMatrix[3][1] = pos->y;
	frame->localMatrix[3][2] = pos->z;
	Frame_MarkDirty(frame, TRUE);
}

VOID Frame_AddTranslation(lpFrame frame, LPVECTOR3D offset) {

	List_CheckItem(frameGlobs.list, frame);
	Error_Fatal(NULL==frame->parent, "Pointless setting the position of an unparented frame");

	frame->localMatrix[3][0] += offset->x;
	frame->localMatrix[3][1] += offset->y;
	frame->localMatrix[3][2] += offset->z;
	Frame_MarkDirty(frame, TRUE);
}

VOID Frame_SetScale(lpFrame frame, LPVECTOR3D scale) {

	List_CheckItem(frameGlobs.list, frame);

	frame->localMatrix[0][0] = scale->x;
	frame->localMatrix[1][1] = scale->y;
	frame->localMatrix[2][2] = scale->z;
	Frame_MarkDirty(frame, TRUE);
}

VOID Frame_AddRotation(lpFrame frame, LPVECTOR3D vec, REAL angle, BOOL before) {

	MATRIX4D result, original;

	List_CheckItem(frameGlobs.list, frame);

	Maths_SetMatrixRotation(result, vec, angle);
	Mem_Copy(original, frame->localMatrix, sizeof(MATRIX4D));
	if (before) Maths_MultiplyMatrix(frame->localMatrix, result, original);
	else Maths_MultiplyMatrix(frame->localMatrix, original, result);

	Frame_MarkDirty(frame, TRUE);
}

VOID Frame_SetRotation(lpFrame frame, LPVECTOR3D vec, REAL angle) {

	List_CheckItem(frameGlobs.list, frame);

	Maths_SetMatrixRotation(frame->localMatrix, vec, angle);
	Frame_MarkDirty(frame, TRUE);
}

VOID Frame_SetOrientation(lpFrame frame, LPVECTOR3D dir, LPVECTOR3D up) {

	VECTOR3D pos = { frame->localMatrix[3][0], frame->localMatrix[3][1], frame->localMatrix[3][2] };

	List_CheckItem(frameGlobs.list, frame);

	Maths_SetMatrixOrientation(frame->localMatrix, &pos, dir, up);
	Frame_MarkDirty(frame, TRUE);
}

VOID Frame_SetWorldOrientation_Old(lpFrame frame, LPVECTOR3D dir, LPVECTOR3D up) {

	VECTOR3D pos = { frame->localMatrix[3][0], frame->localMatrix[3][1], frame->localMatrix[3][2] };

	List_CheckItem(frameGlobs.list, frame);

	Maths_SetMatrixOrientation(frame->worldMatrix, &pos, dir, up);

	Frame_CalculateLocalTransform(frame, frame->worldMatrix);
	Frame_MarkDirty(frame, TRUE);
//	frame->flags &= ~FRAME_FLAG_DIRTY;
}

VOID Frame_SetWorldOrientation(lpFrame frame, LPVECTOR3D dir, LPVECTOR3D up) {

	VECTOR3D pos;

	List_CheckItem(frameGlobs.list, frame);

	Frame_UpdateWorldMatrix(frame);

	pos.x = frame->worldMatrix[3][0];
	pos.y = frame->worldMatrix[3][1];
	pos.z = frame->worldMatrix[3][2];

	Maths_SetMatrixOrientation(frame->worldMatrix, &pos, dir, up);

	Frame_CalculateLocalTransform(frame, frame->worldMatrix);
	Frame_MarkDirty(frame, TRUE);
	frame->flags &= ~FRAME_FLAG_DIRTY;
}

VOID Frame_GetRelativeTransform(lpFrame frame, lpFrame reference, MATRIX4D mat) {		// Untested

	MATRIX4D invRefMat;

	List_CheckItem(frameGlobs.list, frame);
	List_CheckItem(frameGlobs.list, reference);

	Frame_UpdateWorldMatrix(frame);
	Frame_UpdateWorldMatrix(reference);
	Maths_InvertMatrixQuick(invRefMat, reference->worldMatrix);
	Maths_MultiplyMatrix(mat, frame->worldMatrix, invRefMat);
}

VOID Frame_GetWorldTransform(lpFrame frame, MATRIX4D mat) {
	
	List_CheckItem(frameGlobs.list, frame);

	Frame_UpdateWorldMatrix(frame);
	Mem_Copy(mat, frame->worldMatrix, sizeof(MATRIX4D));
}

VOID Frame_SetTransform(lpFrame frame, MATRIX4D mat) {

	List_CheckItem(frameGlobs.list, frame);
	Error_Fatal(NULL==frame->parent, "Pointless setting the transform of an unparented frame");

	Mem_Copy(frame->localMatrix, mat, sizeof(MATRIX4D));
	Frame_MarkDirty(frame, TRUE);
}

VOID Frame_GetRelativePosition(lpFrame frame, lpFrame reference, LPVECTOR3D pos) {

	MATRIX4D invRefMat, mat;

	List_CheckItem(frameGlobs.list, frame);
	List_CheckItem(frameGlobs.list, reference);

	Frame_UpdateWorldMatrix(frame);
	Frame_UpdateWorldMatrix(reference);
	Maths_InvertMatrixQuick(invRefMat, reference->worldMatrix);
	Maths_MultiplyMatrix(mat, frame->worldMatrix, invRefMat);

	pos->x = mat[3][0];
	pos->y = mat[3][1];
	pos->z = mat[3][2];
}

__inline VOID Frame_GetWorldOffset(lpFrame frame, LPVECTOR3D pos, LPVECTOR3D offset) {

	List_CheckItem(frameGlobs.list, frame);

	Frame_UpdateWorldMatrix(frame);
	Maths_MultiplyVectorByMatrix(pos, offset, frame->worldMatrix);
}

__inline VOID Frame_GetRelativeOffset(lpFrame frame, lpFrame reference, LPVECTOR3D pos, LPVECTOR3D offset) {

	MATRIX4D invRefMat, mat;

	List_CheckItem(frameGlobs.list, frame);

	Frame_UpdateWorldMatrix(frame);
	Frame_UpdateWorldMatrix(reference);
	Maths_InvertMatrixQuick(invRefMat, reference->worldMatrix);
	Maths_MultiplyMatrix(mat, frame->worldMatrix, invRefMat);

	Maths_MultiplyVectorByMatrix(pos, offset, mat);
}

__inline VOID Frame_WorldInverseTransform(lpFrame frame, LPVECTOR3D result, LPVECTOR3D worldPos) {

	MATRIX4D invMatrix;

	List_CheckItem(frameGlobs.list, frame);

	Frame_UpdateWorldMatrix(frame);
	Maths_InvertMatrixQuick(invMatrix, frame->worldMatrix);
	Maths_MultiplyVectorByMatrix(result, worldPos, invMatrix);
}

__inline VOID Frame_GetPosition(lpFrame frame, LPVECTOR3D pos) {

	List_CheckItem(frameGlobs.list, frame);

	pos->x = frame->localMatrix[3][0];
	pos->y = frame->localMatrix[3][1];
	pos->z = frame->localMatrix[3][2];
}

__inline VOID Frame_GetWorldPosition(lpFrame frame, LPVECTOR3D pos) {

	List_CheckItem(frameGlobs.list, frame);

	Frame_UpdateWorldMatrix(frame);
	pos->x = frame->worldMatrix[3][0];
	pos->y = frame->worldMatrix[3][1];
	pos->z = frame->worldMatrix[3][2];
}

VOID Frame_GetOrientation(lpFrame frame, LPVECTOR3D dir, LPVECTOR3D up) {

	MATRIX4D mat;
	VECTOR3D stdDir = { 0.0f, 0.0f, 1.0f };
	VECTOR3D stdUp = { 0.0f, 1.0f, 0.0f };

	List_CheckItem(frameGlobs.list, frame);

	Mem_Copy(mat, frame->localMatrix, sizeof(MATRIX4D));
	mat[3][0] = mat[3][1] = mat[3][2] = 0.0f;
	if (dir) {
		Maths_MultiplyVectorByMatrix(dir, &stdDir, mat);
		Maths_Vector3DNormalise(dir);
	}
	if (up) {
		Maths_MultiplyVectorByMatrix(up, &stdUp, mat);
		Maths_Vector3DNormalise(up);
	}
}

VOID Frame_GetRelativeOrientation(lpFrame frame, lpFrame reference, LPVECTOR3D dir, LPVECTOR3D up) {

	MATRIX4D invRefMat, mat;
	VECTOR3D stdDir = { 0.0f, 0.0f, 1.0f };
	VECTOR3D stdUp = { 0.0f, 1.0f, 0.0f };

	List_CheckItem(frameGlobs.list, frame);

	Frame_UpdateWorldMatrix(frame);
	Frame_UpdateWorldMatrix(reference);
	Maths_InvertMatrixQuick(invRefMat, reference->worldMatrix);
	Maths_MultiplyMatrix(mat, frame->worldMatrix, invRefMat);
	mat[3][0] = mat[3][1] = mat[3][2] = 0.0f;
	if (dir) {
		Maths_MultiplyVectorByMatrix(dir, &stdDir, mat);
		Maths_Vector3DNormalise(dir);
	}
	if (up) {
		Maths_MultiplyVectorByMatrix(up, &stdUp, mat);
		Maths_Vector3DNormalise(up);
	}
}

VOID Frame_GetWorldOrientation(lpFrame frame, LPVECTOR3D dir, LPVECTOR3D up) {

	VECTOR3D stdDir = { 0.0f, 0.0f, 1.0f };
	VECTOR3D stdUp = { 0.0f, 1.0f, 0.0f };
	MATRIX4D mat;

	List_CheckItem(frameGlobs.list, frame);

	Frame_UpdateWorldMatrix(frame);
	Mem_Copy(mat, frame->worldMatrix, sizeof(MATRIX4D));
	mat[3][0] = mat[3][1] = mat[3][2] = 0.0f;
	if (dir) {
		Maths_MultiplyVectorByMatrix(dir, &stdDir, mat);
		Maths_Vector3DNormalise(dir);
	}
	if (up) {
		Maths_MultiplyVectorByMatrix(up, &stdUp, mat);
		Maths_Vector3DNormalise(up);
	}
}

lpMesh Frame_GetMesh(lpFrame frame) {

	List_CheckItem(frameGlobs.list, frame);
	Error_Fatal(FrameAttachmentType_Mesh==frame->attachmentType && NULL==frame->attachment, "NULL mesh on frame");

	if (FrameAttachmentType_Mesh == frame->attachmentType) return frame->attachment;
	return NULL;
}

VOID Frame_SetMesh(lpFrame frame, lpMesh mesh) {

	List_CheckItem(frameGlobs.list, frame);

	Error_Fatal(NULL==mesh, "NULL passed as mesh to Frame_SetMesh()");

	Error_Fatal(FrameAttachmentType_None!=frame->attachmentType, "Frame already has an attachment");
	frame->attachment = mesh;
	frame->attachmentType = FrameAttachmentType_Mesh;
}

VOID Frame_SetLight(lpFrame frame, lpLight light) {

	List_CheckItem(frameGlobs.list, frame);

	Error_Fatal(NULL==light, "NULL passed as mesh to Frame_SetLight()");

	Error_Fatal(FrameAttachmentType_None!=frame->attachmentType, "Frame already has an attachment");
	frame->attachment = light;
	frame->attachmentType = FrameAttachmentType_Light;
}

VOID Frame_RemoveAttachment(lpFrame frame) {

	frame->attachment = NULL;
	frame->attachmentType = FrameAttachmentType_None;
}

static VOID Frame_UpdateWorldMatrix(lpFrame frame) {

	// If this frame is marked as dirty, then carry on up the hierarchy until a frame
	// is found that is clean. Recalculate the world matrix for all of the frames in the list..

	lpFrame path[FRAME_MAXDEPTH];
	SLONG loop, depth = 0;

	List_CheckItem(frameGlobs.list, frame);

	while (frame->parent) {
		if (frame->flags & FRAME_FLAG_DIRTY) path[depth++] = frame;
		else break;
		frame = frame->parent;
	}

	for (loop=depth-1 ; loop>=0 ; loop--) {
		frame = path[loop];
		Frame_MultiplyMatrix(frame, frame->localMatrix, frame->parent->worldMatrix);
	}
}

static VOID Frame_MultiplyMatrix(lpFrame frame, MATRIX4D a, MATRIX4D b) {

	List_CheckItem(frameGlobs.list, frame);

	Maths_MultiplyMatrix(frame->worldMatrix, a, b);
	frame->flags &= ~FRAME_FLAG_DIRTY;
}

VOID Frame_BuildRenderList(lpFrame frame, MATRIX4D mat) {

	lpFrame child;
	lpMesh mesh;

	List_CheckItem(frameGlobs.list, frame);

	if (Frame_TestFlags(frame, FRAME_FLAG_TERMINATE|FRAME_FLAG_CLIPTERMINATE, FALSE)) return;

//	if (frame->flags & FRAME_FLAG_IDENTITY) Mem_Copy(frame->worldMatrix, mat, sizeof(MATRIX4D));
//	else
	if (frame->flags & FRAME_FLAG_DIRTY) Frame_MultiplyMatrix(frame, frame->localMatrix, mat);

	if (mesh = Frame_GetMesh(frame)) Mesh_AddToRenderList(mesh, frame);

	for (child=Frame_GetChildren(frame) ; child; child=Frame_GetNextChild(child)) {
		Frame_BuildRenderList(child, frame->worldMatrix);
	}
}

VOID Frame_SetParent(lpFrame frame, lpFrame parent) {

	List_CheckItem(frameGlobs.list, frame);
	Error_Fatal(Frame_IsDecendant(parent, frame), "Infinite parenting detected");

	Frame_Unlink(frame);
	Frame_Link(frame, parent);
}

lpFrame Frame_GetParent(lpFrame frame) {

	List_CheckItem(frameGlobs.list, frame);

	return frame->parent;
}

/*
VOID Frame_IdentityCheck(lpFrame frame) {

	if (frame->localMatrix[0][0] == 1.0f &&
		frame->localMatrix[0][1] == 0.0f &&
		frame->localMatrix[0][2] == 0.0f &&
		frame->localMatrix[0][3] == 0.0f &&
		frame->localMatrix[1][0] == 0.0f &&
		frame->localMatrix[1][1] == 1.0f &&
		frame->localMatrix[1][2] == 0.0f &&
		frame->localMatrix[1][3] == 0.0f &&
		frame->localMatrix[2][0] == 0.0f &&
		frame->localMatrix[2][1] == 0.0f &&
		frame->localMatrix[2][2] == 1.0f &&
		frame->localMatrix[2][3] == 0.0f &&
		frame->localMatrix[3][0] == 0.0f &&
		frame->localMatrix[3][1] == 0.0f &&
		frame->localMatrix[3][2] == 0.0f &&
		frame->localMatrix[3][3] == 1.0f) {

		frame->flags |= FRAME_FLAG_IDENTITY;
	}
}
*/

BOOL Frame_IsDecendant(lpFrame frame, lpFrame ancestor) {

	List_CheckItem(frameGlobs.list, ancestor);

	if (frame == ancestor) return TRUE;

	for (ancestor=Frame_GetChildren(ancestor) ; ancestor ; ancestor=Frame_GetNextChild(ancestor)) {
		if (Frame_IsDecendant(frame, ancestor)) return TRUE;
	}

	return FALSE;
}

__inline lpFrame Frame_GetChildren(lpFrame frame)	{ return frame->children; }
__inline lpFrame Frame_GetNextChild(lpFrame frame)	{ return frame->nextSibling; }

BOOL Frame_Recurse(lpFrame start, BOOL (*Callback)(lpFrame frame, LPVOID data), LPVOID data) {

	if (Callback(start, data)) return TRUE;

	for (start=Frame_GetChildren(start) ; start ; start=Frame_GetNextChild(start)) {
		if (Frame_Recurse(start, Callback, data)) return TRUE;
	}

	return FALSE;
}

VOID Frame_DumpHierarchy(lpFrame root, ULONG level, FILE *ofp) {

	lpFrame frame;
	static SLONG loop, x, y;
	static UCHAR msg[1024];
	static UCHAR item[256];
	UCHAR padding[] = "    ";

	msg[0] = '\0';
	sprintf(item, "\"%s\" 0x%0.4x\n", root->name, root->flags);
	for (loop=0 ; loop<(SLONG) level ; loop++) strcat(msg, padding);
	strcat(msg, item);
	for (y=0 ; y<4 ; y++) {
		for (loop=0 ; loop<(SLONG) level ; loop++) strcat(msg, padding);
		for (x=0 ; x<4 ; x++) {
			sprintf(item, "%0.2f", root->worldMatrix[y][x]);
			strcat(msg, "[");
			for (loop=0 ; loop<(SLONG) (7-strlen(item)) ; loop++) strcat(msg, " ");
			strcat(msg, item);
			strcat(msg, "]");
		}
		strcat(msg, "        ");
		for (x=0 ; x<4 ; x++) {
			sprintf(item, "%0.2f", root->localMatrix[y][x]);
			strcat(msg, "[");
			for (loop=0 ; loop<(SLONG) (7-strlen(item)) ; loop++) strcat(msg, " ");
			strcat(msg, item);
			strcat(msg, "]");
		}
		strcat(msg, "\n");
	}

	fprintf(ofp, "%s", msg);

	for (frame=Frame_GetChildren(root) ; frame ; frame=Frame_GetNextChild(frame)) {
		Frame_DumpHierarchy(frame, level+1, ofp);
	}
}

static VOID Frame_MarkDirty(lpFrame frame, BOOL first) {

	List_CheckItem(frameGlobs.list, frame);

//	if (first) frame->flags &= ~FRAME_FLAG_IDENTITY;

	if (!(frame->flags & FRAME_FLAG_DIRTY)) {
		frame->flags |= FRAME_FLAG_DIRTY;

		for (frame=Frame_GetChildren(frame) ; frame ; frame=Frame_GetNextChild(frame)) {
			Frame_MarkDirty(frame, FALSE);
		}
	}
}

static VOID Frame_Link(lpFrame frame, lpFrame parent) {

	List_CheckItem(frameGlobs.list, frame);

	if (parent) {
		Error_Fatal(NULL!=frame->parent, "Attempt to link parented frame");

		// Link it in at the start of the child list...
		frame->nextSibling = parent->children;
		frame->prevSibling = NULL;
		if (frame->nextSibling) frame->nextSibling->prevSibling = frame;
		parent->children = frame;
		frame->parent = parent;
		frame->enabledLights = parent->enabledLights;
	}
	Frame_MarkDirty(frame, TRUE);
}

static VOID Frame_Unlink(lpFrame frame) {

	List_CheckItem(frameGlobs.list, frame);

	if (frame->parent) {
		// Remove the frame from its current position in the hierachy...
		// Its children remain intact...
		if (frame->prevSibling) frame->prevSibling->nextSibling = frame->nextSibling;
		else if (frame->parent) frame->parent->children = frame->nextSibling;
		if (frame->nextSibling) frame->nextSibling->prevSibling = frame->prevSibling;
		frame->parent = frame->nextSibling = frame->prevSibling = NULL;
		frame->enabledLights = 0x00000000;
	}
}
