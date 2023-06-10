
#include "Standard.h"
#include "Viewports.h"
#include "Frames.h"
#include "Maths.h"
#include "Lists.h"
#include "Draw.h"
#include "Frames.h"
#include "Errors.h"
#include "Collision.h"
#include "Projectiles.h"

struct ProjectileGlobs {

	struct List *dataList;

} projectileGlobs;

struct ProjectileUpdateData {

	lpList list;
	lpCollisionList collisionList;
	REAL delta;

	BOOL (*hitCallback)(lpProjectile projectile, lpCollision collision, LPVOID data);
	LPVOID hitCallbackData;

	VOID (*updateCallback)(lpProjectile projectile, BOOL remove, LPVOID data);
	LPVOID updateCallbackData;
};

VOID Projectile_Initialise(VOID) {

	projectileGlobs.dataList = List_Create(sizeof(struct ProjectileData));
}

lpProjectileData Projectile_CreateData(VOID) {

	return List_ObtainItem(projectileGlobs.dataList);
}

VOID Projectile_RemoveData(lpProjectileData data) {

	List_ReturnItem(projectileGlobs.dataList, data);
}

lpList Projectile_CreateList(VOID) {

	return List_Create(sizeof(struct Projectile));
}

VOID Projectile_SetTimeRemaining(lpProjectile projectile, REAL time) {

	projectile->remaining = time;
	projectile->flags |= PROJECTILE_FLAG_TIMEOUT;
	projectile->flags &= ~PROJECTILE_FLAG_DISTOUT;
}

VOID Projectile_SetAcceleration(lpProjectileData projectileData, REAL acceleration, REAL velocityCutOff) {

	List_CheckItem(projectileGlobs.dataList, projectileData);

	projectileData->acceleration = acceleration;
	projectileData->velocityCutOff = velocityCutOff;
}

VOID Projectile_SetGravity(lpProjectileData projectileData, REAL gravityAcceleration, REAL gravityVelocityCutOff) {

	List_CheckItem(projectileGlobs.dataList, projectileData);

	projectileData->gravityAcceleration = gravityAcceleration;
	projectileData->gravityCutOff = gravityVelocityCutOff;
}

// If 'referenceFrame' is NULL then the frame pointed to by 'moveFrame' will be updated.
lpProjectile Projectile_Create(lpList list, lpProjectileData data, lpFrame *moveFrame, LPVECTOR3D position, LPVECTOR3D direction, LPVECTOR3D up, REAL velocity, lpFrame referenceFrame, ULONG flags) {

	lpProjectile projectile = List_ObtainItem(list);
	
	Error_Fatal(NULL == data, "Requires pointer to ProjectileData structure");

	if (moveFrame) {
	
		if (referenceFrame) {

			Error_Fatal(NULL != (*moveFrame), "Contents of 'moveFrame' must be NULL");

			(*moveFrame) = Frame_Create(referenceFrame);
			projectile->flags |= PROJECTILE_FLAG_REMOVEFRAME;

		} 

		projectile->frame = (*moveFrame);

	} else projectile->frame = NULL;

	projectile->velocity = velocity;
	projectile->data = data;
	projectile->flags |= (flags & PROJECTILE_FLAG_USERMASK);

	if (position) {
		projectile->position = *position;
		if (moveFrame && (*moveFrame)) Frame_SetPosition((*moveFrame), position);
	} else {
		if (moveFrame && (*moveFrame)) Frame_GetPosition((*moveFrame), &projectile->position);
	}

	if (direction) {
		projectile->direction = *direction;
		Maths_Vector3DNormalise(&projectile->direction);
		if (moveFrame && (*moveFrame)) Frame_SetOrientation((*moveFrame), direction, up);
	} else {
		if (moveFrame && (*moveFrame)) Frame_GetOrientation((*moveFrame), &projectile->direction, NULL);
	}

	return projectile;
}

__inline VOID Projectile_GetPosition(lpProjectile projectile, LPVECTOR3D position) {

	*position = projectile->position;
}

VOID Projectile_SetUserData(lpProjectile projectile, LPVOID data) {

	projectile->userData = data;
}

LPVOID Projectile_GetUserData(lpProjectile projectile) {

	return projectile->userData;
}

VOID Projectile_Remove(lpList list, lpProjectile projectile) {

	if (projectile->flags & PROJECTILE_FLAG_REMOVEFRAME) Frame_Remove(projectile->frame, TRUE);
	List_ReturnItem(list, projectile);
}

