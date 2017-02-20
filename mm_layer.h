#ifndef MM_LAYER_H_
#define MM_LAYER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "platform.h"

struct Img {
  Size size;
  SDL_Texture* texture;
};

enum BUTTON_STATE {
  BUTTON_EMPTY,
  BUTTON_PRESSED,
  BUTTON_HELD,
  BUTTON_RELEASED
};

enum BUTTON {
  ESC,
  SELECT,
  ACTION,
  HOLD,
  NEXT,
  UP,
  DOWN,
  LEFT,
  RIGHT,
  ZOOM_IN,
  ZOOM_OUT,
  QUIT
};

const int MAX_BUTTONS = QUIT + 1;

SDL_Keycode key_mapping[MAX_BUTTONS] = {
    SDLK_ESCAPE,        // ESC
    SDL_BUTTON_LEFT,    // SELECT
    SDL_BUTTON_RIGHT,   // ACTION
    SDL_BUTTON_MIDDLE,  // HOLD
    SDLK_SPACE,         // NEXT
    SDLK_UP,            // UP
    SDLK_DOWN,          // DOWN
    SDLK_LEFT,          // LEFT
    SDLK_RIGHT,         // RIGHT
    SDLK_EQUALS,        // ZOOM_OUT
    SDLK_MINUS          // ZOOM_IN
};

struct Input {
  BUTTON_STATE buttons[MAX_BUTTONS];
  Point2D pos;
};

inline void LoadImg(SDL_Renderer* renderer, Img* img, const char* file) {
  SDL_Surface* image = IMG_Load(file);

  if (image == NULL) {
    printf("error loading image %s", file);
  }

  img->texture = SDL_CreateTextureFromSurface(renderer, image);

  if (img->texture == NULL) {
    printf("error loading texture %s", file);
  }

  if (SDL_QueryTexture(img->texture, NULL, NULL, &img->size.w, &img->size.h) <
      0) {
    printf("error querying texture %s", file);
  }

  SDL_FreeSurface(image);
}

inline void ProcessInput(Input* input) {
  SDL_Event event;
  s32 sym;

  while (SDL_PollEvent(&event) != 0) {
    switch (event.type) {
      case SDL_QUIT:
        input->buttons[QUIT] = BUTTON_PRESSED;
        break;
      case SDL_KEYUP:
        sym = event.key.keysym.sym;
        for (int i = 0; i < MAX_BUTTONS; i++) {
          if (key_mapping[i] == sym && input->buttons[i] == BUTTON_HELD) {
            input->buttons[i] = BUTTON_EMPTY;
          }
        }
        break;
      case SDL_KEYDOWN:
        sym = event.key.keysym.sym;
        for (int i = 0; i < MAX_BUTTONS; i++) {
          if (key_mapping[i] == sym && input->buttons[i] == BUTTON_EMPTY) {
            input->buttons[i] = BUTTON_PRESSED;
          }
        }
        break;
      case SDL_MOUSEMOTION:
        input->pos.x = event.motion.x;
        input->pos.y = event.motion.y;
        break;
      case SDL_MOUSEBUTTONDOWN:
        sym = event.button.button;
        for (int i = 0; i < MAX_BUTTONS; i++) {
          if (key_mapping[i] == sym && input->buttons[i] == BUTTON_EMPTY) {
            input->buttons[i] = BUTTON_PRESSED;
          }
        }
        break;
      case SDL_MOUSEBUTTONUP:
        sym = event.button.button;
        for (int i = 0; i < MAX_BUTTONS; i++) {
          if (key_mapping[i] == sym && input->buttons[i] == BUTTON_HELD) {
            input->buttons[i] = BUTTON_EMPTY;
          }
        }
        break;
      case SDL_MOUSEWHEEL:
        if (event.motion.x > 0 && input->buttons[ZOOM_IN] == BUTTON_EMPTY) {
          input->buttons[ZOOM_IN] = BUTTON_PRESSED;
        }

        if (event.motion.x < 0 && input->buttons[ZOOM_OUT] == BUTTON_EMPTY) {
          input->buttons[ZOOM_OUT] = BUTTON_PRESSED;
        }
        break;
    }
  }
}

inline void UpdateInputState(Input* input) {
  if (input->buttons[ZOOM_IN] == BUTTON_PRESSED) {
    input->buttons[ZOOM_IN] = BUTTON_EMPTY;
  }

  if (input->buttons[ZOOM_OUT] == BUTTON_PRESSED) {
    input->buttons[ZOOM_OUT] = BUTTON_EMPTY;
  }

  for (int i = 0; i < MAX_BUTTONS; i++) {
    if (input->buttons[i] == BUTTON_PRESSED) {
      input->buttons[i] = BUTTON_HELD;
    } else if (input->buttons[i] == BUTTON_RELEASED) {
      input->buttons[i] = BUTTON_EMPTY;
    }
  }
}

#endif  // MM_LAYER_H_
