#include "Rule.h"

Rule::Rule(Board& board, PieceColor& color) :
    m_board(board), 
    m_turn(color)
{

}

bool Rule::trySelect(Vector2i pos)
{
    auto& piece = m_board.getSquareData(pos);
    bool haveMove = calculatePossibleMove(piece);

    if (haveMove)
        m_selectingPos = pos;

    return haveMove;
}

bool Rule::tryMove(Vector2i pos)
{
    auto& piece = m_board.getSquareData(pos);
    bool valid = isValidMove(piece, pos);

    if (valid)
    {
        m_board.movePiece(m_selectingPos, pos);
    }

    return valid;
}

bool Rule::isValidMove(shared_ptr<Piece>& piece, Vector2i pos)
{
    cout << "\nChecking is move valid\n";
    getControllingPos(flipColor(m_turn));
    return true;
}

void Rule::calculateBoardState()
{
    cout << "\nUpdating Board...\n";
    return;
}

bool Rule::calculatePossibleMove(shared_ptr<Piece>& piece)
{
    std::cout << "\nCalculating possible moves...\n";
    vector<Vector2i> moveArray = getPieceMoveset(piece);

    printMovesVector(moveArray);

    piece->setPossibleMoveArray(moveArray);
    return !piece->getPossibleMoveArray().empty();

}

vector<Vector2i> Rule::getPieceMoveset(shared_ptr<Piece>& piece, bool onlyGetAttackMove)
{
    vector<Vector2i> possibleMoves = vector<Vector2i>();
    vector<Vector2i> moves;
    switch (piece->getType())
    {
    case PieceType::defult:
        break;
    case PieceType::pawn:
        if (!onlyGetAttackMove)
            joinMoveArray(possibleMoves, pawnMove(piece));
        joinMoveArray(possibleMoves, pawnAtt(piece));
        break;
    case PieceType::knight:
        joinMoveArray(possibleMoves, KnightMove(piece));
        break;
    case PieceType::bishop:
        joinMoveArray(possibleMoves, BishopMove(piece));
        break;
    case PieceType::rook:
        joinMoveArray(possibleMoves, RookMove(piece));
        break;
    case PieceType::queen:
        joinMoveArray(possibleMoves, QueenMove(piece));
        break;
    case PieceType::king:
        joinMoveArray(possibleMoves, KingMove(piece));
        break;
    default:
        break;
    }

    return possibleMoves;
}

vector<Vector2i> Rule::getControllingPos(PieceColor color)
{
#ifdef DEBUG
    cout << "\n//////////////////////////////\n";
    cout << "Checking Controlling Position!\n";
    cout << "//////////////////////////////\n";
    cout << "Color : " << (color == PieceColor::white ? "White" : "Black");
    cout << "\n";
#endif // DEBUG

    vector<Vector2i> controlPos;

    auto pieces = m_board.getPieces();
    for (auto& piece : pieces)
    {
        joinMoveArray(controlPos, getPieceMoveset(piece, true));
    }

#ifdef DEBUG
    cout << "\Controlling Square array : ";
    printMovesVector(controlPos);
#endif // DEBUG


    return controlPos;
}

#ifdef DEBUG
void Rule::printMovesVector(vector<Vector2i> v)
{
    auto it = v.begin();
    auto end = v.end();
    cout << "\nmove Array ::\n[";
    for (it; it != end; it++)
    {
        cout << "(" << it->x << "," << it->y << "),";
    }
    cout << "]\n";
}
#endif // DEBUG

#pragma region Auxiliaries
void Rule::joinMoveArray(vector<Vector2i>& base, const vector<Vector2i>& add)
{
    base.insert(base.end(), add.begin(), add.end());

#pragma endregion

}

PieceColor Rule::flipColor(PieceColor color)
{
    
    return color == PieceColor::white? PieceColor::black : PieceColor:: white;
}
