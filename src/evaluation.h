#ifndef EVALUATION_H
#define EVALUATION_H

#include "board.h"

bool isEndgame(const Board& board);

int evaluateBoardPositionByPieceValue(const Board& board);

#endif
