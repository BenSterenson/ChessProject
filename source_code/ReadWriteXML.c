/*
 * ReadWriteXML.c
 *
 *  Created on: Aug 26, 2015
 *      Author: bensterenson
 */

#include "ReadWriteXML.h"

int setXMLStrings() {
	memset(LineStrXml, '\0', sizeof(char) * numOfXMLLines * maxLenofLine);
	strcpy(LineStrXml[0], "?xml version=\"1.0\" encoding=\"UTF-8\"?");
	strcpy(LineStrXml[1], "game");
	strcpy(LineStrXml[2], "next_turn");
	strcpy(LineStrXml[3], "game_mode");
	strcpy(LineStrXml[4], "difficulty");
	strcpy(LineStrXml[5], "user_color");
	strcpy(LineStrXml[6], "board");
	strcpy(LineStrXml[7], "row_");
	strcpy(LineStrXml[8], "general");
	strcpy(LineStrXml[9], "castling_w");
	strcpy(LineStrXml[10], "castling_b");

	return 1;
}

int errorCheck(int numSucceed, int error) {
	if (numSucceed < 0 || error == 1)
		return 1; //ERROR
	return 0;
}

int extractBoard(xmlNode *c_node, char (*boardStr)[BOARD_SIZE][BOARD_SIZE],
		int i, bool_t err) {
	xmlNode *node = NULL;
	char *str_val, rowNum[5];
	int j = BOARD_SIZE;
	strcpy(rowNum, LineStrXml[LINE_ROW - 1]);

	if (err == 1)
		return FAILED;

	for (node = c_node; node; node = node->next) {
		if (node->type == XML_ELEMENT_NODE) {

			rowNum[4] = '0' + j--;

			err = strcmp((char*) node->name, rowNum) == 0 ? FALSE : TRUE;
			str_val = (char*) xmlNodeGetContent(node);

			strncpy((*boardStr)[i++], str_val, BOARD_SIZE * sizeof(char));

			if (j == 0 && err == 0)
				return PASSED;
		}
		extractBoard(node->children, boardStr, i, err);
	}
	return FAILED;
}

int extractDifficulty(char* strDifficulty) {
	if (*strDifficulty == '\0')
		return 1;
	if (strcmp(strDifficulty, "best") == 0)
		return BEST;
	return atoi(strDifficulty) == BEST ? 0 : atoi(strDifficulty);
}

int readXmlElements(xmlNode * Rootnode, int i) {
	xmlNode *currNode = NULL;
	bool_t error = FALSE;
	//static int i = LINE_GAME;
	int j = 0, castleMode = 0;
	static boardStatus_t boardStatus = NOT_SET, generalStatus = NOT_SET;
	char boardStr[BOARD_SIZE][BOARD_SIZE];
	castling_t *castling;
	char row_x[] = "row_8";

	for (currNode = Rootnode; currNode; currNode = currNode->next) {

		if (currNode->type == XML_ELEMENT_NODE) {
			if (currNode->line < 19 && currNode->line > 17) {
				// printf("\n%s,%s\n", currNode->name, LineStrXml[i]);
				error = strcmp((char*) currNode->name, LineStrXml[i]) == 0 ?
						FALSE : TRUE;
			} else if (currNode->line > LINE_ROW - 1 && currNode->line < 16) {
				row_x[4] = (BOARD_SIZE - (i - BOARD_SIZE)) + '0';
				//	printf("\n%s,%s\n",currNode->name,row_x);
				error = strcmp((char*) currNode->name, row_x) == 0 ?
						FALSE : TRUE;
			} else if (currNode->line < numOfXMLLines) {
				// printf("\n%s,%s\n", currNode->name, LineStrXml[i - 1]);
				error = strcmp((char*) currNode->name, LineStrXml[i - 1]) == 0 ?
						FALSE : TRUE;
			}

			switch (currNode->line) {

			case LINE_TURN:
				pGame->turn = extractColor((char*) xmlNodeGetContent(currNode));
				castling = &(*(getPlayerByColor(WHITE)->castling));
				memset(castling, FALSE, sizeof(castling_t) * 3);
				castling = &(*(getPlayerByColor(BLACK)->castling));
				memset(castling, FALSE, sizeof(castling_t) * 3);
				if (pGame->turn == -1)
					error = TRUE;
				break;

			case LINE_MODE:
				pGame->mode = atoi((char*) xmlNodeGetContent(currNode));
				if (pGame->mode != PLAYER_VS_COMPUTER
						&& pGame->mode != PLAYER_VS_PLAYER)
					error = TRUE;
				break;

			case LINE_DIFFICULTY:
				pGame->difficulty = extractDifficulty(
						(char*) xmlNodeGetContent(currNode));
				if (pGame->difficulty < 1 || pGame->difficulty > BEST)
					error = TRUE;
				break;

			case LINE_USER_COLOR:

				pGame->user = extractColor((char*) xmlNodeGetContent(currNode));
				if (pGame->user == -1)
					error = TRUE;
				break;

			case LINE_BOARD:
				boardStatus = error == FALSE ? READY_TO_WRITE : NOT_SET; //board is ready to write;
				break;

			case LINE_ROW:
				if (boardStatus == READY_TO_WRITE) {
					error = extractBoard(currNode, &boardStr, j, error)
							== PASSED ? FALSE : TRUE;
					if (error == FALSE)
						initGame(&boardStr);
					boardStatus = READY_TO_READ;
				} else if (boardStatus == NOT_SET)
					error = TRUE;

				break;

			case 17:
				generalStatus = error == FALSE ? READY_TO_WRITE : NOT_SET; //board is ready to write;
				break;

			case 18:
				if (generalStatus == READY_TO_WRITE) {
					castling = &(*(getPlayerByColor(WHITE)->castling));
					castleMode = atoi((char*) xmlNodeGetContent(currNode));
					if (castleMode < 0 || castleMode > 3)
						error = TRUE;
					castleModeToArray(castleMode, castling);
				} else if (generalStatus == NOT_SET)
					error = TRUE;
				break;

			case 19:
				if (generalStatus == READY_TO_WRITE) {
					castling = &(*(getPlayerByColor(BLACK)->castling));
					castleMode = atoi((char*) xmlNodeGetContent(currNode));
					if (castleMode < 0 || castleMode > 3)
						error = TRUE;
					castleModeToArray(castleMode, castling);
				} else if (generalStatus == NOT_SET)
					error = TRUE;
				break;
			}
			if (error == 1)
				return FAILED;

			//i >= numOfXMLLines ? LINE_GAME : i++;
			i++;
		}
		readXmlElements(currNode->children, i);
	}
	return PASSED;
}

