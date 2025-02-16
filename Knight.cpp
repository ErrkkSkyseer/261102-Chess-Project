#include "Rule.h"

vector<Vector2i> Rule::KnightMove(shared_ptr<Piece>& piece, Board& board) {
	vector<Vector2i> possibleMove;									//สร้างตัวแปรเก็บค่า x, y ที่สามารถเดินได้
	Vector2i currentPossition = piece->getPosition();				//สร้างตัวแปรเก็บค่า x, y ปัจจุบัน
	// สร้าง moveSet ที่หมากตัวนี้สามารถเดินได้
	vector<Vector2i> moveOffset = { {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
	for (auto& offset : moveOffset) {
		Vector2i targetPosition = currentPossition + offset;		//เช็คว่าหมากมีการเดินออกสนามหรือไม่
		if (board.isInBoard(targetPosition)) {
			possibleMove.push_back(targetPosition);

			if (board.isEmpty(targetPosition))
				break;
		}
	}
	return possibleMove;
}