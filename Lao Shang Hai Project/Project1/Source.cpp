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

//Number of reels visible on each reel
const int SYMBOLS_VISIBLE_PER_REEL = 3;

//Default Y position of reels
int givenYPos = 0; //200;

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

//Reel layouts
char reelArrayOne[SYMBOLS_PER_REEL] = { 'M', 'T', 'A', 'W', 'N', 'T', 'Q', 'J', 'N', 'K', 'J', 'A', 'S', 'N', 'K', 'J', 'A', 'T', 'P', 'Q', 'A', 'P', 'K', 'T', 'M', 'J', 'Q', 'P', 'K', 'Q', 'A', 'N' };
char reelArrayTwo[SYMBOLS_PER_REEL] = { 'M', 'T', 'N', 'Q', 'K', 'J', 'M', 'K', 'Q', 'P', 'W', 'T', 'J', 'A', 'Q', 'N', 'P', 'T', 'A', 'K', 'N', 'A', 'J', 'T', 'S', 'Q', 'A', 'J', 'T', 'P', 'K', 'N' };
char reelArrayThree[SYMBOLS_PER_REEL] = { 'M', 'N', 'J', 'K', 'A', 'T', 'Q', 'J', 'W', 'K', 'Q', 'A', 'S', 'N', 'K', 'J', 'P', 'N', 'A', 'P', 'Q', 'T', 'P', 'M', 'N', 'T', 'A', 'N', 'K', 'Q', 'J', 'T' };
char reelArrayFour[SYMBOLS_PER_REEL] = { 'M', 'A', 'N', 'Q', 'K', 'T', 'N', 'Q', 'A', 'J', 'T', 'K', 'N', 'P', 'Q', 'J', 'S', 'N', 'A', 'J', 'P', 'M', 'K', 'T', 'Q', 'W', 'P', 'K', 'T', 'J', 'N', 'A' };
char reelArrayFive[SYMBOLS_PER_REEL] = { 'M', 'J', 'A', 'N', 'S', 'T', 'Q', 'J', 'N', 'K', 'Q', 'T', 'J', 'N', 'K', 'Q', 'M', 'P', 'T', 'A', 'W', 'K', 'P', 'A', 'Q', 'N', 'K', 'P', 'J', 'T', 'A', 'J' };

//Matrix of visible symbols for checking wins after the spin
char visibleArray[SYMBOLS_VISIBLE_PER_REEL][NUMBER_OF_REELS] = { { 'X', 'X', 'X', 'X', 'X' }, { 'X', 'X', 'X', 'X', 'X' }, { 'X', 'X', 'X', 'X', 'X'} };

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

// Betting Definitions

// Tracks the Player's total credits | Player starts with 10,000 credits
int playerCredit = 10000;

// Line options available to the player, from lowest to highest
const int lineOptionArray[] = { 1, 5, 10, 15, 30, 40 };
// Tracks how many lines the player is betting by storing the index of the line option array
int lineOptionIndex = 0;
// Actual number of lines the player is betting
int lineOption = lineOptionArray[lineOptionIndex];

// Bet multiplier options available to the player, from lowest to highest
const int betMultiplierArray[] = { 1, 2, 3, 5, 10 };
// Tracks the bet multiplier by storing the index of the bet multiplier array
int betMultiplierIndex = 0;
// Variable that tracks the actual bet multiplier the player is betting, defaulting to the lowest multiplier option
int playerBetMultiplier = betMultiplierArray[betMultiplierIndex];
// Variable that tracks the number of lines the player is betting, defaulting to the lowest line option
int playerSelectedLine = 1;

// The last winning amount to show "WIN"
int lastWin = 0;

////////////////////////////////////// Prototyped Functions //////////////////////////////////////

// Start up SDL and create a window
bool init();

// Load media
bool loadMedia();
bool setSymbols();

// Renders the reels
void spinCleanup();

// Reel Spinning Function that takes random destinations for each of the reels
bool spinReels(int reelOneDestination, int reelTwoDestination, int reelThreeDestination, int reelFourDestination, int reelFiveDestination);

