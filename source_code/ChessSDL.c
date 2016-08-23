#include "ChessSDL.h"

/********************GLOBAL ARRAYS FOR SETTINGS*************************/
moode_t gameMode;
int turn;
int playerColor;
int diffMode;
int msgShow = FALSE;
int passed_Loading = FALSE;
int quit = FALSE;
int pieceToSetColor = WHITE;
int KindPieceToSet = -1;
int promotionFlag = FALSE;
int saveFlag = FALSE;
int loadFlag = FALSE;
int BestplayerVsPlayerFlag = FALSE;

//######################################################################################//
//############################ GLOBAL BUTTONS ARRAY ####################################//
//######################################################################################//

control_t* panels[4] = { NULL };
control_t* bGameMode[2] = { NULL };
control_t* bPlayerColor[2] = { NULL };
control_t* bTurn[2] = { NULL };
control_t* diff[5] = { NULL };
control_t* gameButtons[11] = { NULL };
control_t* slotButtons[10] = { NULL };
control_t* gamePieces[6] = { NULL };
coord_t crdMousePos = { -1, -1 };
coord_t prevMousePos = { -1, -1 };

fptr_t fptr_arr[5] = { selectedDiff1, selectedDiff2, selectedDiff3,
		selectedDiff4, selectedDiff5 };

move_t *pMoves = NULL;
guiBoard_t *guiBoard;

//######################################################################################//
//########################### GLOBAL FILE NAMES ARR ####################################//
//######################################################################################//

// ### SETTINGS
//		USED FOR DIFFICULTY - # MARKED
char diffMarked[5][30] = { "GameBMP/1Marked.bmp", "GameBMP/2Marked.bmp",
		"GameBMP/3Marked.bmp", "GameBMP/4Marked.bmp", "GameBMP/bMarked.bmp" };

// 		USED FOR DIFFICULTY - # UNMARKED
char diffTran[5][30] = { "GameBMP/1TranS.bmp", "GameBMP/2TranS.bmp",
		"GameBMP/3TranS.bmp", "GameBMP/4TranS.bmp", "GameBMP/bTranS.bmp" };

// ### LOAD FUNCTION
// 		USED FOR SLOTS - # UNMARKED
char bmpTRAN[10][30] = { "GameBMP/1TranL.bmp", "GameBMP/2TranL.bmp",
		"GameBMP/3TranL.bmp", "GameBMP/4TranL.bmp", "GameBMP/5TranL.bmp",
		"GameBMP/6TranL.bmp", "GameBMP/7TranL.bmp", "GameBMP/8TranL.bmp",
		"GameBMP/9TranL.bmp", "GameBMP/10TranL.bmp" };

// 		USED FOR SLOTS - # UNMARKED
char bmpMarked[10][30] = { "GameBMP/1Marked.bmp", "GameBMP/2Marked.bmp",
		"GameBMP/3Marked.bmp", "GameBMP/4Marked.bmp", "GameBMP/5Marked.bmp",
		"GameBMP/6Marked.bmp", "GameBMP/7Marked.bmp", "GameBMP/8Marked.bmp",
		"GameBMP/9Marked.bmp", "GameBMP/10Marked.bmp" };

//		XML FILE NAMES
char XMLFNameARR[10][30] = { "1.xml", "2.xml", "3.xml", "4.xml", "5.xml",
		"6.xml", "7.xml", "8.xml", "9.xml", "10.xml" };

// #### GAME FUNCTION
// 		USED FOR SLOTS - # UNMARKED
char bmpSaveTRAN[10][30] = { "GameBMP/bsslot1.bmp", "GameBMP/bsslot2.bmp",
		"GameBMP/bsslot3.bmp", "GameBMP/bsslot4.bmp", "GameBMP/bsslot5.bmp",
		"GameBMP/bsslot6.bmp", "GameBMP/bsslot7.bmp", "GameBMP/bsslot8.bmp",
		"GameBMP/bsslot9.bmp", "GameBMP/bsslot10.bmp" };

char bmpSaveMarked[10][30] = { "GameBMP/bsslot1M.bmp", "GameBMP/bsslot2M.bmp",
		"GameBMP/bsslot3M.bmp", "GameBMP/bsslot4M.bmp", "GameBMP/bsslot5M.bmp",
		"GameBMP/bsslot6M.bmp", "GameBMP/bsslot7M.bmp", "GameBMP/bsslot8M.bmp",
		"GameBMP/bsslot9M.bmp", "GameBMP/bsslot10M.bmp" };

/**********************************************/
/*******White piece cell combinations**********/
/**********************************************/
//white piece black Marked cell
char w_p_b_markArr[7][30] = { "GameBMP/wpbm.bmp", "GameBMP/wnbm.bmp",
		"GameBMP/wbbm.bmp", "GameBMP/wrbm.bmp", "GameBMP/wqbm.bmp",
		"GameBMP/wkbm.bmp", "GameBMP/ebm.bmp" };

//white piece black cell
char w_p_b_arr[7][30] = { "GameBMP/wpb.bmp", "GameBMP/wnb.bmp",
		"GameBMP/wbb.bmp", "GameBMP/wrb.bmp", "GameBMP/wqb.bmp",
		"GameBMP/wkb.bmp", "GameBMP/eb.bmp" };

//white piece white Marked cell
char w_p_w_markArr[7][30] = { "GameBMP/wpwm.bmp", "GameBMP/wnwm.bmp",
		"GameBMP/wbwm.bmp", "GameBMP/wrwm.bmp", "GameBMP/wqwm.bmp",
		"GameBMP/wkwm.bmp", "GameBMP/ewm.bmp" };

//white piece white cell
char w_p_w_arr[7][30] = { "GameBMP/wpw.bmp", "GameBMP/wnw.bmp",
		"GameBMP/wbw.bmp", "GameBMP/wrw.bmp", "GameBMP/wqw.bmp",
		"GameBMP/wkw.bmp", "GameBMP/ew.bmp" };
/**********************************************/

/**********************************************/
/*******Black piece cell combinations**********/
/**********************************************/
//black piece black Marked cell
char b_p_b_markArr[7][30] = { "GameBMP/bpbm.bmp", "GameBMP/bnbm.bmp",
		"GameBMP/bbbm.bmp", "GameBMP/brbm.bmp", "GameBMP/bqbm.bmp",
		"GameBMP/bkbm.bmp", "GameBMP/ebm.bmp" };
//black piece black cell
char b_p_b_arr[7][30] = { "GameBMP/bpb.bmp", "GameBMP/bnb.bmp",
		"GameBMP/bbb.bmp", "GameBMP/brb.bmp", "GameBMP/bqb.bmp",
		"GameBMP/bkb.bmp", "GameBMP/eb.bmp" };

//white piece white Marked cell
char b_p_w_markArr[7][30] = { "GameBMP/bpwm.bmp", "GameBMP/bnwm.bmp",
		"GameBMP/bbwm.bmp", "GameBMP/brwm.bmp", "GameBMP/bqwm.bmp",
		"GameBMP/bkwm.bmp", "GameBMP/ewm.bmp" };

//black piece white cell
char b_p_w_arr[7][30] = { "GameBMP/bpw.bmp", "GameBMP/bnw.bmp",
		"GameBMP/bbw.bmp", "GameBMP/brw.bmp", "GameBMP/bqw.bmp",
		"GameBMP/bkw.bmp", "GameBMP/ew.bmp" };

/**********************************************/
/*****************END GLOBAL ARRAYS FOR GAME*************************/

