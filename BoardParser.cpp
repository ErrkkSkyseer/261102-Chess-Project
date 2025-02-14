#include "BoardParser.h"
#include <sstream>

PieceColor BoardParser::ParseColor(char c)
{
	if (c == 'w' || c == 'W') {
		return PieceColor::white;
	}
	else if (c == 'b' || c == 'B') {
		return PieceColor::black;
	}
	else {
		return PieceColor::defult;
	}
}

PieceType BoardParser::ParseType(char c)
{
	switch (toupper(c)) {
	case 'P': return PieceType::pawn;
	case 'R': return PieceType::rook;
	case 'N': return PieceType::knight;
	case 'B': return PieceType::bishop;
	case 'Q': return PieceType::queen;
	case 'K': return PieceType::king;
	default: return PieceType::defult;
	}
}

bool BoardParser::ParseMoved(char c)
{
	return isupper(c);
}

BoardParser::BoardParser(Board& board) : m_board(board)
{
	LoadColorMap("color.txt");
}

void BoardParser::LoadColorMap(const std::string& path)
{
	std::ifstream file(path);
	std::string line;
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string pieceChar, colorStr;
		char delimiter;

		std::getline(ss, pieceChar, ',');
		std::getline(ss, colorStr);

		PieceType type = ParseType(pieceChar[0]);
		PieceColor color = ParseColorFromString(colorStr);
		colorMap[type] = color;
	}
}

PieceColor BoardParser::ParseColorFromString(const std::string& colorStr) {
	if (colorStr == "White") {
		return PieceColor::white;
	}
	else if (colorStr == "Black") {
		return PieceColor::black;
	}
	else {
		return PieceColor::defult;
	}
}

void BoardParser::ParseFile(map<Vector2i, shared_ptr<Piece>>& board,string path)
{

	cout << "parsing\n";
	ifstream f(path);
	string l = "";

	int width, height;
	Vector2i pos;

	getline(f, l);
	width = stoi(l);
	getline(f, l);
	height = stoi(l);
	
	for (int y = height; y > 0; y--)
	{
		getline(f, l);
		cout << l << endl;
		for (int x = 1; x < width+1; x++)
		{
			pos = Vector2i(x, y);
			char c = toupper(l.at(x - 1));
			if (c == '.') continue;

			PieceType type = ParseType(c);
			bool moved = ParseMoved(c);
			PieceColor color = colorMap.count(type) ? colorMap[type] : PieceColor::defult;

			board[pos] = make_shared<Piece>(pos, c, ParseColor(c));

		}
	}
	cout << "parse Completed!\n";
}

