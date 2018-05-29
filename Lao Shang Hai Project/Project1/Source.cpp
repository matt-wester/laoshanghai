//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
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

//Number of reels
const int NUMBER_OF_REELS = 5;

//Default Y position of reels
int givenYPos = 200;

//Symbol size dimension constants
const int SYMBOL_WIDTH = 200;
const int SYMBOL_HEIGHT = 200;

//Length of symbol set (in pixels)
const int SYMBOL_SET_LENGTH = SYMBOL_HEIGHT*SYMBOLS_PER_REEL;

//Number of different symbols
const int NUMBER_OF_SYMBOL_SPRITES = 10;

//Reel Increment/Speed
const int reelSpeed = 10000;

//Unique Reel Destinations 
int reelOneDestination;
int reelTwoDestination;
int reelThreeDestination;
int reelFourDestination;
int reelFiveDestination;

//Unique Reel Flags
bool reelOneStopped;
bool reelTwoStopped;
bool reelThreeStopped;
bool reelFourStopped;
bool reelFiveStopped;

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


//Betting Definitions

// Numeric variable that tracks the Player's total credits | Player starts with 10,000 credits
const int playerCredit = 10000;

// Variable for credit text, used to render the numbered text on screen
const string creditText;

// Variable that tracks how many lines the player is betting | Defaults to 1 line bet (minimum)
const int playerSelectedLine = 1;

// Defaults to 1x bet multiplier
const int playerBetMultiplier = 1;

// Value that stores the last winning amount to show "WIN"
const int lastWin = 0;

////////////////////////////////////// Prototyped Functions //////////////////////////////////////

//Start up SDL and create a window
bool init();

//Load media
bool loadMedia();

bool setSymbols();

// Renders the reels
void spinCleanup();

//Reel Spinning Function that takes random destinations for each of the reels
bool spinReels(int reelOneDestination, int reelTwoDestination, int reelThreeDestination, int reelFourDestination, int reelFiveDestination);

////////////////////////////////////// Flags //////////////////////////////////////

//Main loop flag
bool quit = false;

//Tracks if the reels are spinning or not. By default, the reels are not spinning
bool isSpinning = false;

////////////////////////////////////// Classes //////////////////////////////////////

class Reel
{


public:
	
	//Constructor
	Reel::Reel(int givenXReelPos, const int givenYReelPos, char passedReelArray[]);
	
	//Renders the reel
	void Reel::ReelRender();
	
	//Tests reel movement
	void Reel::TestIncrement();

	//Uses the reel array to assign images to the image objects that will be rendered
	void Reel::ReelTranslator(LTexture reelPlaceImage, char charFromReelArray);
	
	//Animation that increments the reel
	bool Reel::IncrementReel(bool previousReelStopped, int reelDestination);
	
	//Renders the symbol set
	void Reel::SymbolSetRender();

