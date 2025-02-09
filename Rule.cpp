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

bool Rule::calculatePossibleMove(shared_ptr<Piece>& piece)
{
    cout << "Calculating possible moves...\n";
    switch (piece->getType())
    {
    case PieceType::defult:
        break;
    case PieceType::pawn:
        piece->setPossibleMoveArray(pawnMove(piece));
        piece->setPossibleMoveArray(pawnAtt(piece));
        break;
    case PieceType::knight:
        piece->setPossibleMoveArray(KnightMove(piece));
        break;
    case PieceType::bishop:
        piece->setPossibleMoveArray(BishopMove(piece));
        break;
    case PieceType::rook:
        piece->setPossibleMoveArray(RookMove(piece));
        break;
    case PieceType::queen:
        piece->setPossibleMoveArray(QueenMove(piece));
        break;
    case PieceType::king:
        piece->setPossibleMoveArray(KingMove(piece));
        break;
    default:
        break;
    }
    return !piece->getPossibleMoveArray().empty();
}

void Rule::calculateBoardState()
{
    cout << "Updating Board...\n";
    return;
}
