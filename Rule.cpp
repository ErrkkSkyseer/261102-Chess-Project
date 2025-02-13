#include "Rule.h"

Rule::Rule(Board& board, PieceColor& color) : 
    m_board(board), 
    m_turn(color)
{

}

bool Rule::isValidMove(Vector2i init, Vector2i end)
{
    cout << "Compare input position with piece's Possible move vector\n";
    cout << "Checking is move valid\n";
    shared_ptr<Piece>& piece = m_board.getBoard()[init];

    for (int i = 0; i < size(piece->getPossibleMoveArray()); i++) {
        if (piece->getPossibleMoveArray()[i] == end) {
            return true;
        }
    }
    return false;
}

bool Rule::tryMoveSelectedPiece(Vector2i pos)
{
    bool valid = isValidMove(m_selectingPos, pos);

    //check move here

    if (isValidMove(m_selectingPos,pos))
    {
        m_board.movePiece(m_selectingPos, pos);
    }

    return valid;
}

bool Rule::trySelectPiece(Vector2i pos)
{
    bool valid = calculatePossibleMove(pos);

    m_selectingPos = valid ? pos : Vector2i(-1, -1);

    return valid;

}

bool Rule::isGameEnded()
{
    return isGameOver;
}

EndBy Rule::getEndResult()
{
    //Return the result of the game
    //Weather it's draw by... or just checkmate
    return EndBy::null;
}

bool Rule::calculatePossibleMove(Vector2i pos)
{
    std::cout << "Calculating possible moves...\n";
    shared_ptr<Piece>& piece = m_board.getBoard()[pos];

    vector<Vector2i> moveArray = getPieceMove(piece);
    printMovesVector(moveArray);
    piece->setPossibleMoveArray(moveArray);
    return !piece->getPossibleMoveArray().empty();

}

vector<Vector2i> Rule::getPieceMove(shared_ptr<Piece>& piece, bool getOnlyAttackMove)
{
    vector<Vector2i> possibleMoves = vector<Vector2i>();
    vector<Vector2i> moves;
    switch (piece->getType())
    {
    case PieceType::defult:
        break;
    case PieceType::pawn:
        if (!getOnlyAttackMove)
        {
            moves = pawnMove(piece);
            possibleMoves.insert(possibleMoves.end(), moves.begin(), moves.end());
            printMovesVector(possibleMoves);
        }
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
    return possibleMoves;
}

void Rule::calculateBoardState()
{
    cout << "Updating Board...\n";
    return;
}

Vector2i Rule::getKingPos(PieceColor color) {

    Vector2i Kingpos;
    vector<shared_ptr<Piece>&> pieces = m_board.getBoardAsVector();
    for (int i = 0; i < pieces.size(); i++)
    {
        if (pieces[i]->getColor() == color && pieces[i]->getType() == PieceType::king) {
            Kingpos = pieces[i]->getPosition();
        }
    }
    return Kingpos;
}

bool Rule::Check(PieceColor color) {

    Vector2i kingpos = getKingPos(color);
    vector<Vector2i> controllSquare = getcontrollSquare(color);
    for (int i = 0; i < controllSquare.size(); i++)
    {
        if (kingpos == controllSquare[i]) {
            return true;
        }
    }
    return false;
}

vector<Vector2i> Rule::getcontrollSquare(PieceColor color)
{

    vector<Vector2i> controllSquare;
    vector<shared_ptr<Piece>&> pieces = m_board.getBoardAsVector();
    for (int i = 0; i < pieces.size(); i++)
    {
        if (pieces[i]->getColor() == color) {
            joinMoveVector(controllSquare, getPieceMove(pieces[i], true));
        }
    }
    set<Vector2i> temp(controllSquare.begin(), controllSquare.end());
    vector<Vector2i> trimcontrollSquare(temp.begin(), temp.end());
    return trimcontrollSquare;
}

void Rule::FiftyRule() {
    fiftyrule++;

}

vector<Vector2i> Rule::Pin(shared_ptr<Piece>& piece, vector<Vector2i>& possiblemove) {
    PieceColor color = piece->getColor();
    for (int i = 0; i < possiblemove.size(); i++)
    {
        Board ghost = m_board;
     
    }
}

void Rule::joinMoveVector(vector<Vector2i>& u, vector<Vector2i> v)
{
    u.insert(u.end(), v.begin(), v.end());

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
