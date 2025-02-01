#pragma once
#include <fstream>
#include <iostream>
#include <SFML/System.hpp>
#include <map>
#include <string>

#include "Piece.h"
#include "Vector2Utils.h"

using namespace std;
using namespace sf;

class BoardParser
{
public:
	void ParseFile(map<Vector2i,shared_ptr<Piece>>&,string path = "Board/defult.txt");
};

