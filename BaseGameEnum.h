#pragma once

enum class PieceColor
{
	defult,dark,light
};

enum class PieceType
{
	defult,pawn,knight,bishop,rook,queen,king
};

enum class GameType
{
	normal, notNormal
};

enum class GameState
{
	calculating,wait2select,wait2move
};