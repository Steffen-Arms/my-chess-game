#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <cassert>
#include <optional>
#include <string_view>

// forward declaration
struct Move;

constexpr std::array<std::pair<std::size_t, std::size_t>, 8> neighborsOffset = {
    {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}}};

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

// It's not possible to reconstruct the castling or enPassange rights from one
// move and board info alone. That's why we need to save these infomation to
// undo a move.
struct UndoInfo
{
    std::optional<Coord> enPassant;
    std::array<bool, 4> castle;
};

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
    bool containEnemyPiece(std::size_t row, std::size_t column) const;
    bool containEnemyPawn(std::size_t row, std::size_t column) const;
    bool containOrthogonalEnemy(std::size_t row, std::size_t column) const;
    bool containDiagonalEnemy(std::size_t row, std::size_t column) const;
    bool isUnderKnightAttack(std::size_t row, std::size_t column) const;
    bool fieldContainEnemyKnight(std::size_t row, std::size_t column) const;
    bool fieldIsUnderAttack(std::size_t row, std::size_t column) const;
    bool fieldIsUnderAttack(Coord fieldCoord) const;
    bool fieldIsUnderOrthogonalAttack(std::size_t row,
                                      std::size_t column) const;
    bool fieldIsUnderDiagonalAttack(std::size_t row, std::size_t column) const;
    bool isUnderPawnAttack(std::size_t row, std::size_t column) const;
    bool isUnderKingAttack(std::size_t row, std::size_t column) const;
    bool kingInCheckAfterMove(Move newMove);

    [[nodiscard]] UndoInfo makeTestMove(Move move);
    void undoTestMove(Move move, const UndoInfo& info);
    [[nodiscard]] UndoInfo makeMove(Move);
    void undoMove(Move move, const UndoInfo& info);

    // For testing purposes.
    void print() const;

    void setEnPassant(Coord coord) { m_enPassantField = coord; }
    std::optional<Coord> getEnPassant() const { return m_enPassantField; }

    void addPiece(std::size_t rowIndex, std::size_t columnIndex,
                  char charPiece);

    void changeSideToMove()
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

    // this array hold the booleans if a rochade is still possible
    // index 0 is white short rochade, index 1 is white long rochade
    // index 2 is black short rochade, index 3 is black long rochade
    std::array<bool, 4> getCastleKing() const { return m_castleKing; }
    void setCastleKing(std::size_t index, bool value)
    {
        assert(index < 4 && "getCastleKing to big index");
        m_castleKing[index] = value;
    }

    void setWhiteKing(Coord newCoord) { m_whiteKing = newCoord; }
    Coord getWhiteKing() { return m_whiteKing; }

    void setBlackKing(Coord newCoord) { m_blackKing = newCoord; }
    Coord getBlackKing() { return m_blackKing; }

  private:
    // Naive implementation: a 12x12 array with a 2-square border around the
    // 8x8 field, which makes checking for valid moves easier.
    board_array m_board;

    Color m_sideToMove;
    int m_halfMoves; // counted for the 50-move rule
    int m_fullMoves;
    Coord m_whiteKing; // as we need to check after each move if the king is in
                       // check, we save the position of the kings seperate.
    Coord m_blackKing;

    // Note we only store a coordinate for enPassant. It is possible that the
    // enemy pawn capture en passant from both side.
    // Because the enPassant rule only count for the next half round this wont
    // grant enpassant right to other pawn.
    std::optional<Coord> m_enPassantField; // square where an en passant capture
                                           // is possible; empty if none

    // Castling rights per color and side.
    // position 0 is for white king side, position 1 is for white queen side
    // postion 2 is for black king side, position 3 is for black queen side
    std::array<bool, 4> m_castleKing;
};

#endif
