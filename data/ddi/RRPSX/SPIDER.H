//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// spider header file For <LEGO Rock Raiders>
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#ifndef	__SPIDER_H


#define		SPIDER_REACQUIRE_TARGET_TIME			(10)		/* game cycles, not speed adjusted, so it will do less if the game slows down */
#define		SPIDER_TARGET_RANGE						(500000)	/* squared delta for target range */ 
#define		SPIDER_COLLISION_RANGE					(18300)	/* squared delta for collision range */ 
#define		SPIDER_CLIPPED_TIMEOUT					(30)		/* game cycles before a clipped scorpion is 'removed' */
#define		SPIDER_MAX_SPEED							(ToFIXED(10.0))
#define		SPIDER_SPEED_DELTA						(ToFIXED(0.3))
#define		SPIDER_BITE_TIME							(30)
#define		SPIDER_PLAYER_DAMAGE						(50)
#define		SPIDER_BACKOFF_SPEED						(ToFIXED(-8.0))
#define		SPIDER_WANDER_TIME						(30)
#define		SPIDER_BACKOFF_TIME						(15)
#define		SPIDER_TURN_DELTA							(64)


void		Creature_InitialiseSpider(lpCREATURE spider);
void		Creature_ServiceSpider(lpCREATURE spider, int time);



#define	__SPIDER_H

#endif
