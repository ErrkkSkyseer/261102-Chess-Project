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
    vector<Vector2i> moveArray = getPieceMoveset(piece,m_board);

    printMovesVector(moveArray);

    piece->setPossibleMoveArray(moveArray);
    return !piece->getPossibleMoveArray().empty();

}

vector<Vector2i> Rule::getPieceMoveset(shared_ptr<Piece>& piece, Board& board, bool onlyGetAttackMove)
{
    vector<Vector2i> possibleMoves = vector<Vector2i>();
    vector<Vector2i> moves;
    switch (piece->getType())
    {
    case PieceType::defult:
        break; 
    case PieceType::pawn:
        if (!onlyGetAttackMove)
            joinMoveArray(possibleMoves, pawnMove(piece, board));
        joinMoveArray(possibleMoves, pawnAtt(piece, board));
        break;
    case PieceType::knight:
        joinMoveArray(possibleMoves, KnightMove(piece, board));
        break;
    case PieceType::bishop:
        joinMoveArray(possibleMoves, BishopMove(piece, board));
        break;
    case PieceType::rook:
        joinMoveArray(possibleMoves, RookMove(piece, board));
        break;
    case PieceType::queen:
        joinMoveArray(possibleMoves, QueenMove(piece, board));
        break;
    case PieceType::king:
        joinMoveArray(possibleMoves, KingMove(piece, board));
        break;
    default:
        break;
    }

    return possibleMoves;
}

vector<Vector2i> Rule::getControllingPos(PieceColor color, Board& board)
{
#ifdef DEBUG
    cout << "\n//////////////////////////////\n";
    cout << "Checking Controlling Position!\n";
    cout << "//////////////////////////////\n";
    cout << "Color : " << (color == PieceColor::white ? "White" : "Black");
    cout << "\n";
#endif // DEBUG

    vector<Vector2i> controlPos;

    auto& pieces = board.getPieces();
    for (auto& piece : pieces)
    {
        joinMoveArray(controlPos, getPieceMoveset(piece, m_board, true));
    }

#ifdef DEBUG
    cout << "\Controlling Square array : ";
    printMovesVector(controlPos);
#endif // DEBUG


    return controlPos;
}

bool Rule::check(PieceColor color, Board& board)
{
    Vector2i kingPos = findKingPos(color);
    vector<Vector2i> controlpos = getControllingPos(flipColor(color), board);
    for (auto& pos : controlpos)
    {
        if (kingPos == pos)
            return true;
    }
    return false;
}

bool Rule::checkMate(PieceColor color)
{
    Vector2i kingPos = findKingPos(color);
    auto& pieces = m_board.getPieces();

    for (auto& piece : pieces)
    {
        Board ghostBoard = m_board.getGhostBoard();
        if (calculatePossibleMove(piece))
        {
            auto moves = piece->getPossibleMoveArray();
            for (auto& move : moves)
            {

            }
        }

    }

}

Vector2i Rule::findKingPos(PieceColor color)
{
    Vector2i kingPos = Vector2i();
    auto& pieces = m_board.getPieces();
    for (auto& piece : pieces)
    {
        if (piece->getType() == PieceType::king
            && piece->getColor() == PieceColor::white)
        {
            kingPos = piece->getPosition();
            break;
        }
    }
    return kingPos;
}

vector<Vector2i> Rule::getPinnedMove(shared_ptr<Piece>& piece, const vector<Vector2i> moveArray)
{
    vector<Vector2i> pinnedMove;
    for (auto& move : moveArray)
    {
        Board ghostBoard = m_board.getGhostBoard();
        ghostBoard.movePiece(piece->getPosition(), move);

        if (check(piece->getColor(), ghostBoard))
        {
            pinnedMove.push_back(move);
        }
    }
    return pinnedMove;
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


}

PieceColor Rule::flipColor(PieceColor color)
{
    
    return color == PieceColor::white? PieceColor::black : PieceColor:: white;
}

#pragma endregion