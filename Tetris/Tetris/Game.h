#pragma once

#include "Board.h"
#include "Rect.h"
#include <time.h>
#include <string>

/*tetrominos*/
#include "Tetromino.h"
#include  "Square.h"
#include  "TetroI.h"
#include  "TetroL.h"
#include  "TetroLMirror.h"
#include  "TetroN.h"
#include  "TetroNMirror.h"
#include  "TetroT.h"

/*Const variables*/
const unsigned short int offSetBoard = 24 ;
const unsigned short int tileHeightAndWidht = 30;
const unsigned short int initialPositionX = 3, initialPositionY = 0;
const unsigned short int xPositionNewPiece = 385, yPositionNewPiece = 60;
const unsigned short int initialWaitTime = 1200;
const unsigned short int necessary_Lines_To_LVL_Up = 10;

class Game
{
public:
	Game();
	~Game();

	/*Restart methods*/
	bool gameIdle();
	void restartGame();
	void setGameStatus(bool onOff);	
	
	/*Next level and store*/
	void storePiecesAndDelete();
	

	/*This method is here to protect the interaction with the private variables
	 working with AsignNewTetro to create tetrominos*/
	void TetroFactory(); 
	
	/*Getters*/
	unsigned short int getLvl();
	unsigned short int getWaitTime();
	short int getX();
	short int getY();

	/*Asks if it's game over*/
	bool gameOver();

	/*Draw scene*/
	void drawAll(Rect &rect, Rect &BG, Rect &rect2, Rect &numbers);
	
	/*Asigns the position of the ACTUAL tetromino to the NEXT one*/
	void getNextPiece();//
	
	/*Sets a new position for the piece*/
	void setX(const short int a);
	void setY(const short int b);

	/*Transforms a BOARD coord to a PIXEL coord */
	short int xInPixels(const short int x);
	short int yInPixels(const short int y);

	/*Movement*/
	void moveRight();
	void moveLeft();
	void moveDown();
	void pullEvents(Window &window, Rect &rect, Rect &BG, Rect  &rect2, Rect &numbers);
	bool pieceFalls();

	/*A method that gives a random number between 0 and  6*/
	unsigned short int RandNumber();

private:

	/*Game elements*/
	Board pBoard;	
	Tetromino *pPiece, *pNextPiece;

	/*Levels up and updates the wait time*/
	void LvlUp();

	/*Creates a new piece*/
	void AsignNewTetro(unsigned short int rand);

	unsigned short int Lvl, WaitTime, linesDeleted;
	bool idleState;

	/*Initializes game*/
	void Init();
	
	
	/*this is where the piece is falling */
	short int xOfThePieceInTheBoard, yOfThePieceInTheBoard;
	
	
	
};

