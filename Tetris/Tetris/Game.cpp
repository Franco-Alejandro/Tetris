#include "stdafx.h"
#include "Game.h"


Game::Game()
{	
	Lvl = 0;
	linesDeleted = 0;
	WaitTime = initialWaitTime;
	idleState = false;
	Init();	
}

bool Game::gameIdle()
{
	return idleState;
}

void Game::restartGame()
{
	if (gameIdle())
	{
		Lvl = 0;
		WaitTime = initialWaitTime;
		linesDeleted = 0;
		pBoard.Initialize();
		idleState = false;
	}
}

void Game::setGameStatus(bool onOff)
{
	idleState = onOff;
}

Game::~Game()
{

}

void Game::storePiecesAndDelete()
{
	/*Store the piece*/
	pBoard.Store(pPiece, xOfThePieceInTheBoard, yOfThePieceInTheBoard);

	/*Frees the memory of the tetromino*/
	pPiece->~Tetromino();
	operator delete (pPiece);
	pPiece = 0;

	/*Delete the lines and adds how many lines where deleted to the acum*/
	linesDeleted += pBoard.CheckAndDelete();

	if (linesDeleted == necessary_Lines_To_LVL_Up)
	{
		LvlUp();
		/*Resets the DELETED LINES count*/
		linesDeleted = 0;

	}
}

void Game::LvlUp()
{
	++Lvl;
	/*Wait time is reduced by 5% every level*/
	WaitTime = initialWaitTime * (1 - ((float)0.05 *Lvl));
}

void Game::AsignNewTetro(unsigned short int rand)
{
	switch (rand)
	{
	case 0:
		pNextPiece = new Square;
		break;
	case 1:
		pNextPiece = new TetroI;
		break;
	case 2:
		pNextPiece = new TetroL;
		break;
	case 3:
		pNextPiece = new TetroLMirror;
		break;
	case 4:
		pNextPiece = new TetroN;
		break;
	case 5:
		pNextPiece = new TetroNMirror;
		break;
	case 6:
		pNextPiece = new TetroT;
		break;
	}
}

void Game::TetroFactory()
{
	unsigned short int rand = RandNumber();	
	AsignNewTetro(rand);

}


unsigned short int Game::getLvl()
{
	return Lvl;
}


unsigned short int Game::getWaitTime()
{
	return WaitTime;
}

void Game::drawAll(Rect &rect, Rect &BG, Rect &rect2, Rect &numbers)
{
	BG.draw();
	unsigned short int vPixelsX = xInPixels(xOfThePieceInTheBoard);
	unsigned short int vPixelsY = yInPixels(yOfThePieceInTheBoard);
	for (size_t x = 0; x < TetroHAndW; ++x)
	{
		for (size_t y = 0; y < TetroHAndW; ++y)
		{
			if (pPiece->getPiece(x, y) != 0)
			{
				rect.changeXandYto( vPixelsX + (((short)x)*tileHeightAndWidht), (vPixelsY + (((short)y)*tileHeightAndWidht)));
				rect.draw();
			}
			if (pNextPiece->getPiece(x, y) != 0)
			{
				rect2.changeXandYto(((short)x*tileHeightAndWidht) + xPositionNewPiece, ((short)y*tileHeightAndWidht) + yPositionNewPiece);
				rect2.draw();
			}
		}

	}

	for (size_t i = 0; i <BoardHeight; ++i)
	{
		for (size_t j = 0; j <  BoardWidht; ++j)
		{
			if (pBoard.returnPosition(j, i)!=0)
			{
				rect2.changeXandYto(xInPixels((const short)j), xInPixels((const short)i));				
				rect2.draw();
				
			}
		}
		
	}

	numbers.drawPoints(Lvl, linesDeleted);
	
}


void Game::getNextPiece()
{	
	pPiece = pNextPiece;	
}

short int Game::getX()
{
	return xOfThePieceInTheBoard;
}

short int Game::getY()
{
	return yOfThePieceInTheBoard;
}

bool Game::gameOver()
{
	if (pBoard.CanThePieceMove(pPiece, initialPositionX, initialPositionY)) //can the piece spawn?
	{
		return false; //it isn't game over
	}	
	
	// it is game over
	return true;
}

void Game::setX(const short int a)
{
	xOfThePieceInTheBoard = a;
}

void Game::setY(const short int b)
{
	yOfThePieceInTheBoard = b;
}

short int Game::xInPixels(const short int x)
{
	short int xPixels = x * tileHeightAndWidht + offSetBoard;

	return xPixels;
}

short int Game::yInPixels(const short int y)
{
	short int yPixels = (y)* tileHeightAndWidht + offSetBoard;

	return yPixels;
}

void Game::Init() //Selects the new tetromino
{
	int a = RandNumber(), b;
	TetroFactory();

	pPiece = pNextPiece;	
	do 
	{
		b = RandNumber();
		TetroFactory();

	} while (a == b);

	xOfThePieceInTheBoard = initialPositionX;
	yOfThePieceInTheBoard = initialPositionY;	
}


void Game::moveRight()
{
	++xOfThePieceInTheBoard;
}

void Game::moveLeft()
{ 
	--xOfThePieceInTheBoard;
}

void Game::moveDown()
{
	++yOfThePieceInTheBoard;
}

void Game::pullEvents(Window & window, Rect &rect, Rect &BG, Rect  &rect2, Rect &numbers)
{	
	SDL_Event event;
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_LEFT:
					if (pBoard.CanThePieceMove(pPiece,xOfThePieceInTheBoard - 1,yOfThePieceInTheBoard))
					{
						moveLeft();
					}
					break;
				case SDLK_RIGHT:
					if (pBoard.CanThePieceMove(pPiece, xOfThePieceInTheBoard + 1, yOfThePieceInTheBoard))
					{
						moveRight();
					}
					break;
				case SDLK_DOWN:
					if (pBoard.CanThePieceMove(pPiece, xOfThePieceInTheBoard, yOfThePieceInTheBoard + 1))
					{
						moveDown();
					}
					break;
				case SDLK_UP:
					pPiece->rotateRight();
					if (!pBoard.CanThePieceMove(pPiece, xOfThePieceInTheBoard, yOfThePieceInTheBoard))
					{
						pPiece->rotateLeft();
					}
					break;
				case SDLK_z:
					pPiece->rotateLeft();
					if (!pBoard.CanThePieceMove(pPiece, xOfThePieceInTheBoard, yOfThePieceInTheBoard))
					{
						pPiece->rotateRight();
					}
					break;
				case SDLK_y:									
					restartGame();
					break;
				case SDLK_n:
					window.closeWindow();
					idleState = false;
					break;
				default:
					break;
				}	
				/*Draw scene */
				drawAll(rect, BG, rect2, numbers);
				window.clear();
			}
			window.event(event);
			
		}

		
	}

bool Game::pieceFalls()
{
	if (pBoard.CanThePieceMove(pPiece, xOfThePieceInTheBoard, yOfThePieceInTheBoard + 1))
	{
		return true;
	}
	return false;
}


unsigned short int Game::RandNumber()
{
	srand(time(NULL));
	return rand() % 7 ;
}



