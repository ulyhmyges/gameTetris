#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "utils.h"

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

static SDL_Texture *texture = NULL;
static int texture_width = 0;
static int texture_height = 0;

SDL_Surface *surface = NULL;

static int W_Y = 480;
static int W_X = 240;
static int SIZE_BLOCK = 8;
static int FACTOR = 3;

static std::vector<Point> shape; // array
Tetris game = Tetris();

// CALL FIRST
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{   
    char *png_path = NULL;
    game.add(game.block());

    /* Create the window */
    if (!SDL_CreateWindowAndRenderer("Hello World", W_X, W_Y, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_asprintf(&png_path, "%s../../sprites/7.png", SDL_GetBasePath());  /* allocate a string of the full file path */
    surface = SDL_LoadPNG(png_path);
    if (!surface) {
        SDL_Log("Couldn't load png: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_free(png_path);  /* done with this, the file is loaded. */

    texture_width = surface->w;
    texture_height = surface->h;

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_Log("Couldn't create static texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_DestroySurface(surface);  /* done with this, the texture has a copy of the pixels now. */

    return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if ((event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_Q)||
        event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }

    // MOVE LEFT
    if (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_LEFT 
        && game.current().canMoveLeft(Tetrimino::STEP)
        && game.current().canMove(game.m_grid, 'l')){
            game.current().moveLeft(game.m_grid);
            // game.current().m_pos.x -= Tetrimino::STEP;
            // game.current().update(game.current().m_pos, game.current().m_window);
    }

    // MOVE RIGHT
    if (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_RIGHT 
        && game.current().canMoveRight(W_X - Tetrimino::STEP)
        && game.current().canMove(game.m_grid, 'r')) {
            game.current().moveRight(game.m_grid);
        // game.current().m_pos.x+= Tetrimino::STEP;
        // game.current().update(game.current().m_pos, game.current().m_window);
    }

    // MOVE DOWN
    if (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_DOWN 
        && game.current().canMoveDown(W_Y - Tetrimino::STEP)
        && game.current().canMove(game.m_grid, 'd')) {
            game.current().moveDown(game.m_grid);
        // game.current().m_pos.y+= Tetrimino::STEP;
        // game.current().update(game.current().m_pos, game.current().m_window); 
    }

    return SDL_APP_CONTINUE;
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    SDL_FRect dst;
    shape = game.current().getShape();
    
    const char* message = "Hi!";
    int w = 0;
    int h = 0;
    float x;
    float y;
   
    /* Center the message and scale it up */
    SDL_GetRenderOutputSize(renderer, &w, &h);
    x = ((w ) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * SDL_strlen(message)) / 2;
    y = ((h ) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE) / 2;

    SDL_SetRenderDrawColorFloat(renderer, 0.5, 0, 0, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */
        /* clear the window to the draw color. */
    SDL_RenderClear(renderer);
   
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDebugText(renderer, x, y, message);

    // tetriminos
    for (std::unique_ptr<Tetrimino> const& t : game.m_tetriminos){
        // TODO change shape into Vector
        // loop with vector.size()
        
        
        shape = t->getShape();
        for (int i = 0; i < 4; ++i) {
            dst.x = static_cast<float>(shape[i].x);
            dst.y = static_cast<float>(shape[i].y);
            dst.h = static_cast<float>(texture_height)* Tetrimino::FACTOR;
            dst.w = static_cast<float>(texture_width) * Tetrimino::FACTOR;
            SDL_RenderTexture(renderer, texture, NULL, &dst);
        }
    }
     
    SDL_RenderPresent(renderer);

    // EVERY SECOND MOVE DOWN
    static Uint64 last_time = 0;
    Uint32 time_now = SDL_GetTicks();
    if (time_now - last_time >= 1000){
        last_time = time_now;

        if (game.current().canMoveDown(W_Y - Tetrimino::STEP) && (game.current().canMove(game.m_grid, 'd'))){
                // game.current().m_pos.y+= Tetrimino::STEP;
                // game.current().update(game.current().m_pos, game.current().m_window);
                game.current().moveDown(game.m_grid);
        } else {
            game.updateGrid();
            game.add(game.block(Type::J));
        }
    }
 
    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    SDL_Log("%s, rand: %f, x: %d, y: %d", "bye bye!", SDL_randf(), game.current().m_pos.x, game.current().m_pos.y);
    SDL_Log("x=%d, y=%d", shape[3].x, shape[3].y);
}