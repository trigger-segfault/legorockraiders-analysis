
#include "Standard.h"
#include "Viewports.h"
#include "Errors.h"
#include "Frames.h"
#include "Boxes.h"
#include "Lists.h"

#include "ModelClip.h"

struct ModelClipGlobs {

//	struct ListType *listType;
	lpViewport currVP;
	lpFrame currCamera;
	REAL currFOVDP, currSafeDistance;

} modelClipGlobs = { 0 };

VOID ModelClip_Initialise(VOID) {

//	modelClipGlobs.listType = List_SetupType(sizeof(struct ModelClip));
}

lpModelClip ModelClip_Create(lpFrame frame, lpViewport vp) {

	lpModelClip modelClip;
	
	if (modelClip = List_ObtainItem(Viewport_GetModelClipList(vp))) {

		modelClip->frame = frame;

		return modelClip;
	}

	return NULL;
}

VOID ModelClip_Remove(lpModelClip modelClip, lpViewport vp) {

	Error_Fatal(NULL == modelClip, "NULL passed to ModelClip_Remove()");
	List_CheckItem(Viewport_GetModelClipList(vp), modelClip);

	List_ReturnItem(Viewport_GetModelClipList(vp), modelClip);
}

VOID ModelClip_SetBox(lpModelClip modelClip, LPBOX3D box) {

	Error_Fatal(NULL == modelClip, "NULL passed to ModelClip_SetBox()");
	List_CheckItem(NULL, modelClip);

	modelClip->box = *box;
	Box_BuildVectorList(box, modelClip->vectorList);
}

LPBOX3D ModelClip_GetBox(lpModelClip modelClip) {

	Error_Fatal(NULL == modelClip, "NULL passed to ModelClip_GetBox()");
	List_CheckItem(NULL, modelClip);

	return &modelClip->box;
}

lpFrame ModelClip_GetFrame(lpModelClip modelClip) {

	Error_Fatal(NULL == modelClip, "NULL passed to ModelClip_GetFrame()");
	List_CheckItem(NULL, modelClip);

	return modelClip->frame;
}

lpModelClip debugStopClip = NULL;

BOOL ModelClip_IsClipped(lpModelClip modelClip) {

	Error_Fatal(NULL == modelClip, "NULL passed to ModelClip_IsClipped()");
	List_CheckItem(NULL, modelClip);

	return Frame_TestFlags(modelClip->frame, FRAME_FLAG_CLIPTERMINATE, TRUE);
}

static BOOL ModelClip_ProcessCallback(lpModelClip modelClip, LPVOID data) {

	LPBOX3D frustum = data;
	VECTOR3D screenBox[8];
	BOX3D bounds;
	ULONG loop;

	if (debugStopClip == modelClip) {
		ULONG a = 10;
	}

	Viewport_SetupBatchTransform(modelClipGlobs.currVP, modelClip->frame, modelClipGlobs.currCamera);

	for (loop=0 ; loop<8 ; loop++) {
		Viewport_BatchTransform(modelClipGlobs.currVP, &screenBox[loop], &modelClip->vectorList[loop]);
	}

	Box_Get(&bounds, screenBox, 8);

	if (!Box_IntersectionImpossible(&bounds, frustum)) {

		MATRIX4D mat;
		VECTOR3D pos, forward = { 0.0f, 0.0f, 1.0f };
		REAL dist, dp;
		VECTOR3D offset;

		Box_GetCenter(&modelClip->box, &offset);
		Frame_GetRelativeTransform(modelClip->frame, modelClipGlobs.currCamera, mat);
		Maths_MultiplyVectorByMatrix(&pos, &offset, mat);

		dist = Maths_Vector3DLength(&pos);
		Maths_Vector3DScale(&pos, &pos, 1.0f / dist);
		dp = Maths_Vector3DDotProduct(&pos, &forward);

//		Frame_SetPriority(modelClip->frame, (SWORD) -((dist / Viewport_GetBackClip(modelClipGlobs.currVP)) * MAX_SWORD), FALSE);

		if (dist < modelClipGlobs.currSafeDistance) {
//			modelClip->frame->flags &= ~FRAME_FLAG_TERMINATE;
			Frame_SetFlags(modelClip->frame, FRAME_FLAG_CLIPTERMINATE, FALSE);
			return FALSE;
		}

		if (dp > modelClipGlobs.currFOVDP * 0.5f) {

			const ULONG lineList[12][2] = {
				{ 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 },
				{ 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 },
				{ 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 }
			};

			for (loop=0 ; loop<12 ; loop++) {
				if (Box_LineIntersection(frustum, &screenBox[lineList[loop][0]], &screenBox[lineList[loop][1]])) {
					
//					modelClip->frame->flags &= ~FRAME_FLAG_TERMINATE;
					Frame_SetFlags(modelClip->frame, FRAME_FLAG_CLIPTERMINATE, FALSE);
					return FALSE;

				}
			}
		}

		for (loop=0 ; loop<8 ; loop++) {
			if (Box_PointInside(frustum, &screenBox[loop])) {
//				modelClip->frame->flags &= ~FRAME_FLAG_TERMINATE;
				Frame_SetFlags(modelClip->frame, FRAME_FLAG_CLIPTERMINATE, FALSE);
				return FALSE;
			}
		}
	}

//	modelClip->frame->flags |= FRAME_FLAG_TERMINATE;
	Frame_SetFlags(modelClip->frame, FRAME_FLAG_CLIPTERMINATE, TRUE);

	return FALSE;
}

