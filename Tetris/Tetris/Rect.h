#pragma once
#include "window.h"
#include "stdafx.h"
class Rect : public Window /*I needed to use the same renderer as window, this is the class for all the textures*/
{
public:
	
	Rect(const Window &window, int widht, int height, int x, int y, const std::string &imagePath);
	Rect(const Window &window, int widht, int height, const std::string &imagePath);


	void LoadMedia(const std::string &imagePath);
	~Rect();
	void draw() const;
	
	/*This method changes the X and Y where the piece will be*/
	void changeXandYto(const short int newX, const short int newY);

	void drawPoints(const unsigned short int a, const unsigned short int b);
private:

	
	short int textureWidht, textureHeight;
	short int posX, posY;
	

	SDL_Texture *pTexture = nullptr;
};

