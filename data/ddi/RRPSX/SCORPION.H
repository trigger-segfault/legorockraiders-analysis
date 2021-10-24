//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// scorpion header file For <LEGO Rock Raiders>
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#ifndef	__SCORPION_H

#define		SCORPION_REACQUIRE_TARGET_TIME			(10)		/* game cycles, not speed adjusted, so it will do less if the game slows down */
#define		SCORPION_TARGET_RANGE						(500000)	/* squared delta for target range */ 
#define		SCORPION_COLLISION_RANGE					(18300)	/* squared delta for collision range */ 
#define		SCORPION_CLIPPED_TIMEOUT					(30)		/* game cycles before a clipped scorpion is 'removed' */
#define		SCORPION_MAX_SPEED							(ToFIXED(15.0))
#define		SCORPION_SPEED_DELTA							(ToFIXED(0.5))
#define		SCORPION_BITE_TIME							(30)
#define		SCORPION_PLAYER_DAMAGE						(50)
#define		SCORPION_BACKOFF_SPEED						(ToFIXED(-15.0))
#define		SCORPION_WANDER_TIME							(30)
#define		SCORPION_BACKOFF_TIME						(15)
#define		SCORPION_TURN_DELTA							(128)


void		Creature_InitialiseScorpion(lpCREATURE scorpion);
void		Creature_ServiceScorpion(lpCREATURE scorpion, int time);



#define	__SCORPION_H

#endif


