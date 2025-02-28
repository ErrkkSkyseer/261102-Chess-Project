#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class UIboard
{	
	int m_boardSize = 8;
	int m_tileSize = 80;
	Vector2f m_offset;

	vector <RectangleShape> squares;
	 
public:
	void draw(RenderWindow&);
	UIboard(int boardSize, int tileSize, Vector2f offset);
	void Initialize();
};

