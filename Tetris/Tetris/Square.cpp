#include "stdafx.h"
#include "Square.h"


const unsigned short int Square::getPiece(const int pX, const int pY) const
{
	return (piece[pX][pY]);
}

void Square::rotateRight()
{
	/*no rotation*/
}

void Square::rotateLeft()
{ /*no rotation*/
}

Square::Square()
{
}


Square::~Square()
{
}
