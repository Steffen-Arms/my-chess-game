#include "board.h"
#include "move_list.h"
#include <cassert>
#include <vector>

void addMovesOfOnePawn(const Piece& piece, const Board& board_ref, size_t row,
                       size_t column, MoveList& moves)
{
    if (piece.getColor() == Color::White)
    { // depending on the color of the pawn we specify if he is allow to
      // move 2 fields.
        if (row == 3 && board_ref.isEmptyField(row + 1, column) &&
            board_ref.isEmptyField(row + 1, column))
        {
            moves.push_back(Move{{row, column}, {row + 2, column}});
        }
        if (row == 8 && board_ref.isEmptyField(row, column + 1))
        { // in this case the pawn reach the other side and can transform to
          // a queen, knight, bishop or rook
            // Even it make little sense to transform the Pawn to a Bishop
            // or rook we will keep it as a option to reflect the rules.
            moves.push_back(Move{{row, column},
                                 {row + 1, column},
                                 Piece{Color::White, PieceType::Queen}});
            moves.push_back(Move{{row, column},
                                 {row + 1, column},
                                 Piece{Color::White, PieceType::Rook}});
            moves.push_back(Move{{row, column},
                                 {row + 1, column},
                                 Piece{Color::White, PieceType::Bishop}});
            moves.push_back(Move{{row, column},
                                 {row + 1, column},
                                 Piece{Color::White, PieceType::Knight}});

            ///////////////////////////////////////////////////
            // now check if we can capture a piece to move one field diagonal
            if (board_ref.containEnemyPiece(row + 1, column + 1, Color::White))
            {
                moves.push_back(Move{{row, column},
                                     {row + 1, column + 1},
                                     Piece{Color::White, PieceType::Queen}});
                moves.push_back(Move{{row, column},
                                     {row + 1, column + 1},
                                     Piece{Color::White, PieceType::Rook}});
                moves.push_back(Move{{row, column},
                                     {row + 1, column + 1},
                                     Piece{Color::White, PieceType::Bishop}});
                moves.push_back(Move{{row, column},
                                     {row + 1, column + 1},
                                     Piece{Color::White, PieceType::Knight}});
            }
            if (board_ref.containEnemyPiece(row + 1, column - 1, Color::White))
            {
                moves.push_back(Move{{row, column},
                                     {row + 1, column - 1},
                                     Piece{Color::White, PieceType::Queen}});
                moves.push_back(Move{{row, column},
                                     {row + 1, column - 1},
                                     Piece{Color::White, PieceType::Rook}});
                moves.push_back(Move{{row, column},
                                     {row + 1, column - 1},
                                     Piece{Color::White, PieceType::Bishop}});
                moves.push_back(Move{{row, column},
                                     {row + 1, column - 1},
                                     Piece{Color::White, PieceType::Knight}});
            }
        }
        if (row < 8)
        {
            if (board_ref.isEmptyField(row + 1, column))
            {
                moves.push_back(Move{{row, column}, {row + 1, column}});
            }
            ////////////////
            // Add moves where we captur a other piece diagonal and are not on
            // the row 8 ToDo: Maybe save these special moves seperate or with a
            // flag?
            if (board_ref.containEnemyPiece(row + 1, column + 1, Color::White))
            {
                moves.push_back(Move{{row, column}, {row + 1, column + 1}});
            }
            if (board_ref.containEnemyPiece(row + 1, column - 1, Color::White))
            {
                moves.push_back(Move{{row, column}, {row + 1, column - 1}});
            }
        }
    }
    else
    { // here we define the black pawn analog to the above white pawn moves
        if (row == 8 && board_ref.isEmptyField(row - 1, column) &&
            board_ref.isEmptyField(row - 2, column))
        { // if the color is black and we are in the start row we can move
          // two fields
            moves.push_back(Move{{row, column}, {row - 2, column}});
        }
        if (row == 3 && board_ref.isEmptyField(row - 1, column))
        {
            moves.push_back(Move{{row, column},
                                 {row - 1, column},
                                 Piece{Color::Black, PieceType::Queen}});
            moves.push_back(Move{{row, column},
                                 {row - 1, column},
                                 Piece{Color::Black, PieceType::Rook}});
            moves.push_back(Move{{row, column},
                                 {row - 1, column},
                                 Piece{Color::Black, PieceType::Bishop}});
            moves.push_back(Move{{row, column},
                                 {row - 1, column},
                                 Piece{Color::Black, PieceType::Knight}});
        }
        if (row > 3 && board_ref.isEmptyField(row - 1, column))
        {
            moves.push_back(Move{{row, column}, {row - 1, column}});
        }
    }
}

