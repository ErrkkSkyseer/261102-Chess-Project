#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<conio.h>
#include<set>
#include<algorithm>

#define K2S(x) case sf::Keyboard::Key:: ## x : ret = #x; break;

using namespace sf;
using namespace std;

class Input
{
private:
	bool m_isAnyKeyDown = false;
	set<Keyboard::Key> m_keysPressed;

	string m_consoleInput = "";

	void resetFlag();
	string Key2Str(const Keyboard::Key&);


public:

	void UpdateEvent(vector<optional<Event>>& eventCollection);

	void collectInputKey();
	void resetConsoleInput();
	string getConsoleInput();

	bool getAnyKeyPress();
	bool getKeyPress(Keyboard::Key);

	bool OnClick();
};

