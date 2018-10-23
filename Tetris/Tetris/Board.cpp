#include "stdafx.h"
#include "Board.h"
#include <iostream>

Board::Board()
{
	Initialize();
}


Board::~Board()
{
}

void Board::Store(const Tetromino*  tetro, short int x, short int y)
{
	for (size_t i = 0; i < TetroHAndW; ++i)
	{
		for (size_t j = 0; j < TetroHAndW; ++j) // we move the other axis
		{
			if (tetro->getPiece(i, j) == 1) //checks the position in the array of the piece
			{
				ArrayBoard[x + i][y + j] = OC;			
			}
		}
	}
}

int Board::CheckAndDelete()
{
	short int _LinesDeleted = 0;
	/* this method works with "DeleteOneLine", so it can delete as many lines as necessary*/

	for (size_t j = 0; j < BoardHeight; ++j) // we move through the ROWS
	{
		short int OCacum = 0;
		for (size_t i = 0; i < BoardWidht; ++i)   // we need to see if all the positions in the row we are looking are filled
		{
			
			if (ArrayBoard[i][j] == OC)
			{
				
				++OCacum;	 //if ONE position isnt filled we just skip the addition on the accumulator "j" and breaks the loop. This is VERY important, if we don't break the loop it would continue for ever
				
			}


			if (OCacum == BoardWidht ) //this means all positions were "OC"
			{
				DeleteOneLine((unsigned short)j); //we delete that line
				
				++_LinesDeleted;
				//std::cout << "Deleted " << j << std::endl << "Lines deleted " << _LinesDeleted << std::endl;
			}
		}
	}
	return _LinesDeleted;
}

bool Board::CanThePieceMove(const Tetromino * tetro, const short int x, const short int y)
{	
		for (size_t i = 0; i < TetroHAndW; ++i)//rows on the piece array
		{
			for (size_t j = 0; j < TetroHAndW; ++j) // we move the other axis, collumns on the piece array
			{
				/* Is the piece outside the limit*/

				if ((i + x)< 0 || (i + x)> BoardWidht - 1 || (j + y) > BoardHeight - 1)
				{
					if (tetro->getPiece(i, j) == 1 )
					{		
						return false;
					}
				}

				if (j >= 0) //collision with something stored
				{
					if ((tetro->getPiece(i, j) != 0) && (returnPosition(x + i, y + j) != 0))
					{						
						return false;
					}
				}
			}
		}

	return true;//There was no collision
}

char Board::returnPosition(const short int x, const short int y)
{
		return ArrayBoard[x][y];
}




void Board::Initialize()
{
	for (int y = 0; y < BoardHeight; ++y)
	{
		for (int x = 0; x < BoardWidht; ++x)
		{
			ArrayBoard[x][y] = VACANT;
			
		}
		
	}
	
}

void Board::DeleteOneLine(unsigned short int y)
{ 
	for (int j = y; j > 0; --j)
	{
		for (int i = 0; i < BoardWidht; ++i)
		{
			ArrayBoard[i][j] = ArrayBoard[i][j-1];/*We start on the line we need to erase (j),
													and we go through that line equating values with the previous line  */
		}

	}

}
/*Franco Amatta*/