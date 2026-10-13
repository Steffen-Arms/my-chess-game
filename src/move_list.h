#ifndef MOVE_LIST_H
#define MOVE_LIST_H

#include "board.h"
#include <array>
#include <cassert>
#include <cstddef>

// If a pawn reach the other end of the board we have to save the piece it
// transform to For a rochade (where to piece move simultaneously) the board
// logic will have to handle this. Here we only store how the king move. Because
// at a rochade the king move 2 or three field its unambiguous
struct Move
{
    Coord from;
    Coord to;
    Piece capturePiece = Piece{};
    Piece transform = Piece{};
    bool enPassage = false; // is true if this move create a enPassage right
};

// We need a data structur so we can access the last element of a array.
struct MoveList
{
    // we assume there are no more than 218 moves in one position.
    // https://lichess.org/@/Tobs40/blog/why-a-reachable-position-can-have-at-most-218-playable-moves/a5xdxeqs
    // We round that up to the next power of 2 so we obtain 256
    std::array<Move, 256> move_list;
    std::size_t index{0};

    // this is analog to the push_back function of a vector
    void push_back(const Move& newMove)
    {
        assert(index < move_list.size());
        move_list[index++] = newMove;
    }

    void clear() { index = 0; }

    std::size_t size() const { return index; }

    Move& operator[](std::size_t i) { return move_list[i]; }
    const Move& operator[](std::size_t i) const { return move_list[i]; }

    // define range-base
    Move* begin() { return move_list.data(); }
    Move* end() { return move_list.data() + index; }
    const Move* begin() const { return move_list.data(); }
    const Move* end() const { return move_list.data() + index; }
};

#endif
