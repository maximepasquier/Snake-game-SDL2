#include "game.hpp"

#define EMPTY 0
#define HEAD 1
#define WALL -2
#define FRUIT -1
#define DELAY 200

game::game()
{
    //* Init generator
    init_random_generation_numbers();

    //* Init grid game
    set_grid();

    //* Init game
    init_game();

    //* SDL game rendering
    game_SDL_render();
}

game::~game()
{
}

bool game::init()
{
    // Initialization flag
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
    if (TTF_Init() < 0)
    {
        std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
        success = false;
    }
    return success;
}

bool game::loadMedia()
{
    // Loading success flag
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

    //* Load ttf
    font_title = TTF_OpenFont("./assets/text.ttf", 128);
    font_button_idle = TTF_OpenFont("./assets/text.ttf", 50);
    font_button_selected = TTF_OpenFont("./assets/text.ttf", 60);
    font_numbers = TTF_OpenFont("./assets/numbers.ttf", 50);
    font_sentence = TTF_OpenFont("./assets/numbers.ttf", 30);
    if (!font_title && !font_button_idle && !font_button_selected)
    {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
    }

    return success;
}

SDL_Surface *game::loadSurface(std::string path)
{
    SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == NULL)
    {
        std::cout << "Unable to load the image " << path << ", " << SDL_GetError();
    }
    return loadedSurface;
}

void game::close()
{
    //*Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //*Quit SDL subsystems
    SDL_Quit();
}

void **game::set_grid()
{
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
            grid[i][j].id = WALL;
        }
    }

    //* Set grid game to empty
    for (int i = 1; i < GRID_LINES + 1; i++)
    {
        for (int j = 1; j < GRID_COLUMNS + 1; j++)
        {
            grid[i][j].id = EMPTY;
        }
    }
}

void game::init_game()
{
    //+ Snake initial length
    snake_length = 2;
    //+ Snake head coords at start
    snake_head_x = GRID_LINES / 2;
    snake_head_y = GRID_COLUMNS - 2;
    //+ Define the head of the snake, rotation to the top
    grid[snake_head_x][snake_head_y].id = HEAD;
    //+ Define the tail of the snake, rotation to the bottom
    grid[snake_head_x + 1][snake_head_y].id = HEAD + 1;
    //+ Orientation of the snake
    orientation = up;
    fruit = false;
    quit_game = false;
    quit_menu = false;
    quit_scores = false;
    quit_save_score = false;
    menu_position = PLAY; // iterator on PLAY
}

void game::game_SDL_render()
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
            menu_loop();
            game_loop();
            save_score_loop();
        }
    }
    //+ Free resources and close SDL
    close();
}

void game::init_random_generation_numbers()
{
    generator.seed(seed);
}

void game::menu_loop()
{
    SDL_Event e;
    while (!quit_menu)
    {
        poll_event_menu(e);
        render_menu();
    }
}

void game::game_loop()
{
    SDL_Event e;
    while (!quit_game)
    {
        poll_event_game(e);
        update_game();
        render_game();
    }
}

void game::scores_loop()
{
    SDL_Event e;
    quit_scores = false;
    while (!quit_scores)
    {
        poll_event_scores(e);
        render_scores();
    }
}

void game::save_score_loop()
{
    SDL_Event e;
    better_score = false;
    read_json_scores();
    char_iterator = 0;
    memset(user_name, 0, 20);
    // user_name[0] = 'a';
    while (!quit_save_score)
    {
        poll_event_save_score(e);
        render_save_score();
    }
    save_score_to_json();
}

void game::save_score_to_json()
{
    if (char_iterator == 0)
    {
        //+ The user didn't enter enything
        strcpy(user_name, "user");
    }
    int number_of_scores = 0;
    int player_score = snake_length - 2;
    std::ifstream scores_json("data/scores.json");
    Json::Reader reader;
    Json::Value obj;
    Json::Value new_score;
    Json::Value all_scores;
    new_score["name"] = user_name;
    new_score["score"] = player_score;
    reader.parse(scores_json, obj); // reader can also read strings
    bool placed = false;
    {
    }
    for (const auto &jv : obj)
    {
        if (player_score > jv["score"].asInt() && !placed)
        {
            //+ Place the new score first
            all_scores.append(new_score);
            number_of_scores++;
            placed = true;
        }
        all_scores.append(jv);
        number_of_scores++;
        if (number_of_scores == 5)
        {
            break;
        }
    }
    //* Write scores
    std::ofstream json_file;
    json_file.open("data/scores.json");
    //+ Empty file
    if (obj.size() == 0)
    {
        all_scores.append(new_score);
    }
    json_file << all_scores.toStyledString() << std::endl;
}

