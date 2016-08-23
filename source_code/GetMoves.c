///*
// * GetMoves.c
// *
// *  Created on: Aug 22, 2015
// *      Author: bensterenson
// */

#include "GetMoves.h"

void simulateMove(move_t *curMove, chessPiece_t **srcPiece,
	chessPiece_t **dstPiece) {
	int row = curMove->dstCoord.row;
	*srcPiece = (*pBoard)[curMove->srcCoord.row][curMove->srcCoord.col];
	*dstPiece = (*pBoard)[curMove->dstCoord.row][curMove->dstCoord.col];

	if (curMove->srcCoord.row == curMove->dstCoord.row && curMove->srcCoord.col == curMove->dstCoord.col) {
		castleMove(*srcPiece);
	}
	else {
		if ((pieceToChar(*srcPiece) == 'm' && row == 7)
			|| (pieceToChar(*srcPiece) == 'M' && row == 0))
			(*srcPiece)->kind = curMove->promotion;

		// disabling the option of overriding a piece with same color
		if (*dstPiece == NULL || (*dstPiece)->color != (*srcPiece)->color)
			movePiece(curMove->srcCoord, curMove->dstCoord, FALSE);
	}
	pGame->turn ^= 1;
}


void undoMove(move_t *pMove, chessPiece_t *srcPiece, chessPiece_t *dstPiece) {
	// castling
	if (pMove->srcCoord.row == pMove->dstCoord.row && pMove->srcCoord.col == pMove->dstCoord.col) {
		undoCastleMove(dstPiece);
	}
	else {
		if (dstPiece == NULL || dstPiece->color != srcPiece->color) {
			movePiece(pMove->dstCoord, pMove->srcCoord, FALSE);
			(*pBoard)[pMove->dstCoord.row][pMove->dstCoord.col] = dstPiece;
			insertPiece(dstPiece);

			if (pMove->promotion != -1)
				srcPiece->kind = PAWN;
		}
	}
	pGame->turn ^= 1;
}

move_t *getPieceMoves(move_t* pMove, chessPiece_t* pPiece) {
	coord_t dstCoord, srcCoord;
	chessPiece_t *srcPiece, *dstPiece;
	moveFunc_t func = pPiece->moveFunc;
	blocked_t blocked[8];
	chessPiece_t *pKing;
	pKing = getPlayerByColor(pPiece->color)->pKing;

	memset(blocked, FREE, sizeof(blocked_t) * 8);

	do {
		func(&(pPiece->coord), &dstCoord, (blocked_t*)blocked);
		if (dstCoord.row == -1) {
			dstPiece = NULL;
			break;
		}

		srcCoord = pPiece->coord;
		move_t curMove = { srcCoord, dstCoord, 0, -1 };

		// special PAWN case:
		if (pPiece->kind == PAWN) {
			if (!isValidPawnMove(pPiece, dstCoord))
				continue;
			else
				curMove.promotion = PAWN;
		}

		simulateMove(&curMove, &srcPiece, &dstPiece);
		pGame->turn ^= 1;
		if (isThreatened(pKing->coord) == TRUE) {
			// restore
			undoMove(&curMove, srcPiece, dstPiece);
			pGame->turn ^= 1;

			if (dstPiece != NULL)
				blocked[extractDirection(srcCoord, dstCoord)] = BLOCKED;

			continue;
		}

		// restore
		undoMove(&curMove, srcPiece, dstPiece);
		pGame->turn ^= 1;

		// add move - cell is free or occupied by enemy.
		if (dstPiece == NULL || dstPiece->color != pPiece->color)
			pMove = addMove(pMove, newMove_c(srcCoord, dstCoord));

		// block future moves - cell is occupied
		if (dstPiece != NULL)
			blocked[extractDirection(pPiece->coord, dstCoord)] = BLOCKED;

	} while (dstCoord.row != -1);
	return pMove;
}

