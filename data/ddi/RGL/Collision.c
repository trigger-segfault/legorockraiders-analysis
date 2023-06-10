
#include "Standard.h"
#include "Maths.h"
#include "Lists.h"
#include "Boxes.h"
#include "Frames.h"
#include "Errors.h"
#include "Boxes.h"
#include "Collision.h"

struct CollisionGlobs {

	struct List *listList;

} collisionGlobs = { 0 };

typedef struct CollisionCheckLineData {

	LPLINE3D line;
	lpCollision minDelta;
	BOOL first;

} *lpCollisionCheckLineData;

VOID Collision_Initialise(VOID) {

	collisionGlobs.listList = List_Create(sizeof(struct CollisionList));
}

VOID Collision_Shutdown(VOID) {

	List_Remove(collisionGlobs.listList);
	collisionGlobs.listList = NULL;
}

lpCollisionList Collision_CreateList(VOID) {

	lpCollisionList list = List_ObtainItem(collisionGlobs.listList);

	list->list = List_Create(sizeof(struct Collision));

	return list;
}

VOID Collision_RemoveList(lpCollisionList collisionList) {

	Error_Fatal(NULL == collisionList, "NULL passed to as collisionList Collision_RemoveList()");
	List_CheckItem(collisionGlobs.listList, collisionList);

	List_Remove(collisionList->list);
	List_ReturnItem(collisionGlobs.listList, collisionList);
}

VOID Collision_Remove(lpCollisionList list, lpCollision collision) {

	Error_Fatal(NULL == list, "NULL passed to as list Collision_Remove()");
	Error_Fatal(NULL == collision, "NULL passed to as collision Collision_Remove()");
	List_CheckItem(collisionGlobs.listList, list);

	List_ReturnItem(list->list, collision);
}

LPVOID Collision_GetObject(lpCollision collision) {

	Error_Fatal(NULL == collision, "NULL passed to as collision Collision_Remove()");
	List_CheckItem(NULL, collision);

	return collision->object;
}

lpCollision Collision_Create(lpCollisionList collisionList, lpFrame frame, LPVOID object, BOOL linearMotion) {

	lpCollision collision = List_ObtainItem(collisionList->list);

	collision->frame = frame;
	collision->object = object;
	Collision_SetFlags(collision, COLLISION_FLAG_LINEAR, linearMotion);

	Frame_GetWorldPosition(frame, &collision->lastPos);

	return collision;
}

lpFrame Collision_GetFrame(lpCollision collision) {

	Error_Fatal(NULL == collision, "NULL passed to as collision Collision_Remove()");
	List_CheckItem(NULL, collision);

	return collision->frame;
}

VOID Collision_SetWorldRadius(lpCollision collision, REAL radius) {

	Error_Fatal(NULL == collision, "NULL passed to as collision Collision_Remove()");
	List_CheckItem(NULL, collision);

	collision->worldRadius = radius;
}

ULONG Collision_AddBox(lpCollision collision, LPBOX3D box) {

	VECTOR3D list[8];
	ULONG loop;

	Error_Fatal(NULL == collision, "NULL passed to as collision Collision_Remove()");
	List_CheckItem(NULL, collision);
	Error_Overflow(collision->boxCount, COLLISION_MAXBOXES);

	collision->boxList[collision->boxCount].box = *box;

	Box_BuildVectorList(box, list);
	for (loop=0 ; loop<8 ; loop++) {
		collision->boxRadius = max(collision->boxRadius, Maths_Vector3DLength(&list[loop]));
	}

	return collision->boxCount++;
}

__inline VOID Collision_DisableBox(lpCollision collision, ULONG box, BOOL disable) {

	Error_Fatal(NULL == collision, "NULL passed to as collision Collision_Remove()");
	List_CheckItem(NULL, collision);

	if (disable) collision->boxList[box].flags |= COLLISIONBOX_FLAG_DISABLED;
	else collision->boxList[box].flags &= ~COLLISIONBOX_FLAG_DISABLED;
}

__inline VOID Collision_SetBoxUserFlags(lpCollision collision, ULONG box, UWORD flags, BOOL set) {

	Error_Fatal(NULL == collision, "NULL passed to as collision Collision_Remove()");
	List_CheckItem(NULL, collision);

	if (set) collision->boxList[box].userFlags |= flags;
	else collision->boxList[box].userFlags &= ~flags;
}

__inline BOOL Collision_TestBoxUserFlags(lpCollision collision, ULONG box, UWORD flags, BOOL all) {

	Error_Fatal(NULL == collision, "NULL passed to as collision Collision_Remove()");
	List_CheckItem(NULL, collision);

	if (all) return (collision->boxList[box].userFlags & flags) == flags;
	else return (collision->boxList[box].userFlags & flags) ? TRUE : FALSE;
}

