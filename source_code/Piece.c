/*
* Piece.c
*
*  Created on: Jul 22, 2015
*      Author: bensterenson
*/

#include "Piece.h"
int iPieces = 0;

chessPiece_t* newPiece(chessPieceKind_t kind, color_t color) {

	chessPiece_t *piece = (chessPiece_t *)malloc(sizeof(chessPiece_t));
	checkAllocError(piece, "malloc");

	iPieces++;

	piece->kind = kind;
	piece->coord.row = -1;
	piece->coord.col = -1;
	piece->color = color;
	piece->displayFunc = NULL;
	piece->moveFunc = getMove_Func(kind);
	piece->next = NULL;
	piece->prev = NULL;

	return piece;
}

char pieceToChar(chessPiece_t *pPiece) {
	if (!pPiece)
		return '_';
	if (pPiece->color == BLACK)
		return toupper(kindToChar(pPiece->kind));
	return kindToChar(pPiece->kind);
}

void freePieces(chessPiece_t *pPiece) {
	if (pPiece == NULL)
		return;
	freePieces(pPiece->next);
	free(pPiece);
	iPieces--;
}

//###########################
//			MOVES			#

void getMove_knight(coord_t *coord, coord_t *newCoord, blocked_t *blocked) {
	// accepts coord and address of temp coord

	static int count = 0; // number of moves produced.

	int offsetCol[] = { +1, +1, -1, -1, +2, +2, -2, -2 };
	int offsetRow[] = { +2, -2, +2, -2, +1, -1, +1, -1 };

	while (count < 8) {
		newCoord->col = coord->col + offsetCol[count];
		newCoord->row = coord->row + offsetRow[count];

		count++;
		if (!(newCoord->col < 0 || newCoord->col >= 8 || newCoord->row < 0
			|| newCoord->row >= 8))  // out of board
			return;

	}

	// count == 8 stopping condition
	newCoord->col = newCoord->row = -1;
	count = 0;
}

void getMove_pawn(coord_t *coord, coord_t *newCoord, blocked_t *blocked) {

	int direction = pGame->turn == BLACK ? -1 : +1;
	static int count = 0;

	int offsetCol[] = { +0, -1, +1 };
	int offsetRow[] = { +1, +1, +1 };

	while (count < 3) {
		newCoord->col = coord->col + offsetCol[count] * direction;
		newCoord->row = coord->row + offsetRow[count] * direction;

		count++;

//		if (offsetRow[count - 1] == +2) { // special case for first pawn move
//			if ((row == 1 && pGame->turn == WHITE) || (row == 6 && pGame->turn == BLACK))
//				return;
//		}

		if (!(newCoord->col < 0 || newCoord->col >= 8 || newCoord->row < 0
			|| newCoord->row >= 8))  // out of board
			return;
	}

	newCoord->col = newCoord->row = -1;
	count = 0;
}

void getMove_king(coord_t *coord, coord_t *newCoord, blocked_t *blocked) {
	// accepts coord and address of temp coord

	static int count = 0; // number of moves produced.

	int offsetCol[] = { +0, +1, +1, +1, +0, -1, -1, -1 };
	int offsetRow[] = { +1, +1, +0, -1, -1, -1, +0, +1 };

	while (count < 8) {
		newCoord->col = coord->col + offsetCol[count];
		newCoord->row = coord->row + offsetRow[count];

		count++;
		if (!(newCoord->col < 0 || newCoord->col >= 8 || newCoord->row < 0
			|| newCoord->row >= 8))  // out of board
			return;
	}

	// count == 8 stopping condition
	newCoord->col = newCoord->row = -1;
	count = 0;
}

