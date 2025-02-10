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
	,InputSelect
	,InputTarget
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

	PieceColor m_turn = PieceColor::black;

	bool m_isPlaying = false;

	string m_consoleInput;
	Vector2i m_selectingVector;
	Vector2i m_targetVector;


	//void ParseInputIOTesting(); // <- Purley for testing

	void stateMachine(GameState state);
	void enterState(GameState state);
	void exitState(GameState state);

	bool tryParse2Vector2i(string s, Vector2i& out);
	bool movePiece(Vector2i first, Vector2i end);

	pair<string, string> splitString(string s, char c);

public:
	GameManager();

	int _fiftyRuleCount = 0;
	void input(vector<optional<Event>>& eventCollections);
	void update(double fps);
	void draw(RenderWindow& window);
};

