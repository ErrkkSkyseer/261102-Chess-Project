#pragma once
#include <SFML/System.hpp>
#include <iostream>
#include <memory>
#include <set>

#include "Board.h"
#include "BaseGameEnum.h"

#include "Debug.h"

using namespace sf;
using namespace std;
class Rule
{
private:
	Board& m_board;
	PieceColor& m_turn;

	Vector2i m_selectingPos;
	
	bool calculatePossibleMove(shared_ptr<Piece>& piece);

#pragma region PieceMovement
	vector<Vector2i> pawnMove(shared_ptr<Piece>& piece	,Board& board);
	vector<Vector2i> pawnAtt(shared_ptr<Piece>& piece	,Board& board);
	vector<Vector2i> KnightMove(shared_ptr<Piece>& piece,Board& board);
	vector<Vector2i> BishopMove(shared_ptr<Piece>& piece,Board& board);
	vector<Vector2i> RookMove(shared_ptr<Piece>& piece	,Board& board);
	vector<Vector2i> QueenMove(shared_ptr<Piece>& piece	,Board& board);
	vector<Vector2i> KingMove(shared_ptr<Piece>& piece	,Board& board);
#pragma endregion
	vector<Vector2i> getPieceMoveset(shared_ptr<Piece>& piece, Board& board, bool onlyGetAttackMove = false);

	bool isValidMove(shared_ptr<Piece>& piece, Vector2i end);
	vector<Vector2i> getControllingPos(PieceColor color, Board& board);
	Vector2i findKingPos(PieceColor color);
	
	bool check(PieceColor color, Board& board);
	bool checkMate(PieceColor color);

	vector<Vector2i> getPinnedMove(shared_ptr<Piece>& piece, const vector<Vector2i> moveArray);

#ifdef DEBUG

	void printMovesVector(vector<Vector2i>);

#endif // DEBUG

	void joinMoveArray(vector<Vector2i>& base, const vector<Vector2i>& add);
	PieceColor flipColor(PieceColor color);

public:
	Rule(Board& board, PieceColor& color);

	bool trySelect(Vector2i pos);
	bool tryMove(Vector2i pos);

	void calculateBoardState();
	
};

