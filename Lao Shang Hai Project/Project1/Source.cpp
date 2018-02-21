//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <ctime>
#include <stdlib.h>
#include "LTexture.h"
#include <iostream>

#pragma once

//Screen dimension constants
const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT = 900;

//Symbols per reel constant
const int SYMBOLS_PER_REEL = 32;

//Symbol size dimension constants
const int SYMBOL_WIDTH = 200;
const int SYMBOL_HEIGHT = 200;

//Length of symbol set (in pixels)
const int SYMBOL_SET_LENGTH = SYMBOL_HEIGHT*SYMBOLS_PER_REEL;

//Number of different symbols
const int NUMBER_OF_SYMBOL_SPRITES = 10;

//Reel Increment/Speed
const int reelSpeed = 10000;

//Testing Reel destination variables
/*
int reelOneDestination = 20000;
int reelTwoDestination = 660000;
int reelThreeDestination = 280000;
int reelFourDestination = 200000;
int reelFiveDestination = 60000;
*/

//Reel stop boolean checks
bool reelOneStop;
bool reelTwoStop;
bool reelThreeStop;
bool reelFourStop;
bool reelFiveStop;

//Reel layouts
char reelArrayOne[SYMBOLS_PER_REEL] = { 'M', 'T', 'A', 'W', 'N', 'T', 'Q', 'J', 'N', 'K', 'J', 'A', 'S', 'N', 'K', 'J', 'A', 'T', 'P', 'Q', 'A', 'P', 'K', 'T', 'M', 'J', 'Q', 'P', 'K', 'Q', 'A', 'N' };
char reelArrayTwo[SYMBOLS_PER_REEL] = { 'M', 'T', 'N', 'Q', 'K', 'J', 'M', 'K', 'Q', 'P', 'W', 'T', 'J', 'A', 'Q', 'N', 'P', 'T', 'A', 'K', 'N', 'A', 'J', 'T', 'S', 'Q', 'A', 'J', 'T', 'P', 'K', 'N' };
char reelArrayThree[SYMBOLS_PER_REEL] = { 'M', 'N', 'J', 'K', 'A', 'T', 'Q', 'J', 'W', 'K', 'Q', 'A', 'S', 'N', 'K', 'J', 'P', 'N', 'A', 'P', 'Q', 'T', 'P', 'M', 'N', 'T', 'A', 'N', 'K', 'Q', 'J', 'T' };
char reelArrayFour[SYMBOLS_PER_REEL] = { 'M', 'A', 'N', 'Q', 'K', 'T', 'N', 'Q', 'A', 'J', 'T', 'K', 'N', 'P', 'Q', 'J', 'S', 'N', 'A', 'J', 'P', 'M', 'K', 'T', 'Q', 'W', 'P', 'K', 'T', 'J', 'N', 'A' };
char reelArrayFive[SYMBOLS_PER_REEL] = { 'M', 'J', 'A', 'N', 'S', 'T', 'Q', 'J', 'N', 'K', 'Q', 'T', 'J', 'N', 'K', 'Q', 'M', 'P', 'T', 'A', 'W', 'K', 'P', 'A', 'Q', 'N', 'K', 'P', 'J', 'T', 'A', 'J' };

//Symbol Definitions
const char SYMBOL_MAHJONG = 'M';
const char SYMBOL_PIPE = 'P';
const char SYMBOL_SEAL = 'S';
const char SYMBOL_WILD = 'W';
const char SYMBOL_ACE = 'A';
const char SYMBOL_KING = 'K';
const char SYMBOL_QUEEN = 'Q';
const char SYMBOL_JACK = 'J';
const char SYMBOL_TEN = 'T';
const char SYMBOL_NINE = 'N';


////////////////////////////////////// Prototyped Functions //////////////////////////////////////

//Start up SDL and create a window
bool init();

//Load media
bool loadMedia();

bool setSymbols();

void spinCleanup();

////////////////////////////////////// Flags //////////////////////////////////////

//Main loop flag
bool quit = false;


////////////////////////////////////// Classes //////////////////////////////////////

class Reel
{


public:
	
	//Constructor
	Reel::Reel(int GivenXReelPos, char passedReelArray[]);
	
	//Renders the reel
	void Reel::ReelRender(int yReelPos);
	
