#include <iostream>

#include "board.cpp"
#include "engine_info.hpp"
#include "move.cpp"
#include "move_list.h"

// this is the perft test. It test if the calculation of possible moves is
// correct. For this we specify a depth (amount of half moves) and count all
// possible positions. We compare this with already computed values from here:
// https://chessprogramming.org/Perft_Results
void perft_test(Board board, int depth) {}

int main()
{
    Board testBoard{};
    testBoard.print();
    std::cout << '\n';
    MoveList testMoveList = generateMoves(testBoard);
    std::cout << "amount of moves " << testMoveList.size() << '\n';
}
