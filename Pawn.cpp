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
	return possibleMove;
}

vector<Vector2i> Rule::pawnAtt(shared_ptr<Piece>& piece, Board& board) {
	vector<Vector2i> possibleMove;											//สร้างตัวแปรเก็บตำแหน่ง x, y ที่สามารถเดินได้
	Vector2i currentPossition = piece->getPosition();						//สร้างตัวแปรเก็บตำแหน่ง x, y ตำแหน่งปัจจุบัน
	int direction = (piece->getColor() == PieceColor::white) ? 1 : -1;		//สร้างตัวแปรเก็บค่าการเดิน แกน y
	//การโจมตี
	vector<Vector2i> attackMoves = { currentPossition + Vector2i(-1, direction), currentPossition + Vector2i(1, direction) };
	for (auto& attackMove : attackMoves) {
		if (board.isInBoard(attackMove))
		{
			possibleMove.push_back(attackMove);
		}
	}
	return possibleMove;
}

vector<Vector2i> Rule::enPassant(shared_ptr<Piece>& piece, Board& board)
{
	vector<Vector2i> moves;
	vector<Vector2i> offsets = {{1,0},{-1,0}};

	if (piece->getType() != PieceType::pawn)
		return moves;

	auto& lastMovePiece = board.getLastMocePiece();
	if (lastMovePiece == nullptr)
		return moves;

	for (auto& offset : offsets)
	{
		Vector2i targetPos = piece->getPosition() + offset;
		if (lastMovePiece->getPosition() == targetPos
			&& lastMovePiece->getIsFirsrMove())
		{
			targetPos += piece->getColor() == PieceColor::white ? Vector2i(0, 1) : Vector2i(0, -1);
			moves.push_back(targetPos);
		}
	}
	return moves;
}