__inline VOID Collision_SetFlags(lpCollision collision, ULONG flags, BOOL set) {

	Error_Fatal(NULL == collision, "NULL passed to as collision Collision_Remove()");
	List_CheckItem(NULL, collision);

	if (set) collision->flags |= flags;
	else collision->flags &= ~flags;
}

__inline BOOL Collision_TestFlags(lpCollision collision, ULONG flags, BOOL all) {

	Error_Fatal(NULL == collision, "NULL passed to as collision Collision_Remove()");
	List_CheckItem(NULL, collision);

	if (all) return (collision->flags & flags) == flags;
	else return (collision->flags & flags)?TRUE:FALSE;
}

__inline static BOOL Collision_CheckWorldRadiusPoint(lpCollision collision, LPVECTOR3D point) {

	VECTOR3D framePos;

	Error_Fatal(NULL == collision, "NULL passed to as collision Collision_Remove()");
	List_CheckItem(NULL, collision);

	if (0.0f != collision->worldRadius) {

		Frame_GetWorldPosition(collision->frame, &framePos);

		if (Maths_Vector3DDistance(&framePos, point) > collision->worldRadius) return FALSE;

	}
	
	return TRUE;	
}

__inline static BOOL Collision_CheckWorldRadiusLine(lpCollision collision, LPLINE3D line) {

	VECTOR3D framePos;

	Error_Fatal(NULL == collision, "NULL passed to as collision Collision_Remove()");
	List_CheckItem(NULL, collision);

	if (0.0f != collision->worldRadius) {

		Frame_GetWorldPosition(collision->frame, &framePos);

		if (Maths_PointLineDistance(&framePos, &line->start, &line->end) > collision->worldRadius) return FALSE;

	}
	
	return TRUE;	
}

BOOL Collision_CheckPointCallback(lpCollision collision, LPVECTOR3D worldPos) { 

	VECTOR3D localPos;
	ULONG loop;

	Error_Fatal(NULL == collision, "NULL passed to as collision Collision_Remove()");
	List_CheckItem(NULL, collision);

	if (!(collision->flags & COLLISION_FLAG_DISABLED)) {
		if (Collision_CheckWorldRadiusPoint(collision, worldPos)) {

			if (0 == collision->boxCount) return TRUE;

			Frame_WorldInverseTransform(collision->frame, &localPos, worldPos);

			if (Maths_Vector3DLength(&localPos) < collision->boxRadius) {

				for (loop=0 ; loop<collision->boxCount ; loop++) {
					if (!(collision->boxList[loop].flags & COLLISIONBOX_FLAG_DISABLED)) {
						if (Box_PointInside(&collision->boxList[loop].box, &localPos)) {

							collision->hitBox = loop;

							return TRUE;
						}
					}
				}
			}
		}
	}

	return FALSE;
}

BOOL Collision_CheckLineStatic(lpCollision collision, lpCollisionCheckLineData data) { 

	VECTOR3D localPos[2], origin = { 0.0f, 0.0f, 0.0f };
	enum BoxesSide side;
	VECTOR3D localHit;
	REAL delta;
	ULONG loop;
	LPLINE3D worldLine = data->line;

	Error_Fatal(NULL == collision, "NULL passed to as collision Collision_Remove()");
	List_CheckItem(NULL, collision);

	if (!(collision->flags & COLLISION_FLAG_DISABLED)) {
		if (Collision_CheckWorldRadiusLine(collision, worldLine)) {

			Frame_WorldInverseTransform(collision->frame, &localPos[0], &worldLine->start);
			Frame_WorldInverseTransform(collision->frame, &localPos[1], &worldLine->end);

			collision->delta = 2.0f;

			if (Maths_PointLineDistance(&origin, &localPos[0], &localPos[1]) < collision->boxRadius) {

				for (loop=0 ; loop<collision->boxCount ; loop++) {
					if (!(collision->boxList[loop].flags & COLLISIONBOX_FLAG_DISABLED)) {
						if (Box_LineIntersectionEx(&collision->boxList[loop].box, &localPos[0], &localPos[1], &localHit, &delta, &side)) {

							if (delta < collision->delta) {

								collision->delta = delta;
								collision->localHit = localHit;
								collision->side = side;

								Frame_GetWorldOffset(collision->frame, &collision->worldHit, &collision->localHit);

								collision->hitBox = loop;

								if (NULL == data->minDelta || delta < data->minDelta->delta) data->minDelta = collision;

								if (data->first) return TRUE;
							}
						}
					}
				}
			}
		}
	}

	return FALSE;
}

