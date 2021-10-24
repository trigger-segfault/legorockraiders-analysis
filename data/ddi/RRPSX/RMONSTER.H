//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// rockmonster header file For <LEGO Rock Raiders>
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#ifndef	__ROCKMONSTER_H

#define		ROCKMONSTER_REACQUIRE_TARGET_TIME			(10)		/* game cycles, not speed adjusted, so it will do less if the game slows down */
#define		ROCKMONSTER_TARGET_RANGE						(500000)	/* squared delta for target range */ 
#define		ROCKMONSTER_COLLISION_RANGE					(18300)	/* squared delta for collision range */ 
#define		ROCKMONSTER_CLIPPED_TIMEOUT					(30)		/* game cycles before a clipped scorpion is 'removed' */
#define		ROCKMONSTER_MAX_SPEED							(ToFIXED(10.0))
#define		ROCKMONSTER_SPEED_DELTA							(ToFIXED(0.3))
#define		ROCKMONSTER_BITE_TIME							(30)
#define		ROCKMONSTER_PLAYER_DAMAGE						(50)
#define		ROCKMONSTER_BACKOFF_SPEED						(ToFIXED(-5.0))
#define		ROCKMONSTER_WANDER_TIME							(30)
#define		ROCKMONSTER_BACKOFF_TIME						(15)
#define		ROCKMONSTER_TURN_DELTA							(64)





void		Creature_InitialiseRockMonster(lpCREATURE rockMonster);
void		Creature_ServiceRockMonster(lpCREATURE rockMonster, int time);

#define	__ROCKMONSTER_H

#endif
