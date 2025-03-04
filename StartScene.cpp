#include "StartScene.h"

Texture& StartScene::setTexture(string Texturename)
{
	string path = "assets/" + Texturename + ".png";
	return TextureHolder::getTexture(path);
}

StartScene::StartScene(Input& input, bool& isPlayingRef, GameType& gameType)
	: m_input(input),
	m_isPlayingRef(isPlayingRef),
	m_gameType(gameType)
{
	Initilize();
}

void StartScene::Initilize()
{
	m_bgSprite.setPosition(m_position);
	m_normalModeButton.setPosition(m_position + m_button1Offset);
	m_specialModeButton.setPosition(m_position + m_button2Offset);
}

int StartScene::getButtonClick()
{
	Vector2f mousePos = Vector2f(m_input.getMousePos().x, m_input.getMousePos().y);

	if (m_normalModeButton.getGlobalBounds().contains(mousePos))
	{
		return 1;
	}
	if (m_specialModeButton.getGlobalBounds().contains(mousePos))
	{
		return 2;
	}

	return -1;
}

void StartScene::setEnable(bool value)
{
	m_enable = value;
}

bool StartScene::isEnable()
{
	return m_enable;
}

void StartScene::draw(RenderWindow& window)
{
	if (!m_enable)
		return;

	window.draw(m_bgSprite);
	window.draw(m_normalModeButton);
	window.draw(m_specialModeButton);
}
