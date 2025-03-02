#include "Rule.h"

vector<Vector2i> Rule::QueenMove(shared_ptr<Piece>& piece, Board& board) {
	vector<Vector2i> possibleMove;
	Vector2i currentPosition = piece->getPosition();
	//สร้าง moveset การเดินของ Queen
	vector<Vector2i> moveOffSet = { {1, 0}, {-1, 0}, {0, 1}, {0, -1},{1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
	for (auto& moveset : moveOffSet) {
		Vector2i targetPosition = currentPosition;
		while (true)
		{
			targetPosition += moveset;
			//เช็คว่าอยู่ในกระดานไหม และ สามารถโจมตีได้ไหม
			if (!board.isInBoard(targetPosition))
			{
				break;
			}

			possibleMove.push_back(targetPosition);

			if (!board.isEmpty(targetPosition))
				break;
			
		}
	}
	return possibleMove;
}