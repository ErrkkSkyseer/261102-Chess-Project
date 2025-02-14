#include "Board.h"

Board::Board()
{

}

shared_ptr<Piece>& Board::getSquareData(Vector2i pos)
{
#ifdef DEBUG
	cout << "\nBoard::getSquareData()\n";
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
	cout << "\nBoard::isEmpty()\n";
	cout << "Checking pos : " << "(" << pos.x << "," << pos.y << ") = ";
	cout << ((m_board[pos] == nullptr) ? "Empty" : "Have Piece " )<< "\n";
#endif // DEBUG

	return m_board[pos] == nullptr;
}

map<Vector2i, shared_ptr<Piece>>& Board::getBoard()
{
	return m_board;
}

Board Board::getGhostBoard()
{
	Board ghostBoard;
	auto& ghostm_Board = ghostBoard.getBoard();

	for (auto& kvp : m_board)
	{
		if (!kvp.second)
			continue;

		ghostm_Board[kvp.first] = make_shared<Piece>(*kvp.second);
	}

	return move(ghostBoard);
}

vector<shared_ptr<Piece>>& Board::getPieces()
{
	m_pieces.clear();
	for (auto& kvp : m_board)
	{
		if (!kvp.second) 
			continue;
		
		m_pieces.push_back(kvp.second);
	}


	return m_pieces;
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


