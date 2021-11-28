#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <chrono>
#include <random>

enum Direction
{
	up,
	down,
	left,
	right
};
/*
enum Snake_parts
{
	head,
	body_straight,
	body_turn,
	tail,
	empty
};
*/

typedef struct snake_part
{
	int id;
} snake_part;

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

SDL_Surface *loadSurface(std::string path);

//* Grid
snake_part **grid;

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

	//+ Background
	gbackground = loadSurface("./assets/background.bmp");
	if (gbackground == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "./background.bmp", SDL_GetError());
		success = false;
	}
	//+ Snake body straight
	gsnakebodystraightUD = loadSurface("./assets/snakebodystraightUD.bmp");
	if (gsnakebodystraightUD == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "./snakebodystraightUD.bmp", SDL_GetError());
		success = false;
	}
	gsnakebodystraightLR = loadSurface("./assets/snakebodystraightLR.bmp");
	if (gsnakebodystraightLR == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "./snakebodystraightLR.bmp", SDL_GetError());
		success = false;
	}
	//+ Snake body trun
	gsnakebodyturnUL = loadSurface("./assets/snakebodyturnUL.bmp");
	if (gsnakebodyturnUL == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "./snakebodyturnUL.bmp", SDL_GetError());
		success = false;
	}
	gsnakebodyturnUR = loadSurface("./assets/snakebodyturnUR.bmp");
	if (gsnakebodyturnUR == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "./snakebodyturnUR.bmp", SDL_GetError());
		success = false;
	}
	gsnakebodyturnDL = loadSurface("./assets/snakebodyturnDL.bmp");
	if (gsnakebodyturnDL == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "./snakebodyturnDL.bmp", SDL_GetError());
		success = false;
	}
	gsnakebodyturnDR = loadSurface("./assets/snakebodyturnDR.bmp");
	if (gsnakebodyturnDR == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "./snakebodyturnDR.bmp", SDL_GetError());
		success = false;
	}
	//+ Snake head
	gsnakeheadU = loadSurface("./assets/snakeheadU.bmp");
	if (gsnakeheadU == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "./snakeheadU.bmp", SDL_GetError());
		success = false;
	}
	gsnakeheadD = loadSurface("./assets/snakeheadD.bmp");
	if (gsnakeheadD == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "./snakeheadD.bmp", SDL_GetError());
		success = false;
	}
	gsnakeheadL = loadSurface("./assets/snakeheadL.bmp");
	if (gsnakeheadL == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "./snakeheadL.bmp", SDL_GetError());
		success = false;
	}
	gsnakeheadR = loadSurface("./assets/snakeheadR.bmp");
	if (gsnakeheadR == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "./snakeheadR.bmp", SDL_GetError());
		success = false;
	}
	//+ Snake tail
	gsnaketailU = loadSurface("./assets/snaketailU.bmp");
	if (gsnaketailU == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "./snaketailU.bmp", SDL_GetError());
		success = false;
	}
	gsnaketailD = loadSurface("./assets/snaketailD.bmp");
	if (gsnaketailD == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "./snaketailD.bmp", SDL_GetError());
		success = false;
	}
	gsnaketailL = loadSurface("./assets/snaketailL.bmp");
	if (gsnaketailL == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "./snaketailL.bmp", SDL_GetError());
		success = false;
	}
	gsnaketailR = loadSurface("./assets/snaketailR.bmp");
	if (gsnaketailR == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "./snaketailR.bmp", SDL_GetError());
		success = false;
	}
	//+ Fruit
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
	grid = new snake_part *[GRID_LINES + 2];
	for (int i = 0; i < GRID_LINES + 2; i++)
	{
		grid[i] = new snake_part[GRID_COLUMNS + 2];
	}

	//* Set grid game to wall
	for (int i = 0; i < GRID_LINES + 2; i++)
	{
		for (int j = 0; j < GRID_COLUMNS + 2; j++)
		{
			grid[i][j].id = -2;
		}
	}

	//* Set grid game to empty
	for (int i = 1; i < GRID_LINES + 1; i++)
	{
		for (int j = 1; j < GRID_COLUMNS + 1; j++)
		{
			grid[i][j].id = 0;
		}
	}

	for (int i = 0; i < GRID_LINES + 2; i++)
	{
		for (int j = 0; j < GRID_COLUMNS + 2; j++)
		{
			std::cout << grid[i][j].id << " ";
		}
		std::cout << std::endl;
	}

	//* Init game
	//+ Snake initial length
	int snake_length = 2;
	//+ Snake head coords
	int snake_head_x = GRID_LINES / 2;
	int snake_head_y = GRID_COLUMNS / 2;
	//+ Define the head of the snake, rotation to the top
	grid[snake_head_x][snake_head_y].id = 1;
	//+ Define the tail of the snake, rotation to the bottom
	grid[snake_head_x + 1][snake_head_y].id = 2;
	//+ Orientation of the snake
	Direction orientation = up;
	//+ Fruit presence
	std::uniform_real_distribution<> fruit_generation(0.0, 1.0);
	std::uniform_int_distribution<> x_coord_generation(0, GRID_LINES);
	std::uniform_int_distribution<> y_coord_generation(0, GRID_COLUMNS);
	bool fruit = false;

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
			bool input = false;
			SDL_Event e;
			while (!quit)
			{
				input = false;
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN)
					{
						if (!input)
						{
							input = true;
							switch (e.key.keysym.sym)
							{
							case SDLK_UP:
								std::cout << "UP" << std::endl;
								if (orientation != down)
								{
									orientation = up;
								}
								break;

							case SDLK_DOWN:
								std::cout << "DOWN" << std::endl;
								if (orientation != up)
								{
									orientation = down;
								}
								break;

							case SDLK_LEFT:
								std::cout << "LEFT" << std::endl;
								if (orientation != right)
								{
									orientation = left;
								}
								break;

							case SDLK_RIGHT:
								std::cout << "RIGHT" << std::endl;
								if (orientation != left)
								{
									orientation = right;
								}
								break;

							default:
								break;
							}
						}
					}
				}
				//*Draw the background
				SDL_BlitSurface(gbackground, NULL, gScreenSurface, NULL);
				//* Generate fruit
				if (!fruit)
				{
					double r = fruit_generation(generator);
					if (r < 0.5)
					{
						//+ Generate a fruit
						int x = x_coord_generation(generator);
						int y = y_coord_generation(generator);
						if (grid[x][y].id == 0)
						{
							//+ Place fruit
							grid[x][y].id = -1;
							fruit = true;
						}
					}
				}
				//* Update snake position
				//+ Move all the body
				for (int line = 1; line < GRID_LINES + 1; line++)
				{
					for (int column = 1; column < GRID_COLUMNS + 1; column++)
					{
						if (grid[line][column].id > 0)
						{
							grid[line][column].id++;
							//+ See if it exceeds the length of the snake
							if (grid[line][column].id > snake_length)
							{
								grid[line][column].id = 0;
							}
						}
					}
				}
				//+ Check orientation
				switch (orientation)
				{
				case up:
					snake_head_y--;
					break;
				case down:
					snake_head_y++;
					break;
				case left:
					snake_head_x--;
					break;
				case right:
					snake_head_x++;
					break;

				default:
					break;
				}
				//+ Move head
				std::cout << snake_head_x << "," << snake_head_y << std::endl;

				if (grid[snake_head_x][snake_head_y].id > 0 || grid[snake_head_x][snake_head_y].id == -2)
				{
					std::cout << "LOST" << std::endl;
					break;
				}
				bool add_fruit = false;
				if (grid[snake_head_x][snake_head_y].id == -1)
				{
					//+ A fruit is present on the head cell
					add_fruit = true;
					fruit = false;
				}
				grid[snake_head_x][snake_head_y].id = 1;

				//* Draw snake
				for (int line = 1; line < GRID_LINES + 1; line++)
				{
					for (int column = 1; column < GRID_COLUMNS + 1; column++)
					{
						if (grid[line][column].id != 0)
						{
							SDL_Rect image_position;
							image_position.x = (line-1) * ASSETS_SIZE;
							image_position.y = (column-1) * ASSETS_SIZE;
							if (grid[line][column].id == -1)
							{
								//+ Fruit on this cell
								SDL_BlitSurface(gfruit, NULL, gScreenSurface, &image_position);
								continue;
							}

							if (grid[line][column].id == 1)
							{
								//+ head part
								switch (orientation)
								{
								case up:
									SDL_BlitSurface(gsnakeheadU, NULL, gScreenSurface, &image_position);
									break;
								case down:
									SDL_BlitSurface(gsnakeheadD, NULL, gScreenSurface, &image_position);
									break;
								case left:
									SDL_BlitSurface(gsnakeheadL, NULL, gScreenSurface, &image_position);
									break;
								case right:
									SDL_BlitSurface(gsnakeheadR, NULL, gScreenSurface, &image_position);
									break;
								default:
									break;
								}
							}
							else if (grid[line][column].id == snake_length)
							{
								//+ tail part
								if (grid[line][column - 1].id == snake_length - 1)
								{
									SDL_BlitSurface(gsnaketailD, NULL, gScreenSurface, &image_position);
								}
								else if (grid[line][column + 1].id == snake_length - 1)
								{
									SDL_BlitSurface(gsnaketailU, NULL, gScreenSurface, &image_position);
								}
								else if (grid[line - 1][column].id == snake_length - 1)
								{
									SDL_BlitSurface(gsnaketailR, NULL, gScreenSurface, &image_position);
								}
								else if (grid[line + 1][column].id == snake_length - 1)
								{
									SDL_BlitSurface(gsnaketailL, NULL, gScreenSurface, &image_position);
								}
							}
							else
							{
								//+ body part
								if (grid[line][column].id - 1 == grid[line][column - 1].id)
								{
									if (grid[line][column].id + 1 == grid[line][column + 1].id)
									{
										SDL_BlitSurface(gsnakebodystraightUD, NULL, gScreenSurface, &image_position);
									}
									else if (grid[line][column].id + 1 == grid[line - 1][column].id)
									{
										SDL_BlitSurface(gsnakebodyturnUL, NULL, gScreenSurface, &image_position);
									}
									else if (grid[line][column].id + 1 == grid[line + 1][column].id)
									{
										SDL_BlitSurface(gsnakebodyturnUR, NULL, gScreenSurface, &image_position);
									}
								}
								else if (grid[line][column].id - 1 == grid[line][column + 1].id)
								{
									if (grid[line][column].id + 1 == grid[line][column - 1].id)
									{
										SDL_BlitSurface(gsnakebodystraightUD, NULL, gScreenSurface, &image_position);
									}
									else if (grid[line][column].id + 1 == grid[line - 1][column].id)
									{
										SDL_BlitSurface(gsnakebodyturnDL, NULL, gScreenSurface, &image_position);
									}
									else if (grid[line][column].id + 1 == grid[line + 1][column].id)
									{
										SDL_BlitSurface(gsnakebodyturnDR, NULL, gScreenSurface, &image_position);
									}
								}
								else if (grid[line][column].id - 1 == grid[line - 1][column].id)
								{
									if (grid[line][column].id + 1 == grid[line + 1][column].id)
									{
										SDL_BlitSurface(gsnakebodystraightLR, NULL, gScreenSurface, &image_position);
									}
									else if (grid[line][column].id + 1 == grid[line][column + 1].id)
									{
										SDL_BlitSurface(gsnakebodyturnDL, NULL, gScreenSurface, &image_position);
									}
									else if (grid[line][column].id + 1 == grid[line][column - 1].id)
									{
										SDL_BlitSurface(gsnakebodyturnUL, NULL, gScreenSurface, &image_position);
									}
								}
								else if (grid[line][column].id - 1 == grid[line + 1][column].id)
								{
									if (grid[line][column].id + 1 == grid[line - 1][column].id)
									{
										SDL_BlitSurface(gsnakebodystraightLR, NULL, gScreenSurface, &image_position);
									}
									else if (grid[line][column].id + 1 == grid[line][column + 1].id)
									{
										SDL_BlitSurface(gsnakebodyturnDR, NULL, gScreenSurface, &image_position);
									}
									else if (grid[line][column].id + 1 == grid[line][column - 1].id)
									{
										SDL_BlitSurface(gsnakebodyturnUR, NULL, gScreenSurface, &image_position);
									}
								}
							}
						}
					}
				}
				if(add_fruit)
				{
					snake_length++;
					add_fruit = false;
				}
				//*Update the surface
				SDL_UpdateWindowSurface(gWindow);
				SDL_Delay(300);
			}
		}
	}
	//Free resources and close SDL
	close();

	return 0;
}