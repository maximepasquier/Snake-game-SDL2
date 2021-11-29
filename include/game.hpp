#ifndef game_hpp
#define game_hpp

#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <chrono>
#include <random>

#include "enumerations.hpp"
#include "structures.hpp"

class game
{
private:
    //*Screen dimension constants
    const int ASSETS_SIZE = 40;
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    const int GRID_LINES = SCREEN_WIDTH / ASSETS_SIZE;
    const int GRID_COLUMNS = SCREEN_HEIGHT / ASSETS_SIZE;
    //*The window we'll be rendering to
    SDL_Window *gWindow = NULL;

    //*The surface contained by the window
    SDL_Surface *gScreenSurface = NULL;

    //*The image we will load and show on the screen
    SDL_Surface *gbackground = NULL;

    SDL_Surface *gsnakebodystraightUD = NULL;
    SDL_Surface *gsnakebodystraightLR = NULL;

    SDL_Surface *gsnakebodyturnUR = NULL;
    SDL_Surface *gsnakebodyturnUL = NULL;
    SDL_Surface *gsnakebodyturnDR = NULL;
    SDL_Surface *gsnakebodyturnDL = NULL;

    SDL_Surface *gsnakeheadU = NULL;
    SDL_Surface *gsnakeheadD = NULL;
    SDL_Surface *gsnakeheadL = NULL;
    SDL_Surface *gsnakeheadR = NULL;

    SDL_Surface *gsnaketailU = NULL;
    SDL_Surface *gsnaketailD = NULL;
    SDL_Surface *gsnaketailL = NULL;
    SDL_Surface *gsnaketailR = NULL;

    SDL_Surface *gfruit = NULL;

    //* Grid
    snake_part **grid;

    //* Generator
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();

public:
    game();
    ~game();
    bool init();
    bool loadMedia();
    void close();
    SDL_Surface *loadSurface(std::string path);
};

#endif