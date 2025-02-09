#include "GameManager.h"

void GameManager::stateMachine(GameState state)
{
	Vector2i pos = Vector2i();
	switch (state)
	{
	case GameState::Start:
		if (m_input.getKeyPress(Keyboard::Key::Enter))
		{
			startGame();
		}
		break;
	case GameState::Select:
		// when get input
		if (onSquareInput(pos)) // verdify input
		{
			// empty square --> return
			if (m_board.isEmpty(pos))
			{
				cout << "Empty Square\n";
				return;
			}

			// get piece position
			auto& piece = m_board.getSquareData(pos);
			if (m_rule.calculatePossibleMove(piece))
			{
				m_selectPos = pos;
				switchState(state, GameState::Target);
			}
			else
			{
				cout << "Unmovable Piece\n";
			}
		}
		break;
	
	case GameState::Target:

		//when got input
		if (onSquareInput(pos))
		{
			//check if that input is a legel moce
			auto& piece = m_board.getSquareData(pos);
			if (m_rule.isValidMove(piece, pos))
			{
				m_board.movePiece(m_selectPos, pos);
				nextTurn();
				switchState(state, GameState::Select);
			}
			else
			{
				cout << "Illegle Move\n";
				switchState(state, GameState::Select);
			}
		}
		break;
	case GameState::End:
		break;
	}

}


void GameManager::enterState(GameState state)
{
	string debugmsg = "Enter State :: ";
	switch (state)
	{
	case GameState::Start:
		debugmsg += "Start";
		m_gameState = GameState::Start;
		break;
	case GameState::Select:
		debugmsg += "Select";
		m_gameState = GameState::Select;
		break;
	case GameState::Target:
		m_gameState = GameState::Target;
		debugmsg += "Target";
		break;
	case GameState::End:
		m_gameState = GameState::End;
		debugmsg += "End";
		break;
	}
#ifdef DEBUG
	cout << debugmsg << endl;
#endif // DEBUG

}

void GameManager::exitState(GameState state)
{
	string debugmsg = "Exit State :: ";
	switch (state)
	{
	case GameState::Start:
		debugmsg += "Start";
		break;
	case GameState::Select:
		debugmsg += "Select";
		break;
	case GameState::Target:
		debugmsg += "Target";
		m_board.drawIO();
		break;
	case GameState::End:
		debugmsg += "End";
		break;
	}
#ifdef DEBUG
	cout << debugmsg << endl;
#endif // DEBUG
}

void GameManager::switchState(GameState from, GameState to)
{
	exitState(from);
	enterState(to);
}


