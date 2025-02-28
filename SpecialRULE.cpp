#include "Rule.h"
#include <cstdlib>
// Special Rule are here!
void Rule::BurnSquare_Special() {
    srand(time(0));
    cout << "Be Careful...IT TIME FOR BURN YOUR PIECE🔥\n";
    vector<Vector2i> possi_pos;
    for (int y = 3; y <= 6; y++) {
        for (int x = 1; x <= 8; x++) {
            Vector2i pos = { x, y };
            possi_pos.push_back(pos);
        }
    }
    int num_for_select = rand() % possi_pos.size();
    Vector2i select_pos = possi_pos[num_for_select];

    vector<Vector2i> destroySquares = {select_pos + Vector2i(1, 0), select_pos + Vector2i(-1, 0), select_pos + Vector2i(0, 1), select_pos + Vector2i(0, -1), select_pos};
    for (auto& targetpos : destroySquares) {
        if (m_board.isInBoard(targetpos) && !m_board.isEmpty(targetpos)) {
            cout << "Piece at X = " << targetpos.x << "and Y = " << targetpos.y << " BURNED!!!\n";
            m_board.getBoard()[targetpos] = nullptr;
        }
    }
}


bool Rule::CheckKingThreeTime_Special() {
    if (isCheck(PieceColor::white, m_board)) whitecheckcount++;
    if (isCheck(PieceColor::black, m_board)) blackcheckcount++;

    if (whitecheckcount >= 3) {
        cout << "While wins by CheckKingThreeTime! \n";
        m_endType = EndType::threecheck;
        return true;

    }
    if (blackcheckcount >= 3) {
        cout << "Black wins by CheckKingThreeTime! \n";
        m_endType = EndType::threecheck;
        return true;
    }
    return false;
}

bool Rule::KingInMiddle_Special() {
    Vector2i W_KingPossition = findKingPos(PieceColor::white, m_board);
    Vector2i B_KingPossition = findKingPos(PieceColor::black, m_board);
    
    vector<Vector2i> middleSq = { {4, 4}, {5, 4}, {4, 5}, {5, 5} };
    if (find(middleSq.begin(), middleSq.end(), W_KingPossition) != middleSq.end()) {
        if (W_kinginmiddle) {
            cout << "White wins by controlling the middle square for 1 turn!\n";
            m_endType = EndType::kinginmiddle;
        }
        W_kinginmiddle = true;
        return true;
    }
    else {
        W_kinginmiddle = false;
    }
    if (find(middleSq.begin(), middleSq.end(), B_KingPossition) != middleSq.end()) {
        if (B_kimginmiddle) {
            cout << "black wins by controlling the middle square for 1 turn!\n";
            m_endType = EndType::kinginmiddle;
        }
        B_kimginmiddle = true;
        return true;
    }
    else {
        B_kimginmiddle = false;
    }
}