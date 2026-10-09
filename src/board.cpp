#include <array>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>

enum class Color
{
    White,
    Black,
    No_color,
};

enum class PieceType
{
    Empty,
    Not_valid,
    Pawn,
    Rook,
    Bishop,
    Knight,
    Queen,
    King,
};

struct Coord
{
    int row{0};
    int col{0};
};

class Piece
{
  private:
    Color m_color;
    PieceType m_pieceType;

  public:
    Piece() : m_color{Color::No_color}, m_pieceType{PieceType::Empty} {};

    Piece(Color color, PieceType pieceType)
        : m_color{color}, m_pieceType{pieceType}
    {
    }

    Color getColor() { return m_color; }
    PieceType getType() { return m_pieceType; }

    // we use the FEN notation for the pieces
    char toChar()
    {
        switch (m_pieceType)
        {
        case PieceType::Empty:
            return '.';
        case PieceType::Not_valid:
            return '#';
        case PieceType::Pawn:
            return 'p';
        case PieceType::Rook:
            return 'r';
        case PieceType::Knight:
            return 'n';
        case PieceType::Bishop:
            return 'b';
        case PieceType::Queen:
            return 'q';
        case PieceType::King:
            return 'k';
        }
        return '?';
    }
};

using board_array = std::array<std::array<Piece, 12>, 12>;

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

class Board
{
  private:
    // naive implementation with a 12 x 12 array to represent the 2 square
    // boundary around the field. This makes the calculation for a valid move
    // easier.
    board_array m_board; // 12 rows and 12 columns

    Color m_sideToMove;
    int m_halfMoves; // we have to count that for the 50 move rule
    std::optional<Coord> m_enPassant; // The square a pawn can be capturedon en
                                      // passant. Empty if none

    // store the castrling rights for each color and which side (King or Queen
    // side).
    bool castlingRightsWhiteKing{true};
    bool castlingRightsWhiteQueen{true};
    bool castlingRightsBlackKing{true};
    bool castlingRightsBlackQueen{true};

  public:
    // with now parameters we generate a board in the start position.
    Board() : m_board{startBoard()}, m_sideToMove{Color::White}, m_halfMoves{0}
    {
    }

    Color const getSideToMove() { return m_sideToMove; }

    // we use this print function for testing purpose
    void print()
    {
        std::cout << "This is the board \n";
        for (auto row : m_board)
        {
            for (auto piece : row)
            {
                std::cout << piece.toChar() << ' ';
            }
            std::cout << '\n';
        }
    }
};