//## Initialization GUI
void initGuiMain() {
	control_t *panel = panels[GUI_MAIN] = newPanel(window,
			"GameBMP/menuBackGround.bmp", 0, 0, WIN_H, WIN_W);
	int offset = 40;

	int load_x = mid_x(panel->rect.x, panel->rect.w, BTN_W);
	int load_y = mid_y(panel->rect.y, panel->rect.h, BTN_H);

	int new_x = load_x;
	int new_y = offset_y(load_y, BTN_H, +offset, BTN_H);

	int quit_x = load_x;
	int quit_y = offset_y(load_y, BTN_H, -offset, BTN_H);

	newButton(panel, "GameBMP/ButtonNewGameTRAN.bmp",
			"GameBMP/ButtonNewGame.bmp", new_x, new_y, guiSettings);
	newButton(panel, "GameBMP/ButtonLoadGameTRAN.bmp",
			"GameBMP/ButtonLoadGame.bmp", load_x, load_y, guiLoad);
	newButton(panel, "GameBMP/ButtonQuitTRAN.bmp", "GameBMP/ButtonQuit.bmp",
			quit_x, quit_y, selectedQuit);
}
control_t* initGuiLoad() {

	control_t *panel = panels[GUI_SLOTS] = newPanel(window,
			"GameBMP/menuLOAD.bmp", 0, 0, WIN_H, WIN_W);
	int offset = 10;

	int slot_x = mid_x(panel->rect.x, panel->rect.w, BTN_BOX);
	int slot_y_start = BTN_BOX + offset * 10;

	int row5_x[5] = { WIN_W / 10 - BTN_BOX / 2, WIN_W * 3 / 10 - BTN_BOX / 2,
			WIN_W * 5 / 10 - BTN_BOX / 2, WIN_W * 7 / 10 - BTN_BOX / 2, WIN_W
					* 9 / 10 - BTN_BOX / 2 }; // 5 buttons

	//loading slots.
	for (int i = 0; i < slotAmount; i++) {
		slotButtons[i] = newButton(panel, bmpTRAN[i], bmpMarked[i],
				row5_x[i % 5], (slot_y_start), dummyFunc);
		if (i == 4)
			slot_y_start = slot_y_start + BTN_BOX + offset;
	}
	slot_x = mid_x(panel->rect.x, panel->rect.w, BTN_W);

	control_t * bCancel = newButton(panel, "GameBMP/ButtonCancelTRAN.bmp",
			"GameBMP/ButtonCancel.bmp", slot_x, 322, gui);
	return bCancel;
}
void initGuiGame() {
	control_t *panel = panels[GUI_GAME] = newPanel(window, "GameBMP/board.bmp",
			0, 0, WIN_H_GAME, WIN_W_GAME);
	int offset = 1;

	int row2_x[2] = { WIN_W_GAME * 15 / 20 - BTN_S_W / 2, WIN_W_GAME * 18 / 20
			- BTN_S_W / 2 }; // 2 buttons

	int width = (WIN_W_GAME * 18 / 20 + BTN_S_W / 2)
			- (WIN_W_GAME * 15 / 20 - BTN_S_W / 2);

	int mid = mid_x(WIN_W_GAME * 15 / 20 - BTN_S_W / 2, width, CELL_SIZE);

	int row3_x[3] = { mid - offset - CELL_SIZE, mid, CELL_SIZE + offset + mid }; // 3 buttons

	int row4_y[4] = { WIN_H_GAME * 13 / 20 - BTN_S_W / 2, WIN_H_GAME * 15 / 20
			- BTN_S_W / 2, WIN_H_GAME * 17 / 20 - BTN_S_W / 2, WIN_H_GAME * 19
			/ 20 - BTN_S_W / 2 };

	int row4_top_y[4] = { //
			WIN_H_GAME * 1 / 10 - BTN_BOX / 2, //
			WIN_H_GAME * 1 / 10 + BTN_BOX / 2 + 2 * 3, //
			WIN_H_GAME * 1 / 10 + BTN_BOX / 2 + 2 * 3 + offset + CELL_SIZE, //
			WIN_H_GAME * 1 / 10 + BTN_BOX / 2 + 2 * 60 + offset + BTN_BOX //
			};

	// setting buttons
	gameButtons[B_START] = newButton(panel, "GameBMP/startG.bmp",
			"GameBMP/startB.bmp", row2_x[0], row4_y[0], startGame);

	gameButtons[B_NEWGAME] = newButton(panel, "GameBMP/newGameG.bmp",
			"GameBMP/newGameB.bmp", row2_x[1], row4_y[0], selectedNewGame);

	gameButtons[B_REMOVE] = newButton(panel, "GameBMP/removeG.bmp",
			"GameBMP/removeB.bmp", row2_x[0], row4_y[1], selectedRemovePiece);

	gameButtons[B_CLEAR] = newButton(panel, "GameBMP/ClearBoardG.bmp",
			"GameBMP/ClearBoardB.bmp", row2_x[1], row4_y[1],
			selectedClearBoard);

	gameButtons[B_BEST_SET] = newButton(panel, "GameBMP/setPieceG.bmp",
			"GameBMP/setPieceB.bmp", row2_x[0], row4_y[2], selectedSetPiece);

	gameButtons[B_SAVE] = newButton(panel, "GameBMP/saveG.bmp",
			"GameBMP/saveB.bmp", row2_x[1], row4_y[2], selectedSave);

	gameButtons[B_MAIN] = newButton(panel, "GameBMP/mainmenuG.bmp",
			"GameBMP/mainmenuB.bmp", row2_x[0], row4_y[3], selectedMainMenu);

	gameButtons[B_QUIT] = newButton(panel, "GameBMP/QuitG.bmp",
			"GameBMP/QuitB.bmp", row2_x[1], row4_y[3], selectedQuit);

	// setting color pieces for user to choose
	gameButtons[B_BLACK] = newButton(panel, "GameBMP/BlackG.bmp",
			"GameBMP/BlackMarked.bmp", row2_x[0], row4_top_y[0], dummyFunc);

	gameButtons[B_WHITE] = newButton(panel, "GameBMP/WhiteG.bmp",
			"GameBMP/WhiteMarked.bmp", row2_x[1], row4_top_y[0], dummyFunc);

	updatePieceSetColor();

	// setting pieces for user
	gamePieces[PAWN] = newButton(panel,
			getBasicImgByKind(PAWN, pieceToSetColor, 0, 0),
			getMarkedImgByKind(PAWN, pieceToSetColor, 0, 0), row3_x[0],
			row4_top_y[1], selectedKindToSet);
	gamePieces[KNIGHT] = newButton(panel,
			getBasicImgByKind(KNIGHT, pieceToSetColor, 0, 0),
			getMarkedImgByKind(KNIGHT, pieceToSetColor, 0, 0), row3_x[1],
			row4_top_y[1], selectedKindToSet);
	gamePieces[BISHOP] = newButton(panel,
			getBasicImgByKind(BISHOP, pieceToSetColor, 0, 0),
			getMarkedImgByKind(BISHOP, pieceToSetColor, 0, 0), row3_x[2],
			row4_top_y[1], selectedKindToSet);
	gamePieces[ROOK] = newButton(panel,
			getBasicImgByKind(ROOK, pieceToSetColor, 0, 0),
			getMarkedImgByKind(ROOK, pieceToSetColor, 0, 0), row3_x[0],
			row4_top_y[2], selectedKindToSet);
	gamePieces[QUEEN] = newButton(panel,
			getBasicImgByKind(QUEEN, pieceToSetColor, 0, 0),
			getMarkedImgByKind(QUEEN, pieceToSetColor, 0, 0), row3_x[1],
			row4_top_y[2], selectedKindToSet);
	gamePieces[KING] = newButton(panel,
			getBasicImgByKind(KING, pieceToSetColor, 0, 0),
			getMarkedImgByKind(KING, pieceToSetColor, 0, 0), row3_x[2],
			row4_top_y[2], selectedKindToSet);

	mid = mid_x(WIN_W_GAME * 15 / 20 - BTN_S_W / 2, width, BTN_BOX_SAVE);
	int row5_x_slots[5] = { mid - (offset + BTN_BOX_SAVE) * 2, mid - offset
			- BTN_BOX_SAVE, mid, BTN_BOX_SAVE + offset + mid, (BTN_BOX_SAVE
			+ offset) * 2 + mid }; // 3 buttons
	int row_y_slots[2] =
			{ row4_top_y[3], row4_top_y[3] + offset + BTN_BOX_SAVE }; // 3 buttons

	// create slots for save
	for (int i = 0; i < slotAmount; i++) {
		slotButtons[i] = newButton(panel, bmpSaveTRAN[i], bmpSaveMarked[i],
				row5_x_slots[i % 5], i > 4 ? row_y_slots[1] : row_y_slots[0],
				dummyFunc);
	}
	if (pGame->mode == PLAYER_VS_PLAYER) {
		// create diff buttons
		for (int i = 0; i < 5; i++) {
			diff[i] = newButton(panel, bmpSaveMarked[i], bmpSaveMarked[i],
					row5_x_slots[i % 5],
					i > 4 ? row_y_slots[1] : row_y_slots[0], dummyFunc);
		}
		diff[4]->basicImgPath = "GameBMP/bsslotBest.bmp";
		diff[4]->MarkedImgPath = "GameBMP/bsslotBest.bmp";
		loadBmpImg(&(diff[4]->surf), diff[4]->MarkedImgPath);

	}
	//updateAllPiecesChoiceImg();

	gameButtons[B_MSGBOX] = newButton(panel, "GameBMP/msgBoxE.bmp",
			"GameBMP/msgBoxE.bmp", row2_x[0], row4_top_y[3] - 31, dummyFunc);

	newGuiBoard();
	initGuiBoard();
}
void initGuiSettings(control_t** bStart, control_t** bCancel) {
	control_t *panel = panels[GUI_SETTINGS] = newPanel(window,
			"GameBMP/menuSettings.bmp", 0, 0, WIN_H, WIN_W);

	int row2_x[2] = { WIN_W / 4 - BTN_S_W / 2, WIN_W * 3 / 4 - BTN_S_W / 2 }; // 2 buttons
	int row5_x[5] = { WIN_W / 10 - BTN_BOX / 2, WIN_W * 3 / 10 - BTN_BOX / 2,
			WIN_W * 5 / 10 - BTN_BOX / 2, WIN_W * 7 / 10 - BTN_BOX / 2, WIN_W
					* 9 / 10 - BTN_BOX / 2 }; // 5 buttons

	int row_y[5] = { WIN_H / 10 - BTN_H / 2, WIN_H * 3 / 10 - BTN_BOX / 2, WIN_H
			* 5 / 10 - BTN_H / 2, WIN_H * 7 / 10 - BTN_H / 2, WIN_H * 9 / 10
			- BTN_H / 2 }; // 5 rows
	// row 1

	bGameMode[0] = newButton(panel, "GameBMP/PlayerVsPlayerTran.bmp",
			"GameBMP/PlayerVsPlayer.bmp", row2_x[0], row_y[0] + 10,
			selectedGamePvsP);

	bGameMode[1] = newButton(panel, "GameBMP/PlayerVsComputerTran.bmp",
			"GameBMP/PlayerVsComputer.bmp", row2_x[1], row_y[0] + 10,
			selectedGamePvsc);

	gameMode = pGame->mode;
	if (pGame->mode == PLAYER_VS_PLAYER)
		loadBmpImg(&(bGameMode[0]->surf), bGameMode[0]->MarkedImgPath);
	else
		loadBmpImg(&(bGameMode[1]->surf), bGameMode[1]->MarkedImgPath);

	// row 2

	int gameDiff = diffMode = pGame->difficulty;

	for (int i = 0; i < 5; i++) {
		diff[i] = newButton(panel, diffTran[i], diffMarked[i], row5_x[i],
				row_y[1], fptr_arr[i]);
		if (i == (gameDiff - 1))
			loadBmpImg(&(diff[i]->surf), diff[i]->MarkedImgPath);
	}

	// row 3

	bPlayerColor[0] = newButton(panel, "GameBMP/BlackTran.bmp",
			"GameBMP/BlackMarked.bmp", row2_x[0], row_y[2],
			selectedPlayerColorB);
	bPlayerColor[1] = newButton(panel, "GameBMP/WhiteTran.bmp",
			"GameBMP/WhiteMarked.bmp", row2_x[1], row_y[2],
			selectedPlayerColorW);
	playerColor = pGame->user;
	if (pGame->user == BLACK)
		loadBmpImg(&(bPlayerColor[0]->surf), bPlayerColor[0]->MarkedImgPath);
	else
		loadBmpImg(&(bPlayerColor[1]->surf), bPlayerColor[1]->MarkedImgPath);

	// row 4

	bTurn[0] = newButton(panel, "GameBMP/BlackTurnTran.bmp",
			"GameBMP/BlackMarked.bmp", row2_x[0], row_y[3], selectedTurnColorB);

	bTurn[1] = newButton(panel, "GameBMP/WhiteTurnTran.bmp",
			"GameBMP/WhiteMarked.bmp", row2_x[1], row_y[3], selectedTurnColorW);
	turn = pGame->turn;
	if (pGame->turn == BLACK)
		loadBmpImg(&(bTurn[0]->surf), bTurn[0]->MarkedImgPath);
	else
		loadBmpImg(&(bTurn[1]->surf), bTurn[1]->MarkedImgPath);

	// row 5
	*bCancel = newButton(panel, "GameBMP/CancelSmallTran.bmp",
			"GameBMP/CancelSmallMarked.bmp", row2_x[0], row_y[4], gui);
	*bStart = newButton(panel, "GameBMP/startTran.bmp",
			"GameBMP/startSmallMarked.bmp", row2_x[1], row_y[4], selectedStart);
}
void newGuiBoard() {
	guiBoard = (guiBoard_t*) calloc(BOARD_SIZE * BOARD_SIZE,
			sizeof(guiBoard_t));
}
//## END OF Initialization GUI

