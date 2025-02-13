#pragma once
#include<iostream>
#include<fstream>
#include <vector>
#include <map>

#include "Piece.h"
#include "Vector2Utils.h"

#include "Debug.h"


using namespace std;

class Board
{
private:
	map<Vector2i, shared_ptr<Piece>> m_board;

	int m_width = 8;
	int m_height = 8;

public:
	Board();

	map<Vector2i, shared_ptr<Piece>>& getBoard();
	vector<shared_ptr<Piece>&> getBoardAsVector();


	shared_ptr<Piece>& getSquareData(Vector2i pos);
	bool isEmpty(Vector2i pos);

	bool movePiece(Vector2i init, Vector2i end);
	
	void initializeBoardByIO();
	void drawIO();	

};

