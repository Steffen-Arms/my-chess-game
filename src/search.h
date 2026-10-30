#ifndef SEARCH_H
#define SEARCH_H

#include "board.h"
#include "move.h"

// we can't use std::numeric_limits<int>::min() as if we return the negative of
// it we obtain a overflow
constexpr int INF = 1'000'000;
constexpr int MATE = 100000;

int negaMax(Board& board, int depth);

std::optional<Move> rootSearch(Board& board, int search_depth);

#endif
