#pragma once

enum class PieceColor
{
	defult,white,black
};

enum class PieceType
{
	defult,pawn,knight,bishop,rook,queen,king
};

enum class GameType
{
	isntInGame, normal, notNormal
};

enum class EndBy
{
	null, checkmate, stalemate, repeatation, fiftyRule, material
};
