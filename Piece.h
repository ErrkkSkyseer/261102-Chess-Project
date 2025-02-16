#pragma once
#include <SFML/System.hpp>
#include <iostream>

#include <vector>

#include "BaseGameEnum.h"
#include "Debug.h"

using namespace std;
using namespace sf;

class Piece
{
private:
	Vector2i m_position;
	vector<Vector2i> m_possibleMove;

	PieceType m_type = PieceType::defult;
	PieceColor m_color = PieceColor::defult;

	char m_char = '\0';

	bool m_hasMoved = false;

public:

	Piece(Vector2i pos, char type, PieceColor color = PieceColor::defult);

	vector<Vector2i> getPossibleMoveArray();
	void setPossibleMoveArray(vector<Vector2i> v);

	PieceType getType();
	PieceColor getColor();

	Vector2i getPosition();
	void setPosition(Vector2i pos);

	char getChar();

	bool getHasMove();
	void setHasMove(bool value);


	void printStatus();
};

