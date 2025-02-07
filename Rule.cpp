#include "Rule.h"

Rule::Rule(Board& board)
{
    m_Board = &board;
}


bool Rule::canMove(shared_ptr<Piece>& piece)
{

    return piece != nullptr;
}

bool Rule::isValidMove(shared_ptr<Piece>& piece, Vector2i pos)
{
    cout << "Compare input position with piece's Possible move vector\n";
    cout << "Checking is move valid\n";
    return true;
}

void Rule::calculatePossibleMove(shared_ptr<Piece>& piece)
{
    cout << "Calculating possible moves...\n";
    switch (piece->getType())
    {
    case PieceType::defult:
        break;
    case PieceType::pawn:
        pawnMove(piece);
        break;
    case PieceType::knight:

        break;
    case PieceType::bishop:

        break;
    case PieceType::rook:

        break;
    case PieceType::queen:

        break;
    case PieceType::king:

        break;
    default:
        break;
    }
}

void Rule::calculateBoardState()
{
    cout << "Updating Board...\n";
    return;
}