	//Uses the reel array to assign images to the image objects that will be rendered
	void Reel::ReelTranslator(LTexture reelPlaceImage, char charFromReelArray);
	
	//Renders the symbol set
	void Reel::SymbolSetRender(int symbolSetOffset);

	void Reel::SymbolRender(char charFromReelArray, int symbolOffset);

private:
	//Variables that control the position of the reels and the symbol set - xReelPos is passed into the object constructor and shared by both the reels and the symbol sets 
	int _xReelPos, _yReelPos;
	int _ySymbolSetOffset;
	
	//The reel array of characters that the reel object will use to determine the symbols in the symbol set
	char _reelArray[SYMBOLS_PER_REEL];

};




////////////////////////////////////// Objects //////////////////////////////////////

//Event handler
SDL_Event e;

//The window we will be rendering to:
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Current displayed image
SDL_Surface* gCurrentSurface = NULL;

//Loads individual image as texture
SDL_Texture* loadTexture(std::string path);

//Current displayed texture
SDL_Texture* gTexture = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Globally used font
TTF_Font *gFont = NULL;

//Background Texture
LTexture gBackgroundTexture;

//Reel Strip Texture
LTexture gReelStripTexture;

//Symbol Sheet Texture
LTexture gSymbolSheetTexture;

//Rectangles for pulling individual symbols from the symbol sheet
SDL_Rect gSymbolClips[NUMBER_OF_SYMBOL_SPRITES];

//Creates reel objects
Reel reelOne(100, reelArrayOne);
Reel reelTwo(325, reelArrayTwo);
Reel reelThree(550, reelArrayThree);
Reel reelFour(775, reelArrayFour);
Reel reelFive(1000, reelArrayFive);


////////////////////////////////////// Variables //////////////////////////////////////

//Modulation Components
Uint8 r = 255;
Uint8 g = 255;
Uint8 b = 255;
Uint8 a = 255;

int reelOnePosition;
int reelTwoPosition;
int reelThreePosition;
int reelFourPosition;
int reelFivePosition;

//////////////////////// MAIN FUNCTION ///////////////////////////////////


