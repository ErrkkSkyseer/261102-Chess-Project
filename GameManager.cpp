#include "GameManager.h"

GameManager::GameManager()
{
	m_parser.ParseFile(m_board.getBoard());
	m_board.drawIO();
	enterState(GameState::InputSelect);
}

void GameManager::input(vector<optional<Event>>& eventCollections)
{
	m_input.UpdateEvent(eventCollections);
}


void GameManager::update(double dt)
{
	//ParseInputIOTesting();
	
	stateMachine(m_gameState);

}

void GameManager::draw(RenderWindow& window)
{

}

void GameManager::stateMachine(GameState state)
{
	switch (state)
	{
	case GameState::Start:
		break;
	case GameState::InputSelect:
		m_input.parseInputKey(m_consoleInput);

		if (m_input.getKeyPress(Keyboard::Key::Enter))
		{
			if (tryParse2Vector2i(m_consoleInput, m_selectingVector))
			{
				cout << "\n\nSelecting Vector = " << m_selectingVector.x << ":" << m_selectingVector.y << "\n";
				//Check if selectiing square contain a piece and if it can move
				if (!m_board.isEmpty(m_selectingVector)
					&& m_rule.canMove(m_board.getSquareData(m_selectingVector)))
				{
					// Forward to Selecting Input State
					m_rule.calculatePossibleMove(m_board.getSquareData(m_selectingVector));
					exitState(GameState::InputSelect);
					enterState(GameState::InputTarget);
					return;
				}
				else
				{
					// Enter this state again
					cout << "Empty Square\n";
					exitState(GameState::InputSelect);
					enterState(GameState::InputSelect);
					return;
				}
			}
			else
			{
				// Enter this state again
				cout << "Invalid vector\n";
				exitState(GameState::InputSelect);
				enterState(GameState::InputSelect);
					return;
			}
		}
		break;
	case GameState::InputTarget:
		m_input.parseInputKey(m_consoleInput);
		if (m_input.getKeyPress(Keyboard::Key::Enter))
		{
			if (tryParse2Vector2i(m_consoleInput, m_targetVector))
			{
				cout << "\n\nTarget Vector = " << m_selectingVector.x << ":" << m_selectingVector.y << "\n";
				if (m_rule.isValidMove(m_board.getSquareData(m_selectingVector), m_targetVector))
				{
					//Move piece and calculate board state
					m_board.movePiece(m_selectingVector, m_targetVector);
					m_rule.calculateBoardState();
					exitState(GameState::InputTarget);
					enterState(GameState::InputSelect);
					return;
				}
				else
				{
					cout << "Invalid vector\n";
					exitState(GameState::InputTarget);
					enterState(GameState::InputSelect);
					return;
				}
			}
			else
			{
				// Enter this state again
				cout << "Invalid vector\n";
				exitState(GameState::InputTarget);
				enterState(GameState::InputTarget);
				return;
			}
		}
		break;
	case GameState::End:
		break;
	}

}


void GameManager::enterState(GameState state)
{
	switch (state)
	{
	case GameState::Start:
		m_gameState = GameState::Start;
		break;
	case GameState::InputSelect:
		m_gameState = GameState::InputSelect;
		cout << "Input Select Square :: ";
		m_selectingVector = Vector2i(0, 0);
		break;
	case GameState::InputTarget:
		m_gameState = GameState::InputTarget;
		cout << "Input Target Square :: ";
		m_targetVector = Vector2i(0, 0);
		break;
	case GameState::End:
		m_gameState = GameState::End;
		break;
	}
}

void GameManager::exitState(GameState state)
{
	switch (state)
	{
	case GameState::Start:
		break;
	case GameState::InputSelect:
		
		m_consoleInput = "";
		break;
	case GameState::InputTarget:
		m_consoleInput = "";
		m_board.drawIO();
		break;
	case GameState::End:
		break;
	}
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



