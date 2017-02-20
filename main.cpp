#include <math.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "camera.h"
#include "map.h"
#include "mm_layer.h"

const int FPS = 60;
const char* title = "Worlds";

enum Mode { MenuMode, GameMode };

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
Mode mode = GameMode;

auto input = new Input();
auto cam = new Camera();
auto earth = new Map();
auto land = new Img();
auto water = new Img();

void DrawMenu() {
  if (input->buttons[ESC] == BUTTON_PRESSED) {
    mode = GameMode;
  }

  SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
}

void DrawGame() {
  SDL_GetWindowSize(window, &cam->win_size.w, &cam->win_size.h);

  cam->map_size.w = earth->size.w;
  cam->map_size.h = earth->size.h;

  cam->max_size.w =
      earth->size.w * cam->tile_size / cam->zoom - cam->win_size.w;
  cam->max_size.h =
      earth->size.h * cam->tile_size / cam->zoom - cam->win_size.h;

  double scroll_x = cam->win_size.w * 0.05;
  double scroll_y = cam->win_size.h * 0.05;

  if (input->buttons[ESC] == BUTTON_PRESSED) {
    mode = MenuMode;
  }

  if (input->pos.y < scroll_y || input->buttons[UP] == BUTTON_PRESSED ||
      input->buttons[UP] == BUTTON_HELD) {
    MoveCameraUp(cam);
  }

  if (input->pos.y > (cam->win_size.h - scroll_y) ||
      input->buttons[DOWN] == BUTTON_PRESSED ||
      input->buttons[DOWN] == BUTTON_HELD) {
    MoveCameraDown(cam);
  }

  if (input->pos.x < scroll_x || input->buttons[LEFT] == BUTTON_PRESSED ||
      input->buttons[LEFT] == BUTTON_HELD) {
    MoveCameraLeft(cam);
  }

  if (input->pos.x > (cam->win_size.w - scroll_x) ||
      input->buttons[RIGHT] == BUTTON_PRESSED ||
      input->buttons[RIGHT] == BUTTON_HELD) {
    MoveCameraRight(cam);
  }

  if (input->buttons[ZOOM_IN] == BUTTON_PRESSED) {
    ZoomCameraIn(cam);
  }

  if (input->buttons[ZOOM_OUT] == BUTTON_PRESSED) {
    ZoomCameraOut(cam);
  }

  int w = earth->size.w;
  int h = earth->size.h;

  int start = ClipCamera(cam, &w, &h);

  int size = ceil(cam->tile_size / cam->zoom);

  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
  SDL_RenderClear(renderer);

  SDL_Rect rect = {0, 0, size, size};
  SDL_Rect tile = {0, 0, 50, 50};

  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      Tile t = earth->tiles[start + x];
      tile.x = 0;

      if (t.terrain == OCEAN) {
        SDL_RenderCopy(renderer, water->texture, &tile, &rect);
      } else {
        tile.x = ((t.terrain - 1) % 5) * 50;

        SDL_RenderCopy(renderer, land->texture, &tile, &rect);
      }

      rect.x += size;
    }
    rect.x = 0;
    rect.y += size;
    start += earth->size.w;
  }

  SDL_RenderPresent(renderer);
}

int main(int argc, char* args[]) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_LogSetAllPriority(SDL_LOG_PRIORITY_INFO);

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

  // Load assets
  LoadImg(renderer, land, "assets/imgs/land.png");
  LoadImg(renderer, water, "assets/imgs/water.png");

  // Set input values
  SDL_PumpEvents();
  s32 x, y;

  SDL_GetMouseState(&input->pos.x, &input->pos.y);

  // Set map values
  earth->size.w = 200;
  earth->size.h = 150;
  BuildMap(earth);

  // Set camera values
  cam->tile_size = 50;
  cam->speed = 10;
  cam->min_zoom = 1;
  cam->max_zoom = 3;
  cam->zoom = 1;

  uint32_t delay = 1000 / FPS;

  while (1) {
    uint32_t start = SDL_GetTicks();

    ProcessInput(input);

    if (input->buttons[QUIT] == BUTTON_PRESSED) {
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

    UpdateInputState(input);

    uint32_t now = SDL_GetTicks() - start;

    if (now < delay) {
      SDL_Delay(delay - now);
    }
  }

  // Clean-up before quiting

  SDL_DestroyTexture(land->texture);
  SDL_DestroyTexture(water->texture);

  SDL_DestroyRenderer(renderer);

  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}
