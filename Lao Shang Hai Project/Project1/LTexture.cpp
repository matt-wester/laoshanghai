#include "LTexture.h"



LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;

}


LTexture::~LTexture()
{
	//Deallocate
	free();

}

bool LTexture::loadFromFile(std::string path, SDL_Renderer* gRenderer)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture * newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		//Create texture from sufrace pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);

	}
	
	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
	
}

bool LTexture::loadFromRenderedText(TTF_Font *gFont, std::string textureText, SDL_Color textColor, SDL_Renderer* gRenderer)
{
	//Get rid of preexisting texture
	free();

	//Render texture surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Creature texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}



	}
	return true;

}


void LTexture::free()
{
	//Free texture if it exsits
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}


void LTexture::render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip)
{
	//Set rendering space
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	
	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;

	}
	
	SDL_RenderCopy(gRenderer,mTexture,clip,&renderQuad);
	
}


void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture
	SDL_SetTextureColorMod(mTexture, red, green, blue);

}


void LTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}



int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}


