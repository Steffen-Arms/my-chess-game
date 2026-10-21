#include "board.h"
#include "perft.h"
#include <iostream>

int main()
{
    // Initial position
    // tested correct until depth 5
    // Board testBoard{};
    // testBoard.print();
    // std::cout << '\n';
    // for (int i{1}; i < 6; ++i)
    // {
    //     long amountOfNodes = perft_test(testBoard, i);
    //     std::cout << "Board after " << i << " : " << amountOfNodes << '\n';
    // }

    // these difirent positions are the chess positions from the above website
    // "https://chessprogramming.org/Perft_Results" I compare.
    //  Position 2 or Kiwipete test
    //  tested correct until depth 6
    //  Board kiwipete{
    //      "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -
    //      "};
    //  kiwipete.print();
    //  std::cout << '\n';
    //  for (int i{1}; i < 7; ++i)
    //  {
    //      long amountOfNodes = perft_test(kiwipete, i);
    //      std::cout << "Board after " << i << " : " << amountOfNodes << '\n';
    //  }

    // Position 3
    // tested correct until depth 7
    // Board position3{"8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1 "};
    // position3.print();
    // std::cout << '\n';
    // for (int i{1}; i < 8; ++i)
    // {
    //     long amountOfNodes = perft_test(position3, i);
    //     std::cout << "Board after " << i << " : " << amountOfNodes << '\n';
    // }

    // Position 4
    // tested correct until depth 5
    // Board position4{
    //     "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1"};
    // position4.print();
    // std::cout << '\n';
    // for (int i{1}; i < 6; ++i)
    // {
    //     long amountOfNodes = perft_test(position4, i);
    //     std::cout << "Board after " << i << " : " << amountOfNodes << '\n';
    // }

    // Position 5
    // tested correct until depth 5
    // Board position5{
    //     "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8"};
    // position5.print();
    // std::cout << '\n';
    // for (int i{1}; i < 6; ++i)
    // {
    //     long amountOfNodes = perft_test(position5, i);
    //     std::cout << "Board after " << i << " : " << amountOfNodes << '\n';
    // }

    // Position 6
    // tested correct until depth 5
    Board position6{"r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/"
                    "R4RK1 w - - 0 10 "};
    position6.print();
    std::cout << '\n';
    for (int i{1}; i < 6; ++i)
    {
        long amountOfNodes = perft_test(position6, i);
        std::cout << "Board after " << i << " : " << amountOfNodes << '\n';
    }
}
