#pragma once
#include <fstream>
#include <iostream>
#include <SFML/System.hpp>
#include <map>
#include <string>
#include <memory>

#include "Piece.h"
#include "Board.h"
#include "Vector2Utils.h"
#include "BaseGameEnum.h"

using namespace sf;

class BoardParser
{
private:
	Board& m_board;
	std::map<PieceType, PieceColor> colorMap;

	PieceColor ParseColor(char c);
	PieceType ParseType(char c);
	bool ParseMoved(char c);

public:
	BoardParser(Board& board);
	void ParseFile(map<Vector2i, shared_ptr<Piece>>&, string path = "Board/inboard.txt"); //Create Piece from inboard.txt
	void SaveFile(const map<Vector2i, shared_ptr<Piece>>& board, int m_move, PieceColor m_currentTurn, string path = "Board/SaveLoad.txt"); //Save in SaveLoad.txt
};