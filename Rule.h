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

public:
	Rule(Board& board);

	bool canMove(shared_ptr<Piece>& piece);
	bool isValidMove(shared_ptr<Piece>& piece, Vector2i pos);

	void calculateBoardState();
	void calculatePossibleMove(shared_ptr<Piece>& piece);
	
};

