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
	// [Class Instances]
	Board m_board;
	Rule m_rule = Rule(m_board);
	BoardParser m_parser;
	Input m_input;

	//[Game State]
	GameState m_gameState = GameState::Start;
	GameType m_gameType = GameType::normal; //GameType::isntInGame;

	// [Game Variables]
	PieceColor m_turn = PieceColor::defult;
	int m_move = 0;
	bool m_isPlaying = false;
	Vector2i m_selectPos;

	void stateMachine(GameState state);
	void enterState(GameState state);
	void exitState(GameState state);

	void switchState(GameState from, GameState to);

	bool onSquareInput(Vector2i& out);

	void startGame();
	void nextTurn();
	void gameOver();
#ifdef DEBUG
	void ParseInputIOTesting(); // <- Purley for testing

	bool tryParse2Vector2i(string s, Vector2i& out);
	pair<string, string> splitString(string s, char c);
#endif // DEBUG

public:
	GameManager();

	void input(vector<optional<Event>>& eventCollections);
	void update(double fps);
	void draw(RenderWindow& window);
};

