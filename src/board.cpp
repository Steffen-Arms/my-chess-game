#include "board.h"
#include "move_list.h"
#include <array>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>

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
        }
        else
        {
            m_board[rowIndex][columnIndex] =
                Piece{Color::Black, PieceType::Pawn};
        }
        break;
    case 'r':
        if (std::isupper(charPiece))
        {
            m_board[rowIndex][columnIndex] =
                Piece{Color::White, PieceType::Rook};
        }
        else
        {
            m_board[rowIndex][columnIndex] =
                Piece{Color::Black, PieceType::Rook};
        }
        break;
    case 'n':
        if (std::isupper(charPiece))
        {
            m_board[rowIndex][columnIndex] =
                Piece{Color::White, PieceType::Knight};
        }
        else
        {
            m_board[rowIndex][columnIndex] =
                Piece{Color::Black, PieceType::Knight};
        }
        break;
    case 'b':
        if (std::isupper(charPiece))
        {
            m_board[rowIndex][columnIndex] =
                Piece{Color::White, PieceType::Bishop};
        }
        else
        {
            m_board[rowIndex][columnIndex] =
                Piece{Color::Black, PieceType::Bishop};
        }
        break;
    case 'q':
        if (std::isupper(charPiece))
        {
            m_board[rowIndex][columnIndex] =
                Piece{Color::White, PieceType::Queen};
        }
        else
        {
            m_board[rowIndex][columnIndex] =
                Piece{Color::Black, PieceType::Queen};
        }
        break;
    case 'k':
        if (std::isupper(charPiece))
        {
            m_board[rowIndex][columnIndex] =
                Piece{Color::White, PieceType::King};
        }
        else
        {
            m_board[rowIndex][columnIndex] =
                Piece{Color::Black, PieceType::King};
        }
        break;
    default:
        break;
    }
}

Board::Board()
    : m_board{startBoard()}, m_sideToMove{Color::White}, m_halfMoves{0}
{
}

// We don't validate if its a valid FEN yet
Board::Board(std::string_view fen) : m_board{}, m_sideToMove{}, m_halfMoves{}
{
    fillBoardBoundaries(m_board);
    // fen has this format: rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -
    // 0 1
    std::cout << "FEN: " << fen << '\n';

    // first seperate the first part (pieces postion) from the other
    // information
    auto splitPosition = fen.find(' ');
    std::string_view piecePositions = fen.substr(0, splitPosition);
    std::string_view metaInformation = fen.substr(splitPosition + 1);

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
    for (const auto& row : m_board | std::views::reverse)
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
    if (move.enPassage)
    {
        m_enPassant = move.to;
    }
    m_board[move.to.row][move.to.column] =
        m_board[move.from.row][move.from.column];
    m_board[move.from.row][move.from.column] =
        Piece{}; // if we make a move we leave a emtpy field behind

    changeColor();
}

// ToDo: implement castle
void Board::undoMove(Move move)
{
    if (move.enPassage)
    {
        m_enPassant.reset();
    }
    m_board[move.from.row][move.from.column] =
        m_board[move.to.row][move.to.column];

    // note if we don't capture a piece move.capturePiece give as a empty piece.
    m_board[move.to.row][move.to.column] = move.capturePiece;

    changeColor();
}
