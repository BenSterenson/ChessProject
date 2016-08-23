/*
 * Chess.c
 *
 *  Created on: Aug 22, 2015
 *      Author: bensterenson
 */

#define _CRT_SECURE_NO_WARNINGS

#include "Chess.h"

#define WINDOWS_STR_CMP _stricmp
#define LINUX_STR_CMP strcasecmp
#define STR_CMP(x,y) LINUX_STR_CMP(x,y)
//TODO---- choose windows/linux
#define DEBUG

int main(int argc, char *argv[]) {
	newGame();
	printBoard();

	if (argc == 2 && strcmp(argv[1], "gui") == 0) {
		gui();
	}
	// create the board of your dreams!
	char my_board[BOARD_SIZE][BOARD_SIZE] = {
	/* 8 */{ '_', 'R', '_', '_', '_', '_', '_', '_' },
	/* 7 */{ 'K', '_', 'm', '_', '_', '_', 'r', '_' },
	/* 6 */{ 'M', '_', 'k', 'M', '_', '_', '_', '_' },
	/* 5 */{ 'm', '_', 'N', '_', '_', '_', '_', '_' },
	/* 4 */{ '_', '_', '_', '_', '_', '_', '_', '_' },
	/* 3 */{ '_', '_', '_', '_', '_', '_', '_', '_' },
	/* 2 */{ '_', '_', '_', '_', '_', '_', '_', '_' },
	/* 1 */{ '_', '_', '_', '_', '_', '_', '_', '_' }
	/*        a    b    c    d    e    f    g    h  */
	};

	/*
	 pGame->mode = 2;
	 pGame->user = WHITE;
	 pGame->gameState = PLAYING;
	 pGame->turn = BLACK;
	 */

	if (my_board[0][0] == 'x') {
		initGame(&my_board);
		printBoard();
	}

	while (pGame->gameState != END)
		getCommands();

	freeAllMemory();
	return 0;
}

void ReadInput(char *input) {
	char c;
	unsigned int i = 0;
	//accept user input until end of file
	while ((c = getchar()) != '\n')
		input[i++] = c;

	input[i] = '\0';
}

color_t extractColor(char *color_str) {
	if (STR_CMP(color_str, "black") == 0)
		return BLACK;

	else if (STR_CMP(color_str, "white") == 0)
		return WHITE;

	else if (strcmp(color_str, "") == 0)
		return WHITE;

	return -1;
}

void extractCoord(char *string, coord_t *coord) {
	int row, col;
	char *token;
	if (string == NULL) {
		coord->row = coord->col = -1;
		return;
	}

	token = strtok(string, " <>,");

	if (*token - 'a' >= BOARD_SIZE || *token - 'a' < 0) {
		printf(WRONG_POSITION);
		coord->row = coord->col = -1;
		return;
	}
	col = *token - 'a';

	token = strtok(NULL, " <>,");
	if (atoi(token) > BOARD_SIZE || atoi(token) < 1) {
		printf(WRONG_POSITION);
		coord->row = coord->col = -1;
		return;
	}
	row = atoi(token) - 1;
	coord->row = row;
	coord->col = col;
}

command_t extractCommand(char *input_buffer, char **parameters) {
	char *token = strtok(input_buffer, " ");
	command_t command = stringToCommand(token);
	int i = 0;

	for (token = strtok(NULL, " "); token != NULL && i < 5;
			token = strtok(NULL, " "), i++) {
		if (STR_CMP(token, "to") != 0)
			*(parameters + i) = (char*) token;
		else
			i--;
	}
	return command;
}

move_t * chooseRandomBestMove(move_t* pMove) {
	// calling function should free pointer to first move
	if (pMove == NULL)
		return NULL;

	// count number of moves with highest score
	move_t* curMove = pMove;
	int countBestMove, bestScore;
	for (curMove = pMove, countBestMove = 0, bestScore = pMove->score;
			curMove != NULL && curMove->score == bestScore;
			countBestMove++, curMove = curMove->next)
		;

	// choose a random move between best moves
	int randomMove = (rand() % countBestMove) + 1;
	for (curMove = pMove, countBestMove = 1;
			curMove != NULL && randomMove != countBestMove;
			curMove = curMove->next, countBestMove++)
		;

	// free moves that come after the selected move
	freeMoves(&(curMove->next));
	curMove->next = NULL;

	return curMove;
}