// ## GUI FUNCTION
// 		GUI MAIN MENU
int gui() {
	int flip = 1;

	if (window == NULL)
		window = newWindow(WIN_H, WIN_W);

	if (SDL_Init(SDL_INIT_VIDEO) < 0) { // perror
		fprintf(stderr, "ERROR: function SDL_Init has failed: %s\n",
				SDL_GetError());
		freeAllMemoryAndExit();
	}

	SDL_WM_SetCaption("chess Game by Ben & Michael", 0);

	loadFlag = FALSE;
	saveFlag = FALSE;
	passed_Loading = FALSE;

	if (panels[GUI_MAIN] == NULL)
		initGuiMain();
	control_t *panel = panels[GUI_MAIN];
	loadBmpImg(&(panel->surf), panel->basicImgPath);

	int cur_x = event.button.x;
	int cur_y = event.button.y;

	for (control_t * control = panel->child; control != NULL;
			control = control->next) {
		if (control->type == BUTTON) {
			if (isInside(cur_x, cur_y, control))
				loadBmpImg(&(control->surf), control->MarkedImgPath);

			else
				loadBmpImg(&(control->surf), control->basicImgPath);
		}
	}
	drawElement(panel);
	draw(panel->child);

	while (!quit) {
		if (flip) {
			flipGui();
			flip = 0;
		}

		int press_x, press_y;

		while (SDL_PollEvent(&event)) {

			switch (event.type) {
			case SDL_QUIT:
				quit = TRUE;
				break;

			case SDL_MOUSEBUTTONDOWN:
				press_x = event.button.x;
				press_y = event.button.y;
				break;

			case SDL_MOUSEBUTTONUP:
				cur_x = event.button.x;
				cur_y = event.button.y;

				for (control_t *control = panel->child; control != NULL;
						control = control->next)
					//if (isInside(cur_x, cur_y, bNew)
					//	&& isInside(press_x, press_y, control)) {
					if (control->type == BUTTON
							&& isInside(cur_x, cur_y, control)
							&& isInside(press_x, press_y, control)) {
						control->func(TRUE);
						// pressed the button
					}
				break;

			case SDL_MOUSEMOTION:
				cur_x = event.button.x;
				cur_y = event.button.y;

				for (control_t *control = panel->child; control != NULL;
						control = control->next) {
					if (isInside(cur_x, cur_y, control))
						loadBmpImg(&(control->surf), control->MarkedImgPath);

					else
						loadBmpImg(&(control->surf), control->basicImgPath);
					drawElement(control);
					flip = TRUE;

				}
				break;

			case (SDL_KEYUP):
				if (event.key.keysym.sym == SDLK_ESCAPE)
					quit = TRUE;
				break;

			default:
				break;
			}
		}
	}
	freeAllMemoryAndExit();
	return 1;

}
// 		GUI SETTINGS
int guiSettings() {
	int flip = 1;
	int quit = FALSE;

	static control_t *bStart, *bCancel;
	if (panels[GUI_SETTINGS] == NULL)
		initGuiSettings(&bStart, &bCancel);
	control_t *panel = panels[GUI_SETTINGS];

	loadBmpImg(&(panel->surf), panel->basicImgPath);

	int cur_x = event.button.x;
	int cur_y = event.button.y;

	loadBmpImg(&(bCancel->surf), bCancel->basicImgPath);
	loadBmpImg(&(bStart->surf), bStart->basicImgPath);

	drawElement(panel);
	draw(panel->child);

	while (!quit) {
		if (flip) {
			flipGui();
			flip = 0;
		}

		int press_x, press_y;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit = TRUE;
				break;

			case SDL_MOUSEBUTTONDOWN:
				press_x = event.button.x;
				press_y = event.button.y;
				break;

			case SDL_MOUSEBUTTONUP:
				cur_x = event.button.x;
				cur_y = event.button.y;

				for (int i = 0; i < 5; i++) {

					//two button choice:
					if (i < 2) {
						//row 1
						if (bGameMode[i]->type == BUTTON
								&& isInside(cur_x, cur_y, bGameMode[i])
								&& isInside(press_x, press_y, bGameMode[i])) {
							bGameMode[i]->func(TRUE);
							selectButton(&(bGameMode[0]), i, 2);
						}
						// row 3
						if (bPlayerColor[i]->type == BUTTON
								&& isInside(cur_x, cur_y, bPlayerColor[i])
								&& isInside(press_x, press_y,
										bPlayerColor[i])) {
							bPlayerColor[i]->func(TRUE);
							selectButton(&(bPlayerColor[0]), i, 2);

						}
						//row 4
						if (bTurn[i]->type == BUTTON
								&& isInside(cur_x, cur_y, bTurn[i])
								&& isInside(press_x, press_y, bTurn[i])) {
							bTurn[i]->func(TRUE);
							selectButton(&(bTurn[0]), i, 2);
						}

						flip = TRUE;
					}
					// 5 button choice
					if (i < 5) {
						//row 2
						if (diff[i]->type == BUTTON
								&& isInside(cur_x, cur_y, diff[i])
								&& isInside(press_x, press_y, diff[i])) {
							diff[i]->func(TRUE);
							selectButton(&(diff[0]), i, 5);
						}
					}
				}

				for (control_t *control = panel->child; control != NULL;
						control = control->next)
					if (control->type == BUTTON
							&& isInside(cur_x, cur_y, control)
							&& isInside(press_x, press_y, control)) {
						control->func(TRUE);
						loadBmpImg(&(control->surf), control->MarkedImgPath);
						drawElement(control);
						flip = TRUE;
					}
				break;

			case SDL_MOUSEMOTION:
				cur_x = event.button.x;
				cur_y = event.button.y;

				if (isInside(cur_x, cur_y, bCancel))
					loadBmpImg(&(bCancel->surf), bCancel->MarkedImgPath);
				else if (isInside(cur_x, cur_y, bStart))
					loadBmpImg(&(bStart->surf), bStart->MarkedImgPath);
				else {
					loadBmpImg(&(bStart->surf), bStart->basicImgPath);
					loadBmpImg(&(bCancel->surf), bCancel->basicImgPath);
				}
				drawElement(bCancel);
				drawElement(bStart);
				flip = TRUE;
				break;

			case (SDL_KEYUP):
				if (event.key.keysym.sym == SDLK_ESCAPE)
					quit = TRUE;
				break;

			default:
				break;
			}
		}
	}
	freeAllMemoryAndExit();
	return 1;
}
int guiGame() {
	int flip = 1;
	control_t * control;
	if (window == NULL)
		window = newWindow(WIN_H_GAME, WIN_W_GAME);

	if (SDL_Init(SDL_INIT_VIDEO) < 0) { // perror
		fprintf(stderr, "ERROR: function SDL_Init has failed: %s\n",
				SDL_GetError());
		freeAllMemoryAndExit();
	}

	if (panels[GUI_GAME] == NULL)
		initGuiGame();
	control_t *panel = panels[GUI_GAME];

	loadBmpImg(&(panel->surf), panel->basicImgPath);
	drawElement(panel);
	draw(panel->child);
	if (TRUE == loadFlag) {
		passed_Loading == TRUE ?
				loadBmpImg(&(gameButtons[B_MSGBOX]->surf),
						"GameBMP/msgboxLoad.bmp") :
				loadBmpImg(&(gameButtons[B_MSGBOX]->surf),
						"GameBMP/msgBoxLoadError.bmp");
		passed_Loading = FALSE;
		loadFlag = FALSE;
	}
	drawElement(gameButtons[B_MSGBOX]);
	drawElement(gameButtons[B_MSGBOX]);

	while (!quit) {
		if (flip) {
			flipGui();
			flip = 0;
		}

		int press_x, press_y, cur_x, cur_y;

		while (SDL_PollEvent(&event)) {

			switch (event.type) {
			case SDL_QUIT:
				quit = TRUE;
				break;

			case SDL_MOUSEBUTTONDOWN:
				press_x = event.button.x;
				press_y = event.button.y;
				break;

			case SDL_MOUSEBUTTONUP:
				cur_x = event.button.x;
				cur_y = event.button.y;

				// go over board.
				for (int row = 0; row < BOARD_SIZE; row++) {
					for (int col = 0; col < BOARD_SIZE; col++) {
						control = (*guiBoard)[row][col];
						if (control->type == BUTTON
								&& isInside(cur_x, cur_y, control)
								&& isInside(press_x, press_y, control)&&(promotionFlag == FALSE)) {
							//update selection coord only if promotion flag is not on
							crdMousePos.row = BOARD_SIZE
									- relativePos(
											event.button.y - OFFSET_BOARD * 2)
									- 1;
							crdMousePos.col = relativePos(
									event.button.x - OFFSET_BOARD);

							control->func(
									inMoves(crdMousePos.row, crdMousePos.col));
							flip = TRUE;
						}
					}
				}
				//iterate on pieces buttons
				for (int kind = 0; kind < 6; kind++) {
					control = gamePieces[kind];
					if (control->type == BUTTON
							&& isInside(cur_x, cur_y, control)
							&& isInside(press_x, press_y, control)) {
						control->func(kind);
						flip = TRUE;
					}
				}
				//iterate on slot buttons
				if (TRUE == saveFlag) {
					for (int i = 0; i < slotAmount; i++) {
						control = slotButtons[i];
						if (control->type == BUTTON
								&& isInside(cur_x, cur_y, control)
								&& isInside(press_x, press_y, control)) {
							control->func(i);
							flip = TRUE;
						}
					}
				}
				//iterate on diff buttons
				if (TRUE == BestplayerVsPlayerFlag) {
					for (int i = 0; i < 5; i++) {
						control = diff[i];
						if (control->type == BUTTON
								&& isInside(cur_x, cur_y, control)
								&& isInside(press_x, press_y, control)) {
							control->func(i);
							flip = TRUE;
						}
					}
				}

				//	iterate over game buttons
				//		B_START, B_SAVE, B_CLEAR, B_BEST_SET, B_MAIN, B_QUIT, B_REMOVE, B_NEWGAME, B_BLACK, B_WHITE
				for (int i = 0; i < 10; i++) {
					control = gameButtons[i];
					if (control->type == BUTTON
							&& isInside(cur_x, cur_y, control)
							&& isInside(press_x, press_y, control)) {
						if (B_BLACK == i)
							control->func(BLACK);
						else if (B_WHITE == i)
							control->func(WHITE);
						else
							control->func(TRUE);
						flip = TRUE;
					}
				}
				break;

			case SDL_MOUSEMOTION:
				cur_x = event.button.x;
				cur_y = event.button.y;

				for (int i = 0; i < 8; i++) {
					control = gameButtons[i];
					if (isInside(cur_x, cur_y, control))
						loadBmpImg(&(control->surf), control->MarkedImgPath);
					else
						loadBmpImg(&(control->surf), control->basicImgPath);
					drawElement(control);
					flip = TRUE;

				}

				break;

			case (SDL_KEYUP):
				if (event.key.keysym.sym == SDLK_ESCAPE)
					quit = TRUE;
				break;

			default:
				break;
			}
		}
	}

	freeAllMemoryAndExit();
	return 1;
}
int guiLoad() {
	int flip = 1;
	control_t * control;
	static control_t* bCancel;
	if (panels[GUI_SLOTS] == NULL)
		bCancel = initGuiLoad();
	control_t *panel = panels[GUI_SLOTS];
	loadBmpImg(&(panel->surf), panel->basicImgPath);
	loadBmpImg(&(bCancel->surf), bCancel->basicImgPath);

	for (int i = 0; i < slotAmount; i++) {
		checkAccess(XMLFNameARR[i]) == TRUE ?
				loadBmpImg(&(slotButtons[i]->surf),
						slotButtons[i]->MarkedImgPath) :
				loadBmpImg(&(slotButtons[i]->surf),
						slotButtons[i]->basicImgPath);
		drawElement(slotButtons[i]);
		slotButtons[i]->func =
				checkAccess(XMLFNameARR[i]) == TRUE ? selectedSlot : dummyFunc;
	}
	drawElement(panel);
	draw(panel->child);

	while (!quit) {
		if (flip) {
			flipGui();
			flip = 0;
		}

		int press_x, press_y, cur_x, cur_y;

		while (SDL_PollEvent(&event)) {

			switch (event.type) {
			case SDL_QUIT:
				quit = TRUE;
				break;

			case SDL_MOUSEBUTTONDOWN:
				press_x = event.button.x;
				press_y = event.button.y;
				break;

			case SDL_MOUSEBUTTONUP:
				cur_x = event.button.x;
				cur_y = event.button.y;

				//slotButtons[i]
				//iterate on slot buttons
				for (int i = 0; i < slotAmount; i++) {
					control = slotButtons[i];
					if (control->type == BUTTON
							&& isInside(cur_x, cur_y, control)
							&& isInside(press_x, press_y, control)) {
						control->func(i);
						flip = TRUE;
					}
				}
				if (bCancel->type == BUTTON && isInside(cur_x, cur_y, bCancel)
						&& isInside(press_x, press_y, bCancel)) {
					bCancel->func(TRUE);
					flip = TRUE;
				}

				break;

			case SDL_MOUSEMOTION:
				cur_x = event.button.x;
				cur_y = event.button.y;

				if (isInside(cur_x, cur_y, bCancel))
					loadBmpImg(&(bCancel->surf), bCancel->MarkedImgPath);
				else
					loadBmpImg(&(bCancel->surf), bCancel->basicImgPath);
				drawElement(bCancel);

				flip = TRUE;

				break;

			case (SDL_KEYUP):
				if (event.key.keysym.sym == SDLK_ESCAPE)
					quit = TRUE;
				break;

			default:
				break;
			}
		}
	}

	freeAllMemoryAndExit();
	return 1;
}