void game::read_json_scores()
{

    int count = 0;
    int number_max_of_scores = 5;
    int player_score = snake_length - 2;
    std::ifstream scores_json("data/scores.json");
    Json::Reader reader;
    Json::Value obj;
    reader.parse(scores_json, obj);

    for (const auto &jv : obj)
    {
        if (player_score > jv["score"].asInt() && count < number_max_of_scores)
        {
            //+ Better score detected
            better_score = true;
        }

        count++;
    }
    //+ There was no score
    if (count == 0)
    {
        //+ Better score detected
        better_score = true;
    }
}

void game::poll_event_save_score(SDL_Event e)
{
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            quit_save_score = true;
        }
        else if (e.type == SDL_KEYDOWN && !better_score)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_RETURN:
                quit_save_score = true;
                break;
            default:
                break;
            }
        }
        else if (e.type == SDL_KEYDOWN && better_score)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_RETURN:
                //+ Save the name
                quit_save_score = true;
                break;
            case SDLK_BACKSPACE:
                if (char_iterator > 0)
                {
                    char_iterator--;
                    memset(user_name + char_iterator, 0, 1);
                }
                break;
            case SDLK_a:
                user_name[char_iterator] = 'a';
                char_iterator++;
                break;
            case SDLK_b:
                user_name[char_iterator] = 'b';
                char_iterator++;
                break;
            case SDLK_c:
                user_name[char_iterator] = 'c';
                char_iterator++;
                break;
            case SDLK_d:
                user_name[char_iterator] = 'd';
                char_iterator++;
                break;
            case SDLK_e:
                user_name[char_iterator] = 'e';
                char_iterator++;
                break;
            case SDLK_f:
                user_name[char_iterator] = 'f';
                char_iterator++;
                break;
            case SDLK_g:
                user_name[char_iterator] = 'g';
                char_iterator++;
                break;
            case SDLK_h:
                user_name[char_iterator] = 'h';
                char_iterator++;
                break;
            case SDLK_i:
                user_name[char_iterator] = 'i';
                char_iterator++;
                break;
            case SDLK_j:
                user_name[char_iterator] = 'j';
                char_iterator++;
                break;
            case SDLK_k:
                user_name[char_iterator] = 'k';
                char_iterator++;
                break;
            case SDLK_l:
                user_name[char_iterator] = 'l';
                char_iterator++;
                break;
            case SDLK_m:
                user_name[char_iterator] = 'm';
                char_iterator++;
                break;
            case SDLK_n:
                user_name[char_iterator] = 'n';
                char_iterator++;
                break;
            case SDLK_o:
                user_name[char_iterator] = 'o';
                char_iterator++;
                break;
            case SDLK_p:
                user_name[char_iterator] = 'p';
                char_iterator++;
                break;
            case SDLK_q:
                user_name[char_iterator] = 'q';
                char_iterator++;
                break;
            case SDLK_r:
                user_name[char_iterator] = 'r';
                char_iterator++;
                break;
            case SDLK_s:
                user_name[char_iterator] = 's';
                char_iterator++;
                break;
            case SDLK_t:
                user_name[char_iterator] = 't';
                char_iterator++;
                break;
            case SDLK_u:
                user_name[char_iterator] = 'u';
                char_iterator++;
                break;
            case SDLK_v:
                user_name[char_iterator] = 'v';
                char_iterator++;
                break;
            case SDLK_w:
                user_name[char_iterator] = 'w';
                char_iterator++;
                break;
            case SDLK_x:
                user_name[char_iterator] = 'x';
                char_iterator++;
                break;
            case SDLK_y:
                user_name[char_iterator] = 'y';
                char_iterator++;
                break;
            case SDLK_z:
                user_name[char_iterator] = 'z';
                char_iterator++;
                break;
            default:
                break;
            }
        }
    }
}

