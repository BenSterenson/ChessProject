/*
 * Piece.h
 *
 *  Created on: Jul 22, 2015
 *      Author: bensterenson
 */

#ifndef PIECE_H
#define PIECE_H

#include "General.h"

//###########################
//#		DECLARATIONS		#

extern char pieceToChar(chessPiece_t*);
extern chessPiece_t* newPiece(chessPieceKind_t, color_t);
extern void freePieces(chessPiece_t*);

extern moveFunc_t getMove_Func(chessPieceKind_t kind);
extern void getMove_loop(coord_t*, direction_t*, blocked_t*, coord_t*, int*, int*, int*);

extern void getMove_bishop(coord_t*, coord_t*, blocked_t*);
extern void getMove_king(coord_t*, coord_t*, blocked_t*);
extern void getMove_knight(coord_t*, coord_t*, blocked_t*);
extern void getMove_pawn(coord_t*, coord_t*, blocked_t*);
extern void getMove_queen(coord_t*, coord_t*, blocked_t*);
extern void getMove_rook(coord_t*, coord_t*, blocked_t*);
extern int iPieces;
//#		DECLARATIONS		#
//###########################

#endif /* PIECE_H */
