#ifndef CHESSSDL_H
#define CHESSSDL_H

#include <SDL/SDL.h>
#include "General.h"
#include "unistd.h"
#include "ReadWriteXML.h"

#define EMPTYCELL 6
#define slotAmount 7

typedef enum {
	BUTTON, PANEL, LABEL, WINDOW
} controlType_t;

typedef enum {
	WIN_W = 400,
	WIN_H = 500,

	WIN_W_GAME = 1000,
	WIN_H_GAME = 700,

	BTN_W = 251,
	BTN_H = 63,

	BTN_S_W = 144,
	BTN_BOX = 63,
	BTN_BOX_SAVE = 40,

	CELL_SIZE = 70,

	BTN_Y = 100,
	BTN_X = 100,

	OFFSET_BOARD = 50
} winSize_t;

typedef enum {
	GUI_MAIN, GUI_SETTINGS, GUI_SLOTS, GUI_GAME
} panels_t;
typedef enum {
	B_START, B_SAVE, B_CLEAR, B_BEST_SET, B_MAIN, B_QUIT, B_REMOVE, B_NEWGAME, B_BLACK, B_WHITE,B_MSGBOX
} game_buttons_t;
typedef struct control {

	color_t color;
	int isMarked;

	//int info[2];

	char * basicImgPath;
	char * MarkedImgPath;

	controlType_t type;
	SDL_Surface *surf;

	struct control *parent;
	struct control *next;
	struct control *child;

	SDL_Rect rect;
	int (*func)(int);

} control_t;

// GLOBALS
typedef control_t* guiBoard_t[BOARD_SIZE][BOARD_SIZE];
control_t *window;
SDL_Event event;
typedef int (*fptr_t)(int);


// FUNCTIONS

// GUI Initialization
extern void initGuiMain();
extern control_t* initGuiLoad();
extern void initGuiGame();
extern void initGuiSettings(control_t**, control_t**);
extern void newGuiBoard();

// GUI
extern int gui();
extern int guiSettings();
extern int guiGame();
extern int guiLoad();

// free GUI & ERROR handeling
extern void freeControls(struct control *curr);
extern void freeGui();
extern void freeAllMemoryAndExit();
extern void checkForSurfaceError(control_t *);
extern void drawError(control_t* );

// DISPLAY GUI
extern void flipGui();
extern void loadBmpImg(SDL_Surface **, char *);
extern void draw(control_t *);
extern void drawElement(control_t *);
extern void markCell(int , int , int );
extern void markCells(int );
extern char* getImg(chessPiece_t *, int , int , int );
extern char* getEmptyCell(int row, int , int );
extern char* getBasicImgByPiece(chessPiece_t *, int , int );
extern char* getBasicImgByKind(chessPieceKind_t , color_t , int , int );
extern char* getMarkedImgByPiece(chessPiece_t *, int , int );
extern char* getMarkedImgByKind(chessPieceKind_t kind, color_t , int , int );
extern void updateMSG(char * );
extern int selectedPieceSetColor(int );
extern void updatePieceSetColor();
extern void updatePieceChoiceImg(control_t* bPiece, chessPieceKind_t kind);
extern int updateAllPiecesChoiceImg();
extern void disablefunctions(int );
// Calculate position
extern int isInside(int ,int , control_t *);
extern int mid_x(int ,int ,int);
extern int mid_y(int ,int ,int);
extern int offset_y(int ,int ,int ,int );
extern int insideButton(int ,int , SDL_Rect* );
extern int relativePos(int);

// Updating buttons
extern void updateGameButtonBMP(game_buttons_t, int);
extern void updateGamePiecesBMP(chessPieceKind_t , int );
extern void updateButtons(control_t *);

// Button selection
extern int selectedQuit(int);
extern void selectButton(control_t** arr , int , int );

// Working with files
extern int checkAccess(char* fName);

// Control
extern control_t *newWindow(winSize_t , winSize_t );
extern control_t *newButton(control_t *,char *, char *,int,int,int(*func)());
extern control_t *newPanel(control_t *, char *, int,int,int,int);
extern control_t *newLabel(control_t *, char*, int, int);
extern control_t* newControl(control_t *, int, int, int,int);

// Button & Pieces functions
extern int showPieceMoves(int , int );
extern int selectedBestPlayerVsPlayer(int);
extern void selectedBestByDepth(int);
extern bool_t inMoves(int , int );
extern int checkWinner();
extern int checkInitBoard(int);
extern bool_t isKingSelected(move_t*);
extern int dummyFunc(int);
extern int getPieceKind(chessPiece_t*);
extern void initGuiBoard();
extern int selectedStart(int);
extern int startGame(int);
extern int selectedMainMenu(int);
extern int selectedKindToSet(int kind);
extern void resetGlobalVariable();
extern int selectedSetPiece(int);
extern void guiPromotion();
extern int selectedKindToPromotion(int kind);
extern void disablePieceSet();
// bestMove
extern void selectedBestByDepth(int);
extern int selectedBestPlayerVsPlayer(int);
extern int selectedBestMove(int dummy);

extern int selectedDiff1(int);
extern int selectedDiff2(int);
extern int selectedDiff3(int);
extern int selectedDiff4(int);
extern int selectedDiff5(int);

// Board GUI update
extern void refreshGuiBoard(int);
extern void updateFuncCell(int , int , int (*funcN)(int));
extern void updateAllFuncCells(int (*funcN)(int));
extern void updateCell(int, int);
// Settings
extern int selectedPieceSettingsFunc(int);
extern int selectedClearBoard(int);
extern int selectedRemovePiece(int);

extern int selectedGamePvsP(int);
extern int selectedGamePvsc(int);

extern int selectedTurnColorB(int);
extern int selectedTurnColorW(int);

extern int selectedPlayerColorW(int);
extern int selectedPlayerColorB(int);

// Game mode
extern int selectedPieceFunc(int); // start game
extern int selectedNewGame(int);

//Load/Save
extern int selectedSlot(int );
extern int selectedSaveSlot(int);
extern int selectedSave(int);

//
#endif /* CHESSSDL_H */