void game::render_save_score()
{
    //* Draw the background
    SDL_BlitSurface(gbackground, NULL, gScreenSurface, NULL);

    SDL_Color color = {255, 0, 170};
    SDL_Color color_selection = {245, 236, 66};
    SDL_Surface *result;

    std::string score_s = std::to_string(snake_length - 2);

    const char *score_c = score_s.c_str();

    char result_c[] = "Your score is : ";
    strcat(result_c, score_c);

    result = TTF_RenderText_Solid(font_numbers, result_c, color);

    SDL_Rect result_position;
    //+ Back button
    result_position.x = (SCREEN_WIDTH - result->w) / 2;
    result_position.y = 100;
    SDL_BlitSurface(result, NULL, gScreenSurface, &result_position);

    if (better_score)
    {
        char sentence[] = "Enter your name : ";
        result = TTF_RenderText_Solid(font_sentence, sentence, color);

        SDL_Rect result_position;
        //+ Back button
        result_position.x = (SCREEN_WIDTH - result->w) / 2;
        result_position.y = 200;
        SDL_BlitSurface(result, NULL, gScreenSurface, &result_position);

        result = TTF_RenderText_Solid(font_sentence, user_name, color);
        SDL_Rect name_position;
        if (char_iterator == 0)
        {
            result_position.x = SCREEN_WIDTH / 2;
        }
        else
        {
            result_position.x = (SCREEN_WIDTH - result->w) / 2;
        }
        result_position.y = 250;
        SDL_BlitSurface(result, NULL, gScreenSurface, &result_position);

        char sentence1[] = "SAVE AND QUIT";

        result = TTF_RenderText_Solid(font_button_selected, sentence1, color_selection);

        //+ Back button
        result_position.x = (SCREEN_WIDTH - result->w) / 2;
        result_position.y = 300;
        SDL_BlitSurface(result, NULL, gScreenSurface, &result_position);
    }
    else
    {
        char sentence[] = "Your score won't reach the leaderboard";

        result = TTF_RenderText_Solid(font_sentence, sentence, color);

        SDL_Rect result_position;
        //+ Back button
        result_position.x = (SCREEN_WIDTH - result->w) / 2;
        result_position.y = 200;
        SDL_BlitSurface(result, NULL, gScreenSurface, &result_position);

        char sentence1[] = "QUIT";

        result = TTF_RenderText_Solid(font_button_selected, sentence1, color_selection);

        //+ Back button
        result_position.x = (SCREEN_WIDTH - result->w) / 2;
        result_position.y = 300;
        SDL_BlitSurface(result, NULL, gScreenSurface, &result_position);
    }

    //* Update the surface
    SDL_UpdateWindowSurface(gWindow);
    //+ Adding delay between frames
    SDL_Delay(DELAY / 10);
}

void game::poll_event_scores(SDL_Event e)
{
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            quit_scores = true;
            quit_menu = true;
            quit_game = true;
            quit_save_score = true;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_RETURN:
                quit_scores = true;
                break;
            default:
                break;
            }
        }
    }
}

void game::render_scores()
{

    //* Draw the background
    SDL_BlitSurface(gbackground, NULL, gScreenSurface, NULL);

    SDL_Color color_selection = {245, 236, 66};
    SDL_Color color = {255, 0, 70};

    int number_max_of_scores = 5;
    std::ifstream scores_json("data/scores.json");
    Json::Reader reader;
    Json::Value obj;
    reader.parse(scores_json, obj);

    SDL_Surface *one_score;
    SDL_Rect one_score_position;
    int initial_height = 50;

    for (const auto &jv : obj)
    {
        char c[40];
        memset(c, 0, 40);
        strcat(c, jv["name"].asCString());
        strcat(c, " : ");
        char integer_string[5];
        sprintf(integer_string, "%d", jv["score"].asInt());
        strcat(c, integer_string);

        one_score = TTF_RenderText_Solid(font_numbers, c, color);
        one_score_position.x = 100;
        one_score_position.y = initial_height;
        SDL_BlitSurface(one_score, NULL, gScreenSurface, &one_score_position);
        initial_height += 50;
    }
    SDL_Surface *back_button;

    back_button = TTF_RenderText_Solid(font_button_selected, "BACK", color_selection);

    SDL_Rect back_button_position;
    //+ Back button
    back_button_position.x = (SCREEN_WIDTH - back_button->w) / 2;
    back_button_position.y = SCREEN_HEIGHT - 100;
    SDL_BlitSurface(back_button, NULL, gScreenSurface, &back_button_position);

    //* Update the surface
    SDL_UpdateWindowSurface(gWindow);
    //+ Adding delay between frames
    SDL_Delay(DELAY / 10);
}