// FREE GUI
void freeAllMemoryAndExit() {
	freeMoves(&pMoves);
	freeGui();
	SDL_Quit();
	freeAllMemory();
}

void freeGui() {
	// free buttons/labels/panels under window
	freeControls(window);

	// set null pointers
	panels[GUI_MAIN] = NULL;
	panels[GUI_SETTINGS] = NULL;
	panels[GUI_SLOTS] = NULL;
	window = NULL;
}

void freeControls(struct control *curr) {
	if (curr == NULL)
		return;

	freeControls(curr->child);
	freeControls(curr->next);

	SDL_FreeSurface(curr->surf);

	free(curr);
}
int selectedQuit(int dummy) {
	freeAllMemoryAndExit();
	return 0;
}

void flipGui() {
	if (SDL_Flip(window->surf) == -1) { // perror
		fprintf(stderr, "ERROR: function SDL_Flip has failed: %s\n",
				SDL_GetError());
		freeAllMemoryAndExit();
	}
}

// CALCULATING POSITION
int mid_x(int outer_x, int outer_w, int inner_w) {
	return outer_x + outer_w / 2 - inner_w / 2;
}

int mid_y(int outer_y, int outer_h, int inner_h) {
	return outer_y + outer_h / 2 - inner_h / 2;
}
int offset_y(int from_y, int from_h, int offset, int height) {
	if (offset <= 0)
		return from_y + from_h + abs(offset);
	else
		return from_y - offset - height;
}
int isInside(int x, int y, control_t *control) {
	if (x < control->rect.x || x > control->rect.x + control->rect.w)
		return FALSE;
	if (y < control->rect.y || y > control->rect.y + control->rect.h)
		return FALSE;
	return TRUE;
}
void setButtonColorSetImg(game_buttons_t buttonType, int disableButton, int setPieces){

	if (buttonType == B_BLACK) {

			gameButtons[B_BLACK]->basicImgPath = "GameBMP/BlackG.bmp";
			gameButtons[B_BLACK]->MarkedImgPath = "GameBMP/BlackMarked.bmp";

		if(setPieces == TRUE)
			selectedPieceSetColor(pieceToSetColor);
	}
	if (buttonType == B_WHITE) {

			gameButtons[B_WHITE]->basicImgPath = "GameBMP/WhiteG.bmp";
			gameButtons[B_WHITE]->MarkedImgPath = "GameBMP/WhiteMarked.bmp";

		if(setPieces == TRUE)
			selectedPieceSetColor(pieceToSetColor);
	}
}

void updateGameButtonBMP(game_buttons_t buttonType, int disableButton) {
	if (buttonType == B_START) {
		if (FALSE == disableButton) {
			gameButtons[B_START]->basicImgPath = "GameBMP/startG.bmp";
			gameButtons[B_START]->MarkedImgPath = "GameBMP/startB.bmp";
		} else {
			gameButtons[B_START]->basicImgPath = "GameBMP/startU.bmp";
			gameButtons[B_START]->MarkedImgPath = "GameBMP/startU.bmp";
		}
		loadBmpImg(&(gameButtons[B_START]->surf),
				gameButtons[B_START]->basicImgPath);
		drawElement(gameButtons[B_START]);
	}
	if (buttonType == B_BEST_SET) {
		if (FALSE == disableButton) {
			gameButtons[B_BEST_SET]->basicImgPath = "GameBMP/bestG.bmp";
			gameButtons[B_BEST_SET]->MarkedImgPath = "GameBMP/bestB.bmp";
		} else {
			//swap to set piece
			gameButtons[B_BEST_SET]->basicImgPath = "GameBMP/setPieceG.bmp";
			gameButtons[B_BEST_SET]->MarkedImgPath = "GameBMP/setPieceB.bmp";
		}
		loadBmpImg(&(gameButtons[B_BEST_SET]->surf),
				gameButtons[B_BEST_SET]->basicImgPath);
		drawElement(gameButtons[B_BEST_SET]);
	}
	if (buttonType == B_CLEAR) {
		if (FALSE == disableButton) {
			gameButtons[B_CLEAR]->basicImgPath = "GameBMP/ClearBoardG.bmp";
			gameButtons[B_CLEAR]->MarkedImgPath = "GameBMP/ClearBoardB.bmp";
		} else {
			gameButtons[B_CLEAR]->basicImgPath = "GameBMP/ClearBoardU.bmp";
			gameButtons[B_CLEAR]->MarkedImgPath = "GameBMP/ClearBoardU.bmp";
		}
		loadBmpImg(&(gameButtons[B_CLEAR]->surf),
				gameButtons[B_CLEAR]->basicImgPath);
		drawElement(gameButtons[B_CLEAR]);

	}
	if (buttonType == B_SAVE) {
		if (FALSE == disableButton) {
			gameButtons[B_SAVE]->basicImgPath = "GameBMP/saveG.bmp";
			gameButtons[B_SAVE]->MarkedImgPath = "GameBMP/saveB.bmp";
		} else {
			gameButtons[B_SAVE]->basicImgPath = "GameBMP/saveU.bmp";
			gameButtons[B_SAVE]->MarkedImgPath = "GameBMP/saveU.bmp";
		}
		loadBmpImg(&(gameButtons[B_SAVE]->surf),
				gameButtons[B_SAVE]->basicImgPath);
		drawElement(gameButtons[B_SAVE]);
	}
	if (buttonType == B_REMOVE) {
		if (FALSE == disableButton) {
			gameButtons[B_REMOVE]->basicImgPath = "GameBMP/removeG.bmp";
			gameButtons[B_REMOVE]->MarkedImgPath = "GameBMP/removeB.bmp";
		} else {
			gameButtons[B_REMOVE]->basicImgPath = "GameBMP/removeU.bmp";
			gameButtons[B_REMOVE]->MarkedImgPath = "GameBMP/removeU.bmp";
		}
		loadBmpImg(&(gameButtons[B_REMOVE]->surf),
				gameButtons[B_REMOVE]->basicImgPath);
		drawElement(gameButtons[B_REMOVE]);
	}




}

void updateGamePiecesBMP(chessPieceKind_t pieceType, int disableButton) {
	//Pawn
	if (pieceType == PAWN) {
		if (TRUE == disableButton) {
			if (BLACK == pieceToSetColor) {
				gamePieces[PAWN]->basicImgPath = "GameBMP/bpbU.bmp";
				gamePieces[PAWN]->MarkedImgPath = "GameBMP/bpbU.bmp";
			} else {
				gamePieces[PAWN]->basicImgPath = "GameBMP/wpbU.bmp";
				gamePieces[PAWN]->MarkedImgPath = "GameBMP/wpbU.bmp";
			}
		} else {
			//swap to set piece
			gamePieces[PAWN]->basicImgPath = getBasicImgByKind(PAWN,
					pieceToSetColor, 0, 0);
			gamePieces[PAWN]->MarkedImgPath = getMarkedImgByKind(PAWN,
					pieceToSetColor, 0, 0);
		}
		loadBmpImg(&(gamePieces[PAWN]->surf), gamePieces[PAWN]->basicImgPath);
		drawElement(gamePieces[PAWN]);
	}
	//knight
	if (pieceType == KNIGHT) {
		if (TRUE == disableButton) {
			if (BLACK == pieceToSetColor) {
				gamePieces[KNIGHT]->basicImgPath = "GameBMP/bnbU.bmp";
				gamePieces[KNIGHT]->MarkedImgPath = "GameBMP/bnbU.bmp";
			} else {
				gamePieces[KNIGHT]->basicImgPath = "GameBMP/wnbU.bmp";
				gamePieces[KNIGHT]->MarkedImgPath = "GameBMP/wnbU.bmp";
			}
		} else {
			//swap to set piece
			gamePieces[KNIGHT]->basicImgPath = getBasicImgByKind(KNIGHT,
					pieceToSetColor, 0, 0);
			gamePieces[KNIGHT]->MarkedImgPath = getMarkedImgByKind(KNIGHT,
					pieceToSetColor, 0, 0);
		}
		loadBmpImg(&(gamePieces[KNIGHT]->surf),
				gamePieces[KNIGHT]->basicImgPath);
		drawElement(gamePieces[KNIGHT]);
	}
	//bishop
	if (pieceType == BISHOP) {
		if (TRUE == disableButton) {
			if (BLACK == pieceToSetColor) {
				gamePieces[BISHOP]->basicImgPath = "GameBMP/bbbU.bmp";
				gamePieces[BISHOP]->MarkedImgPath = "GameBMP/bbbU.bmp";
			} else {
				gamePieces[BISHOP]->basicImgPath = "GameBMP/wbbU.bmp";
				gamePieces[BISHOP]->MarkedImgPath = "GameBMP/wbbU.bmp";
			}
		} else {
			//swap to set piece
			gamePieces[BISHOP]->basicImgPath = getBasicImgByKind(BISHOP,
					pieceToSetColor, 0, 0);
			gamePieces[BISHOP]->MarkedImgPath = getMarkedImgByKind(BISHOP,
					pieceToSetColor, 0, 0);
		}
		loadBmpImg(&(gamePieces[BISHOP]->surf),
				gamePieces[BISHOP]->basicImgPath);
		drawElement(gamePieces[BISHOP]);
	}
	//rook
	if (pieceType == ROOK) {
		if (TRUE == disableButton) {
			if (BLACK == pieceToSetColor) {
				gamePieces[ROOK]->basicImgPath = "GameBMP/brbU.bmp";
				gamePieces[ROOK]->MarkedImgPath = "GameBMP/brbU.bmp";
			} else {
				gamePieces[ROOK]->basicImgPath = "GameBMP/wrbU.bmp";
				gamePieces[ROOK]->MarkedImgPath = "GameBMP/wrbU.bmp";
			}
		} else {
			//swap to set piece
			gamePieces[ROOK]->basicImgPath = getBasicImgByKind(ROOK,
					pieceToSetColor, 0, 0);
			gamePieces[ROOK]->MarkedImgPath = getMarkedImgByKind(ROOK,
					pieceToSetColor, 0, 0);
		}
		loadBmpImg(&(gamePieces[ROOK]->surf), gamePieces[ROOK]->basicImgPath);
		drawElement(gamePieces[ROOK]);
	}
	//queen
	if (pieceType == QUEEN) {
		if (TRUE == disableButton) {
			if (BLACK == pieceToSetColor) {
				gamePieces[QUEEN]->basicImgPath = "GameBMP/bqbU.bmp";
				gamePieces[QUEEN]->MarkedImgPath = "GameBMP/bqbU.bmp";
			} else {
				gamePieces[QUEEN]->basicImgPath = "GameBMP/wqbU.bmp";
				gamePieces[QUEEN]->MarkedImgPath = "GameBMP/wqbU.bmp";
			}
		} else {
			//swap to set piece
			gamePieces[QUEEN]->basicImgPath = getBasicImgByKind(QUEEN,
					pieceToSetColor, 0, 0);
			gamePieces[QUEEN]->MarkedImgPath = getMarkedImgByKind(QUEEN,
					pieceToSetColor, 0, 0);
		}
		loadBmpImg(&(gamePieces[QUEEN]->surf), gamePieces[QUEEN]->basicImgPath);
		drawElement(gamePieces[QUEEN]);
	}
	//king
	if (pieceType == KING) {
		if (TRUE == disableButton) {
			if (BLACK == pieceToSetColor) {
				gamePieces[KING]->basicImgPath = "GameBMP/bkbU.bmp";
				gamePieces[KING]->MarkedImgPath = "GameBMP/bkbU.bmp";
			} else {
				gamePieces[KING]->basicImgPath = "GameBMP/wkbU.bmp";
				gamePieces[KING]->MarkedImgPath = "GameBMP/wkbU.bmp";
			}
		} else {
			//swap to set piece
			gamePieces[KING]->basicImgPath = getBasicImgByKind(KING,
					pieceToSetColor, 0, 0);
			gamePieces[KING]->MarkedImgPath = getMarkedImgByKind(KING,
					pieceToSetColor, 0, 0);
		}
		loadBmpImg(&(gamePieces[KING]->surf), gamePieces[KING]->basicImgPath);
		drawElement(gamePieces[KING]);
	}
}

