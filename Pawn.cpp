#include "Rule.h"

vector<Vector2i> Rule::pawnMove(shared_ptr<Piece>& piece, Board& board) {
	vector<Vector2i> possibleMove;											//สร้างตัวแปรเก็บตำแหน่ง x, y ที่สามารถเดินได้
	Vector2i currentPossition = piece->getPosition();						//สร้างตัวแปรเก็บตำแหน่ง x, y ตำแหน่งปัจจุบัน
	int direction = (piece->getColor() == PieceColor::white) ? 1 : -1;		//สร้างตัวแปรเก็บค่าการเดิน แกน y

	//การเดินปกติ
	Vector2i forwardMove = currentPossition + Vector2i(0, direction);
	if (board.isEmpty(forwardMove)) {									//ถ้าตำแหน่งการเดินว่าง ส่งค่าเข้า possibleMove
		possibleMove.push_back(forwardMove);
		//การเดิน 2 ช่อง
		Vector2i doubleForwardMove = currentPossition + Vector2i(0, 2 * direction);		//สร้างตัวแปรสำหรับการเดิน 2 ช่อง
		if (!piece->getHasMove() && board.isEmpty(doubleForwardMove)) {				//เช็คว่าเคยเดินไหม
			possibleMove.push_back(doubleForwardMove);
		}
	}
	//การโจมตี
	vector<Vector2i> attackMoves = {currentPossition + Vector2i(-1, direction), currentPossition + Vector2i(1, direction)};
	for (auto& attackMove : attackMoves) {
		if (!board.isEmpty(attackMove)) {
			shared_ptr<Piece> targetPiece = board.getSquareData(attackMove);
			if (targetPiece->getColor() != piece->getColor()) {
				possibleMove.push_back(attackMove);
			}
		}
	}
	//อัปเดตสถานะเมื่อเดินครั้งแรก
	if (!possibleMove.empty() && !piece->getHasMove()) {
		piece->setHasMove(true);
		piece->setIsFirstMove(false);
	}
	return possibleMove;
}

vector<Vector2i> Rule::pawnAtt(shared_ptr<Piece>& piece, Board& board) {
	vector<Vector2i> possibleMove;											//สร้างตัวแปรเก็บตำแหน่ง x, y ที่สามารถเดินได้
	Vector2i currentPossition = piece->getPosition();						//สร้างตัวแปรเก็บตำแหน่ง x, y ตำแหน่งปัจจุบัน
	int direction = (piece->getColor() == PieceColor::white) ? 1 : -1;		//สร้างตัวแปรเก็บค่าการเดิน แกน y
	//การโจมตี
	vector<Vector2i> attackMoves = { currentPossition + Vector2i(-1, direction), currentPossition + Vector2i(1, direction) };
	for (auto& attackMove : attackMoves) {
		if (!board.isEmpty(attackMove)) {
			shared_ptr<Piece> targetPiece = board.getSquareData(attackMove);
			if (targetPiece->getColor() != piece->getColor()) {
				possibleMove.push_back(attackMove);
			}
		}
	}
	//อัปเดตสถานะเมื่อเดินครั้งแรก
	if (!possibleMove.empty() && !piece->getHasMove()) {
		piece->setHasMove(true);
		piece->setIsFirstMove(false);
	}
	return possibleMove;
}