void opponentMove() {
	move_t *pMoves, *bestMove;
	pMoves = getBestMoves(pGame->difficulty);
	bestMove = chooseRandomBestMove(pMoves);

	// castling
	if (bestMove->srcCoord.row == bestMove->dstCoord.row
			&& bestMove->srcCoord.col == bestMove->dstCoord.col) {
		castleMove((*pBoard)[bestMove->srcCoord.row][bestMove->srcCoord.col]);
		printf("Computer: castle <%c,%d>\n", //
				bestMove->srcCoord.col + 'a', //
				bestMove->srcCoord.row + 1);
	}

	// regular move
	else {
		movePiece(bestMove->srcCoord, bestMove->dstCoord, TRUE);
		promotion(bestMove->promotion, bestMove->dstCoord);
		printf("Computer: move <%c,%d> to <%c,%d>", //
				bestMove->srcCoord.col + 'a', //
				bestMove->srcCoord.row + 1, //
				bestMove->dstCoord.col + 'a', //
				bestMove->dstCoord.row + 1);

		bestMove->promotion == -1 ? //
		printf("\n") : printf("%s\n", kindToString(bestMove->promotion));
	}

	freeMoves(&pMoves);
	pGame->turn ^= 1;
	printBoard();
}

void getCommands() {
	command_t command;
	char input_buffer[51];
	char* parameters[5] = { NULL, NULL, NULL, NULL, NULL };

	while (pGame->gameState != END) {

		// "enter settings"
		if (pGame->gameState == SETTINGS)
			printf(ENTER_SETTINGS);

		// "enter your move"
		else if (pGame->mode == PLAYER_VS_PLAYER || pGame->turn == pGame->user)
			printf("%s player - enter your move:\n",
					pGame->turn == WHITE ? "White" : "Black");

		// get user's input
		if (pGame->gameState == SETTINGS || pGame->mode == PLAYER_VS_PLAYER
				|| pGame->turn == pGame->user) {
			ReadInput((char*) input_buffer);
			if (input_buffer[0] == '\0')
				continue;

			command = extractCommand((char*) input_buffer,
					(char**) &parameters);
			executeCommand(command, (char**) &parameters);
		}

		// computer's turn
		else {
			opponentMove();
			if (printWinner() == -1) // check
				printf("Check!\n");

		}
	}
}

int printWinner() {
	// returns -1 for check, 0 otherwise.

	move_t* pMoves = getAllMoves();
	if (checkmate(pMoves)) {
		pGame->gameState = END;
		printf("Mate! %s player wins the game\n",
		otherColor(pGame->turn) == WHITE ? "White" : "Black");
	} else if (pMoves == NULL) {
		pGame->gameState = END;
		printf(TIE);
	} else if (pGame->gameState == PLAYING
			&& isThreatened(getPlayerByColor(pGame->turn)->pKing->coord))
		return -1;

	freeMoves(&pMoves);
	return 0;
}

int isValidCommand(command_t command) {

	// commands 0-10 are settings (including QUIT)
	if (pGame->gameState == SETTINGS) {
		if (command < 0 || command > 10)
			return 0;
		return 1;
	}

	// commands 10-16 are game (including QUIT)
	if (pGame->gameState == PLAYING) {
		if (command < 10 || command > 16)
			return 0;
		return 1;
	}
	return 0;
}

