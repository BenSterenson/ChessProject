#ifndef CHESS_
#define CHESS_

//#include "Game.h"
#include "miniMax.h"


//###########################
//#			STRUCTS			#

typedef struct chessPiece_tbl_score {
	chessPieceKind_t	pieceId;
	chessPieceScore_t	pieceScore;
} chessPiece_tbl_score_t;

//#			STRUCTS			#
//###########################
//###########################
//#		DECLARATIONS		#

extern int printWinner();
extern int checkmate(move_t*);
extern void getCommands();
extern void executeCommand(command_t, char**);
extern command_t stringToCommand(char*);
extern command_t extractCommand(char*, char**);
extern chessPieceKind_t extractKind(char*);
extern void extractCoord(char*, coord_t*);
extern color_t extractColor(char*);
extern char extractPieceChar(chessPieceKind_t, color_t);
extern int isValidCommand(command_t);
extern int isValidMove(coord_t*, coord_t*);
extern int maxPiecesReached(chessPieceKind_t, color_t, coord_t*);
extern void freeAllMemory();
extern void ReadInput(char*);
extern char extractPieceChar(chessPieceKind_t , color_t );
extern void opponentMove();
extern move_t * chooseRandomBestMove(move_t* );
extern int WriteReadXML(char *destFName, writeRead_t writeRead);
extern int gui();

//#		DECLARATIONS		#
//###########################

#endif /*CHESS_*/