void selectButton(control_t** buttonArr, int i, int numOfbuttons) {
	for (int j = 0; j < numOfbuttons; j++) {
		loadBmpImg(&(buttonArr[j]->surf), buttonArr[j]->basicImgPath);
		if (j == i)
			loadBmpImg(&(buttonArr[i]->surf), buttonArr[i]->MarkedImgPath);
		drawElement(buttonArr[j]);
	}
}

int checkAccess(char* fName) {
	if (access(fName, F_OK) != -1)
		return 1; //file exict
	return 0;
}

void updateButtons(control_t *panel) {
	for (control_t *control = panel->child; control != NULL;
			control = control->next) {
		if (control->type == BUTTON) {
			if (control->func != NULL && control->func != gui) {
				if (control->func(TRUE))
					loadBmpImg(&(control->surf), control->MarkedImgPath);
				else if (control->type == BUTTON)
					loadBmpImg(&(control->surf), control->basicImgPath);
			}

		}
	}
}

control_t *newWindow(winSize_t height, winSize_t width) {

	control_t *window = (control_t*) calloc(1, sizeof(control_t));

	checkAllocError(window, "calloc");

	window->surf = SDL_SetVideoMode(width, height, 0,
	SDL_SWSURFACE);

	checkForSurfaceError(window); // perror

	window->type = WINDOW;
	window->rect.h = height;
	window->rect.w = width;

	/* Clear window to BLACK*/
	if (SDL_FillRect(window->surf, 0, 255) != 0)
		drawError(window);
	return window;
}

control_t *newButton(control_t * parent, char *image, char *imageMarked, int x,
		int y, int (*func)()) {

	control_t *button = newLabel(parent, image, x, y);
	button->basicImgPath = image;
	button->MarkedImgPath = imageMarked;
	button->type = BUTTON;
	button->func = func;

	return button;
}

control_t *newPanel(control_t * parent, char *image, int x, int y, int h, int w) {

	control_t *panel = newControl(parent, x, y, w, h);
	panel->type = PANEL;
	loadBmpImg(&(panel->surf), image);
	panel->basicImgPath = image;
	return panel;
}

void loadBmpImg(SDL_Surface **surf, char *imagePath) {
	SDL_FreeSurface(*surf);

	if ((*surf = SDL_LoadBMP(imagePath)) == NULL) { // perror
		fprintf(stderr,
				"Error: function SDL_LoadBMP has failed to load %s: %s\n",
				imagePath, SDL_GetError());
		freeAllMemoryAndExit();
	}
}

control_t *newLabel(control_t * parent, char *image, int x, int y) {

	control_t *label = newControl(parent, x, y, parent->rect.w, parent->rect.h);

	/*SDL_FreeSurface(lbl->surf);*/
	loadBmpImg(&(label->surf), image);

	label->type = LABEL;
	label->basicImgPath = image;
	checkForSurfaceError(label);

	return label;
}

control_t* newControl(control_t *parent, int x, int y, int w, int h) {

	control_t *current = (control_t*) calloc(1, sizeof(control_t));

	checkAllocError(current, "calloc");

	current->rect.x = x + parent->rect.x;
	current->rect.y = y + parent->rect.y;

	current->rect.h = MAX(0, MIN(h, parent->rect.h-y));
	current->rect.w = MAX(0, MIN(w, parent->rect.w-x));

	current->parent = parent;
	current->next = parent->child;
	parent->child = current;

	return current;
}

void checkForSurfaceError(control_t *control) { // perror
	if (control->type == BUTTON || control->type == LABEL) {
		if (control->surf == NULL) {
			fprintf(stderr,
					"ERROR: function SDL_Surface has failed to load image: %s\n",
					SDL_GetError());
			freeAllMemoryAndExit();
		}
	}

	else if (control->type == WINDOW) {
		if (window->surf == NULL) {
			fprintf(stderr,
					"ERROR: function SDL_Surface has failed to set video mode: %s\n",
					SDL_GetError());
			freeAllMemoryAndExit();
		}
	}
}

void drawError(control_t* cntrl) { // perror

	if (cntrl->type == PANEL)
		fprintf(stderr, "ERROR: function SDL_FillRect has failed: %s\n",
				SDL_GetError());
	else
		fprintf(stderr, "ERROR: function SDL_BlitSurface has failed: %s\n",
				SDL_GetError());

	freeAllMemoryAndExit();
}

void drawElement(control_t *cur) {

	SDL_Rect srcRect = { 0, 0, 0, 0 };
	srcRect.w = cur->rect.w;
	srcRect.h = cur->rect.h;

	if (SDL_BlitSurface(cur->surf, &srcRect, window->surf, &cur->rect) != 0)
		drawError(cur);

}

void draw(control_t *cur) {
	if (!cur)
		return;

	else if (cur->type != PANEL) {

		drawElement(cur);
	}

	else {
		if (SDL_FillRect(window->surf, &(cur->rect),
				SDL_MapRGB(window->surf->format, 255 * cur->color,
						255 * cur->color, 255 * cur->color)) != 0)
			drawError(cur);
	}

	draw(cur->child);
	draw(cur->next);
}

int insideButton(int x, int y, SDL_Rect* rect) {
	if ((x > (rect->x)) && (x < (rect->x + rect->w)) && (y > (rect->y))
			&& (y < (rect->y + rect->h)))
		return 1;
	return 0;
}

/*************************************************/

int showPieceMoves(int row, int col) {
//getmoves in consol
	chessPiece_t * pPiece = (*pBoard)[row][col];
	if ((pPiece = (*pBoard)[row][col]) == NULL)
		return FALSE;

// castling
	castling_t castling = isValidCastlingMove(pGame->turn);
	coord_t tmp_coord = { pPiece->coord.row, pPiece->coord.col };

	if (pPiece->kind == KING) {
		if (castling == CASTLE_KING_SIDE || castling == BOTH_SIDES) {
			tmp_coord.col = BOARD_SIZE - 1;
			pMoves = addMove(pMoves, newMove_c(tmp_coord, tmp_coord));
		}
		if (castling == CASTLE_QUEEN_SIDE || castling == BOTH_SIDES) {
			tmp_coord.col = 0;
			pMoves = addMove(pMoves, newMove_c(tmp_coord, tmp_coord));
		}
	}

	pMoves = getPieceMoves(pMoves, pPiece);
	markCells(TRUE);

	return TRUE;
}

int relativePos(int x) {
	return floor(x / CELL_SIZE);
}
bool_t inMoves(int row, int col) {
// recives two coords
//pMoves does not contains selected button
	if (pMoves == NULL)
		return FALSE;

//user pressed on the same piece that was selected before
	if (pMoves->srcCoord.row == row && pMoves->srcCoord.col == col)
		return TRUE;
// iterate over dst
	for (move_t * curMove = pMoves; curMove != NULL; curMove = curMove->next) {
		if (curMove->dstCoord.row == row && curMove->dstCoord.col == col)
			return TRUE;
	}
	return FALSE;
}

void markCell(int row, int col, int show) {
	if (row == -1 || col == -1)
		return;

	chessPiece_t *pPiece = (*pBoard)[row][col];
	int dstRow = BOARD_SIZE - row - 1;

	loadBmpImg(&((*guiBoard)[dstRow][col]->surf),
			show == TRUE ?
					getMarkedImgByPiece(pPiece, row, col) :
					getBasicImgByPiece(pPiece, row, col));
	drawElement((*guiBoard)[dstRow][col]);
}

void markCells(int show) {
	int dstRow = 0, DstCol = 0;
	chessPiece_t *pDstPiece = NULL;
	if (pMoves != NULL)
		markCell(pMoves->srcCoord.row, pMoves->srcCoord.col, show);
	for (move_t * curMove = pMoves; curMove != NULL; curMove = curMove->next) {
		dstRow = BOARD_SIZE - curMove->dstCoord.row - 1;
		DstCol = curMove->dstCoord.col;
		int srcRow = BOARD_SIZE - 1 - curMove->srcCoord.row;
		int srcCol = curMove->srcCoord.col;

		// castling
		if ((*pBoard)[curMove->dstCoord.row][DstCol] != NULL
				&& (*pBoard)[curMove->dstCoord.row][DstCol]->kind == ROOK //
				&& dstRow == srcRow && DstCol == srcCol) {
			// KING SIDE ROOK
			if (DstCol > 4) {
				loadBmpImg(&((*guiBoard)[srcRow][srcCol - 1]->surf),
						show == TRUE ?
								getMarkedImgByPiece(NULL, curMove->srcCoord.row,
										srcCol - 1) :
								getBasicImgByPiece(NULL, curMove->srcCoord.row,
										srcCol - 1));
				drawElement((*guiBoard)[srcRow][srcCol - 1]);
			}

			// QUEEN SIDE ROOK
			else {
				loadBmpImg(&((*guiBoard)[srcRow][srcCol + 2]->surf),
						show == TRUE ?
								getMarkedImgByPiece(NULL, curMove->srcCoord.row,
										srcCol + 2) :
								getBasicImgByPiece(NULL, curMove->srcCoord.row,
										srcCol + 2));
				drawElement((*guiBoard)[srcRow][srcCol + 2]);
			}
		} else {
			pDstPiece = (*pBoard)[curMove->dstCoord.row][DstCol];
			loadBmpImg(&((*guiBoard)[dstRow][DstCol]->surf),
					show == TRUE ?
							getMarkedImgByPiece(pDstPiece,
									curMove->dstCoord.row,
									curMove->dstCoord.col) :
							getBasicImgByPiece(pDstPiece, curMove->dstCoord.row,
									curMove->dstCoord.col));
			drawElement((*guiBoard)[dstRow][DstCol]);
		}
	}
}

