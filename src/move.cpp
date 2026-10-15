#include "board.h"
#include "move_list.h"
#include <cassert>
#include <vector>

////////////////////////////////////////////////////////////////////////
// Here we define the functions to calculate each possible move for each piece
// seperatly.

/////////////////////
// start with the pawn
//  Note that board_ref is not const as we have to add enPassage flag
void addMovesOfOnePawn(const Piece& piece, const Board& board_ref, size_t row,
                       size_t column, MoveList& moves)
{
    if (piece.getColor() == Color::White)
    { // depending on the color of the pawn we specify if he is allow to
      // move 2 fields.
        if (row == 3 && board_ref.isEmptyField(row + 1, column) &&
            board_ref.isEmptyField(row + 2, column))
        {
            // here we have to check if we bypass a enemy pawn and so activate
            // en passage
            if (board_ref.containEnemyPawn(row + 2, column + 1, Color::White) ||
                board_ref.containEnemyPawn(row + 2, column - 1, Color::White))
            {
                // here we just store that this move create a en passage right.
                // If we select this move later we will save this information to
                // the board.
                moves.push_back(Move{{row, column},
                                     {row + 2, column},
                                     Piece{},
                                     Piece{Color::Black, PieceType::Pawn},
                                     true});
            }
            else
            {
                moves.push_back(Move{{row, column}, {row + 2, column}});
            }
        }
        if (row == 8 && board_ref.isEmptyField(row, column + 1))
        { // in this case the pawn reach the other side and can transform to
          // a queen, knight, bishop or rook
            // Even it make little sense to transform the Pawn to a Bishop
            // or rook we will keep it as a option to reflect the rules.
            moves.push_back(Move{{row, column},
                                 {row + 1, column},
                                 Piece{},
                                 Piece{Color::White, PieceType::Queen}});
            moves.push_back(Move{{row, column},
                                 {row + 1, column},
                                 Piece{},
                                 Piece{Color::White, PieceType::Rook}});
            moves.push_back(Move{{row, column},
                                 {row + 1, column},
                                 Piece{},
                                 Piece{Color::White, PieceType::Bishop}});
            moves.push_back(Move{{row, column},
                                 {row + 1, column},
                                 Piece{},
                                 Piece{Color::White, PieceType::Knight}});

            ///////////////////////////////////////////////////
            // now check if we can capture a piece to move one field diagonal
            if (board_ref.containEnemyPiece(row + 1, column + 1, Color::White))
            {
                moves.push_back(Move{{row, column},
                                     {row + 1, column + 1},
                                     board_ref.getBoard()[row + 1][column + 1],
                                     Piece{Color::White, PieceType::Queen}});
                moves.push_back(Move{{row, column},
                                     {row + 1, column + 1},
                                     board_ref.getBoard()[row + 1][column + 1],
                                     Piece{Color::White, PieceType::Rook}});
                moves.push_back(Move{{row, column},
                                     {row + 1, column + 1},
                                     board_ref.getBoard()[row + 1][column + 1],
                                     Piece{Color::White, PieceType::Bishop}});
                moves.push_back(Move{{row, column},
                                     {row + 1, column + 1},
                                     board_ref.getBoard()[row + 1][column + 1],
                                     Piece{Color::White, PieceType::Knight}});
            }
            if (board_ref.containEnemyPiece(row + 1, column - 1, Color::White))
            {
                moves.push_back(Move{{row, column},
                                     {row + 1, column - 1},
                                     board_ref.getBoard()[row + 1][column + 1],
                                     Piece{Color::White, PieceType::Queen}});
                moves.push_back(Move{{row, column},
                                     {row + 1, column - 1},
                                     board_ref.getBoard()[row + 1][column + 1],
                                     Piece{Color::White, PieceType::Rook}});
                moves.push_back(Move{{row, column},
                                     {row + 1, column - 1},
                                     board_ref.getBoard()[row + 1][column + 1],
                                     Piece{Color::White, PieceType::Bishop}});
                moves.push_back(Move{{row, column},
                                     {row + 1, column - 1},
                                     board_ref.getBoard()[row + 1][column + 1],
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
            // the row 8
            if (board_ref.containEnemyPiece(row + 1, column + 1, Color::White))
            {
                moves.push_back(
                    Move{{row, column},
                         {row + 1, column + 1},
                         board_ref.getBoard()[row + 1][column + 1]});
            }
            if (board_ref.containEnemyPiece(row + 1, column - 1, Color::White))
            {
                moves.push_back(
                    Move{{row, column},
                         {row + 1, column - 1},
                         board_ref.getBoard()[row + 1][column - 1]});
            }
        }

        // here we handle to capture a piece with en passage moves
        if (row == 6)
        {
            // en passage to the right or left
            if (board_ref.getEnPassant() == Coord{row + 1, column - 1})
            {
                moves.push_back(Move{{row, column}, {row + 1, column - 1}});
            }
            if (board_ref.getEnPassant() == Coord{row + 1, column + 1})
            {
                moves.push_back(Move{{row, column}, {row + 1, column + 1}});
            }
        }
    }
    else
    {
        // here we define the black pawn analog to the above white pawn moves
        ///////////////////////////////////////////
        ///

        // depending on the color of the pawn we specify if he is allow to
        // move 2 fields.
        if (row == 8 && board_ref.isEmptyField(row - 1, column) &&
            board_ref.isEmptyField(row - 2, column))
        {
            // here we have to check if we bypass a enemy pawn and so activate
            // en passage
            if (board_ref.containEnemyPawn(row - 2, column + 1, Color::Black) ||
                board_ref.containEnemyPawn(row - 2, column - 1, Color::Black))
            {
                // here we just store that this move create a en passage right.
                // If we select this move later we will save this information to
                // the board.
                moves.push_back(Move{{row, column},
                                     {row - 2, column},
                                     Piece{},
                                     Piece{Color::White, PieceType::Pawn},
                                     true});
            }
            else
            {
                moves.push_back(Move{{row, column}, {row - 2, column}});
            }
        }

        if (row == 3 && board_ref.isEmptyField(row, column - 1))
        { // in this case the pawn reach the other side and can transform to
          // a queen, knight, bishop or rook
            // Even it make little sense to transform the Pawn to a Bishop
            // or rook we will keep it as a option to reflect the rules.
            moves.push_back(Move{{row, column},
                                 {row - 1, column},
                                 Piece{},
                                 Piece{Color::Black, PieceType::Queen}});
            moves.push_back(Move{{row, column},
                                 {row - 1, column},
                                 Piece{},
                                 Piece{Color::Black, PieceType::Rook}});
            moves.push_back(Move{{row, column},
                                 {row - 1, column},
                                 Piece{},
                                 Piece{Color::Black, PieceType::Bishop}});
            moves.push_back(Move{{row, column},
                                 {row - 1, column},
                                 Piece{},
                                 Piece{Color::Black, PieceType::Knight}});

            ///////////////////////////////////////////////////
            // now check if we can capture a piece to move one field diagonal
            if (board_ref.containEnemyPiece(row - 1, column + 1, Color::Black))
            {
                moves.push_back(Move{{row, column},
                                     {row - 1, column + 1},
                                     board_ref.getBoard()[row - 1][column + 1],
                                     Piece{Color::Black, PieceType::Queen}});
                moves.push_back(Move{{row, column},
                                     {row - 1, column + 1},
                                     board_ref.getBoard()[row - 1][column + 1],
                                     Piece{Color::Black, PieceType::Rook}});
                moves.push_back(Move{{row, column},
                                     {row - 1, column + 1},
                                     board_ref.getBoard()[row - 1][column + 1],
                                     Piece{Color::Black, PieceType::Bishop}});
                moves.push_back(Move{{row, column},
                                     {row - 1, column + 1},
                                     board_ref.getBoard()[row - 1][column + 1],
                                     Piece{Color::Black, PieceType::Knight}});
            }
            if (board_ref.containEnemyPiece(row - 1, column - 1, Color::White))
            {
                moves.push_back(Move{{row, column},
                                     {row - 1, column - 1},
                                     board_ref.getBoard()[row - 1][column + 1],
                                     Piece{Color::Black, PieceType::Queen}});
                moves.push_back(Move{{row, column},
                                     {row - 1, column - 1},
                                     board_ref.getBoard()[row - 1][column + 1],
                                     Piece{Color::Black, PieceType::Rook}});
                moves.push_back(Move{{row, column},
                                     {row - 1, column - 1},
                                     board_ref.getBoard()[row - 1][column + 1],
                                     Piece{Color::Black, PieceType::Bishop}});
                moves.push_back(Move{{row, column},
                                     {row - 1, column - 1},
                                     board_ref.getBoard()[row - 1][column + 1],
                                     Piece{Color::Black, PieceType::Knight}});
            }
        }

        // Here we handle normal moves
        if (row > 3)
        {
            if (board_ref.isEmptyField(row - 1, column))
            {
                moves.push_back(Move{{row, column}, {row - 1, column}});
            }
            ////////////////
            // Add moves where we captur a other piece diagonal and are not on
            // the row 3
            if (board_ref.containEnemyPiece(row - 1, column + 1, Color::Black))
            {
                moves.push_back(
                    Move{{row, column},
                         {row - 1, column + 1},
                         board_ref.getBoard()[row - 1][column + 1]});
            }
            if (board_ref.containEnemyPiece(row - 1, column - 1, Color::Black))
            {
                moves.push_back(
                    Move{{row, column},
                         {row - 1, column - 1},
                         board_ref.getBoard()[row - 1][column - 1]});
            }
        }

        // here we handle to capture a piece with en passage moves
        if (row == 5)
        {
            // en passage to the right or left
            if (board_ref.getEnPassant() == Coord{row - 1, column - 1})
            {
                moves.push_back(Move{{row, column}, {row - 1, column - 1}});
            }
            if (board_ref.getEnPassant() == Coord{row - 1, column + 1})
            {
                moves.push_back(Move{{row, column}, {row - 1, column + 1}});
            }
        }
    }
}

/////////////////////
// define moves for the rook
void addMovesOfOneRook(const Piece& piece, const Board& board_ref, size_t row,
                       size_t column, MoveList& moves)
{
    Color ownColor = piece.getColor();

    // first we find all moves horizontal right to the rook
    std::size_t nextColumn{column + 1};
    while (board_ref.isEmptyField(row, nextColumn))
    {
        moves.push_back(Move{{row, column}, {row, nextColumn}});
        ++nextColumn;
    }
    if (board_ref.containEnemyPiece(row, nextColumn, ownColor))
    {
        moves.push_back(Move{{row, column},
                             {row, nextColumn},
                             board_ref.getBoard()[row][nextColumn]});
    }

    // then we find all moves horizontal left to the rook
    nextColumn = column - 1;
    while (board_ref.isEmptyField(row, nextColumn))
    {
        moves.push_back(Move{{row, column}, {row, nextColumn}});
        --nextColumn;
    }
    if (board_ref.containEnemyPiece(row, nextColumn, ownColor))
    {
        moves.push_back(Move{{row, column},
                             {row, nextColumn},
                             board_ref.getBoard()[row][nextColumn]});
    }

    // then we find all moves verticaly up
    std::size_t nextRow{row + 1};
    while (board_ref.isEmptyField(nextRow, column))
    {
        moves.push_back(Move{{row, column}, {nextRow, column}});
        ++nextRow;
    }
    if (board_ref.containEnemyPiece(nextRow, column, ownColor))
    {
        moves.push_back(Move{{row, column},
                             {row, nextColumn},
                             board_ref.getBoard()[nextRow][column]});
    }

    // now we find all moves vertical down
    nextRow = row - 1;
    while (board_ref.isEmptyField(nextRow, column))
    {
        moves.push_back(Move{{row, column}, {nextRow, column}});
        --nextRow;
    }
    if (board_ref.containEnemyPiece(nextRow, column, ownColor))
    {
        moves.push_back(Move{{row, column},
                             {row, nextColumn},
                             board_ref.getBoard()[nextRow][column]});
    }
}

/////////////////////
// define moves for the Knight
void addMovesOfOneKnight(const Piece& piece, const Board& board_ref, size_t row,
                         size_t column, MoveList& moves)
{
    Color ownColor = piece.getColor();

    // the knight has 8 possible moves
    if (board_ref.isEmptyField(row + 2, column + 1))
    {
        moves.push_back(Move{{row, column}, {row + 2, column + 1}});
    }
    else if (board_ref.containEnemyPawn(row + 2, column + 1, ownColor))
    {
        moves.push_back(Move{{row, column},
                             {row + 2, column + 1},
                             board_ref.getBoard()[row + 2][column + 1]});
    }

    if (board_ref.isEmptyField(row + 1, column + 2))
    {
        moves.push_back(Move{{row, column}, {row + 1, column + 2}});
    }
    else if (board_ref.containEnemyPiece(row + 1, column + 2, ownColor))
    {
        moves.push_back(Move{{row, column},
                             {row + 1, column + 2},
                             board_ref.getBoard()[row + 1][column + 2]});
    }

    if (board_ref.isEmptyField(row - 1, column + 2))
    {
        moves.push_back(Move{{row, column}, {row - 1, column + 2}});
    }
    else if (board_ref.containEnemyPiece(row - 1, column + 2, ownColor))
    {
        moves.push_back(Move{{row, column},
                             {row - 1, column + 2},
                             board_ref.getBoard()[row - 1][column + 2]});
    }

    if (board_ref.isEmptyField(row - 2, column + 1))
    {
        moves.push_back(Move{{row, column}, {row - 2, column + 1}});
    }
    else if (board_ref.containEnemyPiece(row - 2, column + 1, ownColor))
    {
        moves.push_back(Move{{row, column},
                             {row - 2, column + 1},
                             board_ref.getBoard()[row - 2][column + 1]});
    }

    if (board_ref.isEmptyField(row - 2, column - 1))
    {
        moves.push_back(Move{{row, column}, {row - 2, column - 1}});
    }
    else if (board_ref.containEnemyPiece(row - 2, column - 1, ownColor))
    {
        moves.push_back(Move{{row, column},
                             {row - 2, column - 1},
                             board_ref.getBoard()[row - 2][column - 1]});
    }

    if (board_ref.isEmptyField(row - 1, column - 2))
    {
        moves.push_back(Move{{row, column}, {row - 1, column - 2}});
    }
    else if (board_ref.containEnemyPiece(row - 1, column - 2, ownColor))
    {
        moves.push_back(Move{{row, column},
                             {row - 1, column - 2},
                             board_ref.getBoard()[row - 1][column - 2]});
    }

    if (board_ref.isEmptyField(row + 1, column - 2))
    {
        moves.push_back(Move{{row, column}, {row + 1, column - 2}});
    }
    else if (board_ref.containEnemyPiece(row + 1, column - 2, ownColor))
    {
        moves.push_back(Move{{row, column},
                             {row + 1, column - 2},
                             board_ref.getBoard()[row + 1][column - 2]});
    }

    if (board_ref.isEmptyField(row + 2, column - 1))
    {
        moves.push_back(Move{{row, column}, {row + 2, column - 1}});
    }
    else if (board_ref.containEnemyPiece(row + 2, column - 1, ownColor))
    {
        moves.push_back(Move{{row, column},
                             {row + 2, column - 1},
                             board_ref.getBoard()[row + 2][column - 1]});
    }
}

/////////////////////
// define moves for the bishop
void addMovesOfOneBishop(const Piece& piece, const Board& board_ref, size_t row,
                         size_t column, MoveList& moves)
{
    Color ownColor = piece.getColor();
    // now we find all moves diagonal upper right
    std::size_t nextRow = row + 1;
    std::size_t nextColumn = column + 1;
    while (board_ref.isEmptyField(nextRow, nextColumn))
    {
        moves.push_back(Move{{row, column}, {nextRow, nextColumn}});
        ++nextRow;
        ++nextColumn;
    }
    if (board_ref.containEnemyPiece(nextRow, nextColumn, ownColor))
    {
        moves.push_back(Move{{row, column},
                             {row, nextColumn},
                             board_ref.getBoard()[nextRow][column]});
    }

    // now we find all moves diagonal down right
    nextRow = row - 1;
    nextColumn = column + 1;
    while (board_ref.isEmptyField(nextRow, nextColumn))
    {
        moves.push_back(Move{{row, column}, {nextRow, nextColumn}});
        --nextRow;
        ++nextColumn;
    }
    if (board_ref.containEnemyPiece(nextRow, nextColumn, ownColor))
    {
        moves.push_back(Move{{row, column},
                             {row, nextColumn},
                             board_ref.getBoard()[nextRow][column]});
    }

    // now we find all moves diagonal down left
    nextRow = row - 1;
    nextColumn = column - 1;
    while (board_ref.isEmptyField(nextRow, nextColumn))
    {
        moves.push_back(Move{{row, column}, {nextRow, nextColumn}});
        --nextRow;
        --nextColumn;
    }
    if (board_ref.containEnemyPiece(nextRow, nextColumn, ownColor))
    {
        moves.push_back(Move{{row, column},
                             {row, nextColumn},
                             board_ref.getBoard()[nextRow][column]});
    }

    // now we find all moves diagonal upper left
    nextRow = row + 1;
    nextColumn = column - 1;
    while (board_ref.isEmptyField(nextRow, nextColumn))
    {
        moves.push_back(Move{{row, column}, {nextRow, nextColumn}});
        ++nextRow;
        --nextColumn;
    }
    if (board_ref.containEnemyPiece(nextRow, nextColumn, ownColor))
    {
        moves.push_back(Move{{row, column},
                             {row, nextColumn},
                             board_ref.getBoard()[nextRow][column]});
    }
}

/////////////////////
// define moves for the rook
void addMovesOfOneQueen(const Piece& piece, const Board& board_ref, size_t row,
                        size_t column, MoveList& moves)
{
    // as the queen is the combination of rook and bishop we can reuse their
    // code here
    addMovesOfOneRook(piece, board_ref, row, column, moves);
    addMovesOfOneBishop(piece, board_ref, row, column, moves);
}

// Add a move if we don't hit a boundary
void addMoveIfaField(Color ownColor, const Board& board_ref, size_t row,
                     size_t column, size_t nextRow, size_t nextColumn,
                     MoveList& moves)
{
    if (board_ref.isEmptyField(nextRow, nextColumn))
    {
        moves.push_back(Move{{row, column}, {nextRow, nextColumn}});
    }
    else if (board_ref.containEnemyPiece(nextRow, nextColumn, ownColor))
    {
        moves.push_back(Move{{row, column},
                             {nextRow, nextColumn},
                             board_ref.getBoard()[nextRow][nextColumn]});
    }
}

bool fieldIsUnderOrthogonalAttack(const Board& board_ref, std::size_t row,
                                  std::size_t column)
{
    // We check for each direction the next field that is not empty. Then we
    // check if it contain a dangerous enemy piece.
    Color ownColor = board_ref.getSideToMove();
    std::size_t nextColumn = column + 1;
    while (board_ref.isEmptyField(row, nextColumn))
    {
        ++nextColumn;
    }
    if (board_ref.containOrthogonalEnemy(row, nextColumn, ownColor))
    {
        return true;
    }
    nextColumn = column - 1;
    while (board_ref.isEmptyField(row, nextColumn))
    {
        --nextColumn;
    }
    if (board_ref.containOrthogonalEnemy(row, nextColumn, ownColor))
    {
        return true;
    }

    std::size_t nextRow = row + 1;
    while ((board_ref.isEmptyField(nextRow, column)))
    {
        ++nextRow;
    }
    if (board_ref.containOrthogonalEnemy(nextRow, column, ownColor))
    {
        return true;
    }
    nextRow = row - 1;
    while (board_ref.containOrthogonalEnemy(nextRow, column, ownColor))
    {
        --nextRow;
    }
    if (board_ref.containOrthogonalEnemy(nextRow, column, ownColor))
    {
        return true;
    }

    // if we dont find orthogonal enemies we return false
    return false;
}

bool fieldIsUnderDiagonalAttack(const Board& board_ref, std::size_t row,
                                std::size_t column)
{
    Color ownColor = board_ref.getSideToMove();
    std::size_t nextRow = row + 1;
    std::size_t nextColumn = column + 1;

    while (board_ref.isEmptyField(nextRow, nextColumn))
    {
        ++nextRow;
        ++nextColumn;
    }
    if (board_ref.containDiagonalEnemy(nextRow, nextColumn, ownColor))
        return true;

    nextRow = row - 1;
    nextColumn = column - 1;
    while ((board_ref.isEmptyField(nextRow, nextColumn)))
    {
        --nextRow;
        --nextColumn;
    }
    if (board_ref.containDiagonalEnemy(nextRow, nextColumn, ownColor))
        return true;

    nextRow = row + 1;
    nextColumn = column - 1;
    while (board_ref.isEmptyField(nextRow, nextColumn))
    {
        ++nextRow;
        --nextColumn;
    }
    if (board_ref.containDiagonalEnemy(nextRow, nextColumn, ownColor))
        return true;

    nextRow = row - 1;
    nextColumn = column + 1;
    while (board_ref.isEmptyField(nextRow, nextColumn))
    {
        --nextRow;
        ++nextColumn;
    }
    if (board_ref.containDiagonalEnemy(nextRow, nextColumn, ownColor))
        return true;

    // if we don't find diagonal enemies we return false
    return false;
}

// return true if a piece of the enemy attack this field right now.
bool fieldIsUnderAttack(const Board& board_ref, std::size_t row,
                        std::size_t column)
{

    // First we check for orthogonal enemies
    if (fieldIsUnderOrthogonalAttack(board_ref, row, column))
        return true;

    // now we check for diagonal enemies
    if (fieldIsUnderDiagonalAttack(board_ref, row, column))
        return true;
}

// Note: here we don't check if the king is in check.
void addMovesOfOneKing(const Piece& piece, const Board& board_ref, size_t row,
                       size_t column, MoveList& moves)
{
    Color ownColor = piece.getColor();

    addMoveIfaField(ownColor, board_ref, row, column, row + 1, column, moves);
    addMoveIfaField(ownColor, board_ref, row, column, row + 1, column + 1,
                    moves);
    addMoveIfaField(ownColor, board_ref, row, column, row, column + 1, moves);
    addMoveIfaField(ownColor, board_ref, row, column, row - 1, column + 1,
                    moves);
    addMoveIfaField(ownColor, board_ref, row, column, row - 1, column, moves);
    addMoveIfaField(ownColor, board_ref, row, column, row - 1, column - 1,
                    moves);
    addMoveIfaField(ownColor, board_ref, row, column, row, column - 1, moves);
    addMoveIfaField(ownColor, board_ref, row, column, row + 1, column - 1,
                    moves);

    // Here we handle the rochade
    std::array<bool, 4> castleArray = board_ref.getCastleKing();
    if (ownColor == Color::White)
    {
        // make sure the rochade is still allowed on this side.
        // all field between the king and rook are empty
        // all field the king pass should not be under attack
        if (castleArray[0] && board_ref.isEmptyField(2, 7) &&
            board_ref.isEmptyField(2, 8))
        {
            moves.push_back(Move{{row, column}, {2, 8}});
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// Note "moves" is a out parameter
// In this method we orcestrate which function we have to call depending on the
// piece type.
void addMovesOfOnePiece(const Piece& piece, const Board& board_ref, size_t row,
                        size_t column, MoveList& moves)
{
    // note we don't get of the array index as we have the 2 field thick
    // boundary
    assert((row > 1 && row < 10) &&
           "Move generation: row index is in the boundary");
    assert((column > 1 && column < 10) &&
           "Move generation: column index is in the boundary");

    switch (piece.getType())
    {
    case PieceType::Pawn:
        addMovesOfOnePawn(piece, board_ref, row, column, moves);
        break;
    case PieceType::Rook:
        addMovesOfOneRook(piece, board_ref, row, column, moves);
        break;
    case PieceType::Knight:
        addMovesOfOneKnight(piece, board_ref, row, column, moves);
        break;
    case PieceType::Bishop:
        addMovesOfOneBishop(piece, board_ref, row, column, moves);
        break;
    case PieceType::Queen:
        addMovesOfOneQueen(piece, board_ref, row, column, moves);
        break;
    case PieceType::King:
        addMovesOfOneKing(piece, board_ref, row, column, moves);
        break;
    default:
        assert("Move generation: didn't find correct piece");
        break;
    }
}

// We will generate a vector of all possible next moves of a given board
// We implement the "legal" approach, so only return moves so the king wont be
// in check. For this we first search for each move and check if after that move
// the king is in check.
MoveList generateMoves(const Board& board)
{
    MoveList moves;

    Color current_color = board.getSideToMove();

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
