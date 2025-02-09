#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Board.h"
#include "BoardParser.h"
#include "Rule.h"
#include "BaseGameEnum.h"
#include "Input.h"

using namespace std;
using namespace sf;

enum class GameState
{
	Start
	,Select
	,Target
	,End
};

class GameManager
{
private:
	Board m_board;
	Rule m_rule = Rule(m_board);
	BoardParser m_parser;
	Input m_input;

	GameState m_gameState = GameState::Start;

	GameType m_gameType = GameType::normal; //GameType::isntInGame;

	PieceColor m_turn = PieceColor::white;

	bool m_isPlaying = false;

	Vector2i m_selectPos;


	//void ParseInputIOTesting(); // <- Purley for testing

	void stateMachine(GameState state);
	void enterState(GameState state);
	void exitState(GameState state);

	void switchState(GameState from, GameState to);

	bool tryParse2Vector2i(string s, Vector2i& out);
	pair<string, string> splitString(string s, char c);

public:
	GameManager();

	void input(vector<optional<Event>>& eventCollections);
	void update(double fps);
	void draw(RenderWindow& window);
};

