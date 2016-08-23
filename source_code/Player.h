/*
 * Player.h
 *
 *  Created on: Jul 22, 2015
 *      Author: bensterenson
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Piece.h"

//###########################
//#		DECLARATIONS		#

extern void removePiece(chessPiece_t*, int);
extern void insertPiece(chessPiece_t*);
extern void freePlayer(chessPlayer_t*);
extern void freePlayers();
extern chessPlayer_t* newPlayer(color_t);
extern chessPlayer_t* getPlayerByColor(color_t);

//#		DECLARATIONS		#
//###########################

#endif /* PLAYER_H */