void game::poll_event_menu(SDL_Event e)
{
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            quit_scores = true;
            quit_menu = true;
            quit_game = true;
            quit_save_score = true;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_UP:
                if (menu_position > PLAY)
                {
                    menu_position--;
                }
                break;

            case SDLK_DOWN:
                if (menu_position < QUIT)
                {
                    menu_position++;
                }
                break;
            case SDLK_RETURN:
                if (menu_position == PLAY)
                {
                    quit_menu = true;
                }
                else if (menu_position == SCORES)
                {
                    // quit_menu = true;
                    scores_loop();
                }
                else if (menu_position == QUIT)
                {
                    quit_menu = true;
                    quit_game = true;
                    quit_save_score = true;
                }
                break;
            default:
                break;
            }
        }
    }
}

void game::render_menu()
{
    //* Draw the background
    SDL_BlitSurface(gbackground, NULL, gScreenSurface, NULL);

    int initial_height_of_button = 150;

    SDL_Color color = {255, 0, 70};
    SDL_Color color_selection = {245, 236, 66};
    SDL_Surface *title = TTF_RenderText_Solid(font_title, "SNAKE", color);
    SDL_Surface *game_button, *score_button, *quit_button;

    if (menu_position == PLAY)
    {
        game_button = TTF_RenderText_Solid(font_button_selected, "PLAY", color_selection);
    }
    else
    {
        game_button = TTF_RenderText_Solid(font_button_idle, "PLAY", color);
    }
    if (menu_position == SCORES)
    {
        score_button = TTF_RenderText_Solid(font_button_selected, "SCORES", color_selection);
    }
    else
    {
        score_button = TTF_RenderText_Solid(font_button_idle, "SCORES", color);
    }
    if (menu_position == QUIT)
    {
        quit_button = TTF_RenderText_Solid(font_button_selected, "QUIT", color_selection);
    }
    else
    {
        quit_button = TTF_RenderText_Solid(font_button_idle, "QUIT", color);
    }

    SDL_Rect title_position, game_button_position, score_button_position, quit_button_position;
    //+ Title
    title_position.x = (SCREEN_WIDTH - title->w) / 2;
    title_position.y = 50;
    SDL_BlitSurface(title, NULL, gScreenSurface, &title_position);
    //+ Game button
    game_button_position.x = (SCREEN_WIDTH - game_button->w) / 2;
    game_button_position.y = initial_height_of_button += 50;
    SDL_BlitSurface(game_button, NULL, gScreenSurface, &game_button_position);
    //+ Score button
    score_button_position.x = (SCREEN_WIDTH - score_button->w) / 2;
    score_button_position.y = initial_height_of_button += 50;
    SDL_BlitSurface(score_button, NULL, gScreenSurface, &score_button_position);
    //+ Quit button
    quit_button_position.x = (SCREEN_WIDTH - quit_button->w) / 2;
    quit_button_position.y = initial_height_of_button += 50;
    SDL_BlitSurface(quit_button, NULL, gScreenSurface, &quit_button_position);

    //* Update the surface
    SDL_UpdateWindowSurface(gWindow);
    //+ Adding delay between frames
    SDL_Delay(DELAY / 10);
}