void executeCommand(command_t command, char **parameters) {
	coord_t tmp_coord, dest_coord;
	color_t tmp_color;
	char tmp_char;
	chessPieceKind_t tmp_kind;
	move_t *moveList;
	chessPiece_t *tmp_piece;
	int depth;

	if (!isValidCommand(command)) {
		printf(ILLEGAL_COMMAND);
		return;
	}

	switch (command) {

	case SET_GAME_MODE:
		if (strcmp(parameters[0], "1") == 0) {
			pGame->mode = PLAYER_VS_PLAYER;
			printf(TWO_PLAYERS_GAME_MODE);
		}

		else if (strcmp(parameters[0], "2") == 0) {
			pGame->mode = PLAYER_VS_COMPUTER;
			printf(PLAYER_VS_AI_GAME_MODE);
		}

		else
			printf(WRONG_GAME_MODE);

		break;

	case SET_DIFFICULTY:
		if (pGame->mode != PLAYER_VS_COMPUTER)
			printf(ILLEGAL_COMMAND);

		else if (STR_CMP(parameters[0], "best") == 0)
			pGame->difficulty = BEST;

		else if (STR_CMP(parameters[0], "depth") == 0) {
			int num;
			if (strlen(parameters[1]) == 1
					&& ((num = atoi(parameters[1])) <= 4 && num > 0))
				pGame->difficulty = num;
			else
				printf(WRONG_MINIMAX_DEPTH);
		}

		else
			printf(WRONG_MINIMAX_DEPTH);
		break;

	case SET_USER_COLOR:
		if (pGame->mode != PLAYER_VS_COMPUTER)
			printf(ILLEGAL_COMMAND);

		else if (STR_CMP(parameters[0], "white") == 0)
			pGame->user = WHITE;

		else if (STR_CMP(parameters[0], "black") == 0)
			pGame->user = BLACK;

		else
			printf(ILLEGAL_COMMAND);
		break;

	case SET_LOAD:
		if (WriteReadXML(parameters[0], READ) == PASSED)
			printBoard();
		break;

	case SET_CLEAR:
		clearBoard();
		break;

	case SET_NEXT_PLAYER:
		if (STR_CMP(parameters[0], "white") == 0)
			pGame->turn = WHITE;

		else if (STR_CMP(parameters[0], "black") == 0)
			pGame->turn = BLACK;

		else
			printf(ILLEGAL_COMMAND);
		break;

	case SET_RM:
		extractCoord(parameters[0], &tmp_coord);

		if (tmp_coord.row != -1)
			rmPiece_c(tmp_coord, TRUE);
		break;

	case SET_SET:
		extractCoord(parameters[0], &tmp_coord);
		if (tmp_coord.row == -1)
			break;

		tmp_color = extractColor(parameters[1]);
		if (tmp_color == -1) {
			printf(ILLEGAL_COMMAND);
			break;
		}

		tmp_kind = extractKind(parameters[2]);
		if (tmp_kind == -1) {
			printf(ILLEGAL_COMMAND);
			break;
		}

		if (maxPiecesReached(tmp_kind, tmp_color, &tmp_coord)) {
			printf(NO_PIECE);
			break;
		}
		tmp_char = extractPieceChar(tmp_kind, tmp_color);
		setPiece_c(tmp_char, &tmp_coord);
		break;

	case SET_PRINT:
		printBoard();
		break;

	case SET_START:
		if (pGame->pBlack->numOfPiece[KING] == 0
				|| pGame->pWhite->numOfPiece[KING] == 0) {
			printf(WROND_BOARD_INITIALIZATION);
			break;
		}
		pGame->gameState = PLAYING;
		break;

	case QUIT:
		freeAllMemory();
		exit(0);
		break;

	case GAME_MOVE:

		//coord extraction
		extractCoord(parameters[0], &tmp_coord);
		extractCoord(parameters[1], &dest_coord);

		if (tmp_coord.row == -1 || dest_coord.row == -1)
			break;

		if (isValidMove(&tmp_coord, &dest_coord)) {
			movePiece(tmp_coord, dest_coord, TRUE);

			tmp_kind = extractKind(parameters[2]);
			promotion(tmp_kind, dest_coord);

			printBoard();
			pGame->turn ^=1;
			if (printWinner() == -1) // check
				printf("Check!\n");
		}
		break;

	case GAME_GET_MOVES:
		moveList = NULL;
		extractCoord(parameters[0], &tmp_coord);
		if (tmp_coord.row == -1)
			break;

		tmp_piece = (*pBoard)[tmp_coord.row][tmp_coord.col];
		if (tmp_piece == NULL || tmp_piece->color != pGame->turn) {
			printf(WRONG_PIECE_SELECTION);
			break;
		}

		moveList = getPieceMoves(moveList, tmp_piece);

		// castling
		castling_t castling = isValidCastlingMove(pGame->turn);
		int row = pGame->turn == BLACK ? BOARD_SIZE - 1 : 0;
		coord_t tmp_coord = { tmp_piece->coord.row, tmp_piece->coord.col };

		if (tmp_piece->kind == KING) {
			if (castling == CASTLE_KING_SIDE || castling == BOTH_SIDES) {
				tmp_coord.col = BOARD_SIZE - 1;
				moveList = addMove(moveList, newMove_c(tmp_coord, tmp_coord));
			}
			if (castling == CASTLE_QUEEN_SIDE || castling == BOTH_SIDES) {
				tmp_coord.col = 0;
				moveList = addMove(moveList, newMove_c(tmp_coord, tmp_coord));
			}
		}

		else if (tmp_piece->kind == ROOK) {

			// king side rook
			if (tmp_coord.row == row && tmp_coord.col == BOARD_SIZE - 1
					&& (castling == CASTLE_KING_SIDE || castling == BOTH_SIDES))
				moveList = addMove(moveList, newMove_c(tmp_coord, tmp_coord));

			// queen side rook
			else if (tmp_coord.row == row && tmp_coord.col == 0
					&& (castling == CASTLE_QUEEN_SIDE || castling == BOTH_SIDES))
				moveList = addMove(moveList, newMove_c(tmp_coord, tmp_coord));
		}

		printAllMoves(moveList);
		freeMoves(&moveList);
		break;

	case GAME_GET_BEST_MOVES:
		if (STR_CMP(parameters[0], "best") == 0)
			depth = BEST;

		else
			depth = atoi(parameters[0]);

		moveList = getBestMoves(depth);

		printAllMoves(moveList);
		freeMoves(&moveList);
		break;

	case GAME_GET_SCORE:

		if (STR_CMP(parameters[0], "best") == 0)
			depth = BEST;

		else
			depth = atoi(parameters[0]);

		//coord extraction
		extractCoord(parameters[2], &tmp_coord);
		if (STR_CMP(parameters[1], "castle") == 0) {
			dest_coord.col = tmp_coord.col;
			dest_coord.row = tmp_coord.row;
		} else if (STR_CMP(parameters[1], "move") == 0) {
			extractCoord(parameters[3], &dest_coord);
		}
		tmp_kind = extractKind(parameters[4]);
		move_t tmpMove = { tmp_coord, dest_coord, 0, tmp_kind };

		scoreMove_depth(&tmpMove, depth);
		printf("%d\n", tmpMove.score);
		break;

	case GAME_SAVE:
		WriteReadXML(parameters[0], WRITE);
		break;

	case GAME_CASTLE:
		extractCoord(parameters[0], &tmp_coord);
		if (tmp_coord.row == -1)
			break;

		tmp_piece = (*pBoard)[tmp_coord.row][tmp_coord.col];

		// doesn't contain your piece
		if (tmp_piece == NULL || tmp_piece->color != pGame->turn) {
			printf(WRONG_PIECE_SELECTION);
			break;
		}

		// if not a rook
		if (tmp_piece->kind != ROOK) {
			printf(WRONG_ROOK_POSITION);
			break;
		}

		int res = isValidCastlingMove(pGame->turn);
		int row2 = tmp_piece->color == WHITE ? 0 : 7;

		if (tmp_coord.row != row2
				|| (tmp_coord.col != 0 && tmp_coord.col != 7)) {
			printf(WRONG_ROOK_POSITION);
			break;
		}

		// left
		if (tmp_coord.col == 0) {
			if (res != BOTH_SIDES && res != CASTLE_QUEEN_SIDE) {
				printf(ILLEGAL_CALTLING_MOVE);
				break;
			}
		}

		// right
		else if (res != BOTH_SIDES && res != CASTLE_KING_SIDE) {
			printf(ILLEGAL_CALTLING_MOVE);
			break;
		}

		castleMove(tmp_piece);
		printBoard();
		pGame->turn ^= 1; // switch turn
		if (printWinner() == -1) // check
			printf("Check!\n");

		break;
	}
}

