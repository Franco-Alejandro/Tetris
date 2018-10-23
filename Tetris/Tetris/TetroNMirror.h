#pragma once
#include "Tetromino.h"
class TetroNMirror : public Tetromino
{
public:
	TetroNMirror();
	~TetroNMirror();
	const unsigned short int getPiece(const int pX, const int pY) const;
	void rotateRight();
	void rotateLeft();
private:
	enum rotation { Nver, Nhor };
	rotation actualRotation = Nver;
	char piece[2][TetroHAndW][TetroHAndW]{
		{			
			{ 0, 1, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 }
		},
	};

};

