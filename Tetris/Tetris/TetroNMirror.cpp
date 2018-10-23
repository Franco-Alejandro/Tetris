#include "stdafx.h"
#include "TetroNMirror.h"


TetroNMirror::TetroNMirror()
{
}


TetroNMirror::~TetroNMirror()
{
}

const unsigned short int TetroNMirror::getPiece(const int pX, const int pY) const
{
	return (piece[static_cast<int>(actualRotation)][pX][pY]);
}

void TetroNMirror::rotateRight()
{
	actualRotation = static_cast<rotation>((static_cast<int>(actualRotation) + 1) % 2);
}

void TetroNMirror::rotateLeft()
{
	if (actualRotation == rotation::Nver)
		actualRotation = static_cast<rotation>(1);
	else
		actualRotation = static_cast<rotation>(static_cast<int>(actualRotation) - 1);
	
}