command_t stringToCommand(char *string) {

	if (STR_CMP(string, "game_mode") == 0)
		return SET_GAME_MODE;
	if (STR_CMP(string, "user_color") == 0)
		return SET_USER_COLOR;
	if (STR_CMP(string, "difficulty") == 0)
		return SET_DIFFICULTY;
	if (STR_CMP(string, "load") == 0)
		return SET_LOAD;
	if (STR_CMP(string, "clear") == 0)
		return SET_CLEAR;
	if (STR_CMP(string, "next_player") == 0)
		return SET_NEXT_PLAYER;
	if (STR_CMP(string, "rm") == 0)
		return SET_RM;
	if (STR_CMP(string, "set") == 0)
		return SET_SET;
	if (STR_CMP(string, "print") == 0)
		return SET_PRINT;
	if (STR_CMP(string, "start") == 0)
		return SET_START;
	//-----------
	if (STR_CMP(string, "quit") == 0)
		return QUIT;
	//-----------
	if (STR_CMP(string, "move") == 0)
		return GAME_MOVE;
	if (STR_CMP(string, "get_moves") == 0)
		return GAME_GET_MOVES;
	if (STR_CMP(string, "get_best_moves") == 0)
		return GAME_GET_BEST_MOVES;
	if (STR_CMP(string, "get_score") == 0)
		return GAME_GET_SCORE;
	if (STR_CMP(string, "save") == 0)
		return GAME_SAVE;
	if (STR_CMP(string, "castle") == 0)
		return GAME_CASTLE;

	return -1;
}