void game::poll_event_game(SDL_Event e)
{
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            quit_scores = true;
            quit_menu = true;
            quit_game = true;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_UP:
                if (!orientations_vector.empty())
                {
                    if (orientations_vector.back() != down)
                    {
                        orientations_vector.push_back(up);
                    }
                }
                else
                {
                    if (orientation != down)
                    {
                        orientations_vector.push_back(up);
                    }
                }
                break;

            case SDLK_DOWN:
                // std::cout << "DOWN" << std::endl;
                if (!orientations_vector.empty())
                {
                    if (orientations_vector.back() != up)
                    {
                        orientations_vector.push_back(down);
                    }
                }
                else
                {
                    if (orientation != up)
                    {
                        orientations_vector.push_back(down);
                    }
                }
                break;

            case SDLK_LEFT:
                // std::cout << "LEFT" << std::endl;
                if (!orientations_vector.empty())
                {
                    if (orientations_vector.back() != right)
                    {
                        orientations_vector.push_back(left);
                    }
                }
                else
                {
                    if (orientation != right)
                    {
                        orientations_vector.push_back(left);
                    }
                }
                break;

            case SDLK_RIGHT:
                // std::cout << "RIGHT" << std::endl;
                if (!orientations_vector.empty())
                {
                    if (orientations_vector.back() != left)
                    {
                        orientations_vector.push_back(right);
                    }
                }
                else
                {
                    if (orientation != left)
                    {
                        orientations_vector.push_back(right);
                    }
                }
                break;

            default:
                break;
            }
        }
    }
}

void game::update_game()
{
    //* Generate fruit
    generate_fruit();

    //* Set orientation
    if (!orientations_vector.empty())
    {
        orientation = orientations_vector[0];
        orientations_vector.erase(orientations_vector.begin());
    }

    //* Update head coords
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

    //* Check if game is lost
    if ((grid[snake_head_x][snake_head_y].id > 0 && grid[snake_head_x][snake_head_y].id != snake_length) || grid[snake_head_x][snake_head_y].id == -2)
    {
        quit_game = true;
        return;
    }

    //* Chack if fruit reached
    if (grid[snake_head_x][snake_head_y].id == FRUIT)
    {
        //+ A fruit is present on the head cell
        snake_length++;
        fruit = false;
    }

    //* Update snake position
    for (int line = 1; line < GRID_LINES + 1; line++)
    {
        for (int column = 1; column < GRID_COLUMNS + 1; column++)
        {
            if (grid[line][column].id > EMPTY)
            {
                grid[line][column].id++;
                //+ See if it exceeds the length of the snake
                if (grid[line][column].id > snake_length)
                {
                    grid[line][column].id = EMPTY;
                }
            }
        }
    }
    //+ Place the head at the new coord
    grid[snake_head_x][snake_head_y].id = HEAD;
}

void game::render_game()
{
    //* Draw the background
    SDL_BlitSurface(gbackground, NULL, gScreenSurface, NULL);

    //* Draw snake
    for (int line = 1; line < GRID_LINES + 1; line++)
    {
        for (int column = 1; column < GRID_COLUMNS + 1; column++)
        {
            if (grid[line][column].id != EMPTY)
            {
                SDL_Rect image_position;
                image_position.x = (line - 1) * ASSETS_SIZE;
                image_position.y = (column - 1) * ASSETS_SIZE;
                if (grid[line][column].id == FRUIT)
                {
                    //+ Fruit on this cell
                    SDL_BlitSurface(gfruit, NULL, gScreenSurface, &image_position);
                    continue;
                }

                if (grid[line][column].id == HEAD)
                {
                    //+ head part on this cell
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
                    //+ tail part on this cell
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
                    //+ body part on this cell
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

    //* Draw score
    SDL_Color color = {255, 0, 70};
    SDL_Surface *score_button;

    std::string score_s = std::to_string(snake_length - 2);

    const char *score_c = score_s.c_str();

    score_button = TTF_RenderText_Solid(font_numbers, score_c, color);

    SDL_Rect score_button_position;
    //+ Back button
    score_button_position.x = 10;
    score_button_position.y = 10;
    SDL_BlitSurface(score_button, NULL, gScreenSurface, &score_button_position);

    //* Update the surface
    SDL_UpdateWindowSurface(gWindow);
    //+ Adding delay between frames
    SDL_Delay(DELAY);
}

void game::generate_fruit()
{
    if (!fruit)
    {
        std::uniform_real_distribution<> fruit_generation(0.0, 1.0);
        std::uniform_int_distribution<> x_coord_generation(0, GRID_LINES);
        std::uniform_int_distribution<> y_coord_generation(0, GRID_COLUMNS);
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
}