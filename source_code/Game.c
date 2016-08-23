/*
 * Game.c
 *
 *  Created on: Jul 23, 2015
 *      Author: bensterenson
 */

#include "Game.h"

chessGame_t *pGame;

void newGame() {
	pGame = (chessGame_t*) malloc(sizeof(chessGame_t));
		checkAllocError(pGame, "malloc");


	pGame->pWhite = newPlayer(WHITE);
	pGame->pBlack = newPlayer(BLACK);

	newBoard();
	pGame->pBoard = pBoard;

	pGame->mode = PLAYER_VS_PLAYER;
	pGame->difficulty = 1;
	pGame->gameState = SETTINGS;
	pGame->turn = WHITE;
	pGame->user = WHITE;

	char INIT_BOARD[BOARD_SIZE][BOARD_SIZE] = {	//
			/*    */{ 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R' }, //
					{ 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M' }, //
					{ '_', '_', '_', '_', '_', '_', '_', '_' }, //
					{ '_', '_', '_', '_', '_', '_', '_', '_' }, //
					{ '_', '_', '_', '_', '_', '_', '_', '_' }, //
					{ '_', '_', '_', '_', '_', '_', '_', '_' }, //
					{ 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm' }, //
					{ 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r' } }; //

	initGame(&INIT_BOARD);
}

void updateCastling() {
	if (pieceToChar((*pBoard)[0][0]) != 'r')
		getPlayerByColor(WHITE)->castling[ROOK_L] = TRUE;
	if (pieceToChar((*pBoard)[0][7]) != 'r')
		getPlayerByColor(WHITE)->castling[ROOK_R] = TRUE;
	if (pieceToChar((*pBoard)[0][4]) != 'k')
		getPlayerByColor(WHITE)->castling[KING_M] = TRUE;

	if (pieceToChar((*pBoard)[7][0]) != 'R')
		getPlayerByColor(BLACK)->castling[ROOK_L] = TRUE;
	if (pieceToChar((*pBoard)[7][7]) != 'R')
		getPlayerByColor(BLACK)->castling[ROOK_R] = TRUE;
	if (pieceToChar((*pBoard)[7][4]) != 'K')
		getPlayerByColor(BLACK)->castling[KING_M] = TRUE;
}

void initGame(char (*board)[BOARD_SIZE][BOARD_SIZE]) {
	chessPiece_t *pPiece;
	int i = 0;

	clearBoard();

	for (char *c = board[0][0]; c - board[0][0] < BOARD_SIZE * BOARD_SIZE;
			c++, i++) {
		if (*c == '_') {
			continue;
		}
		pPiece = newPiece(charToKind(*c), charToColor(*c));
		placePiece(pPiece, BOARD_SIZE - 1 - i / BOARD_SIZE, i % BOARD_SIZE);
		insertPiece(pPiece);
	}

	updateCastling();
}


void clearBoard() {
	memset(pBoard, 0, sizeof(chessPiece_t*) * BOARD_SIZE * BOARD_SIZE);
	freePlayers();
}


void movePiece(coord_t src_coord, coord_t dest_coord, int toFree) {
	chessPiece_t *pPiece = (*pBoard)[src_coord.row][src_coord.col];
	chessPieceKind_t kind = pPiece->kind;
	chessPlayer_t *pPlayer = getPlayerByColor(pPiece->color);

	if (toFree == TRUE) {
		// castling
		int row = pPiece->color == WHITE ? 0 : BOARD_SIZE - 1;

		if (kind == KING)
			pPlayer->castling[KING_M] = TRUE;

		else if (kind == ROOK) {
			if (src_coord.row == row) {
				if (src_coord.col == 0)
					pPlayer->castling[ROOK_L] = TRUE;
				else if (src_coord.col == BOARD_SIZE - 1)
					pPlayer->castling[ROOK_R] = TRUE;
			}
		}
	}
	pPiece->coord.row = dest_coord.row;
	pPiece->coord.col = dest_coord.col;

	rmPiece_c(dest_coord, toFree);

	(*pBoard)[src_coord.row][src_coord.col] = NULL;
	(*pBoard)[dest_coord.row][dest_coord.col] = pPiece;
}

void castleMove(chessPiece_t *pPiece) {
	coord_t dst_coord = pPiece->coord;
	coord_t kingDst_coord = { pPiece->coord.row, 4 };
	coord_t king_coord = { pPiece->coord.row, 4 };

	if (pPiece->coord.col == 0) {
		dst_coord.col += 3;
		kingDst_coord.col -= 2;
	}
	else {
		dst_coord.col -= 2;
		kingDst_coord.col += 2;
	}

	movePiece(pPiece->coord, dst_coord, TRUE);
	movePiece(king_coord, kingDst_coord, TRUE);
}

void undoCastleMove(chessPiece_t *pPiece) {
	chessPlayer_t *pPlayer = getPlayerByColor(pPiece->color);
	chessPiece_t *pKing = pPlayer->pKing;

	coord_t original_king_pos = { pKing->coord.row, 4 };
	coord_t original_rook_pos = { pPiece->coord.row, pKing->coord.col == 2 ? 0 : BOARD_SIZE - 1 };

	movePiece(pPiece->coord, original_rook_pos, TRUE);
	movePiece(pKing->coord, original_king_pos, TRUE);

	if (original_rook_pos.col == 0)
		pPlayer->castling[KING_M] = pPlayer->castling[ROOK_L] = FALSE;
	else
		pPlayer->castling[KING_M] = pPlayer->castling[ROOK_R] = FALSE;
}

void rmPiece(int row, int col, int toFree) {
	chessPiece_t *pPiece = (*(pBoard))[row][col];

	if (pPiece != NULL) {
		(*pBoard)[row][col] = NULL;
		removePiece(pPiece, toFree);
	}
}

void rmPiece_c(coord_t coord, int toFree) {
	rmPiece(coord.row, coord.col, toFree);
}

void setPiece_c(char piece_char, coord_t *coord) {
	setPiece(piece_char, coord->row, coord->col);
}

void setPiece(char piece_char, int row, int col) {
	chessPiece_t *pPiece = newPiece(charToKind(piece_char),
			charToColor(piece_char));

	rmPiece(row, col, TRUE);

	insertPiece(pPiece);
	placePiece(pPiece, row, col);
}

void promotion(chessPieceKind_t pieceKind,coord_t dest_coord) {
	int promotionRow = pGame->turn == WHITE ? 7 : 0;
	if (pieceKind == PAWN || pieceKind == KING || pieceKind == -1)
		pieceKind = QUEEN;
	if ((pieceKind == KNIGHT || pieceKind == BISHOP || pieceKind == ROOK
			|| pieceKind == QUEEN) && dest_coord.row == promotionRow) {

		// check if pawn
		chessPiece_t *pPiece = (*pBoard)[dest_coord.row][dest_coord.col];
		if (pPiece->kind == PAWN)
			setPiece_c(extractPieceChar(pieceKind, pGame->turn), &dest_coord);

	}
}
