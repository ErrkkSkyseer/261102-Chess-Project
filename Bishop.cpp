#include "Rule.h"

vector<Vector2i> Rule::BishopMove(shared_ptr<Piece>& piece, Board& board) {
	vector<Vector2i> possibleMove;
	Vector2i currentPosition = piece->getPosition();
	//สร้าง Moveset สำหรับการเดิน Bishop
	vector<Vector2i> moveOffSet = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
	for (auto& offset : moveOffSet) {
		Vector2i targetPosition = currentPosition;
		//เช็คเมื่อมีหมากอยู่ในทาง และ โจมตี
		while (true) {
			targetPosition += offset;
			if (!board.isInBoard(targetPosition)) {
				break;
			}

			possibleMove.push_back(targetPosition);

			if (board.isEmpty(targetPosition))
				break;

		}
	}
	return possibleMove;
}