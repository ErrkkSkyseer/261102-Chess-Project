#include "GameManager.h"

GameManager::GameManager()
{
	m_parser.ParseFile(m_board.getBoard());

}

void GameManager::input(vector<optional<Event>>& eventCollections)
{
	m_input.UpdateEvent(eventCollections);
#ifdef DEBUG
	m_input.collectInputKey();
#endif // DEBUG

}

void GameManager::update(double dt)
{
	//ParseInputIOTesting();
	if (!m_isPlaying)
	{
		if (m_input.getKeyPress(Keyboard::Key::Enter))
		{
			startGame();
		}
		return;
	}

	Vector2i pos;
	switch (m_inputState)
	{
	case 1:
		if (onSquareInput(pos))
		{
			if (m_board.isEmpty(pos))
			{
				cout << "Empty Square\n";
				return;
			}

			auto& piece = m_board.getSquareData(pos);
			if (m_rule.calculatePossibleMove(piece))
			{
				switchState(2);
				m_selectPos = pos;
			}
			else
			{
				cout << "No move\n";
			}
		}
		break;
	case 2:
		if (onSquareInput(pos))
		{
			auto& piece = m_board.getSquareData(m_selectPos);
			if (m_rule.isValidMove(piece, pos))
			{
				//TODO : Rule should handle moving piece not board
				m_board.movePiece(m_selectPos, pos);
				switchState(1);

			}
			else
			{
				cout << "Illegel move\n";
				switchState(1);
			}
		}
		break;
	}
	

	//stateMachine(m_gameState);

}

void GameManager::enterState(int state)
{
	string debugmsg = "Enter Input State :: ";
	switch (state)
	{
	case 1:
		m_inputState = 1;
		m_board.drawIO();
		debugmsg += "Selecting Piece";
		break;
	case 2:
		m_inputState = 2;
		debugmsg += "Moving Piece";
		break;
	default:
		debugmsg += "State not exist : m_inputState = " + m_inputState;
		break;
	}
#ifdef DEBUG
	cout << debugmsg << endl;
#endif // DEBUG

}

void GameManager::exitState(int state)
{
	string debugmsg = "Exit Input State :: ";
	switch (state)
	{
	case 1:
		m_inputState = 1;
		debugmsg += "Selecting Piece";
		break;
	case 2:
		m_inputState = 2;
		debugmsg += "Moving Piece";
		break;
	default:
		debugmsg += "State not exist : m_inputState = " + m_inputState;
		break;
	}
#ifdef DEBUG
	cout << debugmsg << endl;
#endif // DEBUG
}

void GameManager::switchState(int to)
{
	exitState(m_inputState);
	enterState(to);
}

void GameManager::draw(RenderWindow& window)
{

}

bool GameManager::onSquareInput(Vector2i& out)
{
	//IO Version
#ifdef DEBUG
	
	if (m_input.getKeyPress(Keyboard::Key::Enter))
	{
		if (tryParse2Vector2i(m_input.getConsoleInput(), out))
		{
			return true;
		}
		else
		{
			cout << "Bad vector\n";
		}
	}
	return false;
#endif // DEBUG

	// Game Version
#ifndef DEBUG
	return true;
#endif // !DEBUG

}

void GameManager::nextTurn()
{

	if (m_turn == PieceColor::white)
		m_turn = PieceColor::black;
	else if (m_turn == PieceColor::black)
		m_turn = PieceColor::white;
	else
		m_turn = PieceColor::white;

	m_move++;

	m_rule.calculateBoardState();

#ifdef DEBUG
	cout << (m_turn == PieceColor::white ? "White" : "Black") << " Turn\n";
	cout << "Move #" << m_move << "\n----------\n";
#endif // DEBUG
}

void GameManager::startGame()
{
#ifdef DEBUG
	cout << "GameStart!\n\n";
#endif // DEBUG

	m_isPlaying = true;
	
	m_turn = PieceColor::black;
	m_move = 0;

	nextTurn();

	switchState(1);

}

void GameManager::gameOver()
{
	m_isPlaying = false;
}

#ifdef DEBUG



/// <summary>
/// VERY DANGEROUS FUNCTION. CAN CRASH THE GAME!!!
/// dev skill issue.
/// </summary>
bool GameManager::tryParse2Vector2i(string s, Vector2i& out)
{
	pair<string, string> sp = splitString(s, ' ');
	string sx = sp.first;
	string sy = sp.second;

	if (sx != " " && sy != " ")
	{
		out.x = stoi(sx);
		out.y = stoi(sy);
		return true;
	}
	else
	{
		return false;
	}
}

/// <summary>
/// VERY DANGEROUS FUNCTION. CAN CRASH THE GAME!!!
/// dev skill issue.
/// </summary>
/// <param name="s"></param>
/// <param name="c"></param>
/// <returns></returns>
pair<string, string> GameManager::splitString(string s, char c)
{
	size_t pos = s.find_first_of(c);

	if (pos != string::npos)
	{
		string ls = s.substr(0, pos);
		string rs = s.substr(pos, s.size() - pos);
		return make_pair(ls, rs);
	}
	return make_pair(" ", " ");
}


//Unuse function, for testing purpose

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
	if (m_board.getSquareData(init) == nullptr)
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

#endif // DEBUG