// note "moves" is a out parameter
void addMovesOfOnePiece(const Piece& piece, const Board& board_ref, size_t row,
                        size_t column, MoveList& moves)
{
    // note we don't get of the array index as we have the 2 field thick
    // boundary
    assert(row > 2 && row < 10 && "row index is in the boundary");
    assert(column > 2 && column < 10 && "column index is in the boundary");

    switch (piece.getType())
    {
    case PieceType::Pawn:
        addMovesOfOnePawn(piece, board_ref, row, column, moves);
        break;
    case PieceType::Rook:
    {
        // first we find all moves horizontal right to the rook
        std::size_t nextColumn{column + 1};
        while (board_ref.isEmptyField(row, nextColumn))
        {
            moves.push_back(Move{{row, column}, {row, nextColumn}});
            ++nextColumn;
        }
        // then we find all moves horizontal left to the rook
        nextColumn = column - 1;
        while (board_ref.isEmptyField(row, nextColumn))
        {
            moves.push_back(Move{{row, column}, {row, nextColumn}});
            --nextColumn;
        }
        // then we find all moves verticaly up
        std::size_t nextRow{row + 1};
        while (board_ref.isEmptyField(nextRow, column))
        {
            moves.push_back(Move{{row, column}, {nextRow, column}});
            ++nextRow;
        }
        // now we find all moves vertical down
        nextRow = row - 1;
        while (board_ref.isEmptyField(nextRow, column))
        {
            moves.push_back(Move{{row, column}, {nextRow, column}});
            --nextRow;
        }
        break;
    }
    case PieceType::Knight:
        // the knight has 8 possible moves
        if (board_ref.isEmptyField(row + 2, column + 1))
        {
            moves.push_back(Move{{row, column}, {row + 2, column + 1}});
        }
        if (board_ref.isEmptyField(row + 1, column + 2))
        {
            moves.push_back(Move{{row, column}, {row + 1, column + 2}});
        }

        if (board_ref.isEmptyField(row - 1, column + 2))
        {
            moves.push_back(Move{{row, column}, {row - 1, column + 2}});
        }
        if (board_ref.isEmptyField(row - 2, column + 1))
        {
            moves.push_back(Move{{row, column}, {row - 2, column + 1}});
        }

        if (board_ref.isEmptyField(row - 2, column - 1))
        {
            moves.push_back(Move{{row, column}, {row - 2, column - 1}});
        }
        if (board_ref.isEmptyField(row - 1, column - 2))
        {
            moves.push_back(Move{{row, column}, {row - 1, column - 2}});
        }

        if (board_ref.isEmptyField(row + 1, column - 2))
        {
            moves.push_back(Move{{row, column}, {row + 1, column - 2}});
        }
        if (board_ref.isEmptyField(row + 2, column - 1))
        {
            moves.push_back(Move{{row, column}, {row + 1, column - 1}});
        }
        break;
    case PieceType::Bishop:
    case PieceType::Queen:
    case PieceType::King:

    default:
        break;
    }
}

// We will generate a vector of all possible next moves of a given board
// We implement the "legal" approach, so only return moves so the king wont be
// in check. For this we first search for each move and check if after that move
// the king is in check.
// Todo:
//  - may change vector to array
MoveList generateMoves(const Board& board)
{
    MoveList moves;

    Color current_color = board.getSideToMove();

    const board_array& board_ref = board.getBoard();

    for (size_t row{2}; row < 10; ++row)
    {
        for (size_t column{2}; column < 10; ++column)
        {
            const Piece& currentPiece = board.getBoard()[row][column];

            if (currentPiece.getColor() == current_color &&
                currentPiece.getType() != PieceType::Not_valid &&
                currentPiece.getType() != PieceType::Empty)
            {
                addMovesOfOnePiece(currentPiece, board, row, column, moves);
            }
        }
    }

    return moves;
}
