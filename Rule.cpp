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
}

void Rule::calculateBoardState()
{
    cout << "Updating Board...\n";
    return;
}
