#include "board.h"
#include "move.h"
#include "move_list.h"

// this is the perft test. It test if the calculation of possible moves is
// correct. For this we specify a depth (amount of half moves) and count all
// possible positions. We compare this with already computed values from here:
// https://chessprogramming.org/Perft_Results
// half_moves specify how many half moves are left to calculate
long perft_test(Board& board, int half_moves)
{
    MoveList allPossibleMoves = generateMoves(board);

    ///////////////////////
    // print list
    // std::cout << "halfmoves: " << half_moves << '\n';
    // for (auto move : allPossibleMoves)
    // {
    //     std::cout << move.from.row << ' ' << move.from.column
    //               << " to: " << move.to.row << " " << move.to.column << '\n';
    // }
    // std::cout << '\n';
    ////////////////////////////////

    long nodes{0};
    if (half_moves == 1)
    { // so there is only one half-round left.
        return static_cast<long>(
            allPossibleMoves
                .size()); // the store all moves in a constant size array. Index
                          // will give as the amount of moves in this array.
    }

    for (Move move : allPossibleMoves)
    {
        UndoInfo info = board.makeMove(move);
        nodes += perft_test(board, half_moves - 1);
        board.undoMove(move, info);
    }
    return nodes;
}
