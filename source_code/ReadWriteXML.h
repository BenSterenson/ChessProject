/*
 * ReadWriteXML.h
 *
 *  Created on: Aug 26, 2015
 *      Author: bensterenson
 */

#ifndef READWRITEXML_H_
#define READWRITEXML_H_

#include "Chess.h"

char LineStrXml[numOfXMLLines][maxLenofLine];
extern int setXMLStrings();

extern int setXMLStrings();
extern int errorCheck(int, int);
extern int extractBoard(xmlNode *, char (*boardStr)[BOARD_SIZE][BOARD_SIZE],
		int, bool_t);
extern int extractDifficulty(char*);
extern int readXmlElements(xmlNode *, int);
extern int ReadXMLFormat(char *);
extern int WriteXMLFormat(FILE *);
extern int WriteReadXML(char *, writeRead_t);
extern void castleModeToArray(int, castling_t *);
#endif /* READWRITEXML_H_ */
