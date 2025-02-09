#include "Rule.h"

Rule::Rule(Board& board) : m_Board(board)
{

}

bool Rule::isValidMove(shared_ptr<Piece>& piece, Vector2i pos)
{
    cout << "Compare input position with piece's Possible move vector\n";
    cout << "Checking is move valid\n";
    return true;
}

bool Rule::calculatePossibleMove(shared_ptr<Piece>& piece)
{
    std::cout << "Calculating possible moves...\n";
    vector<Vector2i> possibleMoves = vector<Vector2i>();
    vector<Vector2i> moves ;
    switch (piece->getType())
    {
    case PieceType::defult:
        break;
    case PieceType::pawn:
        moves = pawnMove(piece);
        possibleMoves.insert(possibleMoves.end(), moves.begin(), moves.end());
        printMovesVector(possibleMoves);
        moves = pawnAtt(piece);
        possibleMoves.insert(possibleMoves.end(), moves.begin(), moves.end());
        printMovesVector(possibleMoves);
        break;
    case PieceType::knight:
        moves = KnightMove(piece);
        possibleMoves.insert(possibleMoves.end(), moves.begin(), moves.end());
        break;
    case PieceType::bishop:
        moves = BishopMove(piece);
        possibleMoves.insert(possibleMoves.end(), moves.begin(), moves.end());
        break;
    case PieceType::rook:
        moves = RookMove(piece);
        possibleMoves.insert(possibleMoves.end(), moves.begin(), moves.end());
        break;
    case PieceType::queen:
        moves = QueenMove(piece);
        possibleMoves.insert(possibleMoves.end(), moves.begin(), moves.end());
        break;
    case PieceType::king:
        moves = KingMove(piece);
        possibleMoves.insert(possibleMoves.end(), moves.begin(), moves.end());
        break;
    default:
        break;
    }

    vector<Vector2i> moveArray = possibleMoves;
    printMovesVector(possibleMoves);

    piece->setPossibleMoveArray(possibleMoves);
    return !piece->getPossibleMoveArray().empty();

}

void Rule::calculateBoardState()
{
    cout << "Updating Board...\n";
    return;
}

#ifdef DEBUG
void Rule::printMovesVector(vector<Vector2i> v)
{
    auto it = v.begin();
    auto end = v.end();
    cout << "move Array ::\n[";
    for (it; it != end; it++)
    {
        cout << "(" << it->x << "," << it->y << "),";
    }
    cout << "]\n\n";
}
#endif // DEBUG