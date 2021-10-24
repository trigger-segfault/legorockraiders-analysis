//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// snake header file For <LEGO Rock Raiders>
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#ifndef	__SNAKE_H

#define		SNAKE_REACQUIRE_TARGET_TIME			(10)					/* game cycles, not speed adjusted, so it will do less if the game slows down */
#define		SNAKE_TARGET_RANGE						(500000)				/* squared delta for target range */ 
#define		SNAKE_COLLISION_RANGE					(18300)				/* squared delta for collision range */ 
#define		SNAKE_CLIPPED_TIMEOUT					(30)					/* game cycles before a clipped scorpion is 'removed' */
#define		SNAKE_MAX_SPEED							(ToFIXED(10.0))
#define		SNAKE_SPEED_DELTA							(ToFIXED(0.3))
#define		SNAKE_BITE_TIME							(30)
#define		SNAKE_PLAYER_DAMAGE						(50)
#define		SNAKE_BACKOFF_SPEED						(ToFIXED(-8.0))
#define		SNAKE_WANDER_TIME							(30)
#define		SNAKE_BACKOFF_TIME						(15)
#define		SNAKE_TURN_DELTA							(64)


void		Creature_InitialiseSnake(lpCREATURE snake);
void		Creature_ServiceSnake(lpCREATURE snake, int time);


#define	__SNAKE_H

#endif
