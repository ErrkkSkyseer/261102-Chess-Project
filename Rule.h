#pragma once
#include <SFML/System.hpp>
#include <iostream>
#include <memory>
#include <set>

#include "Board.h"
#include "BaseGameEnum.h"

#include "Debug.h"

#ifdef DEBUGIORule
#define DEBUGIORule

#endif // DEBUGIORule


using namespace sf;
using namespace std;
class Rule
{
private:

	Board& m_board;
	PieceColor& m_turn;
	GameType& m_gametype;

	Vector2i m_selectingPos;
	
	bool m_haveSpecialMove = false;

	bool m_isInCheck = false;
	EndType m_endType = EndType::null;

	vector<string> m_encodedBoardHistory;
	int m_fiftyMoveCounter = 0;
	int m_lastPieceCount;
	int whitecheckcount = 0;
	int blackcheckcount = 0;

	bool W_kinginmiddle = false;
	bool B_kimginmiddle = false;

	vector<shared_ptr<Piece>> m_deadPiece;

	bool m_isPromotion = false;

	bool calculatePossibleMove(shared_ptr<Piece>& piece,bool);

#pragma region PieceMovement
	vector<Vector2i> pawnMove(shared_ptr<Piece>& piece	,Board& board);
	vector<Vector2i> pawnAtt(shared_ptr<Piece>& piece	,Board& board);
	vector<Vector2i> enPassant(shared_ptr<Piece>& piece, Board& board);
	bool checkForPromotion(shared_ptr<Piece>& piece, vector<Vector2i> moveArray);
	
	vector<Vector2i> KnightMove(shared_ptr<Piece>& piece,Board& board);
	vector<Vector2i> BishopMove(shared_ptr<Piece>& piece,Board& board);
	vector<Vector2i> RookMove(shared_ptr<Piece>& piece	,Board& board);
	vector<Vector2i> QueenMove(shared_ptr<Piece>& piece	,Board& board);
	vector<Vector2i> KingMove(shared_ptr<Piece>& piece	,Board& board);
	vector<Vector2i> castel(shared_ptr<Piece>& piece, Board& board);
	
	vector<Vector2i> calculateSpecialMove(shared_ptr<Piece>& piece, Board& board,bool);
#pragma endregion

	vector<Vector2i> validateAttackMove(vector<Vector2i> moveArray, shared_ptr<Piece>& piece, Board& board);

	vector<Vector2i> getPieceMoveset(shared_ptr<Piece>& piece, Board& board, bool onlyGetAttackMove = false);

	bool isValidMove(shared_ptr<Piece>& piece, Vector2i end);
	vector<Vector2i> getControllingPos(PieceColor color, Board& board);
	Vector2i findKingPos(PieceColor color, Board& board);
	
	bool isCheck(PieceColor color, Board& board);
	bool isCheckmate(PieceColor color);
	bool isStalemate(PieceColor color);

	vector<Vector2i> getPinnedMove(shared_ptr<Piece>& piece, const vector<Vector2i> moveArray, Board& board);

	void preformSpecialMove(shared_ptr<Piece>& piece,Vector2i pos);

	bool checkInsufficientMeterial();
	bool checkRepeatation(Board& board);
	string encodeBoard(Board& board);

	void countFiftyMove(PieceType type);

	void printMovesVector(vector<Vector2i>);

#pragma region Auxiliary Functions

	void joinMoveArray(vector<Vector2i>& base, const vector<Vector2i>& add);
	void subtractMoveArray(vector<Vector2i>& base, const vector<Vector2i>& remove);
	void removeDuplicates(vector<Vector2i>& v);
	PieceColor flipColor(PieceColor color);
	void sortMoveArray(vector<Vector2i>& vec);
	int countPositionOccurrences(const vector<string>& vec, string element);
	void BurnSquare_Special();
	bool CheckKingThreeTime_Special();
	bool KingInMiddle_Special();

#pragma endregion
public:
	Rule(Board& board, PieceColor& color,GameType& gametype);

	void eventActivate();

	void reset();

	bool trySelect(Vector2i pos);
	bool tryMove(Vector2i pos);

	void calculateBoardState();

	bool getCheck();
	bool getCheckmate();
	bool getDraw();

	bool isKingAlive(PieceColor& color, Board& board);
	bool isPromotion();
	void promote(Vector2i pos, char c);
	
	EndType getEndType();
	
};

