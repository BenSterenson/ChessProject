/*
 * Board.c
 *
 *  Created on: Jul 22, 2015
 *      Author: bensterenson
 */

#include "Board.h"

chessBoard_t *pBoard;

void newBoard() {
	pBoard = (chessBoard_t*)calloc(BOARD_SIZE * BOARD_SIZE, sizeof(chessPiece_t));
	checkAllocError(pBoard, "calloc");
}

void saveBoard(char (*matrix)[BOARD_SIZE][BOARD_SIZE]) {

	for (int row = 0; row < BOARD_SIZE; row++) {

		for (int col = 0; col < BOARD_SIZE; col++) {
			chessPiece_t *pPiece = (*pBoard)[row][col];
			if (pPiece == NULL) {
				(*matrix)[BOARD_SIZE - 1 - row][col] = '_';
				continue;
			}
			(*matrix)[BOARD_SIZE - 1 - row][col] = pieceToChar(pPiece);
		}
	}
}

void printPiece(chessPiece_t *pPiece) {
	if (pPiece == NULL) {
		printf("|   ");

		return;
	}
	printf("| ");
	printf("%c", pieceToChar(pPiece));
	printf(" ");
}

void printBoard() {
	print_line();

	for (int row = BOARD_SIZE - 1; row >= 0; row--) {
		printf("%d", row + 1);
		for (int col = 0; col < BOARD_SIZE; col++)
			printPiece((*pBoard)[row][col]);

		printf("|\n");
		print_line();
	}
	printf("  ");
	for (int i = 0; i < BOARD_SIZE; i++) {
		printf(" %c  ", (char)('a' + i));
	}
	printf("\n");
}

void placePiece_c(chessPiece_t *pPiece, coord_t* coord) {
	placePiece(pPiece, coord->row, coord->col);
}

void placePiece(chessPiece_t *newPiece, int row, int col) {
	newPiece->coord.row = row;
	newPiece->coord.col = col;
	(*pBoard)[row][col] = newPiece;
}
