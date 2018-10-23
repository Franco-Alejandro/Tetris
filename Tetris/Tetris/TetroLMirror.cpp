#include "stdafx.h"
#include "TetroLMirror.h"


TetroLMirror::TetroLMirror()
{
}


TetroLMirror::~TetroLMirror()
{
}

const unsigned short int TetroLMirror::getPiece(const int pX, const int pY) const
{
	return (piece[static_cast<int>(actualRotation)][pX][pY]);
}
void TetroLMirror::rotateRight() {

	actualRotation = static_cast<rotation>((static_cast<int>(actualRotation) + 1) % 4);
}

void TetroLMirror::rotateLeft()
{
	actualRotation = static_cast<rotation>(static_cast<int>(actualRotation) - 1);

	if (static_cast<int>(actualRotation) == -1)
		actualRotation = Ldown;
}