int main(int argc, char* args[])
{
	//Start Up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
		SDL_Delay(2000);
	}
	else
	{
		//Load media
		if (!loadMedia()){
			printf("Failed to load media!\n");
			SDL_Delay(10000);
		}
		else
		{

				//While application is running
				while (!quit)
				{
					while (SDL_PollEvent(&e) != 0)
					{
						if (e.type == SDL_QUIT)
						{
							quit = true;
						}

						/*
						switch (e.key.keysym.sym)
						*/

						switch (e.type)

						{
						case SDLK_DOWN:
							reelOnePosition += reelSpeed;  break;


						case SDLK_UP:
							reelOnePosition -= reelSpeed;  break;

						case SDL_KEYUP:

							if (e.key.keysym.sym == SDLK_SPACE){

								if (reelOneStop == true && reelTwoStop == true && reelThreeStop == true && reelFourStop == true && reelFiveStop == true)
								{
									reelOneStop = false;
									reelTwoStop = false;
									reelThreeStop = false;
									reelFourStop = false;
									reelFiveStop = false;
								}

								//Set reel destinations to random values

								srand(time(0));
								//int sample = (rand(0)%32);

								int reelOneDestination = 20000 + ((1 + rand() % 32) * 20000);
								int reelTwoDestination = 20000 + ((1 + rand() % 32) * 20000);
								int reelThreeDestination = 20000 + ((1 + rand() % 32) * 20000);
								int reelFourDestination = 20000 + ((1 + rand() % 32) * 20000);
								int reelFiveDestination = 20000 + ((1 + rand() % 32) * 20000);



								//Spin until the last reel is in position
								while (reelOneStop == false)
								{

									//Move all the reels until reel one reaches its destination
									//Once the first reel reaches its destination, mark it as stopped
									if (reelOnePosition == reelOneDestination || reelOnePosition == reelOneDestination + (SYMBOL_SET_LENGTH * 100))
									{
										reelOneStop = true;
									}
									else
									{
										reelOnePosition += reelSpeed;
										reelTwoPosition += reelSpeed;
										reelThreePosition += reelSpeed;
										reelFourPosition += reelSpeed;
										reelFivePosition += reelSpeed;
									}

									spinCleanup();


								}

								while (reelOneStop == true && reelTwoStop == false)
								{

									//Move all the reels until reel one reaches its destination
									//Once the first reel reaches its destination, mark it as stopped
									if (reelTwoPosition == reelTwoDestination || reelTwoPosition == reelTwoDestination + (SYMBOL_SET_LENGTH * 100))
									{
										reelTwoStop = true;
									}
									else
									{
										reelTwoPosition += reelSpeed;
										reelThreePosition += reelSpeed;
										reelFourPosition += reelSpeed;
										reelFivePosition += reelSpeed;
									}
									spinCleanup();
								}

								while (reelOneStop == true && reelTwoStop == true && reelThreeStop == false)
								{

									//Move all the reels until reel one reaches its destination
									//Once the first reel reaches its destination, mark it as stopped
									if (reelThreePosition == reelThreeDestination || reelThreePosition == reelThreeDestination + (SYMBOL_SET_LENGTH * 100))
									{
										reelThreeStop = true;
									}
									else
									{
										reelThreePosition += reelSpeed;
										reelFourPosition += reelSpeed;
										reelFivePosition += reelSpeed;
									}
									spinCleanup();
								}

								while (reelOneStop == true && reelTwoStop == true && reelThreeStop == true && reelFourStop == false)
								{

									//Move all the reels until reel one reaches its destination
									//Once the first reel reaches its destination, mark it as stopped
									if (reelFourPosition == reelFourDestination || reelFourPosition == reelFourDestination + (SYMBOL_SET_LENGTH * 100))
									{
										reelFourStop = true;
									}
									else
									{
										reelFourPosition += reelSpeed;
										reelFivePosition += reelSpeed;
									}
									spinCleanup();
								}

								while (reelOneStop == true && reelTwoStop == true && reelThreeStop == true && reelFourStop == true && reelFiveStop == false)
								{

									//Move all the reels until reel one reaches its destination
									//Once the first reel reaches its destination, mark it as stopped
									if (reelFivePosition == reelFiveDestination || reelFivePosition == reelFiveDestination + (SYMBOL_SET_LENGTH * 100))
									{
										reelFiveStop = true;
									}
									else
									{
										reelFivePosition += reelSpeed;
									}
									spinCleanup();
								}

								SDL_Delay(500);

								break;


							}
						}
					}
					
					//Keystates Go Here
					const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
					if (currentKeyStates[SDL_SCANCODE_Q])
					{
						std::cout << "Press Count" << std::endl;
					}



				
					//Clear screen			
					SDL_SetRenderDrawColor(gRenderer, 132, 58, 89, 255);
					SDL_RenderClear(gRenderer);
					
					reelOne.SymbolSetRender(reelOnePosition);
					reelTwo.SymbolSetRender(reelTwoPosition);
					reelThree.SymbolSetRender(reelThreePosition);
					reelFour.SymbolSetRender(reelFourPosition);
					reelFive.SymbolSetRender(reelFivePosition);
					
					//Render background texture to screen
					gBackgroundTexture.render(0, 0, gRenderer);

					//Update screen
					SDL_RenderPresent(gRenderer);
					
				
				}
			}
		}
	

	return 0;
}
	

bool loadMedia(){
	//Loading success flag
	bool success = true;

		
	//load ReelStrip texture
	if (!gReelStripTexture.loadFromFile("visualassets/reelstrip.png", gRenderer))
	{
		printf("Failed to load reel strip texture!\n");
	}
	
		
	//Load background texture
	if (!gBackgroundTexture.loadFromFile("visualassets/background.png",gRenderer))
	{
		printf("Failed to load background texture image!\n");
		success = false;
	}

	
	//Load Symbol Sheet texture
	if (!gSymbolSheetTexture.loadFromFile("visualassets/SYMBOLSHEET.png", gRenderer))
	{
		printf("Failed to load symbol sheet texture image!\n");
		success = false;
	}
	
	if (!setSymbols())
	{
		printf("Failed to clip symbol texture image!\n");
		success = false;
	}
	
	void close();

	return success;

}

bool init()

{

	//Initialization Flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{

		printf("SDL could not be initialized! SDL_Error: %s\n", SDL_GetError());
		SDL_Delay(2000);
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("Old Shanghai", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			SDL_Delay(2000);
			success = false;
		}
		else{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xAE, 0xDD, 0xBC, 0xCA);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				else
				{
					//Get window surface
					gScreenSurface = SDL_GetWindowSurface(gWindow);
				}
			}


		}
	}
	return success;

}

