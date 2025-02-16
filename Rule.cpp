#include "Rule.h"

/// <summary>
/// Constructor. Initialize references in the class.
/// </summary>
/// <param name="board">Main board ref</param>
/// <param name="color">player turn ref</param>
Rule::Rule(Board& board, PieceColor& color) :
    m_board(board), 
    m_turn(color)
{
    m_isInCheck = false;

    m_endType = EndType::null;
}

/// <summary>
/// Try to select a piece
/// </summary>
/// <param name="pos">board position</param>
/// <returns>Can the piece move</returns>
bool Rule::trySelect(Vector2i pos)
{
    auto& piece = m_board.getSquareData(pos);
    bool haveMove = false;

    if (piece->getColor() == m_turn)
        haveMove = calculatePossibleMove(piece);
    else
        cout << "Wrong piece Color\n";
    if (haveMove)
        m_selectingPos = pos;

    return haveMove;
}

bool Rule::tryMove(Vector2i pos)
{
    auto& piece = m_board.getSquareData(m_selectingPos);
    bool valid = isValidMove(piece, pos);

    if (valid)
    {
        m_board.movePiece(m_selectingPos, pos);
        m_lastMovePiece = m_board.getSquareData(pos);
    }

    return valid;
}

void Rule::calculateBoardState()
{
    cout << "\nUpdating Board...\n";
    m_isInCheck = isCheck(m_turn,m_board);

    if (isCheckmate(m_turn))
        m_endType = EndType::checkmate;
    if (isStalemate(m_turn))
        m_endType = EndType::stalemate;


    return;
}

bool Rule::isValidMove(shared_ptr<Piece>& piece, Vector2i pos)
{
    cout << "\nChecking is move valid\n";
    auto moveArray = piece->getPossibleMoveArray();
    
    //Look for matching move
    for (auto& move : moveArray)
    {
        if (move == pos)
            return true;
    }
    
    return false;
}

