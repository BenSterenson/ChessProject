/*
 * Game.h
 *
 *  Created on: Jul 23, 2015
 *      Author: bensterenson
 */

#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"

//###########################
//#		DECLARATIONS		#

extern void initGame(char (*board)[BOARD_SIZE][BOARD_SIZE]);
extern void newGame();
extern void clearBoard();
extern void movePiece(coord_t, coord_t,int);
extern void rmPiece(int,int,int);
extern void rmPiece_c(coord_t,int);
extern void setPiece(char, int, int);
extern void setPiece_c(char, coord_t*);
extern void castleMove(chessPiece_t *);
extern void promotion(chessPieceKind_t ,coord_t);
extern void updateCastling();
extern char extractPieceChar(chessPieceKind_t , color_t );
//#		DECLARATIONS		#
//###########################

#endif /* GAME_H */
