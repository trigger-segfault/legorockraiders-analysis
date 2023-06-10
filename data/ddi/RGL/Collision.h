
#ifndef _RGL_COLLISION_H_
#define _RGL_COLLISION_H_

#include "Maths.h"

#define COLLISION_MAXBOXES				10

#define COLLISION_FLAG_DISABLED			0x00000001
#define COLLISION_FLAG_LINEAR			0x00000002			// The collision has linear motion with very little or no rotation

#define COLLISIONBOX_FLAG_DISABLED		0x0001

struct CollisionBox {

	BOX3D box;
	UWORD flags, userFlags;
};

struct Collision {

	LPVOID object;			// User defined object that the collision surrounds.

	struct Frame *frame;
	VECTOR3D lastPos;
	REAL worldRadius, boxRadius;
	struct CollisionBox boxList[COLLISION_MAXBOXES];	// Will change...
	ULONG boxCount;

	REAL delta;				// Delta value for when within the update the collision happened.
	VECTOR3D localHit;		// Collision point in the frame's coordinate system.
	VECTOR3D worldHit;		// World collision point (adjusted accoring to the time of impact).
	ULONG hitBox;			// Which box was collided with.
	enum BoxesSide side;

	ULONG flags;
};

struct CollisionList {

	// Keep the array of boxes here and a index into this list in each Collision object.
	// Collision_AddBox() will have to check that boxes are contiguous, maybe have Collision_SetBoxes(),
	// which may only be called once...

	struct List *list;
};

struct CollisionDrawData {

	struct Viewport *vp;
	struct Frame *camera;
	COLOUR colour;

};

typedef struct Collision			*lpCollision;
typedef struct CollisionBox			*lpCollisionBox;
typedef struct CollisionList		*lpCollisionList;
typedef struct CollisionDrawData	*lpCollisionDrawData;

#ifndef _AUTOPROTOTYPES
// Auto Prototypes
extern struct CollisionList *__cdecl Collision_CreateList(VOID);
extern struct Collision *__cdecl Collision_Create(struct CollisionList *collisionListType, struct Frame *frame, void *object, int linearMotion);
extern struct Frame *__cdecl Collision_GetFrame(struct Collision *collision);
extern unsigned long __cdecl Collision_AddBox(struct Collision *collision, LPBOX3D box);
extern BOOL __cdecl Collision_CheckPointCallback(lpCollision collision, LPVECTOR3D worldPos); 
extern struct Collision *__cdecl Collision_CheckPoint(struct CollisionList *collisionList, LPVECTOR3D point);
extern struct Collision *__cdecl Collision_CheckLine(struct CollisionList *collisionList, LPLINE3D point, BOOL first);
extern VOID __cdecl Collision_Draw(struct CollisionList *collisionList, struct Viewport *vp, struct Frame *camera);
extern VOID __cdecl Collision_EndUpdate(struct CollisionList *collisionList);
extern VOID __cdecl Collision_DisableBox(struct Collision *collision, ULONG box, BOOL disable);
extern VOID __cdecl Collision_SetBoxUserFlags(lpCollision collision, ULONG box, UWORD flags, BOOL set);
extern BOOL __cdecl Collision_TestBoxUserFlags(lpCollision collision, ULONG box, UWORD flags, BOOL all);
extern VOID __cdecl Collision_SetFlags(struct Collision *collision, ULONG flags, BOOL set);
extern BOOL __cdecl Collision_TestFlags(struct Collision *collision, ULONG flags, BOOL all);
extern VOID __cdecl Collision_RemoveList(struct CollisionList *collisionList);
extern VOID __cdecl Collision_Remove(struct CollisionList *list, struct Collision *collision);
extern VOID __cdecl Collision_SetWorldRadius(struct Collision *collision, REAL radius);
extern LPVOID __cdecl Collision_GetObject(struct Collision *collision);
extern VOID __cdecl Collision_Initialise(VOID);
extern VOID __cdecl Collision_Shutdown(VOID);
// Auto Prototypes
#endif // !_AUTOPROTOTYPES

#endif // !_RGL_COLLISION_H_