int selectedPieceSettingsFunc(int dummy) {
// add new mark

	if(crdMousePos.row == prevMousePos.row && crdMousePos.col == prevMousePos.col){
		markCell(crdMousePos.row, crdMousePos.col, FALSE);
		prevMousePos.row = crdMousePos.row = -1;
		prevMousePos.col = crdMousePos.col = -1;
		return 0;
	}

	markCell(crdMousePos.row, crdMousePos.col, TRUE);
	if (prevMousePos.row != -1
			&& (*pBoard)[prevMousePos.row][prevMousePos.col] != NULL
			&& (crdMousePos.row != prevMousePos.row
					|| crdMousePos.col != prevMousePos.col)) {

		movePiece(prevMousePos, crdMousePos, TRUE);

		// remove old mark
		markCell(prevMousePos.row, prevMousePos.col, FALSE);

		// add new mark
		markCell(crdMousePos.row, crdMousePos.col, FALSE);

		prevMousePos.row = crdMousePos.row = -1;
		prevMousePos.col = crdMousePos.col = -1;
		return 0;
	}

// remove old mark
	if (prevMousePos.row != -1)
		markCell(prevMousePos.row, prevMousePos.col, FALSE);

	prevMousePos.row = crdMousePos.row;
	prevMousePos.col = crdMousePos.col;
	return 0;
}

int checkWinner() {
//return True if TIE OR MATE
	move_t* pMove = getAllMoves();
	int GameEnd = FALSE;
	if (checkmate(pMove)) {
		pGame->gameState = END;
		// disable all moves untill newgame/quit/mainmenu is done
		updateAllFuncCells(dummyFunc);
		//disable color choose func
		updateGameButtonBMP(B_BLACK, TRUE);
		updateGameButtonBMP(B_WHITE, TRUE);
		gameButtons[B_BLACK]->func = dummyFunc;
		gameButtons[B_WHITE]->func = dummyFunc;

		// change display func of best
		disablefunctions(TRUE);
		gameButtons[B_SAVE]->func = selectedSave;
		updateGameButtonBMP(B_SAVE, FALSE);

		//dsiable pieces
		for (int kind = 0; kind < 6; kind++) {
			gamePieces[kind]->func = dummyFunc;
			updateGamePiecesBMP(kind, TRUE);
		}

		// disable all functions
		updateMSG(
				otherColor(pGame->turn) == WHITE ?
						"GameBMP/msgboxWhiteWin.bmp" :
						"GameBMP/msgboxBlackWin.bmp");
		GameEnd = TRUE;
	} else if (pMove == NULL) {
		pGame->gameState = END;
		updateMSG("GameBMP/msgboxtie.bmp");
		GameEnd = TRUE;
	} else if (isThreatened(getPlayerByColor(pGame->turn)->pKing->coord))
		updateMSG("GameBMP/msgboxcheck.bmp");
	freeMoves(&pMove);
	return GameEnd;
}

bool_t isKingSelected(move_t* pMoves) {
	if (pMoves == NULL)
		return FALSE;

	coord_t kingCoord = (getPlayerByColor(pGame->turn))->pKing->coord;
	coord_t srcCoord = pMoves->srcCoord;
	coord_t dstCoord = pMoves->dstCoord;

	if (srcCoord.row == kingCoord.row && srcCoord.col == kingCoord.col)
		return TRUE;

	if (srcCoord.row == dstCoord.row && srcCoord.col == dstCoord.col)
		return TRUE;

	return FALSE;
}

int selectedPieceFunc(int move) {
// user selected a same piece as chosen - do nothing
	if (move == TRUE && (pMoves != NULL)
			&& pMoves->srcCoord.row == crdMousePos.row
			&& pMoves->srcCoord.col == crdMousePos.col)
		return 0;

// castling
	int row = pGame->turn == WHITE ? 0 : BOARD_SIZE - 1;
	castling_t castle = isValidCastlingMove();
	coord_t kingCoord = getPlayerByColor(pGame->turn)->pKing->coord;
	if (isKingSelected(pMoves) && kingCoord.row == row && kingCoord.col == 4
			&& castle != CANT_CASTLE) {

		// act normally if pressed a piece (for example the "bad" rook)
		chessPiece_t *pressedPiece = (*pBoard)[crdMousePos.row][crdMousePos.col];
		if (pressedPiece) {
			markCells(FALSE);
			freeMoves(&pMoves);
			showPieceMoves(crdMousePos.row, crdMousePos.col);
			return 1;
		}

		// if pressed castling cell (0/7,2) or (0/7,6)
		int col = -1, colQ = 2, colK = 6;

		// castle move
		if (crdMousePos.row == row) {
			// castle QUEEN side:
			if (crdMousePos.col == colQ
					&& (castle == CASTLE_QUEEN_SIDE || castle == BOTH_SIDES))
				col = 0;
			// castle KING side:
			else if (crdMousePos.col == colK
					&& (castle == CASTLE_KING_SIDE || castle == BOTH_SIDES))
				col = 7;

			if (col != -1) {
				castleMove((*pBoard)[row][col]);
				refreshGuiBoard(FALSE);
				flipGui();
				pGame->turn ^= 1;
				if (pGame->mode == PLAYER_VS_COMPUTER) {
					opponentMove();
					refreshGuiBoard(FALSE);
				}
				freeMoves(&pMoves);
				return 1;
			}
		}
	}

// user selected a move
	if (move == TRUE) {

		movePiece(pMoves->srcCoord, crdMousePos, TRUE);
		markCells(FALSE);

		// check promotion.
		if (pMoves->promotion != -1)
			guiPromotion();
		// user needs to select piece to set.
		// enable set piece to set to -1
		// disable all functions.

		updateCell(pMoves->srcCoord.row, pMoves->srcCoord.col); //update src
		updateCell(crdMousePos.row, crdMousePos.col); //update dst
		printBoard();

		flipGui();
		if (FALSE == promotionFlag) {
			//freeMoves(&pMoves);
			pGame->turn ^= 1;

			//delete msg
			loadBmpImg(&(gameButtons[B_MSGBOX]->surf),
					gameButtons[B_MSGBOX]->basicImgPath);
			drawElement(gameButtons[B_MSGBOX]);
			if (checkWinner() == FALSE) {
				flipGui();
				if (saveFlag == FALSE) {
					for (int i = 0; i < slotAmount; i++)
						slotButtons[i]->func = dummyFunc;
				}
				saveFlag = FALSE;

				if (pGame->mode == PLAYER_VS_COMPUTER) {
					opponentMove();
					refreshGuiBoard(FALSE);
					checkWinner();
				}
			} else
				flipGui();
		}
		freeMoves(&pMoves);
		return 1;
	}

//showPieceMoves of selected
	if (pMoves != NULL) {
		// uncheck mark all cells
		//markCells(FALSE);
		freeMoves(&pMoves);
	}
	refreshGuiBoard(FALSE);
	showPieceMoves(crdMousePos.row, crdMousePos.col);
	return 1;
}
int dummyFunc(int x) {
	return 0;
}

int selectedRemovePiece(int dummy) {
	if (crdMousePos.row == -1 || crdMousePos.col == -1)
		return 0;
// remove piece from pBoard
	rmPiece(crdMousePos.row, crdMousePos.col, TRUE);
// refresh cell
	updateCell(crdMousePos.row, crdMousePos.col);

//update varibles
	crdMousePos.row = crdMousePos.col = -1;
	prevMousePos.row = prevMousePos.col = -1;
	return 0;
}

int selectedClearBoard(int dummy) {
	clearBoard();
	for (int row = 0; row < BOARD_SIZE; row++) {
		for (int col = 0; col < BOARD_SIZE; col++)
			updateCell(row, col);
	}

	resetGlobalVariable();

	return 0;
}

int selectedNewGame(int dummy) {
	freeMoves(&pMoves);

	gameButtons[B_CLEAR]->func = selectedClearBoard;
	updateGameButtonBMP(B_CLEAR, FALSE);

	gameButtons[B_REMOVE]->func = selectedRemovePiece;
	updateGameButtonBMP(B_REMOVE, FALSE);

	gameButtons[B_START]->func = startGame;
	updateGameButtonBMP(B_START, FALSE);

	gameButtons[B_BEST_SET]->func = selectedSetPiece;
	updateGameButtonBMP(B_BEST_SET, TRUE);

	selectedPieceSetColor(pieceToSetColor);
	updateGameButtonBMP(B_BLACK, FALSE);
	updateGameButtonBMP(B_WHITE, FALSE);

//dsiable pieces
	for (int kind = 0; kind < 6; kind++) {
		gamePieces[kind]->func = selectedKindToSet;
		updateGamePiecesBMP(kind, FALSE);
	}
	for (int i = 0; i < slotAmount; i++)
		slotButtons[i]->func = dummyFunc;

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
	pGame->gameState = SETTINGS;
	pGame->turn = turn;
	pGame->user = playerColor;
	pGame->difficulty = diffMode;
	pGame->mode = gameMode;
	promotionFlag = FALSE;
	// hiding slots buttons
	loadBmpImg(&(gameButtons[B_MSGBOX]->surf),
			gameButtons[B_MSGBOX]->basicImgPath);
	saveFlag = FALSE;
	BestplayerVsPlayerFlag = FALSE;
	drawElement(gameButtons[B_MSGBOX]);

	//updatePieceSetColor();
	gameButtons[B_BLACK]->basicImgPath = "GameBMP/BlackG.bmp";
	gameButtons[B_BLACK]->MarkedImgPath = "GameBMP/BlackMarked.bmp";

	gameButtons[B_WHITE]->basicImgPath = "GameBMP/WhiteG.bmp";
	gameButtons[B_WHITE]->MarkedImgPath = "GameBMP/WhiteMarked.bmp";

	pieceToSetColor = WHITE;
	for (int kind = 0; kind < 6; kind++)
			updateGamePiecesBMP(kind, FALSE);

	loadBmpImg(&(gameButtons[B_BLACK]->surf), gameButtons[B_BLACK]->basicImgPath);
		loadBmpImg(&(gameButtons[B_WHITE]->surf), gameButtons[B_WHITE]->MarkedImgPath);


	updatePieceSetColor();

	//gameButtons[colorToSetUnMarked]->func = selectedPieceSetColor;

	//setButtonColorSetImg(B_BLACK,TRUE,FALSE);
//	setButtonColorSetImg(B_WHITE,TRUE,FALSE);

	updateAllFuncCells(selectedPieceSettingsFunc);
	resetGlobalVariable();

	return 0;
}

int getPieceKind(chessPiece_t* pPiece) {
	if (pPiece == NULL)
		return EMPTYCELL;
	return pPiece->kind;
}

void initGuiBoard() {
	int guiRow = 0, guiCol = 0;
	for (int row = 0; row < BOARD_SIZE; row++) {
		for (int col = 0; col < BOARD_SIZE; col++) {
			guiRow = BOARD_SIZE - 1 - row;
			guiCol = col;
			control_t *tmp = newButton(panels[GUI_GAME],
					getEmptyCell(guiRow, guiCol, FALSE),
					getEmptyCell(guiRow, guiCol, TRUE),
					OFFSET_BOARD + col * CELL_SIZE,
					2 * OFFSET_BOARD + row * CELL_SIZE,
					selectedPieceSettingsFunc);
			loadBmpImg(&(tmp->surf),
					getImg((*pBoard)[guiRow][col], guiRow, col, FALSE));
			(*guiBoard)[row][col] = tmp;
			drawElement(tmp);
		}
	}
}

