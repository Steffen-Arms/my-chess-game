#include "board.h"
#include "evaluation.h"
#include "move.h"
#include <iostream>
#include <limits>
#include <optional>

// we can't use std::numeric_limits<int>::min() as if we return the negative of
// it we obtain a overflow
constexpr int INF = 1'000'000;
constexpr int MATE = 100000;

// Negamax (https://chessprogramming.org/Negamax)
// Negamax compute the value of a position after looking ahead a given number of
// moves, assuming everyone takes the best moves. Our evaluation always compute
// white Points - black Points, then flips the sign if black is to move That why
// every player can just take the maximum pointed move.
int negaMax(Board& board, int depth)
{

    // if there is already mate here we don't find it as here we only evaluate
    // the board.
    if (depth <= 0)
        return evaluateBoardPositionByPieceValue(board);

    MoveList moveList = generateMoves(board);
    if (moveList.size() == 0)
    {
        // in this case we don't have any move and are in mate or patt
        if (board.kingInCheck())
        {
            // if we are in mate earlier (bigger depth) it is worse than later
            return -(MATE + depth);
        }
        else
        {
            // In this case we don't have any moves but are not in check, so we
            // are in patt.
            return 0;
        }
    }
    int max = -INF;
    int score;
    UndoInfo undoInfo;

    for (auto move : moveList)
    {
        undoInfo = board.makeMove(move);

        // negaMax return we value of a board for the which turn it is. Thats
        // why we take the negative of it here to have the value of the current
        // color.
        score = -negaMax(board, depth - 1);
        board.undoMove(move, undoInfo);
        if (score > max)
        {
            max = score;
        }
    }
    return max;
}

std::optional<Move> rootSearch(Board& board, int search_depth)
{
    Move bestMove;
    int bestScore = -INF;
    int score;
    UndoInfo undoInfo;

    MoveList moveList = generateMoves(board);

    if (moveList.size() == 0)
    {
        return std::nullopt;
    }
    for (auto move : moveList)
    {
        undoInfo = board.makeMove(move);
        score = -negaMax(board, search_depth - 1);
        board.undoMove(move, undoInfo);
        if (score > bestScore)
        {
            bestScore = score;
            bestMove = move;
        }
    }
    return bestMove;
}
