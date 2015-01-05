#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>


static const std::string BASEPATH = SDL_GetBasePath();
static const std::string RESOURCEPATH = BASEPATH + "Resources\\";
static const std::string SAVEPATH = BASEPATH + "Saves\\";
//static const double OPTIMALRESOLUTIONW = 1600;
//static const double OPTIMALRESOLUTIONH = 900;

static int ScreenWidth = 1280;
static int ScreenHeight = 720;

//static double ScreenWidth = 1920;
//static double ScreenHeight = 1080;

static bool fullScreen = false;