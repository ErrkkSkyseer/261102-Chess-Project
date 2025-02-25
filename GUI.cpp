#include "GUI.h"

void GUI::draw(RenderWindow& window)
{
	m_UIboard.draw(window);
}

GUI::GUI()
{
	for (int x = 1; x < 9; x++) {
		for (int y = 1; y < 9; y++) {
			Vector2i position(x, y);
			UIpiece positionsprite = UIpiece(Vector2f(80,80),Vector2f((x-1)*80,(y - 1) * 80));
			m_UIpieces[position] = positionsprite;
			

			
		}
	}
}