void getMove_loop(coord_t *coord, direction_t *direction,
	blocked_t *blocked, coord_t *newCoord, int *count, int *offsetCol,
	int *offsetRow) {
	char maxOffset;
	static char offset = 0; // depth of move in one direction

	// set loop limit by the direction
	switch (direction[*count]) {
	case UU:
		maxOffset = BOARD_SIZE - coord->row - 1;
		break;

	case UR:
		maxOffset = MIN(BOARD_SIZE - coord->row - 1,
			BOARD_SIZE - coord->col - 1);
		break;

	case RR:
		maxOffset = BOARD_SIZE - coord->col - 1;
		break;

	case DR:
		maxOffset = MIN(coord->row, BOARD_SIZE - coord->col - 1);
		break;

	case DD:
		maxOffset = coord->row;
		break;

	case DL:
		maxOffset = MIN(coord->row, coord->col);
		break;

	case LL:
		maxOffset = coord->col;
		break;

	case UL:
		maxOffset = MIN(BOARD_SIZE - coord->row - 1, coord->col);
		break;

	default:
		printf("error direction\n");
	}

	// if route is blocked, don't loop through this direction
	if (blocked[direction[*count]] == BLOCKED)
		maxOffset = 0;

	for (int i = offset; i < maxOffset; i++) {
		newCoord->col = coord->col + offsetCol[*count] * (i + 1);
		newCoord->row = coord->row + offsetRow[*count] * (i + 1);

		if (newCoord->col < 0 || newCoord->col >= 8 || newCoord->row < 0
			|| newCoord->row >= 8)  // out of board
			break;

		else {
			offset++;
			return;
		}
	}
	offset = 0;

	// stopping condition
	if (*count + 1 == 4) {
		newCoord->col = newCoord->row = -1;
		*count = 0;
		return;
	}
	(*count)++;
}

void getMove_bishop(coord_t *coord, coord_t *newCoord, blocked_t *blocked) {
	// accepts coord and address of temp coord

	static int count = 0; // number of moves produced.
	coord_t oldCoord;

	int offsetCol[] = { +1, +1, -1, -1 };
	int offsetRow[] = { +1, -1, -1, +1 };
	direction_t direction[] = { UR, DR, DL, UL };

	oldCoord.row = newCoord->row;
	oldCoord.col = newCoord->col;

	while (oldCoord.row == newCoord->row && oldCoord.col == newCoord->col)
	getMove_loop(coord, direction, blocked, newCoord, &count, offsetCol,
		offsetRow);
}

void getMove_rook(coord_t *coord, coord_t *newCoord, blocked_t *blocked) {
	// accepts coord and address of temp coord

	static int count = 0; // number of moves produced.
	coord_t oldCoord;

	int offsetCol[] = { +0, +1, +0, -1 };
	int offsetRow[] = { +1, +0, -1, +0 };
	direction_t direction[] = { UU, RR, DD, LL };

	oldCoord.row = newCoord->row;
	oldCoord.col = newCoord->col;

	while (oldCoord.row == newCoord->row && oldCoord.col == newCoord->col)
		getMove_loop(coord, (direction_t*)direction, (blocked_t*)blocked, newCoord, &count, offsetCol,
		offsetRow);
}

void getMove_queen(coord_t *coord, coord_t *newCoord, blocked_t *blocked) {
	static int finished_bishop = 0;
	static int finished_rook = 0;

	if (!finished_bishop) {

		getMove_bishop(coord, newCoord, blocked);

		if (newCoord->col == -1)
			finished_bishop = 1;

		else
			return;
	}

	if (!finished_rook) {

		getMove_rook(coord, newCoord, blocked);

		if (newCoord->col == -1)
			finished_rook = 1;

		else
			return;
	}

	finished_bishop = finished_rook = 0;
}

moveFunc_t getMove_Func(chessPieceKind_t kind) {

	switch (kind) {
	case PAWN:
		return getMove_pawn;

	case KNIGHT:
		return getMove_knight;

	case ROOK:
		return getMove_rook;

	case BISHOP:
		return getMove_bishop;

	case QUEEN:
		return getMove_queen;

	case KING:
		return getMove_king;

	default:
		printf("error no move func.\n");
		return NULL;
	}
}

//			MOVES			#
//###########################
