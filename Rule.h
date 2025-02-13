#pragma once
#include <SFML/System.hpp>
#include <iostream>
#include <memory>
#include <set>

#include "Board.h"
#include "BaseGameEnum.h"

#include "Debug.h"

using namespace sf;
using namespace std;
class Rule
{
private:
	Board& m_board;
	PieceColor& m_turn;

	// what piece move last tern
	// -
	// 2 piece movement

	vector<Vector2i> m_controllingSquareWhite;
	vector<Vector2i> m_controllingSquareBlack;
	vector<Vector2i> getcontrollSquare(PieceColor color);

	int fiftyrule = 0;

  	bool isCheck = false;
	bool isGameOver = false;

	EndBy endtype = EndBy::null;

	Vector2i m_selectingPos;
	Vector2i m_lastPieceMove;

	void FiftyRule();
	bool Check(PieceColor color);
	Vector2i getKingPos(PieceColor color);
	vector<Vector2i> Pin(shared_ptr<Piece>& piece , vector<Vector2i>&);
	void joinMoveVector(vector<Vector2i>& u, vector<Vector2i> v);

#pragma region PieceMovement
	vector<Vector2i> pawnMove(shared_ptr<Piece>& piece);
	vector<Vector2i> pawnAtt(shared_ptr<Piece>& piece);
	vector<Vector2i> KnightMove(shared_ptr<Piece>& piece);
	vector<Vector2i> BishopMove(shared_ptr<Piece>& piece);
	vector<Vector2i> RookMove(shared_ptr<Piece>& piece);
	vector<Vector2i> QueenMove(shared_ptr<Piece>& piece);
	vector<Vector2i> KingMove(shared_ptr<Piece>& piece);
#pragma endregion

	vector<Vector2i> getPieceMove(shared_ptr<Piece>& piece,bool getOnlyAttackMove = false);

	bool isValidMove(Vector2i init, Vector2i end);
	bool calculatePossibleMove(Vector2i pos);

#ifdef DEBUG

	void printMovesVector(vector<Vector2i>);

#endif // DEBUG
public:
	Rule(Board& board,PieceColor& color);

	
	bool tryMoveSelectedPiece(Vector2i pos);
	bool trySelectPiece(Vector2i pos);
	bool isGameEnded();
	EndBy getEndResult();

	void calculateBoardState();
	
};

