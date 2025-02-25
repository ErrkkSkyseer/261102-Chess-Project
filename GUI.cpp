#include "GUI.h"

GUI::GUI(Board& board, Rule& rule)
	:m_board(board),m_rule(rule)
{
	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			Vector2i position(x+1, y+1);
			UIpiece sprite = UIpiece(
								Vector2f(TILE_SIZE, TILE_SIZE),
								Vector2f(x * TILE_SIZE,y * TILE_SIZE));
			m_UIpieces.insert(make_pair(position, sprite));

			//Make all pieces show
			auto& p = m_UIpieces[position];
			p.setactive(true);
		}
	}
}

void GUI::draw(RenderWindow& window)
{
	m_UIboard.draw(window);

	for (auto& pair : m_UIpieces)
	{
		pair.second.draw(window);
	}
}

void GUI::onBoardUpdate()
{
	//Logic when the board is updated (will be call when turn change)
}