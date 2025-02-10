#include "Rule.h"

void Rule::Pin() {
    for (int y = 1; y < 9; y++) {
        for (int x = 1; x < 9; x++) {
            Vector2i pos = Vector2i(x, y);
            if (!m_Board->isEmpty(pos)) {
                auto& piece = m_Board->getSquareData(pos);
                if (piece->getType() == PieceType::king) {
                    Vector2i kingpos = piece->getPosition();
                }
            }
        }
    }
}
