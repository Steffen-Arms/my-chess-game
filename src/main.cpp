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
    // Board rookTest{"rnbqkbnr/pppppppp/8/8/8/8/8/3R4 w KQkq - 0 1"};
    // rookTest.print();
    // std::cout << '\n';
    // long amountOfNodes = perft_test(rookTest, 1);
    // std::cout << "rook test 1: " << amountOfNodes << '\n';

    // Board rookKnight{"rnbqkbnr/pppppppp/8/3N4/8/8/8/8 w KQkq - 0 1"};
    // rookKnight.print();
    // std::cout << '\n';
    // long amountOfNodes2 = perft_test(rookKnight, 1);
    // std::cout << "knight test 1: " << amountOfNodes2 << '\n';

    // Board rookBishop{"rnbqkbnr/pppppppp/8/3B4/8/8/8/8 w KQkq - 0 1"};
    // rookBishop.print();
    // std::cout << '\n';
    // long amountOfNodes3 = perft_test(rookBishop, 1);
    // std::cout << "bishop test 1: " << amountOfNodes3 << '\n';

    // Board rookQueen{"rnbqkbnr/pppppppp/8/8/8/8/8/3Q4 w KQkq - 0 1"};
    // rookQueen.print();
    // std::cout << '\n';
    // long amountOfNodes4 = perft_test(rookQueen, 1);
    // std::cout << "queen test 1: " << amountOfNodes4 << '\n';

    Board rookKing{"rnbqkbnr/ppp1pppp/8/8/8/8/3K4/8 w KQkq - 0 1"};
    rookKing.print();
    std::cout << '\n';
    long amountOfNodes5 = perft_test(rookKing, 1);
    std::cout << "king test 1: " << amountOfNodes5 << '\n';

    // Board noFen{};
    // noFen.print();
    // std::cout << '\n';

    // long amountOfNodes = perft_test(noFen, 3);
    // std::cout << "amount of moves depth 2: " << amountOfNodes << '\n';

    // amountOfNodes = perft_test(testBoard, 3);
    // std::cout << "amount of moves depth 3: " << amountOfNodes << '\n';

    // amountOfNodes = perft_test(testBoard, 4);
    // std::cout << "amount of moves depth 4: " << amountOfNodes << '\n';

    // amountOfNodes = perft_test(testBoard, 5);
    // std::cout << "amount of moves depth 5: " << amountOfNodes << '\n';
}
