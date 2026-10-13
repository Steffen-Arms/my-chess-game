#include "board.h"
#include "move_list.h"
#include <array>
#include <iostream>
#include <string>
#include <string_view>

board_array startBoard()
{
    board_array board;
    // first we fill the boundaries with not valid squares
    board[0].fill(Piece(Color::No_color, PieceType::Not_valid));
    board[1].fill(Piece(Color::No_color, PieceType::Not_valid));
    for (std::size_t row{2}; row < 10; ++row)
    {
        board[row][0] = Piece(Color::No_color, PieceType::Not_valid);
        board[row][1] = Piece(Color::No_color, PieceType::Not_valid);
        board[row][10] = Piece(Color::No_color, PieceType::Not_valid);
        board[row][11] = Piece(Color::No_color, PieceType::Not_valid);
    }
    board[10].fill(Piece(Color::No_color, PieceType::Not_valid));
    board[11].fill(Piece(Color::No_color, PieceType::Not_valid));

    // now we place the white pieces
    board[2][2] = Piece(Color::White, PieceType::Rook);
    board[2][3] = Piece(Color::White, PieceType::Knight);
    board[2][4] = Piece(Color::White, PieceType::Bishop);
    board[2][5] = Piece(Color::White, PieceType::Queen);
    board[2][6] = Piece(Color::White, PieceType::King);
    board[2][7] = Piece(Color::White, PieceType::Bishop);
    board[2][8] = Piece(Color::White, PieceType::Knight);
    board[2][9] = Piece(Color::White, PieceType::Rook);

    // not all the squares in between already initialize as Piesce with no_color
    // and empty

    // now we place the black pieces
    board[9][2] = Piece(Color::Black, PieceType::Rook);
    board[9][3] = Piece(Color::Black, PieceType::Knight);
    board[9][4] = Piece(Color::Black, PieceType::Bishop);
    board[9][5] = Piece(Color::Black, PieceType::Queen);
    board[9][6] = Piece(Color::Black, PieceType::King);
    board[9][7] = Piece(Color::Black, PieceType::Bishop);
    board[9][8] = Piece(Color::Black, PieceType::Knight);
    board[9][9] = Piece(Color::Black, PieceType::Rook);

    // now we the black and white pawn
    for (std::size_t col{2}; col < 10; ++col)
    {
        board[3][col] = Piece(Color::White, PieceType::Pawn);
        board[8][col] = Piece(Color::Black, PieceType::Pawn);
    }

    return board;
}

Board::Board()
    : m_board{startBoard()}, m_sideToMove{Color::White}, m_halfMoves{0}
{
}

bool Board::isEmptyField(std::size_t row, std::size_t column) const
{
    return m_board[row][column].getType() == PieceType::Empty;
}

// return false if the field is empty or not_valid or contain a piece of
// ownColor
bool Board::containEnemyPiece(std::size_t row, std::size_t column,
                              Color ownColor) const
{
    // note if a field is empty or not valid it hat "no_color" as color. So it's
    // enough to check agains the color.
    if (ownColor == Color::White)
    {
        return m_board[row][column].getColor() == Color::Black;
    }
    else
    {
        return m_board[row][column].getColor() == Color::White;
    }
}

bool Board::containEnemyPawn(std::size_t row, std::size_t column,
                             Color ownColor) const
{
    // note if a field is empty or not valid it hat "no_color" as color. So it's
    // enough to check agains the color.
    if (ownColor == Color::White)
    {
        return m_board[row][column].getColor() == Color::Black &&
               m_board[row][column].getType() == PieceType::Pawn;
    }
    else
    {
        return m_board[row][column].getColor() == Color::White &&
               m_board[row][column].getType() == PieceType::Pawn;
    }
}

void Board::print() const
{
    std::cout << "This is the board\n";
    for (const auto& row : m_board)
    {
        for (const auto& piece : row)
        {
            std::cout << piece.toChar() << ' ';
        }
        std::cout << '\n';
    }
}

// ToDo: implement castle
void Board::makeMove(Move move)
{
    m_board[move.to.row][move.to.column] =
        m_board[move.from.row][move.from.column];
    m_board[move.from.row][move.from.column] =
        Piece{}; // if we make a move we leave a emtpy field behind
}

// ToDo: implement castle
void Board::undoMove(Move move)
{
    m_board[move.from.row][move.from.column] =
        m_board[move.to.row][move.to.column];

    // note if we don't capture a piece move.capturePiece give as a empty piece.
    m_board[move.to.row][move.to.column] = move.capturePiece;
}