void refreshGuiBoard(int updateToDummyF) {
//int guiRow = 0;
	for (int row = 0; row < BOARD_SIZE; row++) {
		for (int col = 0; col < BOARD_SIZE; col++) {
			updateCell(row, col);
			if (TRUE == updateToDummyF)
				updateFuncCell(row, col, dummyFunc);
		}
	}

	for (int kind = 0; kind < 6; kind++)
		updateGamePiecesBMP(kind, TRUE);
}
void updateFuncCell(int row, int col, int (*funcN)(int)) {
	int guiRow = BOARD_SIZE - row - 1;
	int guiCol = col;
	((*guiBoard)[guiRow][guiCol])->func = funcN;
}
void updateAllFuncCells(int (*funcN)(int)) {

	for (int row = 0; row < BOARD_SIZE; row++) {
		for (int col = 0; col < BOARD_SIZE; col++) {
			updateCell(row, col);
			updateFuncCell(row, col, funcN);

		}
	}
}

void updateCell(int row, int col) {
	int guiRow = BOARD_SIZE - row - 1;
	int guiCol = col;
	loadBmpImg(&(((*guiBoard)[guiRow][guiCol])->surf),
			getBasicImgByPiece((*pBoard)[row][col], row, col));
	drawElement((*guiBoard)[guiRow][guiCol]);
}

char* getImg(chessPiece_t *pPiece, int row, int col, int isMarked) {
	return isMarked ?
			getMarkedImgByPiece(pPiece, row, col) :
			getBasicImgByPiece(pPiece, row, col);
}
char* getEmptyCell(int row, int col, int Marked) {
	if (Marked == FALSE)
		return (row + col) % 2 == 0 ?
				b_p_b_arr[EMPTYCELL] : b_p_w_arr[EMPTYCELL];
	return (row + col) % 2 == 0 ?
			b_p_b_markArr[EMPTYCELL] : b_p_w_markArr[EMPTYCELL];
}

char* getBasicImgByPiece(chessPiece_t *pPiece, int row, int col) {
	chessPieceKind_t kind = getPieceKind(pPiece);

	if (pPiece == NULL)
		return (row + col) % 2 == 0 ? b_p_b_arr[kind] : b_p_w_arr[kind];

	return getBasicImgByKind(kind, pPiece->color, row, col);
}

char* getBasicImgByKind(chessPieceKind_t kind, color_t color, int row, int col) {
	if (color == WHITE)
		return (row + col) % 2 == 0 ? w_p_b_arr[kind] : w_p_w_arr[kind];

	return (row + col) % 2 == 0 ? b_p_b_arr[kind] : b_p_w_arr[kind];
}
char* getMarkedImgByPiece(chessPiece_t *pPiece, int row, int col) {
	chessPieceKind_t kind = getPieceKind(pPiece);

	if (pPiece == NULL)
		return (row + col) % 2 == 0 ? b_p_b_markArr[kind] : b_p_w_markArr[kind];

	return getMarkedImgByKind(kind, pPiece->color, row, col);

}
char* getMarkedImgByKind(chessPieceKind_t kind, color_t color, int row, int col) {
	if (color == WHITE)
		return (row + col) % 2 == 0 ? w_p_b_markArr[kind] : w_p_w_markArr[kind];

	return (row + col) % 2 == 0 ? b_p_b_markArr[kind] : b_p_w_markArr[kind];
}
/*************************************************/

int selectedSlot(int slot) {

	passed_Loading = WriteReadXML(XMLFNameARR[slot], READ);
//freeGui();
//panels[0] = panels[1] = panels[2] = NULL;
//memset(slotButtons, '\0', sizeof(control_t*) * 10);
	loadFlag = TRUE;
	guiSettings();

	return 0;
}

int selectedGamePvsP(int dummy) {
	gameMode = PLAYER_VS_PLAYER;
	return gameMode;
}
int selectedGamePvsc(int dummy) {
	gameMode = PLAYER_VS_COMPUTER;
	return gameMode;
}
int selectedPlayerColorW(int dummy) {
	playerColor = WHITE;
	return playerColor;
}
int selectedPlayerColorB(int dummy) {
	playerColor = BLACK;
	return playerColor;
}
int selectedTurnColorW(int dummy) {
	turn = WHITE;
	return turn;
}
int selectedTurnColorB(int dummy) {
	turn = BLACK;
	return turn;
}
int selectedDiff1(int dummy) {
	diffMode = 1;
	return diffMode;
}
int selectedDiff2(int dummy) {
	diffMode = 2;
	return diffMode;
}
int selectedDiff3(int dummy) {
	diffMode = 3;
	return diffMode;
}
int selectedDiff4(int dummy) {
	diffMode = 4;
	return diffMode;
}
int selectedDiff5(int dummy) {
	diffMode = BEST;
	return diffMode;
}

