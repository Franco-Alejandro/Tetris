#pragma once
#include "Tetromino.h" // We need to include the piece that we'll store

//  Board is a class that just knows how to STORE values, checks collisions and deletes lines. Note that this class has lots of comments, that's just for this class
// all the other classes will follow the same ordering of data and methods so we won't need such comments
 const short int BoardWidht = 10;
 const short int  BoardHeight = 20;


class Board
{
public:
	/* The constructor will implement initialize */
	Board(); 

	~Board();
	/*It takes the tetromino array and the position where we need to store it*/
	void Store(const Tetromino * tetro, short int x, short int y); 

	/* checks lines that need to be erased (bc they're fully occupied) */
	int CheckAndDelete();

	/*Checks if a piece can move to the position (x,y) in the board*/
	bool CanThePieceMove(const Tetromino *  tetro, const short int x, const short int y);
	
	/*Returns position (x,y) of the board*/
	char returnPosition(const short int x, const short int y);

	
	void Initialize();// the board will be filled with "VACANT"

private:
	
	enum {VACANT, OC};

	
    char ArrayBoard[BoardWidht][BoardHeight];
	
	
	void DeleteOneLine(unsigned short int y); //This method will delete only ONE line of the array, and then it will bring all the pieces one space down
	

};



/*Franco Amatta*/