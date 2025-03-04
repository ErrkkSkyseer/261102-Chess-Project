#include "GUI.h"

string GUI::piecetoTexture(Piece& piece)
{
	if (piece.getType()== PieceType::pawn && piece.getColor() == PieceColor::white)
	{
		return"Whitepawn";
	}
	if (piece.getType() == PieceType::pawn && piece.getColor() == PieceColor::black)
	{
		return"Blackpawn";
	}
	if (piece.getType() == PieceType::rook && piece.getColor() == PieceColor::white)
	{
		return"Whiterook";
	}
	if (piece.getType() == PieceType::rook && piece.getColor() == PieceColor::black)
	{
		return"Blackrook";
	}
	if (piece.getType() == PieceType::bishop && piece.getColor() == PieceColor::white)
	{
		return"WhiteBishop";
	}
	if (piece.getType() == PieceType::bishop && piece.getColor() == PieceColor::black)
	{
		return"BlackBishop";
	}
	if (piece.getType() == PieceType::knight && piece.getColor() == PieceColor::white)
	{
		return"WhiteKnight";
	}
	if (piece.getType() == PieceType::knight && piece.getColor() == PieceColor::black)
	{
		return"BlackKnight";
	}
	if (piece.getType() == PieceType::queen && piece.getColor() == PieceColor::white)
	{
		return"WhiteQueen";
	}
	if (piece.getType() == PieceType::queen && piece.getColor() == PieceColor::black)
	{
		return"BlackQueen";
	}
	if (piece.getType() == PieceType::king && piece.getColor() == PieceColor::white)
	{
		return"WhiteKing";
	}
	if (piece.getType() == PieceType::king && piece.getColor() == PieceColor::black)
	{
		return"BlackKing";
	}
}

GUI::GUI(Board& board, Rule& rule, Input& input, bool& isPlaying, GameType& gameType)
	:m_board(board),
	m_rule(rule),
	m_input(input),
	m_isPLayingRef(isPlaying),
	m_gameType(gameType)
{
	//Spawn Board
	m_UIboard.Initialize();

	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			Vector2i position(x + 1, y + 1);
			UIpiece sprite = UIpiece(
				Vector2f(TILE_SIZE, TILE_SIZE),
				Vector2f(BOARD_OFFSET_X+(x * TILE_SIZE), (BOARD_OFFSET_Y+(BOARD_SIZE - 1) * TILE_SIZE) - (y * TILE_SIZE)));
			m_UIpieces.insert(make_pair(position, sprite));

			//Make all pieces show debug
			/*auto& p = m_UIpieces[position];
			p.setactive(true);*/
		}
	}
}



Vector2i GUI::ScreenToBoard(Vector2i screenCoords)
{
	Vector2i offset(BOARD_OFFSET_X,BOARD_OFFSET_Y);
	Vector2i deOffset = screenCoords - offset;
	Vector2i boardCoord = Vector2i(ceilf(deOffset.x / TILE_SIZE) + 1, BOARD_SIZE - ceilf(deOffset.y / TILE_SIZE));
	return boardCoord;
}

void GUI::draw(RenderWindow& window)
{

	m_UIboard.draw(window);

	for (auto& pair : m_UIpieces)
	{
		pair.second.draw(window);
	}

	if (!m_isPLayingRef)
		m_startScene.draw(window);
}

StartScene& GUI::getStartScene()
{
	return m_startScene;
}

void GUI::onBoardUpdate()
{
	auto& boardMap = m_board.getBoard();

	for (auto& uiEntry : m_UIpieces) {
		Vector2i pos = uiEntry.first;
		UIpiece& uipiece = uiEntry.second;

		auto boardIt = boardMap.find(pos);
		if (boardIt != boardMap.end() && boardIt->second != nullptr){
			char pieceChar = boardIt->second->getChar();

			uipiece.setTexture(piecetoTexture(*(boardIt->second)));
			uipiece.setactive(true);
		}
		else {
			uipiece.setactive(false);
		}
	}
}