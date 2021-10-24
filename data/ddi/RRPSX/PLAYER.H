//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// player File For <LEGO Rock Raiders>
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#ifndef	__PLAYER_H



void	Player_CreatePlayer(int playerId, int minifigureIndex);
BOOL	Player_CreateMinifigure(int x, int y, int rotation, int minifigureIndex);
BOOL	Player_SetMinifigureToCraftPosition(lpPLAYER player, int angle, BOOL flag);
void	Player_UpdateMinifigure(lpOBJECT object,lpPLAYER player, int time);
BOOL	PlayerCheckCollisionAtPoint(int x, int y);


#define	__PLAYER_H

#endif
