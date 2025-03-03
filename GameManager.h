#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>

#include "Board.h"
#include "BoardParser.h"
#include "Rule.h"
#include "BaseGameEnum.h"
#include "Input.h"

#ifdef UseDebugBoard
#define UseDebugBoard "...txt"

#endif // useDebugBoard

#include "GUI.h"

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
	Rule m_rule = Rule(m_board,m_turn,m_gameType);
	BoardParser m_parser = BoardParser(m_board);
	Input m_input;

	GUI m_GUI = GUI(m_board,m_rule);

	//[Game State]
	GameState m_gameState = GameState::Start;
	int m_inputState = 0;
	GameType m_gameType; //GameType::isntInGame;

	// [Game Variables]
	PieceColor m_turn = PieceColor::defult;
	int m_move = 0;
	bool m_isPlaying = false;
	
	Vector2i m_selectPos;

	void enterState(int state);

	void exitState(int state);

	void switchState(int to);

	bool onSquareInput(Vector2i& out);

	void startGame();
	void nextTurn();
	void gameOver(EndType endtype);

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

