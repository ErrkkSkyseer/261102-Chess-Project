#include "GameManager.h"

GameManager::GameManager()
{
	m_parser.ParseFile(m_board.getBoardRef());
	m_board.drawIO();
}

void GameManager::input()
{
}


void GameManager::update()
{
	//ParseInputIOTesting();
}

void GameManager::draw()
{
	m_board.drawIO();
}

void GameManager::ParseInputIOTesting()
{
	//State : Update The Board - Check for stuffs

	int x, y;
	Vector2i init, end;

	//State : Input - Selecting a Square
	cout << "Enter square to select";

	cin >> x >> y;
	init = Vector2i(x, y);

	//State : Update - Check valid input
	if (m_board.getSquareDataRef(init) == nullptr)
	{
		cout << "Invalid Square" << endl;
		return;
	}
	//State : Update - Calculate all possible move for the piece

	//State : Draw all possible move

	//State : Input - Moving a picec
	cout << "Enter target square";

	//State : Update - Check valid input

	//State : Update - Move piece
	cin >> x >> y;
	end = Vector2i(x, y);
	m_board.movePiece(init, end);
	//State : Draw new board
}