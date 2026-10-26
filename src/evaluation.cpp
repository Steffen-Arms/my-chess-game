#include "board.h"
#include <array>

// Here we test a simple material-only evaluation with stategy from Tomasz
// Michniewski: https://chessprogramming.org/Simplified_Evaluation_Function

// For each peace we store a evaluation table to adjust the value of the piece
// depending on the position All these tables are from white perspective, for
// black just mirror the matrix.
constexpr std::array<std::array<int, 8>, 8> pawnTable = {{
    {0, 0, 0, 0, 0, 0, 0, 0},         // row 1
    {5, 10, 10, -20, -20, 10, 10, 5}, // row 2
    {5, -5, -10, 0, 0, -10, -5, 5},   // row 3
    {0, 0, 0, 20, 20, 0, 0, 0},       // row 4
    {5, 5, 10, 25, 25, 10, 5, 5},     // row 5
    {10, 10, 20, 30, 30, 20, 10, 10}, // row 6
    {50, 50, 50, 50, 50, 50, 50, 50}, // row 7
    {0, 0, 0, 0, 0, 0, 0, 0}          // row 8
}};

constexpr std::array<std::array<int, 8>, 8> knightTable = {{
    {-50, -40, -30, -30, -30, -30, -40, -50}, // row 1
    {-40, -20, 0, 5, 5, 0, -20, -40},         // row 2
    {-30, 5, 10, 15, 15, 10, 5, -30},         // row 3
    {-30, 0, 15, 20, 20, 15, 0, -30},         // row 4
    {-30, 5, 15, 20, 20, 15, 5, -30},         // row 5
    {-30, 0, 10, 15, 15, 10, 0, -30},         // row 6
    {-40, -20, 0, 0, 0, 0, -20, -40},         // row 7
    {-50, -40, -30, -30, -30, -30, -40, -50}  // row 8
}};

constexpr std::array<std::array<int, 8>, 8> bishopTable = {{
    {-20, -10, -10, -10, -10, -10, -10, -20}, // row 1
    {-10, 5, 0, 0, 0, 0, 5, -10},             // row 2
    {-10, 10, 10, 10, 10, 10, 10, -10},       // row 3
    {-10, 0, 10, 10, 10, 10, 0, -10},         // row 4
    {-10, 5, 5, 10, 10, 5, 5, -10},           // row 5
    {-10, 0, 5, 10, 10, 5, 0, -10},           // row 6
    {-10, 0, 0, 0, 0, 0, 0, -10},             // row 7
    {-20, -10, -10, -10, -10, -10, -10, -20}  // row 8
}};

constexpr std::array<std::array<int, 8>, 8> rookTable = {{
    {0, 0, 0, 5, 5, 0, 0, 0},       // row 1
    {-5, 0, 0, 0, 0, 0, 0, -5},     // row 2
    {-5, 0, 0, 0, 0, 0, 0, -5},     // row 3
    {-5, 0, 0, 0, 0, 0, 0, -5},     // row 4
    {-5, 0, 0, 0, 0, 0, 0, -5},     // row 5
    {-5, 0, 0, 0, 0, 0, 0, -5},     // row 6
    {5, 10, 10, 10, 10, 10, 10, 5}, // row 7
    {0, 0, 0, 0, 0, 0, 0, 0}        // row 8
}};

constexpr std::array<std::array<int, 8>, 8> queenTable = {{
    {-20, -10, -10, -5, -5, -10, -10, -20}, // row 1
    {-10, 0, 5, 0, 0, 0, 0, -10},           // row 2
    {-10, 5, 5, 5, 5, 5, 0, -10},           // row 3
    {0, 0, 5, 5, 5, 5, 0, -5},              // row 4
    {-5, 0, 5, 5, 5, 5, 0, -5},             // row 5
    {-10, 0, 5, 5, 5, 5, 0, -10},           // row 6
    {-10, 0, 0, 0, 0, 0, 0, -10},           // row 7
    {-20, -10, -10, -5, -5, -10, -10, -20}  // row 8
}};