bool setSymbols(){

	//Success Flag
	bool symbolsSet = true;
	
	gSymbolClips[SYMBOL_MAHJONG].x = 0;
	gSymbolClips[SYMBOL_MAHJONG].y = 0;
	gSymbolClips[SYMBOL_MAHJONG].w = SYMBOL_WIDTH;
	gSymbolClips[SYMBOL_MAHJONG].h = SYMBOL_HEIGHT;

	gSymbolClips[SYMBOL_PIPE].x = 0;
	gSymbolClips[SYMBOL_PIPE].y = 200;
	gSymbolClips[SYMBOL_PIPE].w = SYMBOL_WIDTH;
	gSymbolClips[SYMBOL_PIPE].h = SYMBOL_HEIGHT;

	gSymbolClips[SYMBOL_SEAL].x = 0;
	gSymbolClips[SYMBOL_SEAL].y = 400;
	gSymbolClips[SYMBOL_SEAL].w = SYMBOL_WIDTH;
	gSymbolClips[SYMBOL_SEAL].h = SYMBOL_HEIGHT;

	gSymbolClips[SYMBOL_WILD].x = 0;
	gSymbolClips[SYMBOL_WILD].y = 600;
	gSymbolClips[SYMBOL_WILD].w = SYMBOL_WIDTH;
	gSymbolClips[SYMBOL_WILD].h = SYMBOL_HEIGHT;

	gSymbolClips[SYMBOL_ACE].x = 0;
	gSymbolClips[SYMBOL_ACE].y = 800;
	gSymbolClips[SYMBOL_ACE].w = SYMBOL_WIDTH;
	gSymbolClips[SYMBOL_ACE].h = SYMBOL_HEIGHT;

	gSymbolClips[SYMBOL_KING].x = 0;
	gSymbolClips[SYMBOL_KING].y = 1000;
	gSymbolClips[SYMBOL_KING].w = SYMBOL_WIDTH;
	gSymbolClips[SYMBOL_KING].h = SYMBOL_HEIGHT;

	gSymbolClips[SYMBOL_QUEEN].x = 0;
	gSymbolClips[SYMBOL_QUEEN].y = 1200;
	gSymbolClips[SYMBOL_QUEEN].w = SYMBOL_WIDTH;
	gSymbolClips[SYMBOL_QUEEN].h = SYMBOL_HEIGHT;

	gSymbolClips[SYMBOL_JACK].x = 0;
	gSymbolClips[SYMBOL_JACK].y = 1400;
	gSymbolClips[SYMBOL_JACK].w = SYMBOL_WIDTH;
	gSymbolClips[SYMBOL_JACK].h = SYMBOL_HEIGHT;

	gSymbolClips[SYMBOL_TEN].x = 0;
	gSymbolClips[SYMBOL_TEN].y = 1600;
	gSymbolClips[SYMBOL_TEN].w = SYMBOL_WIDTH;
	gSymbolClips[SYMBOL_TEN].h = SYMBOL_HEIGHT;

	gSymbolClips[SYMBOL_NINE].x = 0;
	gSymbolClips[SYMBOL_NINE].y = 1800;
	gSymbolClips[SYMBOL_NINE].w = SYMBOL_WIDTH;
	gSymbolClips[SYMBOL_NINE].h = SYMBOL_HEIGHT;

	return true;
}

void close()
{
	//Free loaded image
	gBackgroundTexture.free();
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();


}

SDL_Texture* loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_Image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Creature texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to creature texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
	

}



//Reel Class Functions

//Reel Constructor Function
Reel::Reel(int GivenXReelPos, char passedReelArray[])
{
	//When a reel is constructed, we have to give it the x Position it will live in so that the reels are seperated horizontally from one another. This never changes.
	//We also set the default height on all reels to 2000 (200 after it's divided) since all the reels start in the same vertical position.
	_xReelPos = GivenXReelPos;
	_yReelPos = 2000;

	//Sets the reel object's reel array equal to the reel array that was passed in
	for (int i = 0; i < SYMBOLS_PER_REEL; i++)
		_reelArray[i] = passedReelArray[i];

}


