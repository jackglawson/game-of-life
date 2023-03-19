#include <SDL2/SDL.h>
#include "display.h"
#include "world.h"

const int PIXEL_SIZE = 7;
const int SCREEN_WIDTH = PIXEL_SIZE * Params::width;
const int SCREEN_HEIGHT = PIXEL_SIZE * Params::height;
const int LINE_THICKNESS = 0;
const int FRAME_RATE_MS = 100;

int display(const std::string& filepath)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Checkerboard", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    World world;
    int epoch = 0;
    bool is_running = true;
    Uint32 last_tick_time = SDL_GetTicks();
    Uint32 current_tick_time;

    while (is_running) {
        current_tick_time = SDL_GetTicks();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                is_running = false;
            }
        }

        if (current_tick_time - last_tick_time >= FRAME_RATE_MS) {
            world = World("test.txt", epoch);
            last_tick_time = current_tick_time;
            epoch ++;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw the grid
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = 0; i < SCREEN_HEIGHT; i += PIXEL_SIZE) {
            SDL_RenderDrawLine(renderer, 0, i, SCREEN_WIDTH, i);
        }
        for (int j = 0; j < SCREEN_WIDTH; j += PIXEL_SIZE) {
            SDL_RenderDrawLine(renderer, j, 0, j, SCREEN_HEIGHT);
        }

        // Draw the pixels
        for (int i = 0; i < Params::height; i++) {
            for (int j = 0; j < Params::width; j++) {
                if (world.grid[i][j] == 0) {
                    SDL_Rect pixel_rect = { j * PIXEL_SIZE + LINE_THICKNESS, i * PIXEL_SIZE + LINE_THICKNESS, PIXEL_SIZE - 2 * LINE_THICKNESS, PIXEL_SIZE - 2 * LINE_THICKNESS };
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderFillRect(renderer, &pixel_rect);
                }
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
