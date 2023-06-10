
#ifndef _RGL_PROJECTILES_H
#define _RGL_PROJECTILES_H

#include "Maths.h"

#define PROJECTILE_FLAG_POINTCHECK		0x00000001
#define PROJECTILE_FLAG_LEVELFLIGHT		0x00000002
#define PROJECTILE_FLAG_USERMASK		0x0000ffff

#define PROJECTILE_FLAG_TIMEOUT			0x80000000
#define PROJECTILE_FLAG_DISTOUT			0x40000000
#define PROJECTILE_FLAG_MAXVELOCITY		0x20000000
#define PROJECTILE_FLAG_MAXGRAVITY		0x10000000
#define PROJECTILE_FLAG_REMOVEFRAME		0x08000000

#ifdef _RGL

struct ProjectileData {

	REAL acceleration;
	REAL velocityCutOff;			// If this velocity is passed or reached then ignore the acceleration.
	REAL gravityAcceleration;
	REAL gravityCutOff;
};

struct Projectile {

	struct Frame *frame;
	struct ProjectileData *data;
	VECTOR3D position;
	VECTOR3D direction;
	REAL velocity, gravityVelocity;
	REAL remaining;					// Time or distance...

	LPVOID userData;

	ULONG flags;
};

#endif // _RGL

typedef struct Projectile		*lpProjectile;
typedef struct ProjectileData	*lpProjectileData;

extern VOID __cdecl Projectile_Initialise(VOID);
extern lpProjectileData __cdecl Projectile_CreateData(VOID);
extern VOID __cdecl Projectile_RemoveData(struct ProjectileData *data);
extern struct List * __cdecl Projectile_CreateList(VOID);
extern lpProjectile __cdecl Projectile_Create(struct List *list, struct ProjectileData *data, struct Frame **moveFrame, LPVECTOR3D position, LPVECTOR3D direction, LPVECTOR3D up, REAL velocity, struct Frame *referenceFrame, ULONG flags);
extern BOOL __cdecl Projectile_Update(lpProjectile projectile, LPVOID p);
extern VOID __cdecl Projectile_GetPosition(lpProjectile projectile, LPVECTOR3D position);
extern VOID __cdecl Projectile_SetUserData(lpProjectile projectile, LPVOID data);
extern LPVOID __cdecl Projectile_GetUserData(lpProjectile projectile);
extern VOID __cdecl Projectile_Remove(struct List * list, lpProjectile projectile);
extern VOID __cdecl Projectile_UpdateList(struct List * list, struct CollisionList * collisionList, REAL delta, BOOL (*hitCallback)(lpProjectile projectile, struct Collision * collision, LPVOID hitCallbackData), LPVOID hitCallbackData, VOID (*updateCallback)(lpProjectile projectile, BOOL remove, LPVOID updateCallbackData), LPVOID updateCallbackData);
extern VOID __cdecl Projectile_DrawMarkers(struct List * list, struct Viewport * vp, struct Frame * camera);
extern VOID __cdecl Projectile_SetTimeRemaining(lpProjectile projectile, REAL time);
extern VOID __cdecl Projectile_SetAcceleration(lpProjectileData projectileData, REAL acceleration, REAL velocityCutOff);
extern VOID __cdecl Projectile_SetGravity(lpProjectileData projectileData, REAL gravityAcceleration, REAL gravityVelocityCutOff);

#endif // !_RGL_PROJECTILES_H
