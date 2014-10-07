#ifndef APPLICATION_CONSTANTS_H
#define APPLICATION_CONSTANTS_H

#include <SDL_image.h>

namespace Mario 
{
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int FPS = 50;
const int UPDATE_RATE = 1000 / FPS;

const int IMG_FORMAT = IMG_INIT_PNG;

const int STATUS_OK = 0;
const int STATUS_FATAL = -1;

const std::string IMAGES_FOLDER = "images";
const std::string RESOURCE_FOLDER = "resources";
}

#endif APPLICATION_CONSTANTS_H