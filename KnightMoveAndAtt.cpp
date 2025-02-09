#include "Rule.h"

vector<Vector2i> Rule::KnightMove(shared_ptr<Piece>& piece) {
	vector<Vector2i> possibleMove;									//สร้างตัวแปรเก็บค่า x, y ที่สามารถเดินได้
	Vector2i currentPossition = piece->getPosition();				//สร้างตัวแปรเก็บค่า x, y ปัจจุบัน
	// สร้าง moveSet ที่หมากตัวนี้สามารถเดินได้
	vector<Vector2i> moveOffset = { {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
	for (auto& offset : moveOffset) {
		Vector2i targetPosition = currentPossition + offset;		//เช็คว่าหมากมีการเดินออกสนามหรือไม่
		if (targetPosition.x >= 1 && targetPosition.x <= 8 && targetPosition.y >= 1 && targetPosition.y <= 8) {
			if (m_Board->isEmpty(targetPosition)) {
				possibleMove.push_back(targetPosition);
			}else{													//โจมตี
				shared_ptr<Piece> targetPiece = m_Board->getSquareData(targetPosition);
				if(targetPiece->getColor() != piece->getColor()){
					possibleMove.push_back(targetPosition);
				}
			}
		}
	}
	return possibleMove;
}