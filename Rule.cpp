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

    for (int i = 0; i < size(piece->getPossibleMoveArray()); i++) {
        if (piece->getPossibleMoveArray()[i] == pos) {
            return true;
        }
    }
    return false;
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

bool Rule::Check() {
    bool turnwhite = true; //wait for checkturn-func
    Vector2i Kingpos;
    for (int y = 1; y < 9; y++){
        for (int x = 1; x < 9; x++) {
            Vector2i pos = Vector2i(x,y);
            if (!m_Board->isEmpty(pos)){
                auto& piece = m_Board->getSquareData(pos);
                if (turnwhite == true) {
                    if (piece->getColor() == PieceColor::white) { //WAIT FOR CHECKTURN-FUNC!!

                        if (piece->getType() == PieceType::king) {
                            Kingpos = pos;

                        }
                    }
                }
                else if(turnwhite == false){
                    if (piece->getColor() == PieceColor::black) { //WAIT FOR CHECKTURN-FUNC!!

                        if (piece->getType() == PieceType::king) {
                            Kingpos = pos;

                        }
                    }
                }
             

            }
        }
    }
    if (turnwhite == true)
    {
        for (int i = 0; i < m_controllingSquareWhite.size(); i++) {
            if (Kingpos == m_controllingSquareWhite[i]) {
                return true;
            }
        }
    }
    else if (turnwhite == false)
    {
        for (int i = 0; i < m_controllingSquareBlack.size(); i++) {
            if (Kingpos == m_controllingSquareBlack[i]) {
                return true;
            }
        }
    }
   
    return false;
}