BOOL Collision_CheckLineLinear(lpCollision collision, lpCollisionCheckLineData data) { 

	// The same, only take into account the motion of the collision excluding rotation...

	VECTOR3D offset, worldStart;
	VECTOR3D localPos[2], origin = { 0.0f, 0.0f, 0.0f };
	enum BoxesSide side;
	VECTOR3D localHit;
	REAL delta;
	ULONG loop;
	LPLINE3D worldLine = data->line;

	Error_Fatal(NULL == collision, "NULL passed to as collision Collision_Remove()");
	List_CheckItem(NULL, collision);

	if (!(collision->flags & COLLISION_FLAG_DISABLED)) {
		if (Collision_CheckWorldRadiusLine(collision, worldLine)) {

			Frame_GetWorldPosition(collision->frame, &offset);
			Maths_Vector3DSubtract(&offset, &offset, &collision->lastPos);
			Maths_Vector3DAdd(&worldStart, &worldLine->start, &offset);

			Frame_WorldInverseTransform(collision->frame, &localPos[0], &worldStart);
			Frame_WorldInverseTransform(collision->frame, &localPos[1], &worldLine->end);

			collision->delta = 2.0f;

			if (Maths_PointLineDistance(&origin, &localPos[0], &localPos[1]) < collision->boxRadius) {

				for (loop=0 ; loop<collision->boxCount ; loop++) {
					if (!(collision->boxList[loop].flags & COLLISIONBOX_FLAG_DISABLED)) {
						if (Box_LineIntersectionEx(&collision->boxList[loop].box, &localPos[0], &localPos[1], &localHit, &delta, &side)) {

							if (delta < collision->delta) {

								collision->delta = delta;
								collision->localHit = localHit;
								collision->side = side;

								Frame_GetWorldOffset(collision->frame, &collision->worldHit, &collision->localHit);
								Maths_Vector3DScale(&offset, &offset, 1.0f - collision->delta);
								Maths_Vector3DSubtract(&collision->worldHit, &collision->worldHit, &offset);

								collision->hitBox = loop;

								if (NULL == data->minDelta || delta < data->minDelta->delta) data->minDelta = collision;

								if (data->first) return TRUE;
							}
						}
					}
				}
			}
		}
	}

	return FALSE;
}

__inline lpCollision Collision_CheckPoint(lpCollisionList collisionList, LPVECTOR3D point) {

	return List_RunThrough(collisionList->list, Collision_CheckPointCallback, point);
}

__inline BOOL Collision_CheckLineCallback(lpCollision collision, lpCollisionCheckLineData data) {

	Error_Fatal(NULL == collision, "NULL passed to as collision Collision_Remove()");
	List_CheckItem(NULL, collision);

	if (Collision_TestFlags(collision, COLLISION_FLAG_LINEAR, TRUE)) return Collision_CheckLineLinear(collision, data);
	else return Collision_CheckLineStatic(collision, data);
}

__inline lpCollision Collision_CheckLine(lpCollisionList collisionList, LPLINE3D line, BOOL first) {

	struct CollisionCheckLineData data;

	data.first = first;
	data.line = line;
	data.minDelta = NULL;

	List_RunThrough(collisionList->list, Collision_CheckLineCallback, &data);

	return data.minDelta;
}

BOOL Collision_EndUpdateCallback(lpCollision collision, LPVOID data) {

	Error_Fatal(NULL == collision, "NULL passed to as collision Collision_Remove()");
	List_CheckItem(NULL, collision);

	Frame_GetWorldPosition(collision->frame, &collision->lastPos);

	return FALSE;
}

VOID Collision_EndUpdate(lpCollisionList collisionList) {

	List_RunThrough(collisionList->list, Collision_EndUpdateCallback, NULL);
}

BOOL Collision_DrawCallback(lpCollision collision, LPVOID p) {

	lpCollisionDrawData data = p;
	ULONG loop;
	COLOUR colourList[COLLISION_MAXBOXES] = {
		COLOUR_FROMCHAR(255, 000, 255),
		COLOUR_FROMCHAR(255, 000, 000),
		COLOUR_FROMCHAR(000, 255, 000),
		COLOUR_FROMCHAR(000, 255, 255),
	};

	Error_Fatal(NULL == collision, "NULL passed to as collision Collision_Remove()");
	List_CheckItem(NULL, collision);

	for (loop=0 ; loop<collision->boxCount ; loop++) {
		if (!(collision->boxList[loop].flags & COLLISIONBOX_FLAG_DISABLED)) {
			Box_Draw(&collision->boxList[loop].box, data->vp, collision->frame, data->camera, colourList[loop]);
		}
	}

	return FALSE;
}

VOID Collision_Draw(lpCollisionList collisionList, lpViewport vp, lpFrame camera) {

	struct CollisionDrawData data = { vp, camera };

	List_RunThrough(collisionList->list, Collision_DrawCallback, &data);
}
