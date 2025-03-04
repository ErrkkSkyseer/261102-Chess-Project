#pragma once
#include <fstream>
#include <iostream>
#include <SFML/System.hpp>
#include <map>
#include <string>
#include <memory>
#include <cassert>

#include "Piece.h"
#include "Rule.h"
#include "Board.h"
#include "Rule.h"
#include "Vector2Utils.h"
#include "BaseGameEnum.h"

using namespace sf;

class BoardParser
{
private:
	Board& m_board;
	Rule& m_rule;
	map<PieceType, PieceColor> colorMap;

	PieceColor ParseColor(char c);
	PieceType ParseType(char c);
	bool ParseMoved(char c);

public:

	BoardParser(Board& board, Rule& rule);
	void ParseFile(map<Vector2i, shared_ptr<Piece>>&, string path = "Board/inboard.txt"); //Create Piece from inboard.txt
	void SaveFile(const map<Vector2i, shared_ptr<Piece>>& board, int& m_move, PieceColor& m_currentTurn, int& fiftyMoveCounter, int& lastPieceCount, vector<string>& encodedBoardHistory, string path = "Board/SaveLoad.txt"); //Save in SaveLoad.txt
	void LoadGame(map<Vector2i, shared_ptr<Piece>>& board, int& m_move, PieceColor& m_currentTurn, int& fiftyMoveCounter, int& lastPieceCount, vector<string>& encodedBoardHistory, string path = "Board/SaveLoad.txt"); //Load from SaveLoad.txt

};