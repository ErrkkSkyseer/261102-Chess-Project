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
	
}

void BoardParser::ParseFile(map<Vector2i, shared_ptr<Piece>>& board, string path)
{
    cout << "parsing\n";
    string p = "Board/" + path;
    ifstream f(p);
    string line;

    while (getline(f, line))
    {
        stringstream ss(line);
        string typeStr, colorStr, xStr, yStr;

        getline(ss, typeStr, ',');
        getline(ss, colorStr, ',');
        getline(ss, xStr, ',');
        getline(ss, yStr, ',');

        PieceType type = ParseType(typeStr[0]);
        PieceColor color = ParseColor(colorStr[0]);
        int x = stoi(xStr);
        int y = stoi(yStr);

        Vector2i pos(x, y);

        char pieceChar = toupper(typeStr[0]);
        if (color == PieceColor::black) {
            pieceChar = tolower(typeStr[0]);
        }

        board[pos] = make_shared<Piece>(pos, pieceChar, color);
    }
	cout << "parse Completed!\n";

}