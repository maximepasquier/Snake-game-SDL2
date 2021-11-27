#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>

//*Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//*Starts up SDL and creates window
bool init();

//*Loads media
bool loadMedia();

//*Frees media and shuts down SDL
void close();

//*The window we'll be rendering to
SDL_Window *gWindow = NULL;

//*The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

//*The image we will load and show on the screen
SDL_Surface *gbackground = NULL;
SDL_Surface *gsnakebodystraight = NULL;
SDL_Surface *gsnakebodytrun = NULL;
SDL_Surface *gsnakehead = NULL;


SDL_Surface *loadSurface(std::string path);

bool init()
{
	//Initialization flag
	bool success = true;

	//*Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//*Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//*Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	gbackground = loadSurface("./assets/background.bmp");
	if (gbackground == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "./background.bmp", SDL_GetError());
		success = false;
	}
	gsnakebodystraight = loadSurface("./assets/snakebodystraight.bmp");
	if (gsnakebodystraight == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "./snakebodystraight.bmp", SDL_GetError());
		success = false;
	}
	gsnakebodytrun = loadSurface("./assets/snakebodyturn.bmp");
	if (gsnakebodytrun == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "./snakebodytrun.bmp", SDL_GetError());
		success = false;
	}
	gsnakehead = loadSurface("./assets/snakehead.bmp");
	if (gsnakehead == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "./snakehead.bmp", SDL_GetError());
		success = false;
	}
	return success;
}

SDL_Surface *loadSurface(std::string path)
{
	SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load the image " << path << ", " << SDL_GetError();
	}
	return loadedSurface;
}

void close()
{
	//*Deallocate surface
	//SDL_FreeSurface(gHelloWorld);
	//gHelloWorld = NULL;

	//*Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//*Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char *args[])
{
	//*Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//*Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			bool quit = false;
			SDL_Event e;
			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym)
						{
						case SDLK_UP:
							std::cout << "UP" << std::endl;
							break;

						case SDLK_DOWN:
							std::cout << "DOWN" << std::endl;
							break;

						case SDLK_LEFT:
							std::cout << "LEFT" << std::endl;
							break;

						case SDLK_RIGHT:
							std::cout << "RIGHT" << std::endl;
							break;

						default:
							break;
						}
					}
				}
				//*Draw the background
				SDL_BlitSurface(gbackground, NULL, gScreenSurface, NULL);
				SDL_BlitSurface(gsnakehead, NULL, gScreenSurface, NULL);
				SDL_Rect gomec;
				gomec.x = 0;
				gomec.y = 40;
				SDL_BlitSurface(gsnakebodystraight, NULL, gScreenSurface, &gomec);

				//*Update the surface
				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}
	//Free resources and close SDL
	close();

	return 0;
}