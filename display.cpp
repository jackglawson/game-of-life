#include <SDL2/SDL.h>
#include <iostream>
#include "gif.h"
#include "display.h"
#include "world.h"

const int SCREEN_WIDTH = Params::display_pixel_size * Params::width;
const int SCREEN_HEIGHT = Params::display_pixel_size * Params::height;


int create_gif(const std::string& in_filepath, const char* out_filepath){
    World world;
    uint8_t image[ SCREEN_WIDTH * SCREEN_HEIGHT * 4 ];

    GifWriter writer;
    GifBegin(&writer, out_filepath, SCREEN_WIDTH, SCREEN_HEIGHT, Params::display_frame_rate_ms);

    for (int epoch = 0; epoch < Params::epochs; epoch++){
        world = World(in_filepath, epoch);
        for (int y = 0; y < SCREEN_HEIGHT; ++y) {
            for (int x = 0; x < SCREEN_WIDTH; ++x) {
                int i = y / Params::display_pixel_size;
                int j = x / Params::display_pixel_size;
                image[(y * SCREEN_WIDTH + x) * 4 + 0] = (1 - world.grid[i][j]) * 255;
                image[(y * SCREEN_WIDTH + x) * 4 + 1] = (1 - world.grid[i][j]) * 255;
                image[(y * SCREEN_WIDTH + x) * 4 + 2] = (1 - world.grid[i][j]) * 255;
            }
        }
        GifWriteFrame( &writer, image, SCREEN_WIDTH, SCREEN_HEIGHT, Params::display_frame_rate_ms / 10, 8, true );
    }

    GifEnd( &writer );

    return 0;
}


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

    while ((is_running) && (epoch < Params::epochs)) {
        current_tick_time = SDL_GetTicks();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                is_running = false;
            }
        }

        if (current_tick_time - last_tick_time >= Params::display_frame_rate_ms) {
            world = World(filepath, epoch);
            last_tick_time = current_tick_time;

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            for (int i = 0; i < Params::height; i++) {
                for (int j = 0; j < Params::width; j++) {
                    if (world.grid[i][j] == 0) {
                        SDL_Rect pixel_rect = {j * Params::display_pixel_size, i * Params::display_pixel_size, Params::display_pixel_size, Params::display_pixel_size};
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                        SDL_RenderFillRect(renderer, &pixel_rect);
                    }
                }
            }

            SDL_RenderPresent(renderer);

            epoch++;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
