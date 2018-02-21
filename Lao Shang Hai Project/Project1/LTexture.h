#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
#include <TTF\SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>
#pragma once

using namespace std;

class LTexture
{
public:

	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Load images from a specified path
	bool loadFromFile(std::string path, SDL_Renderer* gRenderer);

	//Create image from font string
	bool loadFromRenderedText(TTF_Font *gFont, string textureText, SDL_Color textColor, SDL_Renderer* gRenderer);

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip = NULL);

	//Get image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
	
};

