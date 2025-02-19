#include "Piece.h"

Piece::Piece(Vector2i pos, char _char,PieceColor color)
{
	m_position = pos;
	m_char = toupper(_char);
	m_color = color;

	

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

vector<Vector2i> Piece::getPossibleMoveArray()
{
	return m_possibleMove;
}

void Piece::setPossibleMoveArray(vector<Vector2i> v)
{
	m_possibleMove = v;
}

PieceType Piece::getType()
{
	return m_type;
}

PieceColor Piece::getColor()
{
	return m_color;
}

Vector2i Piece::getPosition()
{
	return m_position;
}

void Piece::setPosition(Vector2i pos)
{
	m_position = pos;
}

char Piece::getChar()
{
	return m_char;
}

bool Piece::getIsFirsrMove()
{
	return m_isFirstMove;
}

void Piece::setIsFirsrMove(bool value)
{
	m_isFirstMove = value;
}

bool Piece::getHasMove()
{
	return m_hasMoved;
}

void Piece::setHasMove(bool value)
{
	m_hasMoved = value;
}

void Piece::printStatus()
{
	string color = m_color == PieceColor::white ? "White" : m_color == PieceColor::black ? "Black" : "Defult";
	cout << "\nPiece::printStatus \n";
	cout << "Piece : " << m_char << " Color :" << color << " (" << m_position.x << "," << m_position.y << ")\n";

}



