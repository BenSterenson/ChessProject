/*
 * Board.h
 *
 *  Created on: Jul 22, 2015
 *      Author: bensterenson
 */

#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"

//###########################
//#		DECLARATIONS		#

extern void newBoard();
extern void saveBoard(char (*matrix)[BOARD_SIZE][BOARD_SIZE]);
extern void placePiece(chessPiece_t*, int, int);
extern void placePiece_c(chessPiece_t*, coord_t*);
extern void printBoard();
extern void printPiece();

//#		DECLARATIONS		#
//###########################

#endif /* BOARD_H */
