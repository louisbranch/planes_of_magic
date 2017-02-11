#include <SDL2/SDL.h>
#include <stdio.h>

const int FPS = 60;
const char* title = "Worlds";

enum Mode { MenuMode, GameMode };

SDL_Window* window = NULL;
SDL_Renderer* renderer =  NULL;
Mode mode = GameMode;

int main(int argc, char* args[]) {

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  int flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_WINDOW_FULLSCREEN_DESKTOP;

  window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, flags);

  if (window == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

  renderer = SDL_CreateRenderer(window, -1, flags);

  if (renderer == NULL) {
    printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  uint32_t delay = 1000/FPS;

  while(1) {
    uint32_t start = SDL_GetTicks();

    SDL_Event event;

    while(SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT) {
        goto quit;
      }
    }

    SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    uint32_t now = SDL_GetTicks() - start;

    if (now < delay) {
      SDL_Delay(delay - now);
    }
  }

quit:

  SDL_DestroyRenderer(renderer);

  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}
