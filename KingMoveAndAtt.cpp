#include "Rule.h"

vector<Vector2i> Rule::KingMove(shared_ptr<Piece>& piece) {
	vector<Vector2i> possibleMove;
	Vector2i currentPosition = piece->getPosition();
	//สร้าง moveset การเดินของ King
	vector<Vector2i> moveOffSet = { {1, 0}, {-1, 0}, {0, 1}, {0, -1},{1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
	for (auto& moveset : moveOffSet) {
		Vector2i targetPosition = currentPosition + moveset;
		if (targetPosition.x <= 1 && targetPosition.x >= 8 && targetPosition.y <= 1 && targetPosition.y >= 8) {
			if (m_Board->isEmpty(targetPosition)) {
				possibleMove.push_back(targetPosition);
			}else{
				shared_ptr<Piece> targetPiece = m_Board->getSquareData(targetPosition);
				if (targetPiece->getColor() != piece->getColor()) {
					possibleMove.push_back(targetPosition);
				}

			}
		}
	}
	return possibleMove;

	if (!possibleMove.empty() && !piece->getHasMove()) {
		piece->setHasMove(true);
		piece->setIsFirstMove(false);
	}
	return possibleMove;

	//Castle
	Vector2i kingpos = piece->getPosition();
	vector<Vector2i> moveOffSetforCastle = { {1, 0}, {-1, 0}};
	if (!piece->getHasMove())
	{
		while (true)
		{
			for (auto& moveset : moveOffSetforCastle)
			{
				Vector2i targetPosition = kingpos;
				if (targetPosition.x >= 3 || targetPosition.x <= 7 ){
					break;
				}
				if (m_Board->isEmpty(targetPosition)) {
					for (int i = 0; i < m_controllingSquareWhite.size(); i++)
					{
						if (targetPosition != m_controllingSquareWhite[i]) {
								possibleMove.push_back(targetPosition);
								break;
						}

					}
				}

			}
		}
	}
	return possibleMove;

}
