/*
 * General.h
 *
 *  Created on: Aug 26, 2015
 *      Author: bensterenson
 */

#ifndef GENERAL_H
#define GENERAL_H

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <math.h>
#include <ctype.h>
#include <memory.h>
#include <time.h>
//###########################
//#			ENUM			#

typedef enum commands {
	// (10) settings commands:
	SET_GAME_MODE, SET_DIFFICULTY, SET_USER_COLOR, SET_LOAD, SET_CLEAR, SET_NEXT_PLAYER, SET_RM, SET_SET, SET_PRINT, SET_START,

	// (1) mutual commands:
	QUIT,

	// (5) game commands:
	GAME_MOVE, GAME_GET_MOVES, GAME_GET_BEST_MOVES, GAME_GET_SCORE, GAME_SAVE, GAME_CASTLE

} command_t;

typedef enum kind {
	PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING
} chessPieceKind_t;

typedef enum score {
	SCORE_PAWN = 1,
	SCORE_KNIGHT = 3,
	SCORE_BISHOP = 3,
	SCORE_ROOK = 5,
	SCORE_QUEEN = 9,
	SCORE_KING = 400
} chessPieceScore_t;

typedef enum result {
	OK, TIE, CHECK, CHECKMATE
} result_t;

typedef enum difficulty {
	// 1-4 acts normally
	BEST = 5
} difficulty_t;

typedef enum state {
	SETTINGS, PLAYING, END
} state_t;

typedef enum color {
	BLACK, WHITE
} color_t;

typedef enum mode {
	PLAYER_VS_PLAYER = 1,
	PLAYER_VS_COMPUTER = 2
} moode_t;

typedef enum blocked {
	BLOCKED, FREE
} blocked_t;

typedef enum direction {
	UU, // up
	UR, // up right
	RR, // right
	DR, // down right
	DD, // down
	DL, // down left
	LL, // left
	UL	// up left
} direction_t;

typedef enum {
	numOfXMLLines = 11, maxLenofLine = 50
} xmlStrProperties_t;

typedef enum {
	WRITE, READ
} writeRead_t;

typedef enum {
	NOT_SET = -1, READY_TO_WRITE = 0, READY_TO_READ = 1
} boardStatus_t;

typedef enum {
	FAILED, PASSED
} funcStatus_t;

typedef enum {
	FALSE, TRUE
} bool_t;

typedef enum {
	LINE_XML_VER = 1,
	LINE_GAME = 2,
	LINE_TURN = 3,
	LINE_MODE = 4,
	LINE_DIFFICULTY = 5,
	LINE_USER_COLOR = 6,
	LINE_BOARD = 7,
	LINE_ROW = 8,
	LINE_GENERAL = 9,
	LINE_CASTLING_W = 10,
	LINE_CASTLING_B = 11
} Line_t;

typedef enum {
	CANT_CASTLE,
	CASTLE_KING_SIDE,
	CASTLE_QUEEN_SIDE,
	BOTH_SIDES
}castling_t;

typedef enum {
	ROOK_L,
	ROOK_R,
	KING_M
} haveMoved_t;

//#		END	  ENUMS			#
//###########################
//###########################
//#			DEFINES			#

#define BOARD_SIZE 8
#define MIN(x,y) ((x) > (y)) ? (y) : (x)
#define MAX(x,y) ((x) < (y)) ? (y) : (x)

//#		END	DEFINES			#
//###########################
//###########################
//#		   STRUCTS

typedef struct coord {
	int row;
	int col;
} coord_t;

typedef struct tagChessPiece_t chessPiece_t;
typedef void (*displayFunc_t)();
typedef void (*moveFunc_t)(coord_t*, coord_t*, blocked_t*);

typedef struct tagChessPiece_t {
	coord_t coord;
	color_t color;
	chessPieceKind_t kind;
	displayFunc_t displayFunc;
	moveFunc_t moveFunc;

	struct tagChessPiece_t *next;
	struct tagChessPiece_t *prev;
} chessPiece_t;

typedef struct {
	color_t color;
	chessPiece_t *pHead;
	int numOfPiece[6];
	int totalPieces;
	chessPiece_t *pKing;

	castling_t castling[3];

} chessPlayer_t;

typedef chessPiece_t* chessBoard_t[BOARD_SIZE][BOARD_SIZE];

typedef struct {
	chessPlayer_t *pWhite;
	chessPlayer_t *pBlack;
	chessBoard_t *pBoard;

	color_t turn;
	color_t user;
	moode_t mode;
	difficulty_t difficulty;
	state_t gameState;
} chessGame_t;

extern chessGame_t *pGame;
extern chessBoard_t *pBoard;

//#		END  STRUCTS		#
//###########################
//###########################
//#			PRINTS			#

#define INF 1000000
#define ENTER_SETTINGS "Enter game settings:\n"
#define WRONG_GAME_MODE "Wrong game mode\n"
#define TWO_PLAYERS_GAME_MODE "Running game in 2 players mode\n"
#define PLAYER_VS_AI_GAME_MODE "Running game in player vs. AI mode\n"
#define WRONG_MINIMAX_DEPTH "Wrong value for minimax depth. The value should be between 1 to 4\n"
#define WRONG_FILE_NAME "Wrong file name\n"
#define WRONG_POSITION "Invalid position on the board\n"
#define WRONG_PIECE_SELECTION "The specified position does not contain your piece\n"
#define NO_PIECE "Setting this piece creates an invalid board\n"
#define WROND_BOARD_INITIALIZATION "Wrong board initialization\n"
#define ILLEGAL_COMMAND "Illegal command, please try again\n"
#define ILLEGAL_MOVE "Illegal move\n"
#define WRONG_ROOK_POSITION "Wrong position for a rook\n"
#define ILLEGAL_CALTLING_MOVE "Illegal castling move\n"
#define TIE "The game ends in a tie\n"
#define perror_message(func_name) (perror("Error: standard function %s has failed", func_name));
#define print_message(message) (printf("%s", message));

#define otherColor(color) (color == BLACK ? WHITE : BLACK)

//#		END  PRINTS			#
//###########################
//###########################
//#		DECLARATIONS		#

extern color_t charToColor(char);
extern chessPieceKind_t charToKind(char);
extern char kindToChar(chessPieceKind_t);
extern char* kindToString(chessPieceKind_t);
extern void print_line();
extern void checkAllocError(void *pointer, char *func_name);
extern void freeAllMemory();
extern void freeAllMemoryAndExit();

//#		END DECLARATIONS	#
//###########################

#endif /* GENERAL_H */