direction_t extractDirection(coord_t oldCoord, coord_t newCoord) {
	int offsetY = newCoord.row - oldCoord.row;
	int offsetX = newCoord.col - oldCoord.col;
	offsetX = offsetX > 0 ? +1 : offsetX < 0 ? -1 : 0;
	offsetY = offsetY > 0 ? +1 : offsetY < 0 ? -1 : 0;

	switch (offsetX) {
	case 0:
		switch (offsetY) {
		case 1:
			return UU;

		case -1:
			return DD;
		}
		break;

	case 1:
		switch (offsetY) {
		case 0:
			return RR;
		case 1:
			return UR;
		case -1:
			return DR;
		}
		break;

	case -1:
		switch (offsetY) {
		case 0:
			return LL;
		case 1:
			return UL;
		case -1:
			return DL;
		}
		break;

	default:
		printf("direction error\n");
	}
	return -1;
}

move_t* getAllMoves() {
	chessPlayer_t *pPlayer = getPlayerByColor(pGame->turn);
	move_t *pMoves = NULL;

	// castling
	castling_t castling = isValidCastlingMove(pPlayer->color);
	int row = pPlayer->color == BLACK ? BOARD_SIZE - 1 : 0;
	coord_t tmp_coord = { row, -1 };

	if (castling == CASTLE_KING_SIDE || castling == BOTH_SIDES) {
		tmp_coord.col = BOARD_SIZE - 1;
		pMoves = addMove(pMoves, newMove_c(tmp_coord, tmp_coord));
	}
	if (castling == CASTLE_QUEEN_SIDE || castling == BOTH_SIDES) {
		tmp_coord.col = 0;
		pMoves = addMove(pMoves, newMove_c(tmp_coord, tmp_coord));
	}

	for (chessPiece_t *pPiece = pPlayer->pHead; pPiece != NULL;
		pPiece = pPiece->next)
		pMoves = getPieceMoves(pMoves, pPiece);

	return pMoves;
}

int iMoves = 0;

move_t* newMove_c(coord_t srcCoord, coord_t dstCoord) {
	move_t *pMove = (move_t*)malloc(sizeof(move_t));
	checkAllocError(pMove, "malloc");


	iMoves++;

	pMove->next = NULL;
	pMove->srcCoord = srcCoord;
	pMove->dstCoord = dstCoord;
	pMove->promotion = -1;
	pMove->score = 0;
	return pMove;
}

move_t* newMove(int srcRow, int srcCol, int dstRow, int dstCol) {
	coord_t srcCoord = { srcRow, srcCol };
	coord_t dstCoord = { dstRow, dstCol };

	return newMove_c(srcCoord, dstCoord);
}

move_t* addMove(move_t *move_list, move_t *new_move) {

	move_t* curList = move_list;
	move_t* tmpMove;

	if ((*pBoard)[new_move->srcCoord.row][new_move->srcCoord.col]->kind
		== PAWN) {
		if ((new_move->dstCoord.row == 0 && pGame->turn == BLACK)
			|| (new_move->dstCoord.row == 7 && pGame->turn == WHITE)) {

			// KNIGHT, BISHOP, ROOK
			for (int i = 1; i <= 4; i++) {
				tmpMove = newMove_c(new_move->srcCoord, new_move->dstCoord);

				tmpMove->promotion = i;
				tmpMove->score = scoreMove(tmpMove);
				tmpMove->next = curList;
				curList = tmpMove;
			}
			free(new_move); iMoves--;
			return curList;
		}
	}
	new_move->next = move_list;
	return new_move;
}

int isValidPawnMove(chessPiece_t *pPiece, coord_t coord) {

	chessPiece_t *dstPiece = (*pBoard)[coord.row][coord.col];
	color_t color = pPiece->color;

	direction_t direction = extractDirection(pPiece->coord, coord);

	// UR UL DR DL
	if (direction % 2 == 1) {
		if (dstPiece == NULL || dstPiece->color == color)
			return FALSE;

		return TRUE;
	}

	// UU DD
	if (dstPiece == NULL)
		return TRUE;

	return FALSE;
}

