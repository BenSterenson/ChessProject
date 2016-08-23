/*
 * General.c
 *
 *  Created on: Aug 26, 2015
 *      Author: bensterenson
 */

#include "General.h"

void checkAllocError(void *pnt, char *func){
		if (pnt == NULL) {
			fprintf(stderr, "Error: standard function %s has failed.\n", func);
			freeAllMemoryAndExit();
		}
	}


char kindToChar(chessPieceKind_t kind) {
	switch (kind) {
	case PAWN:
		return 'm';
	case KING:
		return 'k';
	case QUEEN:
		return 'q';
	case BISHOP:
		return 'b';
	case ROOK:
		return 'r';
	case KNIGHT:
		return 'n';
	default:
		printf("kind error2.\n");
		return -1;
	}
}

char* kindToString(chessPieceKind_t kind) {
	switch (kind) {
	case PAWN:
		return " pawn";
	case KING:
		return " king";
	case QUEEN:
		return " queen";
	case BISHOP:
		return " bishop";
	case ROOK:
		return " rook";
	case KNIGHT:
		return " knight";
	default:
		printf("kind error3.\n");
		return "\0";
	}
}

chessPieceKind_t charToKind(char c) {
	switch (tolower(c)) {
	case 'm':
		return PAWN;
	case 'k':
		return KING;
	case 'q':
		return QUEEN;
	case 'b':
		return BISHOP;
	case 'r':
		return ROOK;
	case 'n':
		return KNIGHT;
	default:
		printf("kind error.\n");
		return -1;
	}
}

color_t charToColor(char c) {
	return isupper(c) ? BLACK : WHITE;
}

void print_line() {
	int i;
	printf(" |");
	for (i = 1; i < BOARD_SIZE * 4; i++) {
		printf("-");
	}
	printf("|\n");
}
