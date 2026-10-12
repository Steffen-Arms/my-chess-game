#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <optional>

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
    std::size_t row{0};
    std::size_t col{0};
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

    Color getColor() const { return m_color; }
    PieceType getType() const { return m_pieceType; }

    // we use the FEN notation for the pieces
    char toChar() const
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

class Board
{
  public:
    // With no parameters, the board is created in the start position.
    Board();

    Color getSideToMove() const { return m_sideToMove; }
    const board_array& getBoard() const { return m_board; }

    bool isEmptyField(std::size_t row, std::size_t column) const;
    bool Board::containEnemyPiece(std::size_t row, std::size_t column,
                                  Color ownColor) const;

    // For testing purposes.
    void print() const;

  private:
    // Naive implementation: a 12x12 array with a 2-square border around the
    // 8x8 field, which makes checking for valid moves easier.
    board_array m_board;

    Color m_sideToMove;
    int m_halfMoves;                  // counted for the 50-move rule
    std::optional<Coord> m_enPassant; // square where an en passant capture is
                                      // possible; empty if none

    // Castling rights per color and side.
    bool m_castleWhiteKing{true};
    bool m_castleWhiteQueen{true};
    bool m_castleBlackKing{true};
    bool m_castleBlackQueen{true};
};

#endif