int isThreatenedByPawn(coord_t coord) {
	color_t color = pGame->turn;
	chessPiece_t *left, *right;

	int offsetRow = color == WHITE ? +1 : -1;
	if (coord.row + offsetRow < 0 || coord.row + offsetRow > BOARD_SIZE - 1)
		return FALSE;

	// left
	if (coord.col - 1 < 0)
		left = NULL;
	else
		left = (*pBoard)[coord.row + offsetRow][coord.col - 1];

	// right
	if (coord.col + 1 > BOARD_SIZE - 1)
		right = NULL;
	else
		right = (*pBoard)[coord.row + offsetRow][coord.col + 1];

	if (left != NULL && left->kind == PAWN && left->color == otherColor(color))
		return TRUE;

	if (right != NULL
		&& right->kind == PAWN&& right->color == otherColor(color))
		return TRUE;

	return FALSE;

}

int isThreatenedByKing(coord_t coord) {
	chessPiece_t *pPiece;
	int fromRow, toRow, fromCol, toCol;
	// set boundaries - if row/col out of range

	fromRow = coord.row == 0 ? 0 : coord.row - 1;
	toRow = coord.row == 7 ? BOARD_SIZE - 1 : coord.row + 1;

	fromCol = coord.col == 0 ? 0 : coord.col - 1;
	toCol = coord.col == 7 ? BOARD_SIZE - 1 : coord.col + 1;

	for (int rowIndex = fromRow; rowIndex <= toRow; rowIndex++) {
		for (int colIndex = fromCol; colIndex <= toCol; colIndex++) {
			pPiece = (*pBoard)[rowIndex][colIndex];
			if (pPiece == NULL || pPiece->color == pGame->turn)
				continue;

			if (pPiece->kind == KING && pPiece->color != pGame->turn)
				return TRUE;
		}
	}
	return FALSE;
}

int isThreatenedByKnight(coord_t coord) {
	coord_t newCoord;
	chessPiece_t *pPiece;

	int offsetRow[] = { +2, -2, +2, -2, +1, -1, +1, -1 };
	int offsetCol[] = { +1, +1, -1, -1, +2, +2, -2, -2 };

	for (int stepIndex = 0; stepIndex < 8; stepIndex++) {
		newCoord.row = coord.row + offsetRow[stepIndex];
		newCoord.col = coord.col + offsetCol[stepIndex];

		if (newCoord.col < 0 || newCoord.col >= 8 || newCoord.row < 0
			|| newCoord.row >= 8)  // out of board
			continue;

		pPiece = (*pBoard)[newCoord.row][newCoord.col];

		if (pPiece != NULL && pPiece->kind == KNIGHT
			&& pPiece->color != pGame->turn)
			return TRUE;
	}
	return FALSE;
}

int checkPiece(chessPiece_t * pPiece, direction_t dir) {
	if (dir == UU || dir == DD || dir == RR || dir == LL) {
		if ((pPiece->color != pGame->turn && pPiece->kind == QUEEN)
			|| (pPiece->color != pGame->turn && pPiece->kind == ROOK))
			return TRUE;
	}
	else {
		if ((pPiece->color != pGame->turn && pPiece->kind == QUEEN)
			|| (pPiece->color != pGame->turn && pPiece->kind == BISHOP))
			return TRUE;
	}
	return FALSE;
}

int isThreatenedHorizontal(coord_t coord, direction_t horizontalDir) {
	chessPiece_t *pPiece;
	int row = coord.row;
	int col = coord.col;
	int iterNumber, newRow = row, newCol = col;

	// UP / DOWN
	if (horizontalDir == UU || horizontalDir == DD)
		iterNumber = horizontalDir == UU ? BOARD_SIZE - 1 - row : row;
	// LEFT / RIGHT
	else
		iterNumber = horizontalDir == LL ? BOARD_SIZE - 1 - col : col;

	for (int toAdd = 1; toAdd <= iterNumber; toAdd++) {
		// UP / DOWN
		if (horizontalDir == UU || horizontalDir == DD)
			newRow = horizontalDir == UU ? row + toAdd : row - toAdd;

		// LEFT / RIGHT
		else
			newCol = horizontalDir == LL ? col + toAdd : col - toAdd;

		//printf("%d,%d\n", newRow, newCol);
		pPiece = (*pBoard)[newRow][newCol];
		// check if no piece found
		if (pPiece == NULL)
			continue;

		return checkPiece(pPiece, horizontalDir);
	}
	return FALSE;
}

