#pragma once
#include <iostream>
#include <SFML/System.hpp>

#include "Board.h"
#include "BoardParser.h"
#include "Rule.h"
#include "BaseGameEnum.h"

using namespace std;
using namespace sf;

class GameManager
{
private:
	Board m_board;
	Rule rule;
	BoardParser m_parser;

	GameType m_gameType;

	PieceColor m_turn;

	bool m_isPlaying;

	void ParseInputIOTesting();

public:
	GameManager();

	void input();
	void update();
	void draw();
};

