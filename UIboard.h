#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

#define BOARD_SIZE 8
#define TILE_SIZE 80

class UIboard
{	
	vector <RectangleShape> squares;
	 
public:
	void draw(RenderWindow&);
	UIboard();
};

