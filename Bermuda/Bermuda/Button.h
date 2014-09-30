#pragma once
#include "header_loader.h"
class Button
{
public:
	Button(int x, int y, int w, int h, const char* filePath);
	bool IsIn(int mouseX, int mouseY);
	void render(SDL_Renderer* renderer);
	SDL_Rect getRectangle();
	~Button(void);
private:
	SDL_Rect rect;

	int m_x;
	int m_y;
	int m_width;
	int m_height;
	const char* filePath;
};

