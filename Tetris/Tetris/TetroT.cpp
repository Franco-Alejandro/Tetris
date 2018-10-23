#include "stdafx.h"
#include "TetroT.h"


TetroT::TetroT()
{
}


TetroT::~TetroT()
{
}

const unsigned short int TetroT::getPiece(const int pX, const int pY) const
{
	return (piece[static_cast<int>(actualRotation)][pX][pY]);
}

void TetroT::rotateRight()
{
	actualRotation = static_cast<rotation>((static_cast<int>(actualRotation) + 1) % 4);
}

void TetroT::rotateLeft()
{	
		actualRotation = static_cast<rotation>(static_cast<int>(actualRotation) - 1);

		if (static_cast<int>(actualRotation) == -1)
			actualRotation = Tleft;

}