void castleModeToArray(int castleMode, castling_t * castling) {
	castling[ROOK_L] = FALSE;
	castling[KING_M] = FALSE;
	castling[ROOK_R] = FALSE;

	switch (castleMode) {
	case CANT_CASTLE:
		castling[KING_M] = TRUE;
		break;

	case CASTLE_KING_SIDE:
		castling[ROOK_L] = TRUE;
		break;

	case CASTLE_QUEEN_SIDE:
		castling[ROOK_R] = TRUE;
		break;
	}
}

int ReadXMLFormat(char *filename) {
	// return 0 - error ; return 1 - success
	xmlDoc *xmlDoc = NULL;
	xmlNode *nodeRootElem = NULL;
	int error = FALSE;

	if ((xmlDoc = xmlReadFile(filename, NULL, XML_PARSE_NOERROR)) == NULL) {
		// printf("Error: bad format, could not read file\n");
		xmlSetGenericErrorFunc((void *) xmlDoc, NULL);

		return FAILED;
	}

	else {
		nodeRootElem = xmlDocGetRootElement(xmlDoc);
		error = readXmlElements(nodeRootElem, LINE_GAME) == TRUE ?
				FAILED : PASSED;

		xmlFreeDoc(xmlDoc);
	}

	xmlCleanupParser();
	if (error == 1)
		return FAILED;

	return PASSED;
}

castling_t checkCastling(color_t color) {
	castling_t *hasMoved = &(*(getPlayerByColor(pGame->turn)->castling));

	// king or both rooks have moved
	if (hasMoved[KING_M] || (hasMoved[ROOK_L] && hasMoved[ROOK_R]))
		return CANT_CASTLE;

	// kind and both rooks haven't moved
	if (!hasMoved[ROOK_L] && !hasMoved[ROOK_R])
		return BOTH_SIDES;

	// king side rook hasn't moved
	if (!hasMoved[ROOK_R])
		return CASTLE_KING_SIDE;

	// queen side rook hasn't moved : if (!hasMoved[ROOK_L]))
	return CASTLE_QUEEN_SIDE;
}

