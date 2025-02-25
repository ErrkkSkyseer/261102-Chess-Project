#pragma once
#include"UIboard.h"
#include<SFML/Graphics.hpp>
#include"UIpiece.h"
#include<map>
#include"Vector2Utils.h"

using namespace std;
using namespace sf;

class GUI
{
private:
	UIboard m_UIboard;
	map<Vector2i, UIpiece> m_UIpieces;

public:
	void draw(RenderWindow& window);
	GUI();
};

