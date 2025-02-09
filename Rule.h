#pragma once
#include <SFML/System.hpp>
#include <iostream>
#include <memory>

#include "Board.h"

using namespace sf;
using namespace std;

class Rule
{
private:
	Board* m_Board;

	vector<Vector2i> m_controllingSquareWhite;
	vector<Vector2i> m_controllingSquareBlack;

	vector<Vector2i> pawnMove(shared_ptr<Piece>& piece);
	vector<Vector2i>pawnAtt(shared_ptr<Piece>& piece);
	vector<Vector2i> KnightMove(shared_ptr<Piece>& piece);
	vector<Vector2i> BishopMove(shared_ptr<Piece>& piece);
	vector<Vector2i> RookMove(shared_ptr<Piece>& piece);
	vector<Vector2i> QueenMove(shared_ptr<Piece>& piece);
	vector<Vector2i> KingMove(shared_ptr<Piece>& piece);


public:
	Rule(Board& board);

	bool canMove(shared_ptr<Piece>& piece);
	bool isValidMove(shared_ptr<Piece>& piece, Vector2i pos);

	void calculateBoardState();
	bool calculatePossibleMove(shared_ptr<Piece>& piece);
	
};

