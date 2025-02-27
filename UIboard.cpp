#include "UIboard.h"
void UIboard::draw(RenderWindow&window){

	for (auto& square : squares) {
		window.draw(square);

	}
}

UIboard::UIboard(int boardSize, int tileSize, Vector2f offset)
{
	m_boardSize = boardSize;
	m_tileSize = tileSize;
	m_offset = offset;

}

void UIboard::Initialize()
{
	for (int row = 0; row < m_boardSize; row++) {
		for (int col = 0; col < m_boardSize; col++) {
			Vector2f absolutePosition = { (float)col * m_tileSize,(float)row * m_tileSize };
			Vector2f position = absolutePosition + m_offset;
			RectangleShape s(Vector2f(m_tileSize, m_tileSize));
			s.setPosition(position);

			if ((row + col) % 2 == 0) {
				s.setFillColor(Color(255, 206, 158));
			}
			squares.push_back(s);
		}
	}
}
