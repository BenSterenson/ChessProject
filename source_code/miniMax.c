/*
 * miniMax.c
 *
 *  Created on: Aug 31, 2015
 *      Author: bensterenson
 */

#include "miniMax.h"

int seenBoards = 0;
int minimax_depth = 0;

void scoreMove_depth(move_t *curMove, int depth) {
	chessPiece_t *srcPiece, *dstPiece;
	minimax_depth = depth;
	simulateMove(curMove, &srcPiece, &dstPiece);
	curMove->score = alphaBetaMin(-INF, INF, depth - 1);
	undoMove(curMove, srcPiece, dstPiece);
}
int preEstimateMoveAmount(chessPiece_t *pPiece){
	int numOfMoves = 0;

	for (chessPiece_t* curPiece = pPiece; curPiece != NULL; curPiece = curPiece->next){
		switch (curPiece->kind){
		case PAWN:
			numOfMoves += 3;
			break;
		case KNIGHT:
			numOfMoves += 8;
			break;
		case BISHOP:
			numOfMoves += 13;
			break;
		case ROOK:
			numOfMoves += 14;
			break;
		case QUEEN:
			numOfMoves += 27;
			break;
		case KING:
			numOfMoves += 9;
			break;
		}
	}
	return numOfMoves;
}
int clacBestDepthMinimax(){
	int numOfMoves = 1;
	int limitNumber = MAX_BOARDS;
	int depth = 0;
	chessPlayer_t *pPlayer = getPlayerByColor(pGame->turn);

	while ((numOfMoves *= preEstimateMoveAmount(pPlayer->pHead)) < limitNumber) {
		depth++;
		pPlayer = getPlayerByColor(otherColor(pPlayer->color));
	}
	return depth;
}

move_t* getBestMoves(int depth) {
	move_t* bestMoves = getAllMoves();
	MergeSort(&bestMoves);

	minimax_depth = depth;
	int bestDepth = clacBestDepthMinimax();
	depth = depth == BEST ? bestDepth : MIN(depth, bestDepth);

	for (move_t *curMove = bestMoves; curMove != NULL; curMove = curMove->next)
		scoreMove_depth(curMove, depth);

	MergeSort(&bestMoves);

	// count number of moves with highest score
	int countBestMove = 0;
	move_t* curMove;
	for (curMove = bestMoves; curMove != NULL && curMove->score == bestMoves->score; countBestMove++, curMove = curMove->next);

	// reach the last highest-scored move
	for (curMove = bestMoves; countBestMove-1 > 0; curMove = curMove->next, countBestMove--);

	// free moves that come after
	freeMoves(&(curMove->next));
	curMove->next = NULL;

	return bestMoves;
}


int boardScore(int isMaximizer) {
	chessPlayer_t *player = getPlayerByColor(pGame->turn);
	chessPlayer_t *opponent = getPlayerByColor(otherColor(pGame->turn));
	int total_score = 0;

	move_t* pMoves = getAllMoves();
	if (checkmate(pMoves)) {
		freeMoves(&pMoves);
		return isMaximizer ? LOOSE + 20 * minimax_depth : WIN - 20 * minimax_depth;
	}

	if (pMoves == NULL)
		return TIE_SCORE;

	freeMoves(&pMoves);

	for (chessPiece_t* curPiece = player->pHead; curPiece != NULL; curPiece =
		curPiece->next)
		total_score += getScorePiece(curPiece->kind);

	for (chessPiece_t* curPiece = opponent->pHead; curPiece != NULL; curPiece =
		curPiece->next)
		total_score -= getScorePiece(curPiece->kind);

	return isMaximizer ? total_score : -total_score;

}

int alphaBetaMax(int alpha, int beta, int depth_left) {
	int score;
	chessPiece_t *srcPiece, *dstPiece;
	move_t* curMove, *pMoves;

	if (++seenBoards > MAX_BOARDS || depth_left == 0)
		return boardScore(TRUE);

	pMoves = getAllMoves();
	MergeSort(&pMoves);

	if (checkmate(pMoves)) {
		freeMoves(&pMoves);
		return LOOSE + 20 * (minimax_depth - depth_left);
	}

	if (pMoves == NULL)
		return TIE_SCORE;

	for (curMove = pMoves; curMove != NULL; curMove = curMove->next) {

		// simulate move + recursive call
		simulateMove(curMove, &srcPiece, &dstPiece);
		score = alphaBetaMin(alpha, beta, depth_left - 1);
		undoMove(curMove, srcPiece, dstPiece);

		if (score >= beta) {
			freeMoves(&pMoves);
			return beta;
		}
		if (score > alpha)
			alpha = score;

	}
	freeMoves(&pMoves);
	return alpha;
}

