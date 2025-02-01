#include "Piece.h"

Piece::Piece(Vector2i pos, char _char)
{
	m_position = pos;
	m_char = _char;

	switch (m_char)
	{
	case 'P':
		m_type = PieceType::pawn;
		break;
	case 'N':
		m_type = PieceType::knight;
		break;
	case 'B':
		m_type = PieceType::bishop;
		break;
	case 'R':
		m_type = PieceType::rook;
		break;
	case 'Q':
		m_type = PieceType::queen;
		break;
	case 'K':
		m_type = PieceType::king;
		break;
	default:
		m_type = PieceType::defult;
		break;
	}
}

Vector2i Piece::getPosition()
{
	return m_position;
}

char Piece::getChar()
{
	return m_char;
}

void Piece::move(Vector2i pos)
{

}