BOOL Projectile_Update(lpProjectile projectile, LPVOID p) {

	LINE3D line;
	VECTOR3D offset;
	struct ProjectileUpdateData *data = p;
	lpCollision collision = NULL;
	BOOL remove = FALSE;
	REAL oldVelocity, oldGravity;
	VECTOR3D gravityDir = { 0.0f, -1.0f, 0.0f };

	oldVelocity = projectile->velocity;

	if (!(projectile->flags & PROJECTILE_FLAG_MAXVELOCITY)) {

		projectile->velocity += (projectile->data->acceleration * data->delta);

		if ((oldVelocity >= projectile->data->velocityCutOff && projectile->velocity <= projectile->data->velocityCutOff) ||
			(oldVelocity <= projectile->data->velocityCutOff && projectile->velocity >= projectile->data->velocityCutOff)) {

			projectile->velocity = projectile->data->velocityCutOff;
			projectile->flags |= PROJECTILE_FLAG_MAXVELOCITY;
		}
	}

	Maths_Vector3DScale(&offset, &projectile->direction, ((oldVelocity + projectile->velocity) / 2.0f) * data->delta);

	oldGravity = projectile->gravityVelocity;

	if (!(projectile->flags & PROJECTILE_FLAG_MAXGRAVITY)) {

		projectile->gravityVelocity += (projectile->data->gravityAcceleration * data->delta);

		if ((oldGravity >= projectile->data->gravityCutOff && projectile->gravityVelocity <= projectile->data->gravityCutOff) ||
			(oldGravity <= projectile->data->gravityCutOff && projectile->gravityVelocity >= projectile->data->gravityCutOff)) {

			projectile->gravityVelocity = projectile->data->gravityCutOff;
			projectile->flags |= PROJECTILE_FLAG_MAXGRAVITY;
		}
	}

	Maths_Vector3DScale(&gravityDir, &gravityDir, ((oldGravity + projectile->gravityVelocity) / 2.0f) * data->delta);

	line.start = projectile->position;
	Maths_Vector3DAdd(&projectile->position, &projectile->position, &offset);
	Maths_Vector3DAdd(&projectile->position, &projectile->position, &gravityDir);
	line.end = projectile->position;

	if (projectile->flags & PROJECTILE_FLAG_POINTCHECK) collision = Collision_CheckPoint(data->collisionList, &projectile->position);
	else collision = Collision_CheckLine(data->collisionList, &line, TRUE);

	if (projectile->frame) {
		Frame_SetPosition(projectile->frame, &projectile->position);
		if (!(projectile->flags & PROJECTILE_FLAG_LEVELFLIGHT)) {

			VECTOR3D tDir, tUp;

			Frame_GetOrientation(projectile->frame, &tDir, &tUp);
			Frame_SetOrientation(projectile->frame, Maths_Vector3DSubtract(&tDir, &line.end, &line.start), &tUp);
		}
	}

	if (collision) {

		if (data->hitCallback(projectile, collision, data->hitCallbackData)) remove = TRUE;

	}

	if (projectile->flags & PROJECTILE_FLAG_TIMEOUT) {
		projectile->remaining -= data->delta;
		if (projectile->remaining < 0.0f) remove = TRUE;
	}

	if (data->updateCallback) data->updateCallback(projectile, remove, data->updateCallbackData);

	if (remove) Projectile_Remove(data->list, projectile);

	return FALSE;
}

VOID Projectile_UpdateList(lpList list, lpCollisionList collisionList, REAL delta, BOOL (*hitCallback)(lpProjectile projectile, lpCollision collision, LPVOID hitCallbackData), LPVOID hitCallbackData, VOID (*updateCallback)(lpProjectile projectile, BOOL remove, LPVOID updateCallbackData), LPVOID updateCallbackData) {

	struct ProjectileUpdateData data;

	data.list = list;
	data.collisionList = collisionList;
	data.delta = delta;
	data.hitCallback = hitCallback;
	data.hitCallbackData = hitCallbackData;
	data.updateCallback = updateCallback;
	data.updateCallbackData = updateCallbackData;

	List_RunThrough(list, Projectile_Update, &data);
}

BOOL Projectile_DrawMarkersCallback(lpProjectile projectile, LPVOID p) {

	struct CollisionDrawData *data = p;
	struct DrawCoord coordList[2];
	UWORD indexList[2] = { 0, 1 };

	Maths_Vector3DScale(&coordList[0].position, &projectile->direction, 10.0f);
	Maths_Vector3DSubtract(&coordList[0].position, &projectile->position, &coordList[0].position);
	coordList[0].colour = COLOUR_FROMCHAR(255, 0, 0);

	coordList[1].position = projectile->position;
	coordList[1].colour = COLOUR_FROMCHAR(255, 255, 0);

	Draw_WorldLineList(data->vp, data->camera, coordList, 2, indexList, 2);

	return FALSE;
}

VOID Projectile_DrawMarkers(lpList list, lpViewport vp, lpFrame camera) {

	struct CollisionDrawData data;
	
	data.vp = vp;
	data.camera = camera;

	List_RunThrough(list, Projectile_DrawMarkersCallback, &data);
}