int alphaBetaMin(int alpha, int beta, int depth_left) {
	int score;
	chessPiece_t *srcPiece, *dstPiece;
	move_t *pMoves;

	if (++seenBoards > MAX_BOARDS || depth_left == 0)
		return boardScore(FALSE);

	pMoves = getAllMoves();
	MergeSort(&pMoves);

	if (checkmate(pMoves)) {
		freeMoves(&pMoves);
		return WIN - 20 * (minimax_depth - depth_left);
	}

	if (pMoves == NULL)
		return TIE_SCORE;

	for (move_t* curMove = pMoves; curMove != NULL; curMove = curMove->next) {

		// simulate move + recursive call
		simulateMove(curMove, &srcPiece, &dstPiece);
		score = alphaBetaMax(alpha, beta, depth_left - 1);
		undoMove(curMove, srcPiece, dstPiece);

		if (score <= alpha) {
			freeMoves(&pMoves);
			return alpha;
		}
		if (score < beta)
			beta = score;
	}

	freeMoves(&pMoves);
	return beta;
}



int getScorePiece(chessPieceKind_t kind) {
	switch (kind) {
	case PAWN:
		return SCORE_PAWN;
	case KNIGHT:
		return SCORE_KNIGHT;
	case BISHOP:
		return SCORE_BISHOP;
	case ROOK:
		return SCORE_ROOK;
	case QUEEN:
		return SCORE_QUEEN;
	case KING:
		return SCORE_KING;
	default:
		return 0;
	}
}

int checkmate(move_t* pMoves) {
	chessPiece_t *pKing = getPlayerByColor(pGame->turn)->pKing;

	// king is not threatened
	if (!isThreatened(pKing->coord))
		return FALSE;

	if (pMoves == NULL)
		return TRUE;

	return FALSE;
}

void MergeSort(move_t **headRef) {
	move_t* head = *headRef;
	move_t* a;
	move_t* b;

	if ((head == NULL) || (head->next == NULL))
		return;

	// Split head into 'a' and 'b' sublists
	Partition(head, &a, &b);

	// Recursively sort the sublists
	MergeSort(&a);
	MergeSort(&b);

	// update head to the merge of two sorted lists together
	*headRef = Merge(a, b);
}

void Partition(move_t* source, move_t** frontRef, move_t** backRef) {
	move_t* fast;
	move_t* slow;

	if (source == NULL || source->next == NULL) {
		*frontRef = source;
		*backRef = NULL;
	}

	else {
		slow = source;
		fast = source->next;

		// Advance 'fast' two nodes, and advance 'slow' one node
		while (fast != NULL) {
			fast = fast->next;
			if (fast != NULL) {
				slow = slow->next;
				fast = fast->next;
			}
		}

		// 'slow' is before the midpoint in the list, so split it in two at that point.
		*frontRef = source;
		*backRef = slow->next;
		slow->next = NULL;
	}
}

move_t* Merge(move_t* a, move_t* b) {
	move_t* result = NULL;

	if (a == NULL)
		return b;
	if (b == NULL)
		return a;

	// Pick either a or b, and recur
	if (a->score >= b->score) {
		result = a;
		result->next = Merge(a->next, b);
	}

	else {
		result = b;
		result->next = Merge(a, b->next);
	}

	return result;
}

int scoreMove(move_t* pMove) {
	if (pMove->dstCoord.row == pMove->srcCoord.row && pMove->dstCoord.col == pMove->srcCoord.col)
		return 0;

	int score = 0;
	chessPiece_t *pPiece = (*pBoard)[pMove->dstCoord.row][pMove->dstCoord.col];
	score += pPiece == NULL ? 0 : getScorePiece(pPiece->kind);

	// if promotion - decrease pawn score and add new piece's score
	if (pMove->promotion != -1)
		score += getScorePiece(pMove->promotion) - 1;

	return score;
}

