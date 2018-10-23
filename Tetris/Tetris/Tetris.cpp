#include <windows.h>

#include "stdafx.h"
#include "Window.h"
#include "Rect.h"
#include "Game.h"
#include "Tetromino.h"
#include "Board.h"

#include <SDL.h>
#include <SDL_mixer.h>

#undef main
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") //this line closes the console when the app runs


unsigned short int windowW = 483;
unsigned short int windowH = 650;
unsigned short int pieceInitPosX = 10;
unsigned short int pieceInitPosY = 10;

int main()
{
	/*WINDOW*/
	Window window(windowW, windowH, 100, 150);
	
	/*LOADS MEDIA*/
	Rect BG(window, windowW, windowH, 0, 0, "Images/BG.png");
	Rect numbers(window, windowW, windowH, 393, 230, "");//doesn't need to load a path	
	Rect rect(window, 30, 30, "Images/2_5.png");
	Rect rect2(window, 30, 30, "Images/2_1.png");
	Mix_Music *music = Mix_LoadMUS("Images/TetrisM.wav");

	/*LOADS GAMEOVER MEDIA*/
	Rect YouLose(window, windowW, windowH, 0, 0, "Images/GO.png");
	Rect continueGame(window, windowW, windowH, 0, 0, "Images/Continue.png");
	
	/*GAME VARIABLES*/			
	Game game;
	
	unsigned long mTime1 = SDL_GetTicks();//GETS TIME

	Mix_PlayMusic(music, -1);//RUNS MUSIC

	 /*Draw first scene*/
	game.drawAll(rect, BG, rect2, numbers);
	window.clear();  //Afterwards the game only draws when necessary

	/*Main Loop!*/
	while (!window.isClosed())
	{
		/*movement*/
		game.pullEvents(window, rect, BG, rect2, numbers); // This also draws the scene if a key is pressed
		
		unsigned long mTime2 = SDL_GetTicks();
		
		if (game.getWaitTime() < (mTime2 - mTime1)) //if wait time passed
		{			
			if (game.pieceFalls())
			{
				rect.changeXandYto(game.xInPixels(game.getX()), game.yInPixels(game.getY())); //changes the rectangle's position to be shown
				game.moveDown();
				
			}
			else
			{
				/*STORES THE PIECES, CHECK IF IT HAS TO DELETE A LINE, LEVELING UP WHEN NEEDED, AND CLEANS UP THE OBJECT*/
				game.storePiecesAndDelete();

				/*ASIGNS THE NEXT PIECE TO THE ACTUAL PIECE*/
				game.getNextPiece();

				/*CREATES A NEXT PIECE*/
				game.TetroFactory();

				/*SETS INITIAL POSITIONS WHERE TO SPAWN THE PIECE*/
				game.setY(initialPositionY);
				game.setX(initialPositionX);
				
			}

			/*Draw scene IF time passes*/
			game.drawAll(rect, BG, rect2, numbers);
			window.clear();

			mTime1 = SDL_GetTicks();
			
		}

		/*Game over when the piece spawns and cannot move down*/
		if (game.gameOver())
		{	
			/*User lost the game*/

			game.setGameStatus(true); //Shows the game over screen
			YouLose.draw();
			window.clear();
			SDL_Delay(2000);

			/*User decides if he wants to restart*/
			while (game.gameIdle() && !window.isClosed())
			{
				continueGame.draw();
				window.clear();
				game.pullEvents(window, rect, BG, rect2, numbers);

			}
			mTime1 = SDL_GetTicks(); //Needs to take the time again
		}

	}

	/*Stops music*/
	Mix_FreeMusic(music);
	/*Stops SDL*/
	window.stopSDL();
	

    return 0;
}

