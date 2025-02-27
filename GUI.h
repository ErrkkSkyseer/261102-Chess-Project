#pragma once
#include<SFML/Graphics.hpp>
#include<map>

#include "TextureHolder.h"
#include "Board.h"
#include "Rule.h"
#include "UIboard.h"
#include "UIpiece.h"
#include "Vector2Utils.h"

#define BOARD_SIZE 8
#define TILE_SIZE 80
#define BOARD_OFFSET_X 180
#define BOARD_OFFSET_Y 180

using namespace std;
using namespace sf;

class GUI
{
private: 

	Board& m_board;
	Rule& m_rule;

	UIboard m_UIboard = UIboard(BOARD_SIZE, TILE_SIZE, {BOARD_OFFSET_X,BOARD_OFFSET_Y});
	map<Vector2i, UIpiece> m_UIpieces;

	string piecetoTexture(Piece&);

public:
	TextureHolder m_s_TH;

	GUI(Board& board,Rule& m_rule);

	Vector2i ScreenToBoard(Vector2i screenCoords);

	void onBoardUpdate();
	void draw(RenderWindow& window);
};

