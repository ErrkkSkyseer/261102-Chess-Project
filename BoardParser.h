#pragma once
#include <fstream>
#include <iostream>
#include <SFML/System.hpp>
#include <map>
#include <string>
#include <memory>
#include <cassert>

#include "Board.h"
#include "Vector2Utils.h"
#include "BaseGameEnum.h"

using namespace std;
using namespace sf;

class BoardParser
{
private:
	Board& m_board;
	map<PieceType, PieceColor> colorMap;

	PieceColor ParseColor(char c);
	PieceType ParseType(char c);
	bool ParseMoved(char c);

public:
	BoardParser(Board& board);
	void ParseFile(map<Vector2i, shared_ptr<Piece>>&, string path = "inboard.txt");

};