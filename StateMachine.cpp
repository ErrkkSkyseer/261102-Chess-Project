#include "GameManager.h"

void GameManager::stateMachine(GameState state)
{
	switch (state)
	{
	case GameState::Start:

		break;
	case GameState::Select:

		if (m_input.getKeyPress(Keyboard::Key::Enter))
		{
			Vector2i pos;
			if (tryParse2Vector2i(m_input.getConsoleInput(), pos))
			{
				auto& piece = m_board.getSquareData(pos);
				if (!m_board.isEmpty(pos) && m_rule.calculatePossibleMove(piece))
				{
					m_selectPos = pos;
					switchState(state, GameState::Target);
				}
				else
				{
					cout << "Invalid Square\n";
				}
			}
			else
			{
				cout << "Bad vector\n";
			}
		}
		break;
	case GameState::Target:
		if (m_input.getKeyPress(Keyboard::Key::Enter))
		{
			Vector2i targetPos;
			if (tryParse2Vector2i(m_input.getConsoleInput(), targetPos))
			{
				auto& piece = m_board.getSquareData(targetPos);
				if (m_rule.isValidMove(piece,targetPos))
				{
					m_board.movePiece(m_selectPos, targetPos);
					switchState(state, GameState::Select);
				}
				else
				{
					switchState(state, GameState::Select);	
					cout << "Illegle Move\n";
				}
			}
			else
			{
				cout << "Bad vector\n";
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
	case GameState::Select:
		m_gameState = GameState::Select;
		cout << "Input Select Square :: ";
		break;
	case GameState::Target:
		m_gameState = GameState::Target;
		cout << "Input Target Square :: ";
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
	case GameState::Select:
		break;
	case GameState::Target:
		m_board.drawIO();
		break;
	case GameState::End:
		break;
	}
}

void GameManager::switchState(GameState from, GameState to)
{
	exitState(from);
	enterState(to);
}