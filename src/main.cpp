#include "board.h"
#include "evaluation.cpp"
#include "perft.h"
#include "search.cpp"
#include <iostream>

int main()
{

    // Board board3{"6k1/5ppp/8/8/8/8/8/R5K1 w - - 0 1"};

    // board3.print();

    // std::optional<Move> move = rootSearch(board3, 2);
    // if (move.has_value())
    // {
    //     std::cout << "from: " << move.value().from.row << " "
    //               << move.value().from.column << " to: " <<
    //               move.value().to.row
    //               << " " << move.value().to.column << "\n";
    // }
    // else
    // {
    //     std::cout << "no moves left";
    // }

    Board board4{"7k/8/6Q1/8/8/8/8/6K1 w - - 0 1"};

    board4.print();
    std::optional<Move> move4 = rootSearch(board4, 2);
    if (move4.has_value())
    {
        std::cout << "from: " << move4.value().from.row << " "
                  << move4.value().from.column
                  << " to: " << move4.value().to.row << " "
                  << move4.value().to.column << "\n";
    }
    else
    {
        std::cout << "no moves left \n";
    }
}