constexpr std::array<std::array<int, 8>, 8> kingMidTable = {{
    {20, 30, 10, 0, 0, 10, 30, 20},           // row 1
    {20, 20, 0, 0, 0, 0, 20, 20},             // row 2
    {-10, -20, -20, -20, -20, -20, -20, -10}, // row 3
    {-20, -30, -30, -40, -40, -30, -30, -20}, // row 4
    {-30, -40, -40, -50, -50, -40, -40, -30}, // row 5
    {-30, -40, -40, -50, -50, -40, -40, -30}, // row 6
    {-30, -40, -40, -50, -50, -40, -40, -30}, // row 7
    {-30, -40, -40, -50, -50, -40, -40, -30}  // row 8
}};

// we define endgame if both sides don't have a queen or just a queen and a
// minor piece
constexpr std::array<std::array<int, 8>, 8> kingEndTable = {{
    {-50, -30, -30, -30, -30, -30, -30, -50}, // row 1
    {-30, -30, 0, 0, 0, 0, -30, -30},         // row 2
    {-30, -10, 20, 30, 30, 20, -10, -30},     // row 3
    {-30, -10, 30, 40, 40, 30, -10, -30},     // row 4
    {-30, -10, 30, 40, 40, 30, -10, -30},     // row 5
    {-30, -10, 20, 30, 30, 20, -10, -30},     // row 6
    {-30, -20, -10, 0, 0, -10, -20, -30},     // row 7
    {-50, -40, -30, -20, -20, -30, -40, -50}  // row 8
}};

// Each Piece as a seperate value for its own.
constexpr int obtainPieceValue(const PieceType& pieceType)
{
    // note king don't have a value as both side always have one.
    switch (pieceType)
    {
    case PieceType::Pawn:
        return 100;
    case PieceType::Rook:
        return 500;
    case PieceType::Bishop:
        return 330;
    case PieceType::Knight:
        return 320;
    case PieceType::Queen:
        return 900;
    default:
        return 0;
    }
}

constexpr int getPositionValue(Piece piece, std::size_t row, std::size_t column,
                               bool endgame)
{
    int sum = obtainPieceValue(piece.getType());

    // note we have to adjust the row and column as the board use 12x12 grid
    // with 2 squared boarder and the lookup tables use 8x8 also we have to flip
    // the row for the loopup table if we observe black
    std::size_t newRow;
    std::size_t newColumn;

    switch (piece.getType())
    {
    case PieceType::Pawn:
        // note for black we need to mirror the table that we use different
        // indizes
        piece.getColor() == Color::White
            ? sum += pawnTable[row - 2][column - 2]
            : sum += pawnTable[7 - (row - 2)][column];
        break;
    case PieceType::Rook:
        piece.getColor() == Color::White
            ? sum += rookTable[row - 2][column - 2]
            : sum += rookTable[7 - (row - 2)][column];
        break;
    case PieceType::Knight:
        piece.getColor() == Color::White
            ? sum += knightTable[row - 2][column - 2]
            : sum += knightTable[7 - (row - 2)][column];
        break;
    case PieceType::Bishop:
        piece.getColor() == Color::White
            ? sum += bishopTable[row - 2][column - 2]
            : sum += bishopTable[7 - (row - 2)][column];
        break;
    case PieceType::Queen:
        piece.getColor() == Color::White
            ? sum += queenTable[row - 2][column - 2]
            : sum += queenTable[7 - (row - 2)][column];
        break;
    case PieceType::King:
        if (endgame)
        {
            piece.getColor() == Color::White
                ? sum += kingEndTable[row - 2][column - 2]
                : sum += kingEndTable[7 - (row - 2)][column];
        }
        else
        {
            piece.getColor() == Color::White
                ? sum += kingMidTable[row - 2][column - 2]
                : sum += kingMidTable[7 - (row - 2)][column];
        }
        break;
    default:
        break;
    }

    return sum;
}

// always compute whitePoints - blackPoints then flip the sign if black is to
// move
// we define endgame if both sides don't have a queen or just a queen and a
// minor piece
int evaluateBoardPositionByPieceValue(Board& board)
{
    int boardSum{0};
    bool endgame{false};

    for (std::size_t row{2}; row < 10; ++row)
    {
        for (std::size_t column{2}; column < 10; ++column)
        {
            board.getBoard()[row][column].getColor() == Color::White
                ? boardSum += getPositionValue(board.getBoard()[row][column],
                                               row, column, endgame)
                : boardSum -= getPositionValue(board.getBoard()[row][column],
                                               row, column, endgame);
        }
    }

    return board.getSideToMove() == Color::White ? boardSum : -boardSum;
}
