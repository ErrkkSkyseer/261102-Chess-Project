#pragma once
#include<SFML/Graphics.hpp>
#include<map>

#include "TextureHolder.h"
#include "Board.h"
#include "Rule.h"
#include "UIboard.h"
#include "UIpiece.h"
#include "Vector2Utils.h"


using namespace std;
using namespace sf;

class GUI
{
private: 
	Board& m_board;
	Rule& m_rule;

	UIboard m_UIboard;
	map<Vector2i, UIpiece> m_UIpieces;

public:
	TextureHolder m_s_TH;

	GUI(Board& board,Rule& m_rule);

	void onBoardUpdate();
	void draw(RenderWindow& window);
};