int isThreatenedDiagonal(coord_t coord, direction_t diagonalDir) {
	chessPiece_t *pPiece;
	int row = coord.row;
	int col = coord.col;
	int iterNumber, newRow = row, newCol = col;

	if (diagonalDir == UR || diagonalDir == DL)
		iterNumber =
		diagonalDir == UR ?
		MIN(BOARD_SIZE - 1 - row, BOARD_SIZE - 1 - col) :
		MIN(row, col);
	else
		iterNumber = diagonalDir == UL ? MIN(BOARD_SIZE - 1 - row, col) :
		MIN(row, BOARD_SIZE - 1 - col);

	for (int toAdd = 1; toAdd <= iterNumber; toAdd++) {

		if (diagonalDir == UR || diagonalDir == DL) {
			newRow = diagonalDir == UR ? row + toAdd : row - toAdd;
			newCol = diagonalDir == UR ? col + toAdd : col - toAdd;
		}
		else {
			newRow = diagonalDir == UL ? row + toAdd : row - toAdd;
			newCol = diagonalDir == UL ? col - toAdd : col + toAdd;
		}
		//printf("%d,%d\n", newRow, newCol);
		pPiece = (*pBoard)[newRow][newCol];
		// check if no piece found
		if (pPiece == NULL)
			continue;

		return checkPiece(pPiece, diagonalDir);
	}
	return FALSE;
}

int isThreatenedHorVer(coord_t coord) {
	if (isThreatenedHorizontal(coord, UU) == TRUE)
		return TRUE;
	if (isThreatenedHorizontal(coord, DD) == TRUE)
		return TRUE;
	if (isThreatenedHorizontal(coord, LL) == TRUE)
		return TRUE;
	if (isThreatenedHorizontal(coord, RR) == TRUE)
		return TRUE;

	return FALSE;
}

int isThreatenedAllDia(coord_t coord) {
	if (isThreatenedDiagonal(coord, UR) == TRUE)
		return TRUE;
	if (isThreatenedDiagonal(coord, DL) == TRUE)
		return TRUE;
	if (isThreatenedDiagonal(coord, UL) == TRUE)
		return TRUE;
	if (isThreatenedDiagonal(coord, DR) == TRUE)
		return TRUE;

	return FALSE;
}
int isThreatened(coord_t coord) {
	if (isThreatenedByPawn(coord) == TRUE)
		return TRUE;
	if (isThreatenedByKnight(coord) == TRUE)
		return TRUE;
	if (isThreatenedByKing(coord) == TRUE)
		return TRUE;
	if (isThreatenedHorVer(coord) == TRUE)
		return TRUE;
	if (isThreatenedAllDia(coord) == TRUE)
		return TRUE;

	// if knight

	return FALSE;
}

int isThreatenedRow(int row, int from, int to) {
	// recives row and col range. checks if oppnent threats one of the squares
	coord_t coord;
	for (int col = from; col <= to; col++) {
		coord.row = row;
		coord.col = col;
		if (isThreatened(coord) == TRUE)
			return TRUE;
	}
	return FALSE;

}

int isEmptyBetween(int row, int from, int to) {
	// doesnt include start and end cols
	for (int i = (from + 1); i < to; i++) {
		if ((*pBoard)[row][i] != NULL)
			return FALSE;
	}
	return TRUE;
}

