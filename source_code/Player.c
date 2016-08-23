/*
 * Player.c
 *
 *  Created on: Jul 22, 2015
 *      Author: bensterenson
 */

#include "Player.h"

chessPlayer_t* newPlayer(color_t color) {
	chessPlayer_t *pPlayer = (chessPlayer_t*)malloc(sizeof(chessPlayer_t));
	checkAllocError(pPlayer, "malloc");

	pPlayer->color = color;
	pPlayer->totalPieces = 0;
	pPlayer->pHead = NULL;
	pPlayer->pKing = NULL;
	for (int i = 0; i < 3; pPlayer->castling[i++] = FALSE);
	memset(pPlayer->numOfPiece, 0, sizeof(int));

	return pPlayer;
}

void removePiece(chessPiece_t *pPiece, int toFree) {
	chessPlayer_t *pPlayer = getPlayerByColor(pPiece->color);
	chessPiece_t *next, *prev;

	pPlayer->numOfPiece[pPiece->kind]--;
	pPlayer->totalPieces--;
	next = pPiece->next;
	prev = pPiece->prev;

	if (prev == NULL)
		pPlayer->pHead = next;

	else
		prev->next = next;

	if (next != NULL)
		next->prev = prev;

	if (toFree) {
		free(pPiece); iPieces--;
	}
	else {
		// isolate piece
		pPiece->next = NULL;
		pPiece->prev = NULL;
	}
}

void freePlayer(chessPlayer_t *pPlayer) {

	pPlayer->totalPieces = 0;
	memset(pPlayer->numOfPiece, 0, sizeof(pPlayer->numOfPiece));
	memset(pPlayer->castling, FALSE, sizeof(pPlayer->castling));

	freePieces(pPlayer->pHead);
	pPlayer->pHead = NULL;
	pPlayer->pKing = NULL;
	pPlayer->totalPieces = 0;
}

void freePlayers() {
	freePlayer(pGame->pBlack);
	freePlayer(pGame->pWhite);
}

void insertPiece(chessPiece_t *pPiece) {
	chessPlayer_t *pPlayer;
	if (pPiece == NULL) return;

	pPlayer = getPlayerByColor(pPiece->color);
	if (pPiece->kind == KING)
		pPlayer->pKing = pPiece;

	pPiece->next = pPlayer->pHead;
	if (pPlayer->pHead != NULL)
		pPlayer->pHead->prev = pPiece;
	pPlayer->pHead = pPiece;

	pPlayer->numOfPiece[pPiece->kind]++;
	pPlayer->totalPieces++;
}

chessPlayer_t* getPlayerByColor(color_t color) {
	return color == WHITE ? pGame->pWhite : pGame->pBlack;
}
