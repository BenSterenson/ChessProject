/*
 * miniMax.h
 *
 *  Created on: Aug 31, 2015
 *      Author: bensterenson
 */

#ifndef MINIMAX_H_
#define MINIMAX_H_

#include "General.h"
#include "GetMoves.h"

#define WIN 1000
#define TIE_SCORE -500
#define LOOSE -1000
#define MAX_BOARDS 50000000

extern int getScorePiece(chessPieceKind_t );
extern int checkmate(move_t*);

extern move_t* getBestMoves(int);
extern void scoreMove_depth(move_t *,int);
extern int alphaBetaMax(int alpha, int beta, int depth_left);
extern int alphaBetaMin(int alpha, int beta, int depth_left);
extern int alphaBeta(int alpha, int beta, int depth_left,int);
extern void sortLinkedList(move_t **);

extern void Partition(move_t* source, move_t** , move_t** );

extern move_t* Merge(move_t* , move_t* );
extern void MergeSort(move_t **);
extern int scoreMove(move_t*);
extern void scoreMove_depth(move_t *,int);

#endif /* MINIMAX_H_ */
