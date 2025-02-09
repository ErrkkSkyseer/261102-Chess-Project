#include "Rule.h"

vector<Vector2i> Rule::pawnMove(shared_ptr<Piece>& piece)
{
    return vector<Vector2i>();
}

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

bool Rule::calculatePossibleMove(shared_ptr<Piece>& piece)
{
    cout << "Calculating possible moves...\n";
    switch (piece->getType())
    {
    case PieceType::defult:
        break;
    case PieceType::pawn:
        piece->setPossibleMoveArray(pawnMove(piece));
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

    return true;
}

void Rule::calculateBoardState()
{
    cout << "Updating Board...\n";
    return;
}