int selectedStart(int dummy) {
	char INIT_BOARD[BOARD_SIZE][BOARD_SIZE] = {	//
			/*    */{ 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R' }, //
					{ 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M' }, //
					{ '_', '_', '_', '_', '_', '_', '_', '_' }, //
					{ '_', '_', '_', '_', '_', '_', '_', '_' }, //
					{ '_', '_', '_', '_', '_', '_', '_', '_' }, //
					{ '_', '_', '_', '_', '_', '_', '_', '_' }, //
					{ 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm' }, //
					{ 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r' } }; //

	if ((FALSE == loadFlag) || (FALSE == passed_Loading))
		initGame(&INIT_BOARD);
	pGame->mode = gameMode;
	pGame->difficulty = diffMode;
	pGame->user = playerColor;
	pGame->turn = turn;
	printBoard();
	quit = FALSE;

	freeGui();
	guiGame();
	return 0;
}
void updateMSG(char * string) {
	loadBmpImg(&(gameButtons[B_MSGBOX]->surf), string);
	drawElement(gameButtons[B_MSGBOX]);
	flipGui();
}

int checkInitBoard(int color) {
// too many pieces of some kind
// max pieces possible of each kind
	int max[6];
	max[PAWN] = 8;
	max[ROOK] = 2;
	max[BISHOP] = 2;
	max[KNIGHT] = 2;
	max[QUEEN] = 1;
	max[KING] = 1;
	chessPlayer_t *pPlayer = getPlayerByColor(color);
	for (int i = 0; i < 6; i++) {
		if (pPlayer->numOfPiece[i] > max[i])
			return FALSE;

	}
	return TRUE;
}
int startGame(int dummy) {

// missing king
	if (pGame->pBlack->numOfPiece[KING] == 0
			|| pGame->pWhite->numOfPiece[KING] == 0
			|| checkInitBoard(BLACK) == FALSE
			|| checkInitBoard(WHITE) == FALSE) {
		printf(WROND_BOARD_INITIALIZATION);
		updateMSG("GameBMP/msgboxboardinit.bmp");
		return 0;
	}
	if(saveFlag == TRUE){
		saveFlag = FALSE;
		for(int i = 0 ;i < slotAmount ; i++)
			slotButtons[i]->func = dummyFunc;
	}

	// disable black/white pieces choice
	disablePieceSet();

//unable clear remove start buttons
	gameButtons[B_CLEAR]->func = dummyFunc;
	updateGameButtonBMP(B_CLEAR, TRUE);
	gameButtons[B_REMOVE]->func = dummyFunc;
	updateGameButtonBMP(B_REMOVE, TRUE);
	gameButtons[B_START]->func = dummyFunc;
	updateGameButtonBMP(B_START, TRUE);
	gameButtons[B_BEST_SET]->func = selectedBestMove;
	updateGameButtonBMP(B_BEST_SET, FALSE);

	//updateGameButtonBMP(B_BLACK, TRUE);
	//updateGameButtonBMP(B_WHITE, TRUE);
	//gameButtons[B_BLACK]->func = dummyFunc;
	//gameButtons[B_WHITE]->func = dummyFunc;

//dsiable pieces
	for (int kind = 0; kind < 6; kind++) {
		gamePieces[kind]->func = dummyFunc;
		updateGamePiecesBMP(kind, TRUE);
	}

// update cells function
	for (int row = 0; row < BOARD_SIZE; row++) {
		for (int col = 0; col < BOARD_SIZE; col++)
			updateFuncCell(row, col, selectedPieceFunc);
	}
// change game state
	pGame->gameState = PLAYING;
	updateMSG(gameButtons[B_MSGBOX]->basicImgPath);
	updateCastling();

	checkWinner();

// make move
	if (pGame->mode == PLAYER_VS_COMPUTER && pGame->turn != pGame->user)
		opponentMove();

	refreshGuiBoard(FALSE);
	resetGlobalVariable();
	return 0;
}

int selectedMainMenu(int dummy) {
	if (pMoves != NULL)
		freeMoves(&pMoves);
	pGame->mode = gameMode;
	pGame->difficulty = diffMode;
	pGame->user = playerColor;
	pGame->turn = turn;
	pGame->gameState = SETTINGS;

	freeGui();
	panels[GUI_GAME] = NULL;

	promotionFlag = FALSE;
	clearBoard();
	resetGlobalVariable();
	quit = FALSE;
	gui();
	return 0;
}


void selectedBestByDepth(int minimaxDepth) {
	move_t *pMove = getBestMoves(minimaxDepth);
	move_t *pBest = chooseRandomBestMove(pMove);

	selectedPieceSetColor(pGame->turn);

	//updateGameButtonBMP(B_BLACK, TRUE);
		//updateGameButtonBMP(B_WHITE, TRUE);
		gameButtons[B_BLACK]->func = dummyFunc;
		gameButtons[B_WHITE]->func = dummyFunc;

	//dsiable pieces
		for (int kind = 0; kind < 6; kind++) {
			gamePieces[kind]->func = dummyFunc;
			updateGamePiecesBMP(kind, TRUE);
		}


		pieceToSetColor = pGame->turn;
	for (int kind = 0; kind < 6; kind++){
		updateGamePiecesBMP(kind, TRUE);
	}
	if (pBest->promotion != -1){
		updateGamePiecesBMP(pBest->promotion, FALSE);
	}

	markCell(pBest->srcCoord.row, pBest->srcCoord.col, TRUE);
	markCell(pBest->dstCoord.row, pBest->dstCoord.col, TRUE);

	crdMousePos.row = crdMousePos.col = -1;
//	pieceToSetColor =-1;
	freeMoves(&pMoves);
	freeMoves(&pMove);

}
int selectedBestPlayerVsPlayer(int minimaxDepth) {
	// hide diff
	for (int i = 0; i < 5; i++)
		diff[i]->func = dummyFunc;

	selectedBestByDepth(minimaxDepth + 1);
	BestplayerVsPlayerFlag = FALSE;

	loadBmpImg(&(gameButtons[B_MSGBOX]->surf),
			gameButtons[B_MSGBOX]->basicImgPath);
	BestplayerVsPlayerFlag = FALSE;
	drawElement(gameButtons[B_MSGBOX]);

	return 1;
}
int selectedBestMove(int dummy) {
	refreshGuiBoard(FALSE);

	if (pGame->mode == PLAYER_VS_COMPUTER)
		selectedBestByDepth(pGame->difficulty);
	// player vs player
	else {
		BestplayerVsPlayerFlag ^= 1;
		//update to select a slot
		BestplayerVsPlayerFlag == TRUE ?
				loadBmpImg(&(gameButtons[B_MSGBOX]->surf),
						"GameBMP/msgdiffminimax.bmp") :
				loadBmpImg(&(gameButtons[B_MSGBOX]->surf),
						gameButtons[B_MSGBOX]->basicImgPath);
		drawElement(gameButtons[B_MSGBOX]);

		//show diff
		for (int i = 0; i < 5; i++) {
			if (BestplayerVsPlayerFlag == TRUE) {
				loadBmpImg(&(diff[i]->surf), diff[i]->MarkedImgPath);
				drawElement(diff[i]);
				diff[i]->func = selectedBestPlayerVsPlayer;

			} else {
				loadBmpImg(&(gameButtons[B_MSGBOX]->surf),
						gameButtons[B_MSGBOX]->basicImgPath);
				drawElement(gameButtons[B_MSGBOX]);
				slotButtons[i]->func = dummyFunc;
			}
		}
	}
	return 0;
}

int selectedPieceSetColor(int color) {
	pieceToSetColor = color;

	updatePieceSetColor();
	updateAllPiecesChoiceImg();

	return 0;
}

void disablePieceSet() {
	gameButtons[B_BLACK]->basicImgPath = "GameBMP/BlackU.bmp";
	gameButtons[B_BLACK]->MarkedImgPath = "GameBMP/BlackU.bmp";
	loadBmpImg(&(gameButtons[B_BLACK]->surf),
			gameButtons[B_BLACK]->MarkedImgPath);
	drawElement(gameButtons[B_BLACK]);
	gameButtons[B_BLACK]->func = dummyFunc;

	gameButtons[B_WHITE]->basicImgPath = "GameBMP/WhiteU.bmp";
	gameButtons[B_WHITE]->MarkedImgPath = "GameBMP/WhiteU.bmp";
	loadBmpImg(&(gameButtons[B_WHITE]->surf),
				gameButtons[B_WHITE]->MarkedImgPath);
	drawElement(gameButtons[B_WHITE]);
	gameButtons[B_WHITE]->func = dummyFunc;
}

void enablePieceSet() {

}
void updatePieceSetColor() {
	int colorToSetMarked = pieceToSetColor == BLACK ? B_BLACK : B_WHITE;
	int colorToSetUnMarked = pieceToSetColor == BLACK ? B_WHITE : B_BLACK;

// change display func
	loadBmpImg(&(gameButtons[colorToSetMarked]->surf),
			gameButtons[colorToSetMarked]->MarkedImgPath);
	drawElement(gameButtons[colorToSetMarked]);
	gameButtons[colorToSetMarked]->func = dummyFunc;

	loadBmpImg(&(gameButtons[colorToSetUnMarked]->surf),
			gameButtons[colorToSetUnMarked]->basicImgPath);
	drawElement(gameButtons[colorToSetUnMarked]);
	gameButtons[colorToSetUnMarked]->func = selectedPieceSetColor;
	KindPieceToSet = -1;
}
void updatePieceChoiceImg(control_t* bPiece, chessPieceKind_t kind) {
	bPiece->MarkedImgPath = getMarkedImgByKind(kind, pieceToSetColor, 0, 0);
	bPiece->basicImgPath = getBasicImgByKind(kind, pieceToSetColor, 0, 0);
	loadBmpImg(&(bPiece->surf), bPiece->basicImgPath);
	drawElement(bPiece);
}

int updateAllPiecesChoiceImg() {
	updatePieceChoiceImg(gamePieces[PAWN], PAWN);
	updatePieceChoiceImg(gamePieces[KNIGHT], KNIGHT);
	updatePieceChoiceImg(gamePieces[BISHOP], BISHOP);
	updatePieceChoiceImg(gamePieces[ROOK], ROOK);
	updatePieceChoiceImg(gamePieces[QUEEN], QUEEN);
	updatePieceChoiceImg(gamePieces[KING], KING);

	return 0;
}

int selectedKindToSet(int kind) {
	KindPieceToSet = kind;
	if (kind != -1) {
		updateAllPiecesChoiceImg();
		loadBmpImg(&(gamePieces[kind]->surf), gamePieces[kind]->MarkedImgPath);
		drawElement(gamePieces[kind]);
	}
	return 0;
}
void resetGlobalVariable() {
	KindPieceToSet = -1;
	crdMousePos.row = -1;
	crdMousePos.col = -1;
	prevMousePos.row = -1;
	prevMousePos.col = -1;
}
int selectedSetPiece(int dummy) {
	if (KindPieceToSet == -1
			|| (crdMousePos.row == -1 && crdMousePos.col == -1))
		return 0;
// set piece

	setPiece(extractPieceChar(KindPieceToSet, pieceToSetColor), crdMousePos.row,
			crdMousePos.col);
	updateCell(crdMousePos.row, crdMousePos.col);
	crdMousePos.row = crdMousePos.col = -1;
	prevMousePos.row = prevMousePos.col = -1;
	return 0;
}
void disablefunctions(int disableB) {

//best

	if (FALSE == disableB) {
		gameButtons[B_BEST_SET]->basicImgPath = "GameBMP/bestG.bmp";
		gameButtons[B_BEST_SET]->MarkedImgPath = "GameBMP/bestB.bmp";
	} else {
		//swap to set piece
		gameButtons[B_BEST_SET]->basicImgPath = "GameBMP/bestU.bmp";
		gameButtons[B_BEST_SET]->MarkedImgPath = "GameBMP/bestU.bmp";
	}
	loadBmpImg(&(gameButtons[B_BEST_SET]->surf),
			gameButtons[B_BEST_SET]->basicImgPath);
	drawElement(gameButtons[B_BEST_SET]);
	gameButtons[B_BEST_SET]->func =
			disableB == TRUE ? dummyFunc : selectedBestMove;

	gameButtons[B_SAVE]->func = disableB == TRUE ? dummyFunc : selectedSave;
	updateGameButtonBMP(B_SAVE, disableB);

}
void guiPromotion() {
// enable color in promotion

	promotionFlag = TRUE;
	pieceToSetColor = pGame->turn;

// change display func
	disablefunctions(TRUE);

//dsiable pieces
	for (int kind = 0; kind < 6; kind++) {
		if (kind == BISHOP || kind == QUEEN || kind == KNIGHT || kind == ROOK) {
			gamePieces[kind]->func = selectedKindToPromotion;
			updateGamePiecesBMP(kind, FALSE);
		} else {
			gamePieces[kind]->func = dummyFunc;
			updateGamePiecesBMP(kind, TRUE);
		}
	}
//	gameButtons[B_BLACK]->func = dummyFunc;
	//gameButtons[B_WHITE]->func = dummyFunc;

// disable all moves untill promotion is done
	updateAllFuncCells(dummyFunc);

// enable pieces set piece to set to -1*/
}
int selectedKindToPromotion(int kind) {

// change piece promotion to choosen one
/*	if (kind == KNIGHT)
		setPiece(extractPieceChar(KNIGHT, pGame->turn), pMoves->dstCoord.row,
				pMoves->dstCoord.col);

	if (kind == BISHOP)
		setPiece(extractPieceChar(BISHOP, pGame->turn), pMoves->dstCoord.row,
				pMoves->dstCoord.col);

	if (kind == ROOK)
		setPiece(extractPieceChar(ROOK, pGame->turn), pMoves->dstCoord.row,
				pMoves->dstCoord.col);

	if (kind == QUEEN)
		setPiece(extractPieceChar(QUEEN, pGame->turn), pMoves->dstCoord.row,
				pMoves->dstCoord.col);
*/
	if (kind == KNIGHT)
	setPiece(extractPieceChar(KNIGHT, pGame->turn), crdMousePos.row,
			crdMousePos.col);

if (kind == BISHOP)
	setPiece(extractPieceChar(BISHOP, pGame->turn), crdMousePos.row,
			crdMousePos.col);

if (kind == ROOK)
	setPiece(extractPieceChar(ROOK, pGame->turn), crdMousePos.row,
			crdMousePos.col);

if (kind == QUEEN)
	setPiece(extractPieceChar(QUEEN, pGame->turn), crdMousePos.row,
			crdMousePos.col);

	promotionFlag = FALSE;

//update function back
	color_t color = pGame->turn;

	int colorToSetMarked = color == BLACK ? B_BLACK : B_WHITE;
	int colorToSetUnMarked = color == BLACK ? B_WHITE : B_BLACK;

	updateGameButtonBMP(colorToSetMarked, TRUE);
	updateGameButtonBMP(colorToSetUnMarked, TRUE);
	gameButtons[B_BLACK]->func = dummyFunc;
	gameButtons[B_WHITE]->func = dummyFunc;

	disablefunctions(FALSE);
	updateAllFuncCells(selectedPieceFunc);
//dsiable pieces
	for (int kind = 0; kind < 6; kind++) {
		gamePieces[kind]->func = dummyFunc;
		updateGamePiecesBMP(kind, TRUE);
	}
//free moves
	freeMoves(&pMoves);

	resetGlobalVariable();

	pGame->turn ^= 1;

	if (checkWinner() == FALSE) {

		//if (pGame->mode == PLAYER_VS_PLAYER)
			//pGame->turn ^= 1;
		if (pGame->mode == PLAYER_VS_COMPUTER) {
			//pGame->turn ^= 1;
			opponentMove();
			refreshGuiBoard(FALSE);
		}
	}
	return 1;
}
int selectedSaveSlot(int slot) {
	int passed_saving = WriteReadXML(XMLFNameARR[slot], WRITE);
	passed_saving == TRUE ?
			loadBmpImg(&(gameButtons[B_MSGBOX]->surf),
					"GameBMP/msgBoxEsaved.bmp") :
			loadBmpImg(&(gameButtons[B_MSGBOX]->surf),
					"GameBMP/msgBoxEerrorsave.bmp");
	drawElement(gameButtons[B_MSGBOX]);
//close slots
	for (int i = 0; i < slotAmount; i++)
		slotButtons[i]->func = dummyFunc;
	saveFlag = FALSE;
	msgShow = TRUE;
	return 0;
}

int selectedSave(int slot) {

	saveFlag ^= 1;
//update to select a slot
	saveFlag == TRUE ?
			loadBmpImg(&(gameButtons[B_MSGBOX]->surf),
					"GameBMP/msgBoxEsave.bmp") :
			loadBmpImg(&(gameButtons[B_MSGBOX]->surf),
					gameButtons[B_MSGBOX]->basicImgPath);
	drawElement(gameButtons[B_MSGBOX]);

//go over slots and update to show only availble slots.
	for (int i = 0; i < slotAmount; i++) {
		if (saveFlag == TRUE) {
			checkAccess(XMLFNameARR[i]) == TRUE ?
					loadBmpImg(&(slotButtons[i]->surf),
							slotButtons[i]->MarkedImgPath) :
					loadBmpImg(&(slotButtons[i]->surf),
							slotButtons[i]->basicImgPath);
			drawElement(slotButtons[i]);
			slotButtons[i]->func = selectedSaveSlot;
		} else {
			loadBmpImg(&(gameButtons[B_MSGBOX]->surf),
					gameButtons[B_MSGBOX]->basicImgPath);
			drawElement(gameButtons[B_MSGBOX]);
			slotButtons[i]->func = dummyFunc;
		}
	}
	msgShow = TRUE;
	return 0;
}

