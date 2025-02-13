#pragma once
#include <SFML/System.hpp>
#include <iostream>
#include <memory>

#include "Board.h"

#include "Debug.h"

using namespace sf;
using namespace std;
class Rule
{
private:
	Board& m_Board;
  	bool isCheck = false;
	vector<Vector2i> m_controllingSquareWhite;
	vector<Vector2i> m_controllingSquareBlack;
	int fiftyrule = 0;

	void FiftyRule();
	bool Check();
	Vector2i Kingpos();
	void Pin();

	vector<Vector2i> pawnMove(shared_ptr<Piece>& piece);
	vector<Vector2i> pawnAtt(shared_ptr<Piece>& piece);
	vector<Vector2i> KnightMove(shared_ptr<Piece>& piece);
	vector<Vector2i> BishopMove(shared_ptr<Piece>& piece);
	vector<Vector2i> RookMove(shared_ptr<Piece>& piece);
	vector<Vector2i> QueenMove(shared_ptr<Piece>& piece);
	vector<Vector2i> KingMove(shared_ptr<Piece>& piece);

#ifdef DEBUG

	void printMovesVector(vector<Vector2i>);

#endif // DEBUG
public:
	Rule(Board& board);

	bool isValidMove(shared_ptr<Piece>& piece, Vector2i pos);

	void calculateBoardState();
	bool calculatePossibleMove(shared_ptr<Piece>& piece);
	
};

