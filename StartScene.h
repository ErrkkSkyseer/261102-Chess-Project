#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Input.h"
#include "TextureHolder.h"
#include "BaseGameEnum.h"


using namespace std;
using namespace sf;

class StartScene
{
private:
	bool& m_isPlayingRef;
	GameType& m_gameType;

	Input& m_input;

	bool m_enable = true;

	Vector2f m_position = {250,350};
	Vector2f m_button1Offset = {20,175};
	Vector2f m_button2Offset = {270,175};

	Sprite m_bgSprite = Sprite(setTexture("Select Mode"));
	Sprite m_normalModeButton = Sprite(setTexture("Original"));
	Sprite m_specialModeButton = Sprite(setTexture("Special"));
	
	Texture& setTexture(string path);

	void Initilize();
public:
	StartScene(Input& input,bool& isPlayingRef, GameType& gameType);

	int getButtonClick();
	void setEnable(bool value);
	bool isEnable();
	void draw(RenderWindow& window);
};

