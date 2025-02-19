#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class UIboard
{	
	const int SIZE = 8;
	const int TILE_SIZE = 80;
	vector <RectangleShape> squares;
	
	 
public:
	void draw(RenderWindow&);
	UIboard();
};

