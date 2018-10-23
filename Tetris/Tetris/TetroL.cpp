#include "stdafx.h"
#include "TetroL.h"


TetroL::TetroL()
{
}


TetroL::~TetroL()
{
}
const unsigned short int TetroL::getPiece(const int pX, const int pY) const
{
	return (piece[static_cast<int>(actualRotation)][pX][pY]);
}
void TetroL::rotateRight() { 

	actualRotation = static_cast<rotation>((static_cast<int>(actualRotation) + 1) % 4);

}

void TetroL::rotateLeft()
{

	actualRotation = static_cast<rotation>(static_cast<int>(actualRotation) - 1);

	if (static_cast<int>(actualRotation) == -1)
		actualRotation = Ldown;
}


