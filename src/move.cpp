#include "board.cpp"
#include <vector>

// If a pawn reach the other end of the board we have to save the piece it
// transform to For a rochade (where to piece move simultaneously) the board
// logic will have to handle this. Here we only store how the king move. As at a
// rochade the kind move 2 or three field its unambiguous
struct Move
{
    Coord from;
    Coord to;
    Piece transform;
};

// We will generate a vector of all possible next moves of a given board
// We implement the "legal" approach, so only return moves so the king wont be
// in check. For this we first search for each move and check if after that move
// the kind is in check.
// Todo:
//  - may change vector to array
std::vector<Move> generateMoves(const Board& board)
{
    std::vector<Move> moves;
    Color current_color = board.getSideToMove();

    return moves;
}
