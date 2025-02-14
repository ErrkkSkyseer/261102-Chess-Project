#include "Rule.h"

vector<Vector2i> Rule::KingMove(shared_ptr<Piece>& piece, Board& board) {
	vector<Vector2i> possibleMove;
	Vector2i currentPosition = piece->getPosition();
	//สร้าง moveset การเดินของ King
	vector<Vector2i> moveOffSet = { {1, 0}, {-1, 0}, {0, 1}, {0, -1},{1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
	for (auto& moveset : moveOffSet) {
		Vector2i targetPosition = currentPosition + moveset;
		if (targetPosition.x <= 1 && targetPosition.x >= 8 && targetPosition.y <= 1 && targetPosition.y >= 8) {
			if (board.isEmpty(targetPosition)) {
				possibleMove.push_back(targetPosition);
			}else{
				shared_ptr<Piece> targetPiece = board.getSquareData(targetPosition);
				if (targetPiece->getColor() != piece->getColor()) {
					possibleMove.push_back(targetPosition);
				}
			}
		}
	}
	return possibleMove;
}
