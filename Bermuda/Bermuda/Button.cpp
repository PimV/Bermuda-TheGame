#include "Button.h"
#include "header_loader.h"

Button::Button(int x, int y, int w, int h, const char* filePath)
{
	this->m_x = x;
	this->m_y = y;
	this->m_width = w;
	this->m_height = h;
	this->filePath = filePath;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

}

bool Button::IsIn(int mouseX, int mouseY) {
	if (((mouseX > m_x) && (mouseX < m_x + m_width)) &&
		((mouseY > m_y) && (mouseY < m_y + m_height))) {
			return true;
	} else {
		return false;
	}
}

SDL_Rect Button::getRectangle() {
	return rect;
}

void Button::render(SDL_Renderer* renderer) {
	SDL_Surface* img2 = SDL_LoadBMP(filePath);
	SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, img2);
	SDL_RenderCopy(renderer, texture2, NULL,&rect);

	SDL_DestroyTexture(texture2);
	SDL_FreeSurface(img2);
}

Button::~Button(void)
{

}
