#include "Board.h"

Board::Board()
{

}

shared_ptr<Piece>& Board::getSquareDataRef(Vector2i pos)
{
	return m_board[pos];
}

map<Vector2i, shared_ptr<Piece>>& Board::getBoardRef()
{
	return m_board;
}


bool Board::movePiece(Vector2i init, Vector2i end)
{
	m_board[end] = m_board[init];
	m_board.erase(init);

	return true;
}

void Board::initializeBoardByIO()
{
	cout << "Currently using : InitializeBoardByIO\n\n";
	cout << "Board size (w,h) : ";
	cin >> m_width >> m_height;

	Vector2i pos;
	for (int y = m_height; y > 0; y--)
	{
		for (int x = 1; x < m_width+1; x++)
		{
			cout << x << " " << y << " ";
			pos = Vector2i(x, y);
			char input;

			cin >> input;
			if (
				input == 'P'
				|| input == 'N'
				|| input == 'B'
				|| input == 'R'
				|| input == 'Q'
				|| input == 'K'
				)
			{
				m_board[pos] = make_shared<Piece>(pos, input);

			}
			
		}
	}
}

void Board::drawIO()
{
	Vector2i pos;
	for (int y = m_height; y > 0; y--)
	{
		for (int x = 1; x < m_width +1; x++)
		{
			pos = Vector2i(x, y);
			if (m_board[pos] == nullptr)
			{
				cout << ".";
			}
			else
			{
				cout << m_board[pos]->getChar();
			}
			cout << " ";
		}
		cout << "\n";
	}
}
