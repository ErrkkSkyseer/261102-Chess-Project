#include "Board.h"

Board::Board()
{

}

shared_ptr<Piece>& Board::getSquareData(Vector2i pos)
{
#ifdef DEBUG
	
	cout << "Get Data At (" << pos.x << "," << pos.y <<")";
	if (m_board[pos] != nullptr)
		m_board[pos]->printStatus();
	else
		cout << "\n is empty square\n";

#endif // DEBUG

	return m_board[pos];
}

bool Board::isEmpty(Vector2i pos)
{
#ifdef DEBUG
	cout << "Checking pos : " << "(" << pos.x << "," << pos.y << ") = ";
	cout << ((m_board[pos] == nullptr) ? "Empty" : "Have Piece " )<< "\n";
#endif // DEBUG

	return m_board[pos] == nullptr;
}

map<Vector2i, shared_ptr<Piece>>& Board::getBoard()
{
	return m_board;
}


bool Board::movePiece(Vector2i init, Vector2i end)
{
	m_board[end] = m_board[init];
	m_board.erase(init);

	m_board[end]->setPosition(end);
	m_board[end]->printStatus();

	return true;
}

/// <summary>
/// Initialize The Board Manually
/// </summary>
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

vector<shared_ptr<Piece>&> Board::getBoardAsVector()
{
	vector<shared_ptr<Piece>&> pieces;

	Vector2i pos;
	for (int y = m_height; y > 0; y--)
	{
		for (int x = m_width; x > 0; x--)
		{
			pos = Vector2i(x, y);
			if (!isEmpty(pos))
			{
				pieces.push_back(m_board[pos]);
			}
		}
	}
	return pieces;
}

