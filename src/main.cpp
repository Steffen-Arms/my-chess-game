#include <iostream>

#include "board.cpp"
#include "engine_info.hpp"
#include "move.cpp"
#include "move_list.h"

// this is the perft test. It test if the calculation of possible moves is
// correct. For this we specify a depth (amount of half moves) and count all
// possible positions. We compare this with already computed values from here:
// https://chessprogrammingtestBoard.org/Perft_Results
// half_moves specify how many half moves are left to calculate
long perft_test(Board board, int half_moves)
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
        board.makeMove(move);
        nodes += perft_test(board, half_moves - 1);
        board.undoMove(move);
    }
    return nodes;
}

int main()
{
    Board testBoard{};
    testBoard.print();
    std::cout << '\n';
    for (int i{1}; i < 6; ++i)
    {
        long amountOfNodes = perft_test(testBoard, i);
        std::cout << "Board after " << i << " : " << amountOfNodes << '\n';
    }

    // Board rookKing{
    //     "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - "};
    // rookKing.print();
    // std::cout << '\n';
    // for (int i{1}; i < 4; ++i)
    // {
    //     std::cout << "new i \n";
    //     long amountOfNodes = perft_test(rookKing, i);
    //     std::cout << "######################## \n";
    //     std::cout << "Board after " << i << " : " << amountOfNodes << '\n';
    //     std::cout << '\n';
    //     std::cout << '\n';
    // }

    // Board rookKing{"8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1 "};
    // rookKing.print();
    // std::cout << '\n';
    // for (int i{1}; i < 4; ++i)
    // {
    //     std::cout << "new i \n";
    //     long amountOfNodes = perft_test(rookKing, i);
    //     std::cout << "######################## \n";
    //     std::cout << "Board after " << i << " : " << amountOfNodes << '\n';
    //     std::cout << '\n';
    //     std::cout << '\n';
    // }

    // Board rookKing{"8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1 "};
    // rookKing.print();
    // std::cout << '\n';
    // for (int i{1}; i < 4; ++i)
    // {
    //     std::cout << "new i \n";
    //     long amountOfNodes = perft_test(rookKing, i);
    //     std::cout << "######################## \n";
    //     std::cout << "Board after " << i << " : " << amountOfNodes << '\n';
    //     std::cout << '\n';
    //     std::cout << '\n';
    // }
}
