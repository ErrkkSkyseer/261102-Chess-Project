#include "UIboard.h"
void UIboard::draw(RenderWindow&window){

	for (auto& square : squares) {
		window.draw(square);

	}
}
UIboard::UIboard() {
	for (int row = 0; row < BOARD_SIZE; row++) {
		for (int col = 0; col < BOARD_SIZE; col++) {
			Vector2f Position = {(float)col * TILE_SIZE,(float)row * TILE_SIZE};
			RectangleShape s(Vector2f(TILE_SIZE,TILE_SIZE));
			s.setPosition(Position);

			if ((row + col) % 2 == 0) {
				s.setFillColor(Color(255, 206, 158));
			}
			squares.push_back(s);
		}
	}
}