#include "Rule.h"

vector<Vector2i> Rule::BishopMove(shared_ptr<Piece>& piece) {
	vector<Vector2i> possibleMove;
	Vector2i currentPosition = piece->getPosition();
	//สร้าง Moveset สำหรับการเดิน Bishop
	vector<Vector2i> moveOffSet = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
	for (auto& offset : moveOffSet) {
		Vector2i targetPosition = currentPosition;
		//เช็คเมื่อมีหมากอยู่ในทาง และ โจมตี
		while (true) {
			targetPosition += offset;
			if (targetPosition.x < 1 || targetPosition.x > 8 || targetPosition.y < 1 || targetPosition.y > 8) {
				break;
			}
			if (m_board.isEmpty(targetPosition)) {
				possibleMove.push_back(targetPosition);
			}
			else {
				shared_ptr<Piece> targetPiece = m_board.getSquareData(targetPosition);
				if (targetPiece->getColor() != piece->getColor()) {
					possibleMove.push_back(targetPosition);
				}
				break;
			}

		}
	}
	return possibleMove;
}