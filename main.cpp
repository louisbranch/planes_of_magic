#include <stdio.h>

#include <SDL2/SDL.h>

#include "camera/camera.h"
#include "input/keyboard.h"

const int FPS = 60;
const char* title = "Worlds";

enum Mode { MenuMode, GameMode };

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
Mode mode = GameMode;
input::Keyboard* keyboard = new input::Keyboard();
camera::Camera* cam = new camera::Camera();

void DrawMenu() {
  if (keyboard->keys[input::ESC] == input::KEY_PRESSED) {
    mode = GameMode;
  }
  SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
}

void DrawGame() {
  SDL_GetWindowSize(window, &cam->w, &cam->h);


  if (keyboard->keys[input::ESC] == input::KEY_PRESSED) {
    mode = MenuMode;
  }

  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
}

int main(int argc, char* args[]) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  uint32_t flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC |
                   SDL_WINDOW_FULLSCREEN_DESKTOP;

  window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, 0, 0, flags);

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

  // Set default camera values
  cam->tile_size = 50;
  cam->speed = 10;
  cam->min_zoom = 1;
  cam->max_zoom = 3;
  cam->zoom = 1;

  uint32_t delay = 1000 / FPS;

  while (1) {
    uint32_t start = SDL_GetTicks();

    keyboard->ProcessInput();

    if (keyboard->keys[input::QUIT] == input::KEY_PRESSED) {
      break;
    }

    switch (mode) {
      case MenuMode:
        DrawMenu();
        break;
      case GameMode:
        DrawGame();
        break;
    }

    keyboard->UpdateState();

    uint32_t now = SDL_GetTicks() - start;

    if (now < delay) {
      SDL_Delay(delay - now);
    }
  }

  SDL_DestroyRenderer(renderer);

  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}
