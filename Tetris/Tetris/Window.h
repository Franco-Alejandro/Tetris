#pragma once
#include "SDL.h"
#include <iostream>
#include "SDL_mixer.h"

/*MANAGES THE WINDOW and ONLY THE WINDOW*/
class Window
{
public:
	Window( int widht, int height, int windowPosX, int windowPosY);

	~Window();
	bool isClosed();
	void event(SDL_Event event);
	void clear() const ;
	void closeWindow();
	void stopSDL();

private:// private methods
	bool init();
	void freeTexture(SDL_Texture *txture);

private:
	 short int windowW;
	 short int windowH;
	
	short int windowPosX;
	short int windowPosY;
	bool closed = false;
	SDL_Window *pWindow = nullptr;

	
protected:
	SDL_Renderer *pRender = nullptr; 
};

/*Franco Amatta*/