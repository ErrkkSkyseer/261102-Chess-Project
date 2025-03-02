#include "Rule.h"

vector<Vector2i> Rule::KingMove(shared_ptr<Piece>& piece, Board& board) {
	vector<Vector2i> possibleMove;
	Vector2i currentPosition = piece->getPosition();
	//สร้าง moveset การเดินของ King
	vector<Vector2i> moveOffSet = { {1, 0}, {-1, 0}, {0, 1}, {0, -1},{1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
	for (auto& moveset : moveOffSet) {
		Vector2i targetPosition = currentPosition + moveset;
		if (board.isInBoard(targetPosition)) {
			possibleMove.push_back(targetPosition);
		}
	}
	return possibleMove;
}

vector<Vector2i> Rule::castel(shared_ptr<Piece>& piece, Board& board)
{
	vector<Vector2i> moves;

	if (piece->getType() != PieceType::king
		|| piece->getHasMove())
		return moves;
	
	vector<Vector2i> controlSquares = getControllingPos(flipColor(piece->getColor()),board);
	Vector2i stepLeft = {-1,0};
	Vector2i stepRight = {1,0};

	Vector2i pos = piece->getPosition();
	int step = 0;
	//Left Castle
	while (true)
	{
		pos += stepLeft;
		step++;
		
		//still in board?
		if (!board.isInBoard(pos))
			break;

		if (step <= 2)
		{
			//if going pass control square, it's check! You can't castle pass check!
			if (find(controlSquares.begin(), controlSquares.end(), pos) != controlSquares.end())
				break;
		}

		// find piece bloccking the way (not rook)
		if (!board.isEmpty(pos) && step != 4)
			break;

		// the square rook should've be
		if (step == 4)
		{
			// check if it's actually rook
			if (!board.isEmpty(pos) 
				&& board.getSquareData(pos)->getType() == PieceType::rook)
			{
				auto& rook = board.getSquareData(pos);
				//check if rook moved
				if (!rook->getHasMove())
				{
					moves.push_back(piece->getPosition() + (stepLeft * 2));
				}
			}
		}
	}


	pos = piece->getPosition();
	step = 0;
	//Right Castle
	while (true)
	{
		pos += stepRight;
		step++;

		//still in board?
		if (!board.isInBoard(pos))
			break;

		if (step <= 2)
		{
			//if going pass control square, it's check! You can't castle pass check!
			if (find(controlSquares.begin(), controlSquares.end(), pos) != controlSquares.end())
				break;
		}

		// find piece bloccking the way (not rook)
		if (!board.isEmpty(pos) && step != 3)
			break;

		// the square rook should've be
		if (step == 3)
		{
			// check if it's actually rook
			if (!board.isEmpty(pos)
				&& board.getSquareData(pos)->getType() == PieceType::rook)
			{
				auto& rook = board.getSquareData(pos);
				//check if rook moved
				if (!rook->getHasMove())
				{
					moves.push_back(piece->getPosition() + (stepRight * 2));
				}
			}
		}
	}

	return moves;
}


