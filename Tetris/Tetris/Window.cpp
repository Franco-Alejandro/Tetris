#include "stdafx.h"
#include "Window.h"
#include "SDL_image.h"
#include <SDL_ttf.h>

Window::Window(int width, int height, int posX, int posY):
windowW(width), windowH(height), windowPosX(posX), windowPosY(posY)
{
	closed = !init();
	
}


Window::~Window()
{		
	
}

bool Window::isClosed()
{
	return closed;
}


void Window::event(SDL_Event event)
{
	
	if(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			closed = true;
			break;
		default:
			break;
		}
	}
}

void Window::clear() const
{
	SDL_RenderPresent(pRender);	
	
	SDL_RenderClear(pRender);	
}

void Window::closeWindow()
{
	closed = true;

}

void Window::stopSDL()
{
	Mix_CloseAudio();
	SDL_DestroyRenderer(pRender);
	SDL_DestroyWindow(pWindow);
	IMG_Quit();
	SDL_Quit();
}

bool Window::init()
{
	/*Initialize SDL video and audio*/
	if (SDL_Init(SDL_INIT_VIDEO) != 0 || SDL_Init(SDL_INIT_AUDIO) != 0 )
	{
		std::cerr << "Failed to initialize SDL!   "<< std::endl;
			return false;
	}
	/*Initialize TXT of the SDL*/
	if (TTF_Init() != 0)
	{
		std::cerr << "Failed to init TTF   " << std::endl;
	}

	/*Initialize music device*/
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cerr << "Failed to initialize MIXER!";
		return false;
	}


	/*Initialize SDL IMAGE*/
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		std::cerr << "Failed to initialize SDL_IMAGE!   " << std::endl;
		return false;
	}

	/*Creates window*/
	pWindow = SDL_CreateWindow("Tetris BootCamp",
		windowPosX,
		windowPosY,
		windowW, windowH, SDL_WINDOW_SHOWN);
		
	if (pWindow == nullptr)
	{
			std::cerr << "Failed to create window!   " << std::endl;
				return false;
	}

	/*Creates renderer*/
	pRender = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	

	return true; //Window and initialization succesfully completed
}

void Window::freeTexture(SDL_Texture * txture)
{
	if (txture != nullptr)
	{
		SDL_DestroyTexture(txture);
		txture = nullptr;
		
	}
}
/*Franco Amatta*/