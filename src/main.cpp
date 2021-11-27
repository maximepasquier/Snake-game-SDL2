#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <chrono>
#include <random>

enum Rotation
{
	up,
	down,
	left,
	right
};

enum Snake_parts
{
	head,
	body_straight,
	body_turn,
	tail,
	empty
};

typedef struct snake
{
	Snake_parts p;
	Rotation r;
} snake;

//*Screen dimension constants
const int ASSETS_SIZE = 40;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int GRID_LINES = SCREEN_WIDTH / ASSETS_SIZE;
const int GRID_COLUMNS = SCREEN_HEIGHT / ASSETS_SIZE;

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
SDL_Surface *gsnaketail = NULL;
SDL_Surface *gfruit = NULL;

SDL_Surface *loadSurface(std::string path);

//* Grid
snake **grid;

//* Generator
unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator(seed);

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
	gsnaketail = loadSurface("./assets/snaketail.bmp");
	if (gsnaketail == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "./snaketail.bmp", SDL_GetError());
		success = false;
	}
	gfruit = loadSurface("./assets/fruit.bmp");
	if (gfruit == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "./fruit.bmp", SDL_GetError());
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
	//* Init grid game
	grid = new snake *[GRID_LINES];
	for (int i = 0; i < GRID_LINES; i++)
	{
		grid[i] = new snake[GRID_COLUMNS];
	}

	//* Set grid game to empty
	for (int i = 0; i < GRID_LINES; i++)
	{
		for (int j = 0; j < GRID_COLUMNS; j++)
		{
			grid[i][j].p = empty;
		}
	}

	//* Init game
	//+ Start game with the snake at a fixes position
	int snake_head_x = GRID_LINES / 2;
	int snake_head_y = GRID_COLUMNS / 2;
	//+ Define the head of the snake, rotation to the top
	grid[snake_head_x][snake_head_y].p = head;
	grid[snake_head_x][snake_head_y].r = up;
	//+ Define the tail of the snake, rotation to the bottom
	grid[snake_head_x][snake_head_y + 1].p = tail;
	grid[snake_head_x][snake_head_y + 1].r = down;

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
							grid[snake_head_x][snake_head_y].p = body_straight;
							snake_head_y--;
							grid[snake_head_x][snake_head_y].p = head;
							break;

						case SDLK_DOWN:
							std::cout << "DOWN" << std::endl;
							grid[snake_head_x][snake_head_y].p = body_straight;
							snake_head_y++;
							grid[snake_head_x][snake_head_y].p = head;
							break;

						case SDLK_LEFT:
							std::cout << "LEFT" << std::endl;
							grid[snake_head_x][snake_head_y].p = body_straight;
							snake_head_x--;
							grid[snake_head_x][snake_head_y].p = head;
							break;

						case SDLK_RIGHT:
							std::cout << "RIGHT" << std::endl;
							grid[snake_head_x][snake_head_y].p = body_straight;
							snake_head_x++;
							grid[snake_head_x][snake_head_y].p = head;
							break;

						default:
							break;
						}
					}
				}
				//*Draw the background
				SDL_BlitSurface(gbackground, NULL, gScreenSurface, NULL);
				/*
				SDL_BlitSurface(gsnakehead, NULL, gScreenSurface, NULL);
				SDL_Rect gomec;
				gomec.x = 0;
				gomec.y = 40;
				SDL_BlitSurface(gsnakebodystraight, NULL, gScreenSurface, &gomec);
				*/
				//* Draw snake
				for (int line = 0; line < GRID_LINES; line++)
				{
					for (int column = 0; column < GRID_COLUMNS; column++)
					{
						if (grid[line][column].p != empty)
						{
							SDL_Rect image_position;
							image_position.x = line * ASSETS_SIZE;
							image_position.y = column * ASSETS_SIZE;
							switch (grid[line][column].p)
							{
							case head:
								SDL_BlitSurface(gsnakehead, NULL, gScreenSurface, &image_position);
								break;
							case body_straight:
								SDL_BlitSurface(gsnakebodystraight, NULL, gScreenSurface, &image_position);
								break;
							case body_turn:
								SDL_BlitSurface(gsnakebodytrun, NULL, gScreenSurface, &image_position);
								break;
							case tail:
								SDL_BlitSurface(gsnaketail, NULL, gScreenSurface, &image_position);
								break;
							default:
								break;
							}
						}
					}
				}
				//*Update the surface
				SDL_UpdateWindowSurface(gWindow);
				SDL_Delay(500);
			}
		}
	}
	//Free resources and close SDL
	close();

	return 0;
}