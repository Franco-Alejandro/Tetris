#pragma once
#include "Tetromino.h"
class Square : public Tetromino

{
public:
	const unsigned short int getPiece(const int pX, const int pY) const;
	void rotateRight();
	void rotateLeft();

	Square();
	~Square();
private:
	char piece[TetroHAndW][TetroHAndW]{                 //It doesn't have rotations
			{ 0, 1, 1, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
			};

};

