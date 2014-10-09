#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

static const std::string BASEPATH = SDL_GetBasePath();
static const std::string RESOURCEPATH = BASEPATH + "Resources\\";
static int ScreenWidth = 1600;
static int ScreenHeight = 900;