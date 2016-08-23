/*
 * GetMoves.h
 *
 *  Created on: Aug 22, 2015
 *      Author: bensterenson
 */

#ifndef GETMOVES_H_
#define GETMOVES_H_

#include "Game.h"

typedef struct tagMove_t {
	coord_t srcCoord;
	coord_t dstCoord;
	int score;
	int promotion;

	struct tagMove_t *next;
} move_t;

extern void undoMove(move_t *, chessPiece_t *, chessPiece_t *);
extern void simulateMove(move_t *, chessPiece_t **,chessPiece_t **);

extern move_t* newMove(int, int, int, int);
extern move_t* newMove_c(coord_t, coord_t);
extern move_t* addMove(move_t*, move_t*);

extern int isValidPawnMove(chessPiece_t *pPiece, coord_t);
extern move_t* getAllMoves();
extern direction_t extractDirection(coord_t, coord_t);
extern move_t* getPieceMoves(move_t*, chessPiece_t*);
extern void printAllMoves(move_t *);
//extern void freeMoves(move_t*);
extern void freeMoves(move_t**);

extern int isThreatened(coord_t);
extern int isThreatenedRow(int, int, int);

extern int isEmptyBetween(int, int, int);
extern castling_t isValidCastlingMove();

extern int isThreatenedHorizontal(coord_t, direction_t);
extern int isThreatenedDiagonal(coord_t, direction_t);
extern int isThreatenedByKing(coord_t);
extern int isThreatenedHorVer(coord_t);
extern int isThreatenedByKnight(coord_t);
extern void undoCastleMove(chessPiece_t*);

extern move_t* Merge(move_t*, move_t*);
extern void MergeSort(move_t **);
extern int scoreMove(move_t*);
extern int iMoves;

#endif /* GETMOVES_H_ */