chessPieceKind_t extractKind(char *string) {
	if (string == NULL || string == '\0')
		return -1;
	if (STR_CMP(string, "pawn") == 0)
		return PAWN;
	if (STR_CMP(string, "rook") == 0)
		return ROOK;
	if (STR_CMP(string, "king") == 0)
		return KING;
	if (STR_CMP(string, "queen") == 0)
		return QUEEN;
	if (STR_CMP(string, "bishop") == 0)
		return BISHOP;
	if (STR_CMP(string, "knight") == 0)
		return KNIGHT;
	return -1;
}

char extractPieceChar(chessPieceKind_t kind, color_t color) {
	return color == BLACK ? toupper(kindToChar(kind)) : kindToChar(kind);
}

int maxPiecesReached(chessPieceKind_t kind, color_t color, coord_t *coord) {
	// max pieces possible of each kind
	int max[6];
	max[PAWN] = 8;
	max[ROOK] = 2;
	max[BISHOP] = 2;
	max[KNIGHT] = 2;
	max[QUEEN] = 1;
	max[KING] = 1;

	chessPiece_t *curPiece = (*pBoard)[coord->row][coord->col];
	chessPlayer_t *pPlayer = getPlayerByColor(color);
	int cur_piece = 0;

	if (curPiece != NULL && curPiece->kind == kind && curPiece->color == color)
		cur_piece = 1;

	int num_after = pPlayer->numOfPiece[kind] + 1 - cur_piece;

	return num_after > max[kind] ? 1 : 0;
}

void freeAllMemory() {
	// assuming that whoever allocated allMoves, frees it.

	if (pGame != NULL) {

		//free Pieces
		freePlayers();

		//free Players
		if (pGame->pWhite) {
			free(pGame->pWhite);
			pGame->pWhite = NULL;
		}
		if (pGame->pBlack) {
			free(pGame->pBlack);
			pGame->pBlack = NULL;
		}

		//free Board
		if (pBoard != NULL) {
			free(pBoard);
			pGame->pBoard = NULL;
		}

		//free Game
		free(pGame);
	}
	exit(0);
}

int isValidMove(coord_t *src_coord, coord_t *dest_coord) {
	chessPiece_t *pieceSrc;
	move_t *moveList = NULL;

	// extractCoord return (-1,-1) if out of board
	if (src_coord->row == -1 || dest_coord->row == -1)
		return FAILED;

	// extract pieces from board
	pieceSrc = (*pBoard)[src_coord->row][src_coord->col];

	// check if piece exists and has the same color of user
	if (pieceSrc == NULL || pieceSrc->color != pGame->turn) {
		printf(WRONG_PIECE_SELECTION);
		return FAILED;
	}

	// check if move exists in all-move-list
	moveList = getPieceMoves(moveList, pieceSrc);
	for (move_t *curMove = moveList; curMove != NULL; curMove = curMove->next) {
		if (curMove->dstCoord.row == dest_coord->row
				&& curMove->dstCoord.col == dest_coord->col) {
			freeMoves(&moveList);
			return TRUE;
		}
	}
	freeMoves(&moveList);
	printf(ILLEGAL_MOVE);
	return FALSE;
}