castling_t isValidCastlingMove() {

	castling_t *hasMoved = &(*(getPlayerByColor(pGame->turn)->castling));
	int row = pGame->turn == WHITE ? 0 : BOARD_SIZE - 1;
	int colRQ = 0, colK = 4, colRK = BOARD_SIZE - 1;

	bool_t king_in_place = pGame->turn == WHITE ? pieceToChar((*pBoard)[row][colK]) == 'k' : pieceToChar((*pBoard)[row][colK]) == 'K';
	bool_t kRook_in_place = pGame->turn == WHITE ? pieceToChar((*pBoard)[row][colRK]) == 'r' : pieceToChar((*pBoard)[row][colRK]) == 'R';
	bool_t qRook_in_place = pGame->turn == WHITE ? pieceToChar((*pBoard)[row][colRQ]) == 'r' : pieceToChar((*pBoard)[row][colRQ]) == 'R';

	// king or both rooks have moved
	if (!king_in_place || (!kRook_in_place && !qRook_in_place) //
		|| hasMoved[KING_M] || (hasMoved[ROOK_L] && hasMoved[ROOK_R]))
		return CANT_CASTLE;

	// BOTH SIDES: not threatened, free, and king and rooks haven't moved
	if (king_in_place && kRook_in_place && qRook_in_place //
		&& !hasMoved[KING_M] && !hasMoved[ROOK_L] && !hasMoved[ROOK_R] //
		&& !isThreatenedRow(row, colK - 2, colK + 2) //
		&& isEmptyBetween(row, colK, colRK) //
		&& isEmptyBetween(row, colRQ, colK)) //
		return BOTH_SIDES;

	// KING SIDE: not threatened, free (cols 4 to 7), and king and Queen-Side-Rook haven't moved
	if (king_in_place && kRook_in_place //
		&& !hasMoved[KING_M] && !hasMoved[ROOK_R] //
		&& isEmptyBetween(row, colK, colRK) //
		&& !isThreatenedRow(row, colK, colK + 2))
		return CASTLE_KING_SIDE;

	// QUEEN SIDE: not threatened, free (cols 0 to 4), and king and King-Side-Rook haven't moved
	if (king_in_place && qRook_in_place //
		&& !hasMoved[KING_M] && !hasMoved[ROOK_L] //
		&& isEmptyBetween(row, colRQ, colK) //
		&& !isThreatenedRow(row, colK - 2, colK))
		return CASTLE_QUEEN_SIDE;

	// wasn't moved but is either threatened or blocked on both sides.
	return CANT_CASTLE;
}

void printAllMoves(move_t *pMove) {
	for (move_t* curMove = pMove; curMove != NULL; curMove = curMove->next) {
		// castling
		if (curMove->dstCoord.row == curMove->srcCoord.row && curMove->dstCoord.col == curMove->srcCoord.col) {
			printf("castle <%c,%d>\n", curMove->srcCoord.col + 'a',
				curMove->srcCoord.row + 1);
		}
		else {
			printf("<%c,%d> to <%c,%d>", curMove->srcCoord.col + 'a',
				curMove->srcCoord.row + 1, curMove->dstCoord.col + 'a',
				curMove->dstCoord.row + 1);
			printf("%s\n",
				curMove->promotion == -1 ?
				"\0" : kindToString(curMove->promotion));
		}
	}
}

void printAllMovesWithScore(move_t *pMove) {
	MergeSort(&pMove);
	for (move_t* curMove = pMove; curMove != NULL; curMove = curMove->next) {
		// castling
		if (curMove->dstCoord.row == curMove->srcCoord.row && curMove->dstCoord.col == curMove->srcCoord.col) {
			printf("castle <%c,%d> score: %d\n", curMove->srcCoord.col + 'a',
				curMove->srcCoord.row + 1, curMove->score);
		}
		else {
			printf("<%c,%d> to <%c,%d>", curMove->srcCoord.col + 'a',
				curMove->srcCoord.row + 1, curMove->dstCoord.col + 'a',
				curMove->dstCoord.row + 1);
			printf("%s score: %d\n",
				curMove->promotion == -1 ?
				"\0" : kindToString(curMove->promotion),
				curMove->score);
		}
	}
}

void freeMoves(move_t **pMove) {
	move_t *curMove, *nextMove;

	for (curMove = *pMove; curMove != NULL; curMove = nextMove) {
		nextMove = curMove->next;
		free(curMove);
	}
	*pMove = NULL;
}