int WriteXMLFormat(FILE *fp) {
	// return 0 - error
	// return 1 - success

	char boardStr[BOARD_SIZE][BOARD_SIZE];
	int i, j = 0, error = FALSE;

	if (fp == NULL)
		return FAILED;

	error = errorCheck(fprintf(fp, "<%s>\n", LineStrXml[j++]), error);
	error = errorCheck(fprintf(fp, "<%s>\n", LineStrXml[j++]), error);
	error = errorCheck(
			fprintf(fp, "\t<%s>%s</%s>\n", LineStrXml[j],
					pGame->turn == WHITE ? "White" : "Black", LineStrXml[j]),
			error);
	j++;
	error = errorCheck(
			fprintf(fp, "\t<%s>%d</%s>\n", LineStrXml[j], pGame->mode,
					LineStrXml[j]), error);
	j++;
	if (pGame->difficulty == BEST)
		error = errorCheck(
				fprintf(fp, "\t<%s>%s</%s>\n", LineStrXml[j], "best",
						LineStrXml[j]), error);
	else
		error = errorCheck(
				fprintf(fp, "\t<%s>%d</%s>\n", LineStrXml[j], pGame->difficulty,
						LineStrXml[j]), error);
	j++;
	error = errorCheck(
			fprintf(fp, "\t<%s>%s</%s>\n", LineStrXml[j],
					pGame->user == WHITE ? "White" : "Black", LineStrXml[j]),
			error);
	j++;

	//Board
	error = errorCheck(fprintf(fp, "\t<%s>\n", LineStrXml[j++]), error);
	saveBoard(&boardStr);
	//memset(boardStr, '_', 64 * sizeof(char));

	for (i = 0; i < BOARD_SIZE; i++) {
		error = errorCheck(fprintf(fp, "\t\t<%s%d>%.*s</%s%d>\n", LineStrXml[j],
		BOARD_SIZE - i,
		BOARD_SIZE, boardStr[i], LineStrXml[j], BOARD_SIZE - i), error);
		if (error == TRUE)
			return FAILED;
	}
	error = errorCheck(fprintf(fp, "\t</%s>\n", LineStrXml[LINE_BOARD - 1]),
			error);

	error = errorCheck(fprintf(fp, "\t<%s>\n", LineStrXml[LINE_GENERAL - 1]),
			error);

	error = errorCheck(
			fprintf(fp, "\t\t<%s>%d</%s>\n", LineStrXml[LINE_CASTLING_W - 1],
					checkCastling(pGame->pWhite->color),
					LineStrXml[LINE_CASTLING_W - 1]), error);
	error = errorCheck(
			fprintf(fp, "\t\t<%s>%d</%s>\n", LineStrXml[LINE_CASTLING_B - 1],
					checkCastling(pGame->pBlack->color),
					LineStrXml[LINE_CASTLING_B - 1]), error);

	error = errorCheck(fprintf(fp, "\t</%s>\n", LineStrXml[LINE_GENERAL - 1]),
			error);

	error = errorCheck(fprintf(fp, "</%s>\n", LineStrXml[LINE_GAME - 1]),
			error);

	if (error == TRUE)
		return FAILED;
	return PASSED;
}

int backupXML(FILE *fin) {

	char ch, tmp_file[] = "tmp.xml";
	FILE *ftmp;

	//file does not excit
	if (fin == NULL)
		return PASSED;

	//create copy of file in tmp.xml
	ftmp = fopen(tmp_file, "w");

	if (ftmp == NULL)
		return FAILED;

	while ((ch = fgetc(fin)) != EOF)
		fputc(ch, ftmp);

	// printf("		File copied successfully.\n");

	fclose(ftmp);

	return PASSED;

}

int DeleteXMLBackup(char* file_name) {

	int status;

	status = remove(file_name);
	if (status != 0) {
		// printf(	"		Unable to delete the file doesnt excite - ***double check if the file really doesnt excite*** \n");
		return FAILED;
	}
	// printf("		%s file deleted successfully.\n", file_name);
	return PASSED;
}

int renameFile(char *fileName) {

	int status;
	char oldname[] = "tmp.xml";

	status = rename(oldname, fileName);

	if (status != 0) {
		// printf("		Error: unable to rename the file");
		return FAILED;
	}
	// printf("		File renamed successfully");

	return (PASSED);
}

int recoverXML(char *fileName) {
	DeleteXMLBackup(fileName);
	return renameFile(fileName) == PASSED ? PASSED : FAILED;
}

// Write&Read XML //

int WriteReadXML(char *destFName, writeRead_t writeRead) {

	FILE *fp;
	bool_t error = FALSE;

	setXMLStrings();

	fp = fopen(destFName, "r");
	if (fp == NULL && writeRead == READ) {
		perror("Error: failed openning file.\n");
		printf("Wrong file name\n");
		return FAILED;
	}
	//file excite
	if (fp != NULL) {
		if (writeRead == READ) {
			// printf("		*** reading file ***\n");
			if (ReadXMLFormat(destFName) == FAILED) { //ERROR
				error = TRUE;
				perror("Error: failed reading from file.\n");
				printf("Wrong file name\n");
			}
		} else { // create a backup of file.
				 // printf("		*** found an exciting file - creating a backup ***\n");
			error = backupXML(fp) == PASSED ? FALSE : TRUE;
			if (error == TRUE) {
				perror("Error: failed overriding existing file.\n");
				printf("Wrong file name\n");
			}
		}
		fclose(fp);
	}

	if (writeRead == WRITE && error == FALSE) {
		fp = fopen(destFName, "w");
		if (fp != NULL) {
			// printf("		*** wrting to file ***\n");
			if (WriteXMLFormat(fp) == FAILED) {
				error = TRUE;
				perror("Error: failed writing to file.\n");
				printf("Wrong file name\n");
				// printf("***using saved backup to restore saved game ***\n");
				recoverXML(destFName);
			}
			// printf("		*** Deleting XML backup if was made ***\n");
			DeleteXMLBackup("tmp.xml");
			fclose(fp);
		}
	}

	return error == FALSE ? PASSED : FAILED;
}
