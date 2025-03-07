#include "Rule.h"

/// <summary>
/// Constructor. Initialize references in the class.
/// </summary>
/// <param name="board">Main board ref</param>
/// <param name="color">player turn ref</param>
Rule::Rule(Board& board, PieceColor& color, GameType& gametype) :
    m_board(board), 
    m_turn(color),
    m_gametype(gametype)
{
    m_isInCheck = false;

    m_endType = EndType::null;
}

void Rule::reset()
{
    m_selectingPos = Vector2i(-1, -1);
    m_haveSpecialMove = false;
    m_isInCheck = false;
    m_endType = EndType::null;
    m_encodedBoardHistory.clear();
    m_fiftyMoveCounter = 0;
    m_lastPieceCount = m_board.getPieces().size();
    m_isPromotion = false;
    m_BurnSquare_Special = false;
    m_CheckKingThreeTime_Special = false;
    m_KingInMiddle_Special = false;
    burn_sq.clear();
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
        haveMove = calculatePossibleMove(piece,true,true);
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
        if (m_haveSpecialMove)
        {
            preformSpecialMove(piece, pos);
        }
        else
        {
            m_board.movePiece(m_selectingPos, pos);
        }
        countFiftyMove(m_board.getSquareData(pos)->getType());
    }

    return valid;
}

bool Rule::isKingAlive(PieceColor& color, Board& board) {
    Vector2i kingvector = findKingPos(m_turn, m_board);
    if (kingvector.x == 0 && kingvector.y == 0) return false;
    else kingvector = Vector2i(0, 0);
    return true;
}

void Rule::calculateBoardState()
{
    m_isInCheck = isCheck(m_turn,m_board);
    
    m_isPromotion = false;
    m_selectingPos = {};

    burn_sq.clear();
    if (m_gametype == GameType::notNormal)
    {
        eventActivate();
    }

    if (isCheckmate(m_turn))
        m_endType = EndType::checkmate;
    else if (isStalemate(m_turn))
        m_endType = EndType::stalemate;
    else if (checkRepeatation(m_board))
        m_endType = EndType::repeatation;
    else if (checkInsufficientMeterial())
        m_endType = EndType::material;
    else if (m_gametype == GameType::notNormal) {
        if (CheckKingThreeTime_Special())
            m_endType = EndType::threecheck;
        else if (KingInMiddle_Special())
            m_endType = EndType::kinginmiddle;
        else if (isKingAlive(m_turn,m_board) == false)
            m_endType = EndType::kingdied;
    }
     return;
}

bool Rule::isValidMove(shared_ptr<Piece>& piece, Vector2i pos)
{
    auto moveArray = piece->getPossibleMoveArray();
    
    //Look for matching move
    for (auto& move : moveArray)
    {
        if (move == pos)
            return true;
    }
    
    return false;
}

bool Rule::calculatePossibleMove(shared_ptr<Piece>& piece, bool doUpdateSpecial = true,bool doPrintMoveVector=true)
{
    //Get piece's possible move
    vector<Vector2i> moveArray = getPieceMoveset(piece,m_board);
    //Remove illegle attacking move (attack your own piece)
    moveArray = validateAttackMove(moveArray,piece, m_board);
    
    //calculate special move
    joinMoveArray(moveArray, calculateSpecialMove(piece, m_board, doUpdateSpecial));

    //remove any move that make the king become in check
    vector<Vector2i> pinnedMove = getPinnedMove(piece, moveArray, m_board);
    subtractMoveArray(moveArray, pinnedMove);
    
    //Check for Pawn Promotion
    if (checkForPromotion(piece, moveArray))
        m_haveSpecialMove = true;

    if (doPrintMoveVector)
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

vector<Vector2i> Rule::calculateSpecialMove(shared_ptr<Piece>& piece, Board& board, bool doUpdateSpecial = true)
{
    vector<Vector2i> specialMoves = vector<Vector2i>();
    PieceType type = piece->getType();

    //En Passant
    joinMoveArray(specialMoves, enPassant(piece,board));

    //Castle
    joinMoveArray(specialMoves, castel(piece, board));

    if (doUpdateSpecial)
        m_haveSpecialMove = !specialMoves.empty();

    return specialMoves;
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
            if (piece->getColor() == color && calculatePossibleMove(piece,false,false))
                return false;
        }
        return true;
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
            if (piece->getColor() == color && calculatePossibleMove(piece,false,false))
                return false;
        }
        return true;
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

