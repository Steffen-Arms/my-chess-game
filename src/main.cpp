#include <iostream>

#include "board.cpp"
#include "engine_info.hpp"
#include "move.cpp"
#include "move_list.h"

// this is the perft test. It test if the calculation of possible moves is
// correct. For this we specify a depth (amount of half moves) and count all
// possible positions. We compare this with already computed values from here:
// https://chessprogramming.org/Perft_Results
// half_moves specify how many half moves are left to calculate
long perft_test(Board board, int half_moves)
{
    MoveList allPossibleMoves = generateMoves(board);
    long nodes;
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
    // Board noFen{};
    // noFen.print();
    // std::cout << '\n';

    // Board testBoard{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0
    // 1"}; testBoard.print(); std::cout << '\n';

    // Board test2Board{"r/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"};
    // test2Board.print();
    // std::cout << '\n';

    Board test3Board{
        "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"};
    test3Board.print();
    std::cout << '\n';

    Board test4Board{
        "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2"};
    test4Board.print();
    std::cout << '\n';
    // long amountOfNodes = perft_test(testBoard, 2);
    // std::cout << "amount of moves depth 2: " << amountOfNodes << '\n';

    // amountOfNodes = perft_test(testBoard, 3);
    // std::cout << "amount of moves depth 3: " << amountOfNodes << '\n';

    // amountOfNodes = perft_test(testBoard, 4);
    // std::cout << "amount of moves depth 4: " << amountOfNodes << '\n';

    // amountOfNodes = perft_test(testBoard, 5);
    // std::cout << "amount of moves depth 5: " << amountOfNodes << '\n';
}
