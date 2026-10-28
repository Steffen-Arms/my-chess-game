#ifndef EVALUATION_H
#define EVALUATION_H

#include "board.h"

constexpr int obtainPieceValue(const PieceType& pieceType);

constexpr int getPositionValue(Piece piece, std::size_t row, std::size_t column,
                               bool endgame);

bool colorIsInEndgame(Color color, const Board& board);

bool isEndgame(const Board& board);

int evaluateBoardPositionByPieceValue(const Board& board);

#endif
