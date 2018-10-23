#include "stdafx.h"
#include "Rect.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <sstream>

Rect::Rect(const Window &window, int widht, int height, int x, int y, const std::string &imagePath) :
	Window(window), textureWidht(widht), textureHeight(height), posX(x), posY(y)
{
	LoadMedia(imagePath);
}
Rect::Rect(const Window & window, int widht, int height, const std::string & imagePath):
Window(window), textureWidht(widht), textureHeight(height)
{
	LoadMedia(imagePath);
}


void Rect::LoadMedia(const std::string & imagePath)
{
	auto surface = IMG_Load(imagePath.c_str());
	if (!surface)
	{
		std::cerr << "Failed to create surface";
	}
	/*Creates the texture*/
	pTexture = SDL_CreateTextureFromSurface(pRender, surface);

	if (!pTexture)
	{
		std::cerr << "Failed to create texture";
	}
	/*Dellocates the surface memory*/
	SDL_FreeSurface(surface);
}

Rect::~Rect()
{
	SDL_DestroyTexture(pTexture);
}

void Rect::draw() const
{ 
	SDL_Rect rect = { posX, posY, textureWidht, textureHeight };

	if (pTexture) 
	{
		SDL_RenderCopy(pRender, pTexture, nullptr, &rect);
	}
	else 
	{
		std::cerr << "Failed to draw";
	}
	
}



void Rect::changeXandYto(const short int newX, const short int newY)
{
	posX = newX;
	posY = newY;
}

void Rect::drawPoints(const unsigned short int a, const unsigned short int b)
{
	short int  points =  a * 100 + b*10; //every level is 100 points while every line is 10
	std::string pointsString = std::to_string(points);
	

	/* Font size and color*/
	TTF_Font* font = TTF_OpenFont("Xefus.ttf", 25);
	SDL_Color black = { 0, 0, 0 }; 
	SDL_Surface* pointsSurface = TTF_RenderText_Solid(font, pointsString.c_str(),black);
	pTexture  = SDL_CreateTextureFromSurface(pRender, pointsSurface);

	SDL_FreeSurface(pointsSurface);
	

	SDL_Rect rect = { posX, posY, 20, 20 }; //area to render
		
		if (pTexture)
		{
			SDL_RenderCopy(pRender, pTexture, nullptr, &rect);
		}

		else 
		{
			std::cerr << "Failed to draw";
		}		

		TTF_CloseFont(font);
		SDL_DestroyTexture(pTexture);

		/*In the near future I'd like this to be an object of its own to improve memory usage*/
}

