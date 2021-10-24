//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// creature header file For <LEGO Rock Raiders>
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#ifndef	__CREATURE_H



enum
{
	CREATURE_PROCESS_IF_CLIPPED				=	1,			/* default is don't process if clipped				*/
	CREATURE_KILL_IF_CLIPPED					=	2,			/* default is stay alive if clipped					*/
	CREATURE_,

};


/* structures */






/* prototypes */

BOOL				Creature_CreateCreature(lpTRIGGER_ENTITY entity);
BOOL				Creature_InitialiseLists(void);
void				Creature_ServiceCreatureList(int time);
void				Creature_DamagePlayer(lpMINIFIGURE minifigure, int damage);
void				Creature_KillCreature(lpOBJECT	creatureObject);
lpOBJECT		Creature_GetCraftTarget(lpOBJECT creatureObject, int range, int *deltaX, int *deltaY);
lpOBJECT		Creature_GetMinifigureTarget(lpOBJECT creatureObject, int range, int *deltaX, int *deltaY);


#define	__CREATURE_H

#endif