void Rule::preformSpecialMove(shared_ptr<Piece>& piece, Vector2i pos)
{
    auto type = piece->getType();
    auto color = piece->getColor();

    //Promotion
    if (type == PieceType::pawn)
    {
        switch (color)
        {
        case PieceColor::white:
            m_isPromotion = pos.y == 8;
            break;
        case PieceColor::black:
            m_isPromotion = pos.y == 1;
            break;
        default:
            break;
        }
        if (m_isPromotion)
        {
            m_board.movePiece(m_selectingPos, pos);
            return;
        }
    }

    //En Passant
    if (type == PieceType::pawn)
    {
        Vector2i target = pos - (color == PieceColor::white?
            Vector2i(0,1) : Vector2i(0, -1));
        m_board.movePiece(m_selectingPos,pos);
        if (!m_board.isEmpty(target))
        {
            if (m_board.getSquareData(target)->getColor() != color
                && m_board.getSquareData(target)->getType() == PieceType::pawn)
                m_board.getBoard().erase(target);
        }
        return;
    }

    //Castle
    if (type == PieceType::king)
    {
        //left castle
        if (pos.x == 3)
        {
            m_board.movePiece(Vector2i(1, pos.y), Vector2i(4, pos.y));
        }
        //right castle
        if (pos.x == 7)
        {
            m_board.movePiece(Vector2i(8, pos.y), Vector2i(6, pos.y));
        }
        // move the king last so it count as last piece that moved.
        m_board.movePiece(m_selectingPos, pos);
        return;
    }

}

bool Rule::checkInsufficientMeterial()
{
    auto& pieces = m_board.getPieces();
    if (pieces.size() < 3)
    {
        for (auto& piece : pieces)
        {
            if (piece->getType() != PieceType::king)
                return false;
        }
        return true;
    }
    else if (pieces.size() == 3)
    {
        for (auto& piece : pieces)
        {
            PieceType type = piece->getType();
            if (type != PieceType::king
                && type != PieceType::knight
                && type != PieceType::bishop)
                return false;
        }
        return true;
    }
    return false;
}

bool Rule::checkRepeatation(Board& board)
{
    string newBoardCode = encodeBoard(board);
    m_encodedBoardHistory.push_back(newBoardCode);
    return (countPositionOccurrences(m_encodedBoardHistory, newBoardCode) >= 3);
}

string Rule::encodeBoard(Board& board)
{
    string boardCode;
    Vector2i pos;
    for (int y = 8; y > 0; y--)
    {
        for (int x = 1; x < 9; x++)
        {
            pos = { x,y };
            if (board.isEmpty(pos))
            {
                boardCode += ".";
            }
            else 
            {
                auto& piece = board.getSquareData(pos);
                if (piece->getColor() == PieceColor::white)
                {
                    boardCode += toupper(piece->getChar());
                }
                else
                {
                    boardCode += tolower(piece->getChar());
                }
            }
        }
    }
    return boardCode;
}

void Rule::countFiftyMove(PieceType type)
{
    m_fiftyMoveCounter++;
    int currentPieceCount = m_board.getPieces().size();
    if (type == PieceType::pawn
        || currentPieceCount != m_lastPieceCount)
        m_fiftyMoveCounter = 0;
    m_lastPieceCount = currentPieceCount;
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

bool Rule::isPromotion()
{
    return m_isPromotion;
}

void Rule::promote(Vector2i pos, char c)
{
    m_board.getBoard().erase(pos);
    m_board.getBoard()[pos] = make_shared<Piece>(pos,c,m_turn);
}

EndType Rule::getEndType()
{
    return m_endType;
}

vector<string>& Rule::getEncodedBoardHistoryRef()
{
    return m_encodedBoardHistory;
}

int& Rule::getFiftyMoveCounterRef()
{
    return m_fiftyMoveCounter;
}

int& Rule::getLastPieceCountRef()
{
    return m_lastPieceCount;
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

int Rule::countPositionOccurrences(const vector<string>& vec, string element) {
    int count = 0;

    for (auto& num : vec) {
        if (num == element) {
            count++;
        }
    }

    return count; // Returns 0 if not found, otherwise returns the count
}

void Rule::eventActivate() {
    count_Event++;
    if (count_Event == 6)
    {
        srand(time(0));
        int event = rand() % 3 +1;
        switch (event)
        {
        case 1:
            m_BurnSquare_Special = true;
            count_Event = 0;
            event = 0;
            break;
        case 2:
            m_CheckKingThreeTime_Special = true;
            count_Event = 0;
            event = 0;
            break;
        case 3:
            m_KingInMiddle_Special = true;
            count_Event = 0;
            event = 0;
            break;
        }
    }
}

#pragma endregion