bool Rule::calculatePossibleMove(shared_ptr<Piece>& piece)
{
    std::cout << "\nCalculating possible moves...\n";
    vector<Vector2i> moveArray = getPieceMoveset(piece,m_board);
    moveArray = validateAttackMove(moveArray,piece, m_board);

    vector<Vector2i> pinnedMove = getPinnedMove(piece, moveArray, m_board);

    subtractMoveArray(moveArray, pinnedMove);

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

/// <summary>
/// Remove invalid attacking move
/// </summary>
/// <param name="piece"> : piece to check</param>
/// <param name="board"> : board</param>
/// <returns>Move array that doesn't have attack move on the same color piece</returns>
vector<Vector2i> Rule::validateAttackMove(vector<Vector2i> moveArray, shared_ptr<Piece>& piece, Board& board)
{
    vector<Vector2i> validMove;
    for (auto move : moveArray)
    {
        //Pawn can only attack when there is a piece
        if (piece->getType() == PieceType::pawn && board.isEmpty(move) && move.x != piece->getPosition().x)
            continue;
        //Piece can't capture ally
        if (!board.isEmpty(move) && piece->getColor() == board.getSquareData(move)->getColor())
            continue;

        validMove.push_back(move);
    }

    return validMove;
}

/// <summary>
/// Get all controlled square in the board.
/// </summary>
/// <param name="color"> : color to check</param>
/// <param name="board"> : board</param>
/// <returns>a vector of controlling position</returns>
vector<Vector2i> Rule::getControllingPos(PieceColor color, Board& board)
{
#ifdef DEBUGIORule
    cout << "\n//////////////////////////////\n";
    cout << "Checking Controlling Position!\n";
    cout << "//////////////////////////////\n";
    cout << "Color : " << (color == PieceColor::white ? "White" : "Black");
    cout << "\n";
#endif // DEBUGIORule

    vector<Vector2i> controlPos;

    auto& pieces = board.getPieces();
    for (auto& piece : pieces)
    {
        if (piece->getColor() == color)
            joinMoveArray(controlPos, getPieceMoveset(piece, board, true));
    }

    removeDuplicates(controlPos);

#ifdef DEBUGIORule
    cout << "\nControlling Square array : ";
    printMovesVector(controlPos);
#endif // DEBUGIORule


    return controlPos;
}

/// <summary>
/// Is this position a check?
/// </summary>
/// <param name="color"> : color to check</param>
/// <param name="board"> : board</param>
/// <returns></returns>
bool Rule::isCheck(PieceColor color, Board& board)
{
    Vector2i kingPos = findKingPos(color, board);
    vector<Vector2i> controlpos = getControllingPos(flipColor(color), board);
    for (auto& pos : controlpos)
    {
        if (kingPos == pos)
            return true;
    }
    return false;
}

/// <summary>
/// Is this position a checkmate?
/// </summary>
/// <param name="color">color to check</param>
/// <returns>True if checkmate, false otherwise</returns>
bool Rule::isCheckmate(PieceColor color)
{
    if (isCheck(color, m_board))
    {
        auto& pieces = m_board.getPieces();
        for (auto& piece : pieces)
        {
            if (piece->getColor() == color && !calculatePossibleMove(piece))
                return true;
        }
    }
    return false;
}

bool Rule::isStalemate(PieceColor color)
{
    if (!isCheck(color, m_board))
    {
        auto& pieces = m_board.getPieces();
        for (auto& piece : pieces)
        {
            if (piece->getColor() == color && !calculatePossibleMove(piece))
                return true;
        }
    }
    return false;
}

/// <summary>
/// Find king position.
/// </summary>
/// <param name="color"></param>
/// <param name="board"></param>
/// <returns></returns>
Vector2i Rule::findKingPos(PieceColor color,Board& board)
{
    Vector2i kingPos = Vector2i();
    auto& pieces = board.getPieces();
    for (auto& piece : pieces)
    {
        if (piece->getType() == PieceType::king
            && piece->getColor() == color)
        {
            kingPos = piece->getPosition();
            break;
        }
    }
    return kingPos;
}

vector<Vector2i> Rule::getPinnedMove(shared_ptr<Piece>& piece, const vector<Vector2i> moveArray,Board& board)
{
    vector<Vector2i> pinnedMove;
    for (auto& move : moveArray)
    {
        Board ghostBoard = board.getGhostBoard();
        ghostBoard.movePiece(piece->getPosition(), move);

        if (isCheck(piece->getColor(), ghostBoard))
        {
            pinnedMove.push_back(move);
        }
    }
    return pinnedMove;
}


void Rule::printMovesVector(vector<Vector2i> v)
{
    sortMoveArray(v);
    auto it = v.begin();
    auto end = v.end();
    cout << "\nmove Array ::\n[";
    for (it; it != end; it++)
    {
        cout << "(" << it->x << "," << it->y << "),";
    }
    cout << "]\n";
}

bool Rule::getCheck()
{
    return m_isInCheck;
}

bool Rule::getCheckmate()
{
    return m_endType == EndType::checkmate;
}

bool Rule::getDraw()
{
    return m_endType == EndType::stalemate
        || m_endType == EndType::fiftyRule
        || m_endType == EndType::repeatation
        || m_endType == EndType::material;
}

EndType Rule::getEndType()
{
    return m_endType;
}


#pragma region Auxiliaries
void Rule::joinMoveArray(vector<Vector2i>& base, const vector<Vector2i>& add)
{
    base.insert(base.end(), add.begin(), add.end());
}

PieceColor Rule::flipColor(PieceColor color)
{
    
    return color == PieceColor::white? PieceColor::black : PieceColor:: white;
}

void Rule::subtractMoveArray(vector<Vector2i>& base, const vector<Vector2i>& remove)
{
    set<Vector2i> subtract(remove.begin(), remove.end());
    vector<Vector2i> result;

    for (auto elem : base) 
    {
        if (subtract.find(elem) == subtract.end()) 
        { 
            result.push_back(elem);
        }
    }

    base = result;
}

void Rule::removeDuplicates(vector<Vector2i>& v)
{
    set<Vector2i> s(v.begin(), v.end());
    v = vector<Vector2i>(s.begin(), s.end());
}

void Rule::sortMoveArray(vector<Vector2i>& vec) 
{
    sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {return (a.y > b.y) || (a.y == b.y && a.x < b.x);});
}

#pragma endregion