VOID ModelClip_Process(lpViewport vp, lpFrame camera, REAL safeDistance) {

	REAL width = (REAL) Viewport_GetWidth(vp);
	REAL height = (REAL) Viewport_GetHeight(vp);
	BOX3D frustum;

	frustum.min.x = 0.0f;
	frustum.min.y = 0.0f;
	frustum.min.z = 0.0f;
	frustum.max.x = width;
	frustum.max.y = height;
	frustum.max.z = 1.0f;

	modelClipGlobs.currVP = vp;
	modelClipGlobs.currCamera = camera;
	modelClipGlobs.currFOVDP = Maths_Cos(vp->fov / 2.0f);
	modelClipGlobs.currSafeDistance = safeDistance;

	List_RunThrough(Viewport_GetModelClipList(vp), ModelClip_ProcessCallback, &frustum);
}

static BOOL ModelClip_ProcessCallback_Old(lpModelClip modelClip, LPVOID data) {

	// This should be explanded to allow for multiple boxes per ModelClip in order to take advantage
	// of using model space for the clipping...

	LPVECTOR3D screenBox = data;
	VECTOR3D frustum[8];
	BOX3D frustumBounds;
	ULONG loop;

	for (loop=0 ; loop<8 ; loop++) {
		Viewport_InverseTransform(modelClipGlobs.currVP, modelClip->frame, modelClipGlobs.currCamera, &frustum[loop], &screenBox[loop]);
	}

	Box_Get(&frustumBounds, frustum, 8);

	if (!Box_IntersectionImpossible(&frustumBounds, &modelClip->box)) {

		const ULONG lineList[12][2] = {
			{ 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 },
			{ 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 },
			{ 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 }
		};

		for (loop=0 ; loop<12 ; loop++) {
			if (Box_LineIntersection(&modelClip->box, &frustum[lineList[loop][0]], &frustum[lineList[loop][1]])) {
				modelClip->frame->flags &= ~FRAME_FLAG_TERMINATE;
				return FALSE;
			}
		}

		for (loop=0 ; loop<8 ; loop++) {
			if (Box_PointInside(&modelClip->box, &frustum[loop])) {
				modelClip->frame->flags &= ~FRAME_FLAG_TERMINATE;
				return FALSE;
			}
		}

		Box_SetupVisibiltyCheck(modelClipGlobs.currVP, modelClip->frame, modelClipGlobs.currCamera);
		if (Box_CornerVisibile(&modelClip->box)) {
			modelClip->frame->flags &= ~FRAME_FLAG_TERMINATE;
			return FALSE;
		}

	}

	modelClip->frame->flags |= FRAME_FLAG_TERMINATE;

	return FALSE;
}

VOID ModelClip_Process_Old(lpViewport vp, lpFrame camera) {

	REAL width = (REAL) Viewport_GetWidth(vp);
	REAL height = (REAL) Viewport_GetHeight(vp);
	VECTOR3D screenBox[8];
	
	screenBox[0].x = 0.0f;
	screenBox[0].y = 0.0f;
	screenBox[0].z = 0.0f;
	screenBox[1].x = width;
	screenBox[1].y = 0.0f;
	screenBox[1].z = 0.0f;
	screenBox[2].x = width;
	screenBox[2].y = height;
	screenBox[2].z = 0.0f;
	screenBox[3].x = 0.0f;
	screenBox[3].y = height;
	screenBox[3].z = 0.0f;
	screenBox[4].x = 0.0f;
	screenBox[4].y = 0.0f;
	screenBox[4].z = 1.0f;
	screenBox[5].x = width;
	screenBox[5].y = 0.0f;
	screenBox[5].z = 1.0f;
	screenBox[6].x = width;
	screenBox[6].y = height;
	screenBox[6].z = 1.0f;
	screenBox[7].x = 0.0f;
	screenBox[7].y = height;
	screenBox[7].z = 1.0f;

	modelClipGlobs.currVP = vp;
	modelClipGlobs.currCamera = camera;

	List_RunThrough(Viewport_GetModelClipList(vp), ModelClip_ProcessCallback_Old, screenBox);
}