// Checks Lines
int lineChecker(int positionOne, int positionTwo, int positionThree, int positionFour, int positionFive);

////////////////////////////////////// Flags //////////////////////////////////////

//Main loop flag
bool quit = false;

//Tracks if the reels are spinning or not. By default, the reels are not spinning
bool isSpinning = false;

//Unique Reel Stopped Flags
bool reelOneStopped;
bool reelTwoStopped;
bool reelThreeStopped;
bool reelFourStopped;
bool reelFiveStopped;

//Cheat Mode

bool cheat = false;

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

	//Populates the visible symbol array
	void Reel::PopVisibleSymbols(int reelDestination, int reelNumber);

	//Returns the Y position of the reel (_yReelPos)
	int Reel::getYPosition();

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
								//Calculate the player's bet
								int playerBet = (playerBetMultiplier * playerSelectedLine);
							
								//Check if the player has enough credits to make the bet
								if (playerBet > playerCredit)
								{
									//Don't spin
									cout << "Insufficent Credits" << endl;
								}
								else
								{

									//Deduct the bet from the player's credit count
									playerCredit = (playerCredit - playerBet);

									//initate the spin with the isSpinning flag
									isSpinning = true;

									//Generate random destinations for each reel
									srand( (unsigned int)time(0) );

									reelOneDestination = ((1 + rand() % 32) * 20000);
									reelTwoDestination = ((1 + rand() % 32) * 20000);
									reelThreeDestination = ((1 + rand() % 32) * 20000);
									reelFourDestination = ((1 + rand() % 32) * 20000);
									reelFiveDestination = ((1 + rand() % 32) * 20000);

									//Cheat mode for testing
									if (cheat){
										reelOneDestination = 440000;
										reelTwoDestination = 200000;
										reelThreeDestination = 440000;
										reelFourDestination = 360000;
										reelFiveDestination = 600000;
									}


									//Print the generated the destinations for testing
									cout << reelOneDestination / 20000 << endl;
									cout << reelTwoDestination / 20000 << endl;
									cout << reelThreeDestination / 20000 << endl;
									cout << reelFourDestination / 20000 << endl;
									cout << reelFiveDestination / 20000 << endl;

									//Create temporary array of visible symbols for checking
									reelOne.PopVisibleSymbols(reelOneDestination, 1);
									reelTwo.PopVisibleSymbols(reelTwoDestination, 2);
									reelThree.PopVisibleSymbols(reelThreeDestination, 3);
									reelFour.PopVisibleSymbols(reelFourDestination, 4);
									reelFive.PopVisibleSymbols(reelFiveDestination, 5);

									// Print the visible symbol array

									for (int i = 0; i < SYMBOLS_VISIBLE_PER_REEL; ++i)
									{
										for (int j = 0; j < NUMBER_OF_REELS; ++j)
										{
											std::cout << visibleArray[i][j] << ' ';
										}
										std::cout << std::endl;
									}

								}
							}
						}

					//Keystate for testing (Press 0)
					if (currentKeyState[SDL_SCANCODE_0]){
						cout << "CHEAT MODE ACTIVATED!" <<endl;
						cheat = true;
					}

					//Up Arrow Keystate (increases lines played)
					if (currentKeyState[SDL_SCANCODE_UP]){
						cout << "CHEAT MODE DEACTIVATED!" << endl;
						cheat = false;
					}
					
					//State to Decrease Lines Played)
					if (currentKeyState[SDL_SCANCODE_DOWN]){

					}

					//State to Increase Bet Multiplier)
					if (currentKeyState[SDL_SCANCODE_RIGHT]){

					}

					//State to Decrease Bet Multiplier
					if (currentKeyState[SDL_SCANCODE_LEFT]){

					}

					//Allow the user to quit using the escape key
					if (currentKeyState[SDL_SCANCODE_ESCAPE]){
						quit = true;
					}

						
					
				}

				// Check if the isSpinning flag after polling for events
				if (isSpinning == true)
				{
					//Increments the reels towards their destination if the reels are currently set to spin.
					if (spinReels(reelOneDestination, reelTwoDestination, reelThreeDestination, reelFourDestination, reelFiveDestination) == true)
					{
						//Flags the reels as no longer spinning here:
						isSpinning = false;
						cout << "successfully flagged a finished spin" << endl;

						//Checking lines (5 Line Configuration)
						playerCredit +=
						lineChecker(0, 0, 0, 0, 0) +
						lineChecker(1, 1, 1, 1, 1) +
						lineChecker(2, 2, 2, 2, 2) +
						lineChecker(0, 1, 1, 1, 2) +
						lineChecker(2, 1, 1, 1, 0);

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
	//We also typically set the default Y position on all reels to 2000 (200 after it's divided) since all the reels start in the same vertical position.
	_xReelPos = givenXReelPos;
	_yReelPos = givenYReelPos;

	//Sets the reel object's reel array equal to the reel array that was passed in
	for (int i = 0; i < SYMBOLS_PER_REEL; i++)
		_reelArray[i] = passedReelArray[i];

}

//Renders the reel strip texture (reel background)
void Reel::ReelRender()
{
	gReelStripTexture.render(_xReelPos, _yReelPos / 100, gRenderer);
	gReelStripTexture.render(_xReelPos, (_yReelPos / 100) - gReelStripTexture.getHeight(), gRenderer);
}

// Renders the grouped symbols on the reel strip
void Reel::SymbolSetRender()
{
	for (int j = 0; j < SYMBOLS_PER_REEL; j++)
	{
		Reel::SymbolRender(_reelArray[j], (j*SYMBOL_HEIGHT) + (_yReelPos / 100));
		Reel::SymbolRender(_reelArray[j], (j*SYMBOL_HEIGHT) + (_yReelPos / 100) - SYMBOL_SET_LENGTH);
	}

}
 
// Uses characters on the reel strip to render symbols, used only in the SymbolSetRender method
void Reel::SymbolRender(char charFromReelArray, int symbolOffset){
		
	switch (charFromReelArray){

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

// Test for adjusting reel position
void Reel::TestIncrement()
{
	_yReelPos += reelSpeed;
}

// Returns the y position of the reel
int Reel::getYPosition(){

	return (_yReelPos / 20000);

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

		// if the reel has moved off screen, reset the position of the reel
		if ( (_yReelPos) > (SYMBOL_SET_LENGTH * 100) ) {
			_yReelPos = 0; // (SYMBOL_HEIGHT * 100);
		}

		//Return false to show that the reel hasn't reached the destination yet
		return false;
	}

}

//Populates the visible symbol matrix
void Reel::PopVisibleSymbols(int reelDestination, int reelNumber) {


	int topIndex = ((SYMBOLS_PER_REEL + 1) - (reelDestination / 20000)); // Get a 1-32 number from the destination, then inverse it to get the top
	int middleIndex = topIndex + 1; // If the top is 0, middle is 1
	int bottomIndex = middleIndex + 1; //If the middle is 1, bottom is 2


	if (topIndex > (SYMBOLS_PER_REEL - 1)){
		topIndex = (topIndex - SYMBOLS_PER_REEL);
	}

	if (middleIndex > (SYMBOLS_PER_REEL - 1)) { //If  middle index is outside the reel strip array
		middleIndex = topIndex - (SYMBOLS_PER_REEL - 1); //If top is 31, middle goes to 0
	}

	if (bottomIndex > (SYMBOLS_PER_REEL - 1)) { //If bottom index is outside the reel strip array
		bottomIndex = topIndex - (SYMBOLS_PER_REEL - 2); //If top is 31, middle goes to 1, if top is 30, middle goes to 0
	}

	visibleArray[0][reelNumber - 1] = _reelArray[topIndex];
	visibleArray[1][reelNumber - 1] = _reelArray[middleIndex];
	visibleArray[2][reelNumber - 1] = _reelArray[bottomIndex];
}

//////// Other Functions /////////////

// Checks and increments each of the reels to their destinations. Returns TRUE if the reels have stopped, otherwise returns FALSE.
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

//Takes a text label and a value (like player credit, lines, etc. and loads an updated texture at the given X / Y coordinates 
void labelMaker(string label, int playerNumber, int xCoordinate, int yCoordinate)
{
	//Convert the parameter number and  into text for gLabelMakerTexture
	std::string labelMakerText = label + ": " + std::to_string(playerNumber);

	//create a texture for the label maker to use
	LTexture gLabelMakerTexture;

	//Load the combined label and parameter number to gLabelMakerTexture
	gLabelMakerTexture.loadFromRenderedText(gFont, labelMakerText, textColor, gRenderer);
	
	//Render the new credit texture
	gLabelMakerTexture.render(xCoordinate, yCoordinate, gRenderer, NULL);

}

//Returns the next option of passed array, jumps to a higher value if isIncreasting is TRUE
int nextInArray(int shiftValue, int optionArray[], bool isIncreasing)
{
	//Size of the passed array (divided by 4 from int)
	int arraySize = (sizeof(optionArray)/4);

	if (isIncreasing == true)
	{
		//Before increasing, we first check if the current option isn't already equal to the highest available option
		if (shiftValue >= optionArray[arraySize])
		{
			//If we're already at the highest value, just return the highest value (don't change anything)
			return optionArray[arraySize];
		}
		else
		{
			//We return the next value in the array
			return optionArray[(arraySize++)];
		}

	}
	else
	{
		//Before decreasing, we check if the current option isn't already equal to the first option
		if (shiftValue <= optionArray[0])
		{
			//If we're already at the lowest value, return the lowest value
			return optionArray[0];
		}
		else
		{
			//We return the previous value in the array
			return optionArray[0];
		}
	}

}

//Method that takes 5 integers (between 0 - 2) and checks the lines. 0 corresponds to the top symbol, 1 to middle, 2 to bottom.
int lineChecker(int positionOne, int positionTwo, int positionThree, int positionFour, int positionFive){

	//Line-based multiplier
	int lineMultiplier = 0;
	//Symbol Value
	int symbolValue = 0;

	//If the first and second symbol are the same, we can check for a win, otherwise we can safely return a 0 immediately.
	if (visibleArray[positionOne][0] == visibleArray[positionTwo][1]){
		// If the first symbol is the same as the third symbol, and the first is also equal to the third, we have a base win
		if (visibleArray[positionOne][0] == visibleArray[positionThree][2]){
			lineMultiplier = 1;
			//If the fourth symbol matches too, it's double
			if (visibleArray[positionOne][0] == visibleArray[positionFour][3]){
				lineMultiplier = 2;
				//If the fifth symbol matches too, it's triple
				if (visibleArray[positionOne][0] == visibleArray[positionFive][4]){
					lineMultiplier = 3;
				}
			}


		}

		//As long as the leftmost 3 symbols match, we can lookup the value of the symbol.
		switch (visibleArray[positionOne][0]){
			//Paytable
			case SYMBOL_MAHJONG:
				symbolValue = 300; break;
			case SYMBOL_PIPE:
				symbolValue = 100; break;
			case SYMBOL_SEAL:
				symbolValue = 200; break;
			case SYMBOL_ACE:
				symbolValue = 75; break;
			case SYMBOL_KING:
				symbolValue = 50; break;
			case SYMBOL_QUEEN:
				symbolValue = 40; break;
			case SYMBOL_JACK:
				symbolValue = 30; break;
			case SYMBOL_TEN:
				symbolValue = 20; break;
			case SYMBOL_NINE:
				symbolValue = 10; break;
			default:
				symbolValue = NULL; break;
		}
		//Return the symbol's value times the multiplier
		return (symbolValue * lineMultiplier);
	}
	else{ return 0; }
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
	
	//Render Credits Counter
	labelMaker("Credits", playerCredit, 880, 840);
	//Render Line Counter
	labelMaker("Lines", playerSelectedLine, 580, 840);
	//Render Multiplier Counter
	labelMaker("Multiplier", playerBetMultiplier, 380, 840);


	//Update screen
	SDL_RenderPresent(gRenderer);

}