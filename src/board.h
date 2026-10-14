#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <optional>
#include <string_view>

// forward declaration
struct Move;

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
    std::size_t column{0};
    bool operator==(const Coord&) const = default;
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
            if (m_color == Color::White)
            {
                return 'P';
            }
            else
            {
                return 'p';
            };
        case PieceType::Rook:
            if (m_color == Color::White)
            {
                return 'R';
            }
            else
            {
                return 'r';
            };
        case PieceType::Knight:
            if (m_color == Color::White)
            {
                return 'N';
            }
            else
            {
                return 'n';
            };
        case PieceType::Bishop:
            if (m_color == Color::White)
            {
                return 'B';
            }
            else
            {
                return 'b';
            };
        case PieceType::Queen:
            if (m_color == Color::White)
            {
                return 'Q';
            }
            else
            {
                return 'q';
            };
        case PieceType::King:
            if (m_color == Color::White)
            {
                return 'K';
            }
            else
            {
                return 'k';
            };
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

    // We assume we obtain a string in the FEN format to discribe a board
    // situation.
    Board(std::string_view fen);

    Color getSideToMove() const { return m_sideToMove; }
    void setSideToMove(Color color) { m_sideToMove = color; }

    const board_array& getBoard() const { return m_board; }

    bool isEmptyField(std::size_t row, std::size_t column) const;
    bool containEnemyPiece(std::size_t row, std::size_t column,
                           Color ownColor) const;
    bool containEnemyPawn(std::size_t row, std::size_t column,
                          Color ownColor) const;

    // For testing purposes.
    void print() const;

    void setEnPassant(Coord coord) { m_enPassant = coord; }
    std::optional<Coord> getEnPassant() const { return m_enPassant; }

    void makeMove(Move);
    void undoMove(Move);

    void addPiece(std::size_t rowIndex, std::size_t columnIndex,
                  char charPiece);

    void changeColor()
    {
        if (m_sideToMove == Color::Black)
        {
            m_sideToMove = Color::White;
        }
        else
        {
            m_sideToMove = Color::Black;
        }
    }

  private:
    // Naive implementation: a 12x12 array with a 2-square border around the
    // 8x8 field, which makes checking for valid moves easier.
    board_array m_board;

    Color m_sideToMove;
    int m_halfMoves; // counted for the 50-move rule

    // Note we only store a coordinate for enPassant. It is possible that the
    // enemy pawn capture en passant from both side.
    // Because the enPassant rule only count for the next half round this wont
    // grant enpassant right to other pawn.
    std::optional<Coord> m_enPassant; // square where an en passant capture is
                                      // possible; empty if none

    // Castling rights per color and side.
    bool m_castleWhiteKing{true};
    bool m_castleWhiteQueen{true};
    bool m_castleBlackKing{true};
    bool m_castleBlackQueen{true};
};

#endif
