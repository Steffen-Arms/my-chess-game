#include "board.h"
#include "engine_info.h"
#include "move.h"
#include <iostream>
#include <optional>
#include <search.h>
#include <sstream>
#include <string>
#include <string_view>

std::string toUci(const Move& m)
{
    std::string uci_move;
    uci_move += static_cast<char>('a' + m.from.column - 2);
    uci_move += static_cast<char>('1' + m.from.row - 2);
    uci_move += static_cast<char>('a' + m.to.column - 2);
    uci_move += static_cast<char>('1' + m.to.row - 2);
    if (m.transform.getType() != PieceType::Empty)
    {
        uci_move += static_cast<char>(std::tolower(m.transform.toChar()));
    }
    return uci_move;
}

// here we just generate all moves and pick the one that matched the string.
// ToDo: generate new Move directly. Corrently no big obtimisation
std::optional<Move> fromUci(Board& board, std::string_view uci_move)
{
    for (const Move& m : generateMoves(board))
    {
        if (toUci(m) == uci_move)
            return m;
    }
    return std::nullopt;
}

// UCI interface
//  https://backscattering.de/chess/uci/
//  https://chessprogramming.org/UCI
// the UCI GUI start my chess engine as a seperate program and writes commands
// to it via stdin and reads answers from stdout
void uciLoop()
{
    Board board;
    std::string line;

    while (std::getline(std::cin, line))
    {
        std::istringstream lineStream(
            line); // here we make the string into a stream again.
        std::string cmd;
        lineStream >> cmd; // here we read the character to the next whitespace
                           // to here we obtian we first word.

        if (cmd == "uci")
        {
            std::cout << "id name " << chess::engine_name() << '\n'
                      << "id author " << chess::engine_author() << '\n'
                      << "uciok" << std::endl;
        }
        else if (cmd == "isready")
        {
            std::cout << "readyok" << std::endl;
        }
        else if (cmd == "ucinewgame")
        {
            board = Board{};
        }
        else if (cmd == "position")
        {
            // note we obtain the board state via fen or via all moves played
            // until now (https://backscattering.de/chess/uci/)

            std::string inputWord;
            lineStream >> inputWord;

            if (inputWord == "startpos")
            {
                board = Board{};
                lineStream >> inputWord;
            }
            else if (inputWord == "fen")
            {
                std::string fen, part;
                // fen give as a start position and then all additional moves
                // that was played until now
                while (lineStream >> part && part != "moves")
                {
                    fen += (fen.empty() ? "" : " ") + part;
                }
                board = Board{fen};
                inputWord = part;
            }
            if (inputWord == "moves")
            {
                std::string movesString;
                while (lineStream >> movesString)
                {
                    auto move = fromUci(board, movesString);
                    if (!move)
                        break; // no more moves

                    // here we cast the return value to void. We need that
                    // because makeMove is declared with [[nodiscard]]
                    (void)board.makeMove(
                        *move); // as move is a <optional> we need *
                }
            }
        }
        else if (cmd == "go")
        {
            auto bestMove = rootSearch(board, 3);
            // if we don't find a move we return string "0000"
            std::cout << "bestmove " << (bestMove ? toUci(*bestMove) : "0000")
                      << std::endl;
        }
        else if (cmd == "quit")
        {
            break;
        }
    }
}
