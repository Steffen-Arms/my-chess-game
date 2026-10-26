#include "board.h"
#include "evaluation.cpp"
#include "perft.h"
#include <iostream>

int main()
{
    // Board board{};
    // int sum = evaluateBoardPositionByPieceValue(board);
    // std::cout << "sum: " << sum << "\n";

    // Board board2{
    //     "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2 "};
    // int sum2 = evaluateBoardPositionByPieceValue(board2);
    // std::cout << "sum2 " << sum2 << "\n";

    Board board3{"rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8  "};
    int sum3 = evaluateBoardPositionByPieceValue(board3);
    std::cout << "sum3 " << sum3 << "\n";

    std::cout << "black pawn: "
              << board3.getPieceCount(Color::Black, PieceType::Pawn) << "\n";
    std::cout << "black rook: "
              << board3.getPieceCount(Color::Black, PieceType::Rook) << "\n";
    std::cout << "black knight: "
              << board3.getPieceCount(Color::Black, PieceType::Knight) << "\n";
    std::cout << "black bishop: "
              << board3.getPieceCount(Color::Black, PieceType::Bishop) << "\n";
    std::cout << "black queen: "
              << board3.getPieceCount(Color::Black, PieceType::Queen) << "\n";
}
