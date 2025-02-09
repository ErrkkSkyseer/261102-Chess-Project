#include "GameManager.h"

GameManager::GameManager()
{
	m_parser.ParseFile(m_board.getBoard());
	m_board.drawIO();
	enterState(GameState::Select);

	
}

void GameManager::input(vector<optional<Event>>& eventCollections)
{
	m_input.UpdateEvent(eventCollections);
	m_input.collectInputKey();

	if (m_input.getKeyPress(Keyboard::Key::Enter))
		m_input.resetConsoleInput();
}

void GameManager::update(double dt)
{
	//ParseInputIOTesting();
	
	stateMachine(m_gameState);

}

void GameManager::draw(RenderWindow& window)
{

}

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

//void GameManager::ParseInputIOTesting()
//{
//	//State : Update The Board - Check for stuffs
//
//	int x, y;
//	Vector2i init, end;
//
//	//State : Input - Selecting a Square
//	cout << "Enter square to select";
//
//	cin >> x >> y;
//	init = Vector2i(x, y);
//
//	//State : Update - Check valid input
//	if (m_board.getSquareData(init) == nullptr)
//	{
//		cout << "Invalid Square" << endl;
//		return;
//	}
//	//State : Update - Calculate all possible move for the piece
//
//	//State : Draw all possible move
//
//	//State : Input - Moving a picec
//	cout << "Enter target square";
//
//	//State : Update - Check valid input
//
//	//State : Update - Move piece
//	cin >> x >> y;
//	end = Vector2i(x, y);
//	m_board.movePiece(init, end);
//	//State : Draw new board
//}



