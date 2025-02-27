#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<set>
#include<algorithm>

#include "Debug.h"

#ifdef DEBUG
#include<conio.h>
#endif // DEBUG


#define K2S(x) case sf::Keyboard::Key:: ## x : ret = #x; break;

using namespace sf;
using namespace std;

class Input
{
private:
	bool m_isAnyKeyDown = false;

	bool m_isMouseDown = false;
	Vector2i m_MousePos;

	set<Keyboard::Key> m_keysPressed;

	string m_consoleInput = "";

	string Key2Str(const Keyboard::Key&);


public:

	void UpdateEvent(vector<optional<Event>>& eventCollection);

#ifdef DEBUG
	void collectInputKey();
	void resetConsoleInput();
	string getConsoleInput();
#endif // !DEBUG

	bool getAnyKeyPress();
	bool getKeyPress(Keyboard::Key);

	bool isMouseDown();
	Vector2i getMousePos();

	bool OnClick();
};

