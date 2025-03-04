#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <map>

#include "TextureHolder.h"
#include "Board.h"
#include "Rule.h"
#include "UIboard.h"
#include "UIpiece.h"
#include "Vector2Utils.h"
#include "StartScene.h"
#include "Input.h"

#define BOARD_SIZE 8
#define TILE_SIZE 80
#define BOARD_OFFSET_X 180
#define BOARD_OFFSET_Y 180

using namespace std;
using namespace sf;

class GUI
{
public :
	TextureHolder m_s_TH;
private: 
	bool& m_isPLayingRef;
	GameType& m_gameType;

	Board& m_board;
	Rule& m_rule;
	Input& m_input;


	UIboard m_UIboard = UIboard(BOARD_SIZE, TILE_SIZE, {BOARD_OFFSET_X,BOARD_OFFSET_Y});
	map<Vector2i, UIpiece> m_UIpieces;

	StartScene m_startScene = StartScene(m_input, m_isPLayingRef, m_gameType);

	string piecetoTexture(Piece&);

public:
	GUI(Board& board,Rule& m_rule, Input& input, bool& isPlaying, GameType& gameType);

	Vector2i ScreenToBoard(Vector2i screenCoords);

	void onBoardUpdate();
	void draw(RenderWindow& window);

	StartScene& getStartScene();
};

