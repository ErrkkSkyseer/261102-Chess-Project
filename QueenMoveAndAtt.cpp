#include "Rule.h"

vector<Vector2i> Rule::QueenMove(shared_ptr<Piece>& piece) {
	vector<Vector2i> possibleMove;
	Vector2i currentPosition = piece->getPosition();
	//สร้าง moveset การเดินของ Queen
	vector<Vector2i> moveOffSet = { {1, 0}, {-1, 0}, {0, 1}, {0, -1},{1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
	for (auto& moveset : moveOffSet) {
		Vector2i targetPosition = currentPosition;
		while(true) {
			targetPosition += moveset;
			//เช็คว่าอยู่ในกระดานไหม และ สามารถโจมตีได้ไหม
			if (targetPosition.x < 1 || targetPosition.x > 8 || targetPosition.y < 1 || targetPosition.y > 8) {
				break;
			}if (m_Board->isEmpty(targetPosition)) {
				possibleMove.push_back(targetPosition);
				// เช็คว่ามีหมากอยู่ในเส้นทางหรือไม่ และ โจมตี
			}else{
				shared_ptr<Piece> targetPiece = m_Board->getSquareData(targetPosition);
				if (targetPiece->getColor() != piece->getColor()) {
					possibleMove.push_back(targetPosition);
				}
				break;
			}
		}
	}
	return possibleMove;
}