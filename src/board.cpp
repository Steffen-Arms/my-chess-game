#include "board.h"
#include "move_list.h"
#include <array>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>

constexpr Color oppositeColor(Color c)
{
    if (c == Color::No_color)
    {
        return Color::No_color;
    }
    else
    {
        return c == Color::White ? Color::Black : Color::White;
    }
}

// board is a out parameter
void fillBoardBoundaries(board_array& board)
{
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
}

board_array startBoard()
{
    board_array board;
    fillBoardBoundaries(board);

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

// upper case letters are white pieces and lower case or black once
void Board::addPiece(std::size_t rowIndex, std::size_t columnIndex,
                     char charPiece)
{
    char pieceType = static_cast<char>(std::tolower(charPiece));
    switch (pieceType)
    {
    case 'p':
        if (std::isupper(charPiece))
        {
            m_board[rowIndex][columnIndex] =
                Piece{Color::White, PieceType::Pawn};
            ++m_countPiece[idx(Color::White)][idx(PieceType::Pawn)];
        }
        else
        {
            m_board[rowIndex][columnIndex] =
                Piece{Color::Black, PieceType::Pawn};
            ++m_countPiece[idx(Color::Black)][idx(PieceType::Pawn)];
        }
        break;
    case 'r':
        if (std::isupper(charPiece))
        {
            m_board[rowIndex][columnIndex] =
                Piece{Color::White, PieceType::Rook};
            ++m_countPiece[idx(Color::White)][idx(PieceType::Rook)];
        }
        else
        {
            m_board[rowIndex][columnIndex] =
                Piece{Color::Black, PieceType::Rook};
            ++m_countPiece[idx(Color::Black)][idx(PieceType::Rook)];
        }
        break;
    case 'n':
        if (std::isupper(charPiece))
        {
            m_board[rowIndex][columnIndex] =
                Piece{Color::White, PieceType::Knight};
            ++m_countPiece[idx(Color::White)][idx(PieceType::Knight)];
        }
        else
        {
            m_board[rowIndex][columnIndex] =
                Piece{Color::Black, PieceType::Knight};
            ++m_countPiece[idx(Color::Black)][idx(PieceType::Knight)];
        }
        break;
    case 'b':
        if (std::isupper(charPiece))
        {
            m_board[rowIndex][columnIndex] =
                Piece{Color::White, PieceType::Bishop};
            ++m_countPiece[idx(Color::White)][idx(PieceType::Bishop)];
        }
        else
        {
            m_board[rowIndex][columnIndex] =
                Piece{Color::Black, PieceType::Bishop};
            ++m_countPiece[idx(Color::Black)][idx(PieceType::Bishop)];
        }
        break;
    case 'q':
        if (std::isupper(charPiece))
        {
            m_board[rowIndex][columnIndex] =
                Piece{Color::White, PieceType::Queen};
            ++m_countPiece[idx(Color::White)][idx(PieceType::Queen)];
        }
        else
        {
            m_board[rowIndex][columnIndex] =
                Piece{Color::Black, PieceType::Queen};
            ++m_countPiece[idx(Color::Black)][idx(PieceType::Queen)];
        }
        break;
    case 'k':
        if (std::isupper(charPiece))
        {
            m_board[rowIndex][columnIndex] =
                Piece{Color::White, PieceType::King};
            m_whiteKing = Coord{rowIndex, columnIndex};
        }
        else
        {
            m_board[rowIndex][columnIndex] =
                Piece{Color::Black, PieceType::King};
            m_blackKing = Coord{rowIndex, columnIndex};
        }
        break;
    default:
        break;
    }
}

Board::Board()
    : m_board{startBoard()}, m_sideToMove{Color::White}, m_halfMoves{0},
      m_whiteKing{Coord{2, 6}}, m_blackKing{Coord{9, 6}},
      m_countPiece{{{8, 2, 2, 2, 1}, {8, 2, 2, 2, 1}}}
{
    m_castleKing.fill(true);
}

// We don't validate if its a valid FEN yet
Board::Board(std::string_view fen) : m_board{}
{
    fillBoardBoundaries(m_board);
    // fen has this format: rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -
    // 0 1

    // first seperate the first part (pieces postion) from the other
    // information
    auto splitPosition = fen.find(' ');
    std::string_view piecePositions = fen.substr(0, splitPosition);
    std::string_view metaInformation = fen.substr(splitPosition + 1);

    // Here we construct the board pieces
    std::size_t rowIndex{7}; // note FEN notation start at rank (row) 8.
    std::size_t columnIndex{0};
    for (auto row : piecePositions | std::views::split('/'))
    {
        columnIndex = 0;
        for (char charPiece : row)
        {
            if (charPiece >= '0' && charPiece <= '9')
            {
                columnIndex += static_cast<std::size_t>(charPiece - '0') -
                               1; // here we convert the char number to a int.
                                  // Note we have to subtract 1 cause we already
                                  // are on the current index.
            }
            addPiece(rowIndex + 2, columnIndex + 2,
                     charPiece); // Note in our board representation we have a
                                 // boundary of 2 around the board, thats why +2
            ++columnIndex;
        }
        --rowIndex;
    }

    // Here we insert the metadata

    // Default is no castling rights
    m_castleKing.fill(false);

    int count{0};
    for (auto data_iterator : metaInformation | std::views::split(' '))
    {
        std::string_view data(data_iterator.begin(), data_iterator.end());
        if (count == 0)
        {
            if (data == "w")
            {
                m_sideToMove = Color::White;
            }
            else
            {
                m_sideToMove = Color::Black;
            }
            ++count;
        }
        else if (count == 1)
        {
            for (auto letter : data)
            {
                if (letter == '-')
                {
                    break; // this mean there is no castling rights anymore
                }
                else if (letter == 'K')
                {
                    m_castleKing[0] = true;
                }
                else if (letter == 'Q')
                {
                    m_castleKing[1] = true;
                }
                else if (letter == 'k')
                {
                    m_castleKing[2] = true;
                }
                else if (letter == 'q')
                {
                    m_castleKing[3] = true;
                }
            }
            ++count;
        }
        else if (count == 2)
        {
            if (data == "-")
            {
                m_enPassantField.reset(); // There is no en passage field
            }
            else
            {
                std::size_t enPassant_Column =
                    static_cast<size_t>(data[0] - 'a');

                // subtract -1 because our coordinate system start by 0
                std::size_t enPassant_Row =
                    static_cast<size_t>(data[1] - '0' - 1);
                m_enPassantField = {enPassant_Row + 2, enPassant_Column + 2};
            }
            ++count;
        }
        else if (count == 3)
        {
            m_halfMoves = data[0] - '0';
            ++count;
        }
        else if (count == 4)
        {
            m_fullMoves = data[0] - '0';
        }
    }
}

bool Board::isEmptyField(std::size_t row, std::size_t column) const
{
    return m_board[row][column].getType() == PieceType::Empty;
}

// return false if the field is empty or not_valid or contain a piece of
// ownColor
bool Board::containEnemyPiece(std::size_t row, std::size_t column) const
{
    // note if a field is empty or not valid it hat "no_color" as color.
    return m_board[row][column].getColor() == oppositeColor(m_sideToMove);
}

// orthogonal enemies are rook and queen
bool Board::containOrthogonalEnemy(std::size_t row, std::size_t column) const
{
    if (m_sideToMove == Color::White)
    {
        if (m_board[row][column].getColor() == Color::Black)
        {
            return m_board[row][column].getType() == PieceType::Rook ||
                   m_board[row][column].getType() == PieceType::Queen;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (m_board[row][column].getColor() == Color::White)
        {
            return m_board[row][column].getType() == PieceType::Rook ||
                   m_board[row][column].getType() == PieceType::Queen;
        }
        else
        {
            return false;
        }
    }
    return false;
}

// diagonal enemies are bishop and queen
bool Board::containDiagonalEnemy(std::size_t row, std::size_t column) const
{
    if (m_sideToMove == Color::White)
    {
        if (m_board[row][column].getColor() == Color::Black)
        {
            return m_board[row][column].getType() == PieceType::Bishop ||
                   m_board[row][column].getType() == PieceType::Queen;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (m_board[row][column].getColor() == Color::White)
        {
            return m_board[row][column].getType() == PieceType::Bishop ||
                   m_board[row][column].getType() == PieceType::Queen;
        }
        else
        {
            return false;
        }
    }
    return false;
}

bool Board::fieldContainEnemyKnight(std::size_t row, std::size_t column) const
{

    return m_board[row][column].getType() == PieceType::Knight &&
           m_board[row][column].getColor() == oppositeColor(m_sideToMove);
}

bool Board::isUnderKnightAttack(std::size_t row, std::size_t column) const
{
    return fieldContainEnemyKnight(row + 2, column + 1) ||
           fieldContainEnemyKnight(row + 1, column + 2) ||
           fieldContainEnemyKnight(row - 1, column + 2) ||
           fieldContainEnemyKnight(row - 2, column + 1) ||
           fieldContainEnemyKnight(row - 2, column - 1) ||
           fieldContainEnemyKnight(row - 1, column - 2) ||
           fieldContainEnemyKnight(row + 1, column - 2) ||
           fieldContainEnemyKnight(row + 2, column - 1);
}

bool Board::containEnemyPawn(std::size_t row, std::size_t column) const
{
    // note if a field is empty or not valid it hat "no_color" as color. So it's
    // enough to check agains the color.
    return m_board[row][column].getColor() == oppositeColor(m_sideToMove) &&
           m_board[row][column].getType() == PieceType::Pawn;
}

void Board::print() const
{
    std::cout << "This is the board\n";
    for (const auto& row : m_board | std::views::reverse)
    {
        for (const auto& piece : row)
        {
            std::cout << piece.toChar() << ' ';
        }
        std::cout << '\n';
    }
}

// after each move we have to check if the current king is in check otherwise
// its not a valid move
bool Board::kingInCheckAfterMove(Move newMove)
{
    UndoInfo undoInfo = makeTestMove(newMove);
    bool inCheck = kingInCheck();
    undoTestMove(newMove, undoInfo);
    return inCheck;
}

// return true if the king is in check for the current color
bool Board::kingInCheck() const
{
    return m_sideToMove == Color::White ? fieldIsUnderAttack(m_whiteKing)
                                        : fieldIsUnderAttack(m_blackKing);
}

// same method as makeMove but without changing the color
// this function is just to validate the field after one move
UndoInfo Board::makeTestMove(Move move)
{
    // first we save meta board information to our return value
    UndoInfo info{m_enPassantField, m_castleKing};

    // we update our piece counter
    decreasePieceCound(move.capturePiece);

    // here we handle enPassage
    // here we handle if we have the enPassage right from the previous half
    // round
    //  here we handle if the move itself is a enPassage
    if (m_enPassantField.has_value())
    {
        if (move.isEnPassage)
        {
            // note the move of the pawn itself is handle down below
            // here we handle the capture of the enemy pawn
            if (m_sideToMove == Color::White)
            {
                m_board[move.to.row - 1][move.to.column] = Piece{};
            }
            else
            {
                m_board[move.to.row + 1][move.to.column] = Piece{};
            }
        }
        // if we take the enPassant or not, after that move the enPassant right
        // is gone.
        m_enPassantField.reset();
    }
    // now we handle if a move create a enPassage right
    // we save the coordinates of the enPassage field
    if (move.createEnPassageRight)
    {
        m_enPassantField =
            Coord{(move.from.row + move.to.row) / 2, move.to.column};
    }

    // special treatment if we move the king
    if (move.from == m_whiteKing)
    {
        std::size_t columnDiff = move.from.column < move.to.column
                                     ? move.to.column - move.from.column
                                     : move.from.column - move.to.column;
        m_whiteKing = move.to;
        if (columnDiff > 1) // this is the case we castle
        {
            if (move.to.column == 8)
            { // this is the short castling
                // Note: here we handle only the move of the rook. The move of
                // the king is handle down below where all normal moves are also
                // handled.
                m_board[2][7] = m_board[2][9];
                m_board[2][9] = Piece{};
            }
            else
            {
                // this is the long castling
                m_board[2][5] = m_board[2][2];
                m_board[2][2] = Piece{};
            }
        }
        // regardless how we move the king the castling rights are gone
        m_castleKing[0] = false;
        m_castleKing[1] = false;
    }
    else if (move.from == m_blackKing)
    {
        std::size_t columnDiff = move.from.column < move.to.column
                                     ? move.to.column - move.from.column
                                     : move.from.column - move.to.column;
        m_blackKing = move.to;
        if (columnDiff > 1) // this is the case we castle
        {
            if (move.to.column == 8)
            { // this is the short castling
                // Note: here we handle only the move of the rook. The move of
                // the king is handle down below where all normal moves are also
                // handled.
                m_board[9][7] = m_board[9][9];
                m_board[9][9] = Piece{};
            }
            else
            {
                // this is the long castling
                m_board[9][5] = m_board[9][2];
                m_board[9][2] = Piece{};
            }
        }
        m_castleKing[2] = false;
        m_castleKing[3] = false;
    }

    // if we move a rook or capture one the corresbonding castling right is
    // gone
    if (m_castleKing[0] || m_castleKing[1] || m_castleKing[2] ||
        m_castleKing[3])
    {
        // if the rook is moving we have to change the castle rights
        if (m_board[move.from.row][move.from.column].getType() ==
            PieceType::Rook)
        {
            if (move.from.row == 2 && move.from.column == 9)
            {
                m_castleKing[0] = false; // we dont check if its already
                                         // false. That doesn't matter.
            }
            else if (move.from.row == 2 && move.from.column == 2)
            {
                m_castleKing[1] = false;
            }
            else if (move.from.row == 9 && move.from.column == 9)
            {
                m_castleKing[2] = false;
            }
            else if (move.from.row == 9 && move.from.column == 2)
            {
                m_castleKing[3] = false;
            }
        }
        // if the rook get captured we need to change the castle rights
        if (move.capturePiece.getType() == PieceType::Rook)
        {
            if (move.to.row == 2 && move.to.column == 9)
            {
                m_castleKing[0] = false; // we dont check if its already
                                         // false. That doesn't matter.
            }
            else if (move.to.row == 2 && move.to.column == 2)
            {
                m_castleKing[1] = false;
            }
            else if (move.to.row == 9 && move.to.column == 9)
            {
                m_castleKing[2] = false;
            }
            else if (move.to.row == 9 && move.to.column == 2)
            {
                m_castleKing[3] = false;
            }
        }
    }

    // here we have to check if a pawn is transforming to another piece
    if (move.transform.getType() != PieceType::Empty)
    {
        m_board[move.to.row][move.to.column] = move.transform;
    }
    else
    {
        m_board[move.to.row][move.to.column] =
            m_board[move.from.row][move.from.column];
    }
    m_board[move.from.row][move.from.column] =
        Piece{}; // if we make a move we leave a emtpy field behind

    return info;
}

void Board::undoTestMove(Move move, const UndoInfo& info)
{
    // here we restore the meta board information
    m_enPassantField = info.enPassant;
    m_castleKing = info.castle;

    // update piece count
    increasePieceCound(move.capturePiece);

    // here we detect if the move is a enPassage move
    // that need a special treatment as the captured piece is not from the field
    // the move goes to.
    if (move.isEnPassage)
    {
        m_board[move.from.row][move.from.column] =
            m_board[move.to.row][move.to.column];

        m_board[move.to.row][move.to.column] = Piece{};
        if (m_sideToMove == Color::White)
        {
            m_board[move.to.row - 1][move.to.column] = move.capturePiece;
        }
        else
        {
            m_board[move.to.row + 1][move.to.column] = move.capturePiece;
        }
    }
    else
    {
        // special treatment if we move the king
        if (move.to == m_whiteKing)
        {
            std::size_t columnDiff = move.from.column < move.to.column
                                         ? move.to.column - move.from.column
                                         : move.from.column - move.to.column;
            m_whiteKing = move.from;
            if (columnDiff > 1) // this is the case we castle
            {
                if (move.to.column == 8)
                { // this is the short castling
                    // Note: here we handle only the move of the rook. The move
                    // of the king is handle down below where all normal moves
                    // are also handled.
                    m_board[2][9] = m_board[2][7];
                    m_board[2][7] = Piece{};
                }
                else
                {
                    // this is the long castling
                    m_board[2][2] = m_board[2][5];
                    m_board[2][5] = Piece{};
                }
            }
        }
        else if (move.to == m_blackKing)
        {
            std::size_t columnDiff = move.from.column < move.to.column
                                         ? move.to.column - move.from.column
                                         : move.from.column - move.to.column;
            m_blackKing = move.from;
            if (columnDiff > 1) // this is the case we castle
            {
                if (move.to.column == 8)
                { // this is the short castling
                    // Note: here we handle only the move of the rook. The move
                    // of the king is handle down below where all normal moves
                    // are also handled.
                    m_board[9][9] = m_board[9][7];
                    m_board[9][7] = Piece{};
                }
                else
                {
                    // this is the long castling
                    m_board[9][2] = m_board[9][5];
                    m_board[9][5] = Piece{};
                }
            }
        }

        // here we check if the move take a pawn and transform it. Then we have
        // to specify the new piece as we don't want to copy the transformed
        // piece
        if (move.transform.getType() != PieceType::Empty)
        {
            m_board[move.from.row][move.from.column] =
                Piece{move.transform.getColor(), PieceType::Pawn};
        }
        else
        {

            m_board[move.from.row][move.from.column] =
                m_board[move.to.row][move.to.column];
        }
        // note if we don't capture a piece move.capturePiece give as a empty
        // piece.
        m_board[move.to.row][move.to.column] = move.capturePiece;
    }
}

UndoInfo Board::makeMove(Move move)
{
    // the only difference betweent makeTestMove and makeMove is that makeMove
    // change which turn it is
    UndoInfo info = makeTestMove(move);
    changeSideToMove();
    return info;
}

void Board::undoMove(Move move, const UndoInfo& info)
{
    changeSideToMove();
    undoTestMove(move, info);
}

///////////////////
///////////////////////

bool Board::fieldIsUnderAttack(Coord fieldCoord) const
{
    return fieldIsUnderAttack(fieldCoord.row, fieldCoord.column);
}

// return true if a piece of the enemy attack this field right now.
// return false otherwise or if its not a valid field
bool Board::fieldIsUnderAttack(std::size_t row, std::size_t column) const
{
    // first check if its a valid field
    if (m_board[row][column].getType() == PieceType::Not_valid)
    {
        return false;
    }

    // we check for orthogonal enemies
    if (fieldIsUnderOrthogonalAttack(row, column))
        return true;

    // now we check for diagonal enemies
    if (fieldIsUnderDiagonalAttack(row, column))
        return true;

    if (isUnderKnightAttack(row, column))
        return true;

    // check if enemy pawn attack field
    if (isUnderPawnAttack(row, column))
        return true;

    if (isUnderKingAttack(row, column))
        return true;

    return false;
}

bool Board::fieldIsUnderOrthogonalAttack(std::size_t row,
                                         std::size_t column) const
{
    // We check for each direction the next field that is not empty. Then we
    // check if it contain a dangerous enemy piece.
    std::size_t nextColumn = column + 1;
    while (isEmptyField(row, nextColumn))
    {
        ++nextColumn;
    }
    if (containOrthogonalEnemy(row, nextColumn))
        return true;

    nextColumn = column - 1;
    while (isEmptyField(row, nextColumn))
    {
        --nextColumn;
    }
    if (containOrthogonalEnemy(row, nextColumn))
        return true;

    std::size_t nextRow = row + 1;
    while ((isEmptyField(nextRow, column)))
    {
        ++nextRow;
    }
    if (containOrthogonalEnemy(nextRow, column))
        return true;

    nextRow = row - 1;
    while (isEmptyField(nextRow, column))
    {
        --nextRow;
    }
    if (containOrthogonalEnemy(nextRow, column))
        return true;

    // if we dont find orthogonal enemies we return false
    return false;
}

bool Board::fieldIsUnderDiagonalAttack(std::size_t row,
                                       std::size_t column) const
{
    std::size_t nextRow = row + 1;
    std::size_t nextColumn = column + 1;

    while (isEmptyField(nextRow, nextColumn))
    {
        ++nextRow;
        ++nextColumn;
    }
    if (containDiagonalEnemy(nextRow, nextColumn))
        return true;

    nextRow = row - 1;
    nextColumn = column - 1;
    while ((isEmptyField(nextRow, nextColumn)))
    {
        --nextRow;
        --nextColumn;
    }
    if (containDiagonalEnemy(nextRow, nextColumn))
        return true;

    nextRow = row + 1;
    nextColumn = column - 1;
    while (isEmptyField(nextRow, nextColumn))
    {
        ++nextRow;
        --nextColumn;
    }
    if (containDiagonalEnemy(nextRow, nextColumn))
        return true;

    nextRow = row - 1;
    nextColumn = column + 1;
    while (isEmptyField(nextRow, nextColumn))
    {
        --nextRow;
        ++nextColumn;
    }
    if (containDiagonalEnemy(nextRow, nextColumn))
        return true;

    // if we don't find diagonal enemies we return false
    return false;
}

bool Board::isUnderPawnAttack(std::size_t row, std::size_t column) const
{
    if (m_sideToMove == Color::White)
    {
        return containEnemyPawn(row + 1, column - 1) ||
               containEnemyPawn(row + 1, column + 1);
    }
    else
    {
        return containEnemyPawn(row - 1, column - 1) ||
               containEnemyPawn(row - 1, column + 1);
    }
}

bool Board::isUnderKingAttack(std::size_t row, std::size_t column) const
{
    for (auto [offsetRow, offsetColumn] : neighborsOffset)
    {
        std::size_t currentRow = row + offsetRow;
        std::size_t currentColumn = column + offsetColumn;
        if (m_board[currentRow][currentColumn].getColor() ==
                oppositeColor(m_sideToMove) &&
            m_board[currentRow][currentColumn].getType() == PieceType::King)
            return true;
    }
    return false;
}