//Renders the reel background
void Reel::ReelRender(int yReelPos)
{

	gReelStripTexture.render(_xReelPos, yReelPos / 100, gRenderer);
	gReelStripTexture.render(_xReelPos, (yReelPos / 100) - gReelStripTexture.getHeight(), gRenderer);

}


//renders the symbols at their positions
void Reel::SymbolSetRender(int symbolSetOffset)
{
	for (int j = 0; j < SYMBOLS_PER_REEL; j++)
	{
		Reel::SymbolRender(_reelArray[j], (j*SYMBOL_HEIGHT) + (symbolSetOffset / 100));
		Reel::SymbolRender(_reelArray[j], (j*SYMBOL_HEIGHT) + (symbolSetOffset / 100) - SYMBOL_SET_LENGTH);
	}

}
 
//Assigns the correct image to the passed in texture variable based on the corresponding character in the Character Array.
void Reel::SymbolRender(char charFromReelArray, int symbolOffset)
{
		switch (charFromReelArray)
		{
		case 'W':
			gSymbolSheetTexture.render(_xReelPos, symbolOffset, gRenderer, &gSymbolClips['W']); break;
		case 'M':
			gSymbolSheetTexture.render(_xReelPos, symbolOffset, gRenderer, &gSymbolClips['M']); break;
		case 'P':
			gSymbolSheetTexture.render(_xReelPos, symbolOffset, gRenderer, &gSymbolClips['P']); break;
		case 'S':
			gSymbolSheetTexture.render(_xReelPos, symbolOffset, gRenderer, &gSymbolClips['S']); break;
		case 'K':
			gSymbolSheetTexture.render(_xReelPos, symbolOffset, gRenderer, &gSymbolClips['K']); break;
		case 'Q':
			gSymbolSheetTexture.render(_xReelPos, symbolOffset, gRenderer, &gSymbolClips['Q']); break;
		case 'J':
			gSymbolSheetTexture.render(_xReelPos, symbolOffset, gRenderer, &gSymbolClips['J']); break;
		case 'A':
			gSymbolSheetTexture.render(_xReelPos, symbolOffset, gRenderer, &gSymbolClips['A']); break;
		case 'T':
			gSymbolSheetTexture.render(_xReelPos, symbolOffset, gRenderer, &gSymbolClips['T']); break;
		case 'N':
			gSymbolSheetTexture.render(_xReelPos, symbolOffset, gRenderer, &gSymbolClips['N']); break;
		}

}

//Cleans up after each spin to preserve loop function and render reels / background
void spinCleanup()
{
	//Reset all reels if they reach the end of the strip
	if ((reelOnePosition) > (SYMBOL_SET_LENGTH * 100) + (SYMBOL_HEIGHT*100) )
	{
		reelOnePosition = (SYMBOL_HEIGHT * 100);
	}
	if ((reelTwoPosition) > (SYMBOL_SET_LENGTH * 100) + (SYMBOL_HEIGHT * 100))
	{
		reelTwoPosition = (SYMBOL_HEIGHT * 100);
	}
	if ((reelThreePosition) > (SYMBOL_SET_LENGTH * 100) + (SYMBOL_HEIGHT * 100))
	{
		reelThreePosition = (SYMBOL_HEIGHT * 100);
	}
	if ((reelFourPosition) > (SYMBOL_SET_LENGTH * 100) + (SYMBOL_HEIGHT * 100))
	{
		reelFourPosition = (SYMBOL_HEIGHT * 100);
	}
	if ((reelFivePosition) > (SYMBOL_SET_LENGTH * 100) + (SYMBOL_HEIGHT * 100))
	{
		reelFivePosition = (SYMBOL_HEIGHT * 100);
	}


	SDL_SetRenderDrawColor(gRenderer, 132, 58, 89, 255);
	SDL_RenderClear(gRenderer);

	reelOne.SymbolSetRender(reelOnePosition);
	reelTwo.SymbolSetRender(reelTwoPosition);
	reelThree.SymbolSetRender(reelThreePosition);
	reelFour.SymbolSetRender(reelFourPosition);
	reelFive.SymbolSetRender(reelFivePosition);

	//Render background texture to screen
	gBackgroundTexture.render(0, 0, gRenderer);

	//Update screen
	SDL_RenderPresent(gRenderer);

}