	void Reel::SymbolRender(char charFromReelArray, int symbolOffset);


private:
	//Variables that control the position of the reels and the symbol set
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

//Color used by the font renderer (for text that needs to be reloaded in the main loop)
SDL_Color textColor = { 255, 0, 0 };

//Background Texture
LTexture gBackgroundTexture;

//Reel Strip Texture
LTexture gReelStripTexture;

//Credit Label Text Texture
LTexture gCreditLabelTexture;

//Credit Display Texture
LTexture gCreditCountTexture;

//Symbol Sheet Texture
LTexture gSymbolSheetTexture;

//Rectangles for pulling individual symbols from the symbol sheet
SDL_Rect gSymbolClips[NUMBER_OF_SYMBOL_SPRITES];


//Create reel objects, giving each their X (horizontal) positions, the default Y position, and the symbol arrays
Reel reelOne(100, givenYPos, reelArrayOne);
Reel reelTwo(325, givenYPos, reelArrayTwo);
Reel reelThree(550, givenYPos, reelArrayThree);
Reel reelFour(775, givenYPos, reelArrayFour);
Reel reelFive(1000, givenYPos, reelArrayFive);


////////////////////////////////////// Variables //////////////////////////////////////

//Modulation Components
Uint8 r = 255;
Uint8 g = 255;
Uint8 b = 255;
Uint8 a = 255;


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
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
			SDL_Delay(10000);
		}

		else

		{
			//While application is running
			while (!quit)

			{
				// Renders at the beginning of the loop
				spinCleanup();

				//Pointer to hold the current key state
				const Uint8* currentKeyState = SDL_GetKeyboardState(NULL);

				//Poll for events
				while (SDL_PollEvent(&e) != 0)
				{			
					
					//Checks for a quit event and quits the program if we get one
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}


					//Checks for a space press
					if (currentKeyState[SDL_SCANCODE_SPACE])
					{
						//Check if the reels aren't already spinning
						if (isSpinning == false)
						{
							//initate the spin with the isSpinning flag
							isSpinning = true;

							//Generate random destinations for each reel
							srand(time(0));

							reelOneDestination = 20000 + ((1 + rand() % 32) * 20000);
							reelTwoDestination = 20000 + ((1 + rand() % 32) * 20000);
							reelThreeDestination = 20000 + ((1 + rand() % 32) * 20000);
							reelFourDestination = 20000 + ((1 + rand() % 32) * 20000);
							reelFiveDestination = 20000 + ((1 + rand() % 32) * 20000);
				
							//Print the generated the destinations for testing
							cout << reelOneDestination << endl;
							cout << reelTwoDestination << endl;
							cout << reelThreeDestination << endl;
							cout << reelFourDestination << endl;
							cout << reelFiveDestination << endl;

						}
					}

					if (currentKeyState[SDL_SCANCODE_0])
					{
						cout << "This works" <<endl;
						reelOne.TestIncrement();
					}

					//Allows the user to quit using the escape key
					if (currentKeyState[SDL_SCANCODE_ESCAPE])
					{
						quit = true;
					}

						
					
				}

				// Check if the isSpinning flag was flipped to true after polling for events
				if (isSpinning == true)
				{
					//Increments the reels towards their destination if the reels are currently set to spin.
					if (spinReels(reelOneDestination, reelTwoDestination, reelThreeDestination, reelFourDestination, reelFiveDestination) == true)
					{
						
						//Flags the reels as no longer spinning here:
						isSpinning = false;
						cout << "successfully flagged a finished spin" << endl;
						
						//Functions that run once when a spin is complete should go here
						//REQUIRED: Create temporary array of visible symbols for checking
						//REQUIRED: Check each line's symbols
						//REQUIRED: Calculate the total win
						//REQUIRED: Display win amount, any win animations
					}


					
				}

				// End of game loop
			}	
		}
	}
	return 0;
}	

	
bool loadMedia()
{

	//Loading success flag
	bool success = true;

	//Load Font
	
	gFont = TTF_OpenFont("visualassets/lazy.ttf", 28);
	if (gFont == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %S\n", TTF_GetError());
		success = false;
		
	}
	else
		/*
		{

		
		//Load credit label text
		SDL_Color textColor = { 255, 0, 0 };
		if (!gCreditLabelTexture.loadFromRenderedText(gFont, "Credits", textColor, gRenderer))
		{
			printf("Failed to render credit label texture!\n");
			success = false;
		}

	}
	*/

	//load ReelStrip texture
	if (!gReelStripTexture.loadFromFile("visualassets/reelstrip.png", gRenderer))
	{
		printf("Failed to load reel strip texture!\n");
		success = false;
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

	
		//Create window
		gWindow = SDL_CreateWindow("Old Shanghai", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			SDL_Delay(2000);
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
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
					
					if (TTF_Init() < 0)
					{

						printf("SDL_TTF could not be initialized! SDL_ttf Error: %s\n",TTF_GetError());
						success = false;

					}

					else
						
					//Get window surface
					gScreenSurface = SDL_GetWindowSurface(gWindow);
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

	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;
	
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
Reel::Reel(int givenXReelPos, int givenYReelPos, char passedReelArray[])
{
	//When a reel is constructed, we have to give it the x Position it will live in so that the reels are seperated horizontally from one another. This never changes.
	//We also set the default Y position on all reels to 2000 (200 after it's divided) since all the reels start in the same vertical position.
	_xReelPos = givenXReelPos;
	_yReelPos = givenYReelPos;

	//Sets the reel object's reel array equal to the reel array that was passed in
	for (int i = 0; i < SYMBOLS_PER_REEL; i++)
		_reelArray[i] = passedReelArray[i];

}

//Renders the reel strip texture
void Reel::ReelRender()
{

	gReelStripTexture.render(_xReelPos, _yReelPos / 100, gRenderer);
	gReelStripTexture.render(_xReelPos, (_yReelPos / 100) - gReelStripTexture.getHeight(), gRenderer);

}

//renders the symbols at their positions
void Reel::SymbolSetRender()
{
	for (int j = 0; j < SYMBOLS_PER_REEL; j++)
	{
		Reel::SymbolRender(_reelArray[j], (j*SYMBOL_HEIGHT) + (_yReelPos / 100));
		Reel::SymbolRender(_reelArray[j], (j*SYMBOL_HEIGHT) + (_yReelPos / 100) - SYMBOL_SET_LENGTH);
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

//Test function for adjusting reel position
void Reel::TestIncrement()
{
	_yReelPos += reelSpeed;
}

// Updated reel spining function for each frame. We pass the function the previous reel's status. This function returns false if it has reached its destination.
bool Reel::IncrementReel(bool previousReelStopped, int reelDestination)
{
	// If the reel is at the passed destination, the function returns TRUE
	if ((_yReelPos == reelDestination || _yReelPos == reelDestination + (SYMBOL_SET_LENGTH * 100)) && previousReelStopped == true)
	{
		return true;
	}
	else
	{
		// if the reel is not at its destination and/or the previous reel is still spinning, move the reel 1 tick and return false to indicate this reel still needs to spin
		_yReelPos += reelSpeed;

		// if the reel has moved off scree, reset the position of the reel
		if ((_yReelPos) > (SYMBOL_SET_LENGTH * 100) + (SYMBOL_HEIGHT * 100))
		{
			_yReelPos = (SYMBOL_HEIGHT * 100);
		}

		//Return false to show that the reel hasn't reached the destination yet
		return false;
	}

}


// A function that checks and increments each of the reels before a render. Returns TRUE if the reels have stopped, otherwise returns FALSE.
bool spinReels(int reelOneDestination, int reelTwoDestination, int reelThreeDestination, int reelFourDestination, int reelFiveDestination)
{

	//reelOne recieves the the flag "isSpinning" along with a destination. If the spin has begun this is true and reelOne sees the "previous" reel as
	//stopped. 

	reelOneStopped = reelOne.IncrementReel(isSpinning, reelOneDestination);
	reelTwoStopped = reelTwo.IncrementReel(reelOneStopped, reelTwoDestination);
	reelThreeStopped = reelThree.IncrementReel(reelTwoStopped, reelThreeDestination);
	reelFourStopped = reelFour.IncrementReel(reelThreeStopped, reelFourDestination);
	reelFiveStopped = reelFive.IncrementReel(reelFourStopped, reelFiveDestination);

	if (reelOneStopped == true && reelTwoStopped == true && reelThreeStopped == true && reelFourStopped == true && reelFiveStopped == true && isSpinning == true)
	{
		return true;
	}
	else
	{
		return false;
	}

}

//Cleans up after each spin to preserve loop function and render reels / background
void spinCleanup()
{

	SDL_SetRenderDrawColor(gRenderer, 232, 0, 0, 255);
	SDL_RenderClear(gRenderer);
	
	reelOne.SymbolSetRender();
	reelTwo.SymbolSetRender();
	reelThree.SymbolSetRender();
	reelFour.SymbolSetRender();
	reelFive.SymbolSetRender();

	//Render background texture to screen
	gBackgroundTexture.render(0, 0, gRenderer);
	
	//Render credit label text
	gCreditLabelTexture.render(750, 840, gRenderer, NULL);

	//Convert credits into text
	std::string creditText = "Credits: " + std::to_string(playerCredit);

	//Load new credit texture equal the the player's credits
	gCreditCountTexture.loadFromRenderedText(gFont, creditText, textColor, gRenderer);
	
	//Render the new credit texture
	gCreditCountTexture.render(880, 840, gRenderer,NULL);

	//Update screen
	SDL_RenderPresent(gRenderer);

}