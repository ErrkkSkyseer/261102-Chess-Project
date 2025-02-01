#include "BoardParser.h"

void BoardParser::ParseFile(map<Vector2i, shared_ptr<Piece>>& board,string path)
{
	cout << "parsing";
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
			board[pos] = make_shared<Piece>(pos, c);
		}
	}

	cout << "parse Completed!\n";
}