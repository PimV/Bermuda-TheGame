#include "NightLayer.h"
#include "LightContainer.h"
#include "GameStateManager.h"
#include "GameTimer.h"

NightLayer::NightLayer()
{
	this->alphaLevel = 0;
	this->lightSourceImage = IMG_Load((RESOURCEPATH + "hole.png").c_str());
	this->blackSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, ScreenWidth, ScreenHeight, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	this->nightLayer = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), blackSurface);

	this->screenRect.x = 0;
	this->screenRect.y = 0;
	this->screenRect.h = ScreenHeight;
	this->screenRect.w = ScreenWidth;
}

NightLayer::~NightLayer() 
{
	SDL_FreeSurface(this->lightSourceImage);
	SDL_FreeSurface(this->blackSurface);
	SDL_DestroyTexture(this->nightLayer);
}

void NightLayer::draw(Camera* camera, MainEntityContainer* mec)
{
	SDL_FillRect(blackSurface, &screenRect, 0xFF000000);

	//Update all animating entities
	//Calculate begin and end chunks for the camera (+1 and -1 to make it just a little bigger than the screen)
	int beginChunkX = floor(camera->getX() / mec->getChunkSize()) - 1;
	int endChunkX = floor((camera->getX() + camera->getWidth()) / mec->getChunkSize()) + 1;
	int beginChunkY = floor(camera->getY() / mec->getChunkSize()) - 1;
	int endChunkY = floor((camera->getY() + camera->getHeight()) / mec->getChunkSize()) + 1;

	//Loop through all chunks
	for (int i = beginChunkY; i <= endChunkY; i++)
	{
		for (int j = beginChunkX; j <= endChunkX; j++)
		{
			//light entities
			std::vector<LightEntity*>* vec = mec->getLightContainer()->getChunk(i, j);
			if (vec != nullptr)
			{
				for (LightEntity* e : *vec)
				{
					if (e != nullptr && e->getShining() == true)
					{
						SDL_Rect sourceRect = { 0, 0, lightSourceImage->w, lightSourceImage->h };
						SDL_Rect destRect = { (e->getX() - camera->getX()) - 120, (e->getY() - camera->getY()) - 120, lightSourceImage->w, lightSourceImage->h };

						drawLightSource(blackSurface, &screenRect, &sourceRect, &destRect);
					}
				}
			}
		}
	}

	SDL_UpdateTexture(this->nightLayer, NULL, blackSurface->pixels, blackSurface->pitch);
	calculateAlpha(nightLayer);
	SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), this->nightLayer, NULL, &screenRect);
}

void NightLayer::drawLightSource(SDL_Surface* surface, SDL_Rect* screenRect, SDL_Rect* sourceRect, SDL_Rect* destRect)
{
	// Make sure our rects stays within bounds
	if (destRect->x < 0)
	{
		sourceRect->x -= destRect->x; // remove the pixels outside of the surface
		sourceRect->w -= sourceRect->x; // shrink to the surface, not to offset fog
		destRect->x = 0;
		destRect->w -= sourceRect->x; // shrink the width to stay within bounds
	}
	if (destRect->y < 0)
	{
		sourceRect->y -= destRect->y; // remove the pixels outside
		sourceRect->h -= sourceRect->y; // shrink to the surface, not to offset fog
		destRect->y = 0;
		destRect->h -= sourceRect->y; // shrink the height to stay within bounds
	}

	int xDistanceFromEdge = (destRect->x + destRect->w) - surface->w;
	if (xDistanceFromEdge > 0) // we're busting
	{
		sourceRect->w -= xDistanceFromEdge;
		destRect->w -= xDistanceFromEdge;
	}
	int yDistanceFromEdge = (destRect->y + destRect->h) - surface->h;
	if (yDistanceFromEdge > 0) // we're busting
	{
		sourceRect->h -= yDistanceFromEdge;
		destRect->h -= yDistanceFromEdge;
	}

	SDL_LockSurface(surface);

	Uint32* destPixels = (Uint32*)surface->pixels;
	Uint32* srcPixels = (Uint32*)lightSourceImage->pixels;

	static bool keepFogRemoved = false;

	for (int x = 0; x < destRect->w; ++x)
	{
		for (int y = 0; y < destRect->h; ++y)
		{
			Uint32* destPixel = destPixels + (y + destRect->y) * surface->w + destRect->x + x;
			Uint32* srcPixel = srcPixels + (y + sourceRect->y) * lightSourceImage->w + sourceRect->x + x;

			unsigned char* destAlpha = (unsigned char*)destPixel + 3; // fetch alpha channel
			unsigned char* srcAlpha = (unsigned char*)srcPixel + 3; // fetch alpha channel
			if (*srcAlpha > *destAlpha)
			{
				continue; // skip this pixel
			}

			*destAlpha = *srcAlpha;
		}
	}

	SDL_UnlockSurface(surface);
}

void NightLayer::calculateAlpha(SDL_Texture* texture)
{
	double p = GameTimer::Instance()->getPercentage();

	// it works but can be improved
	if (p >= 65)
	{
		double i = p - 65;
		double j = (i / 20) * 100;

		alphaLevel = (((250 / 100) * j) <= 250) ? (250 / 100) * j : 250;
	}
	else if (p >= 0 && alphaLevel != 0)
	{
		alphaLevel = (250 / 10) * (10 - p);
	}

	//std::cout << "Day%: " << p << " - alphaLevel: " << alphaLevel << std::endl;
	SDL_SetTextureAlphaMod(texture, static_cast<Uint8>(alphaLevel));
}
