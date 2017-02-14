#include "keyboard.h"

#include <stdio.h>

#include <SDL2/SDL.h>

namespace input {

SDL_Keycode key_mapping[MAX_KEYS] = {
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

void Keyboard::ProcessInput() {
  SDL_Event event;
  int sym;

  while (SDL_PollEvent(&event) != 0) {
    switch (event.type) {
      case SDL_QUIT:
        keys[QUIT] = KEY_PRESSED;
        break;
      case SDL_KEYUP:
        sym = event.key.keysym.sym;
        for (int i = 0; i < MAX_KEYS; i++) {
          if (key_mapping[i] == sym && keys[i] == KEY_HELD) {
            keys[i] = KEY_EMPTY;
          }
        }
        break;
      case SDL_KEYDOWN:
        sym = event.key.keysym.sym;
        for (int i = 0; i < MAX_KEYS; i++) {
          if (key_mapping[i] == sym && keys[i] == KEY_EMPTY) {
            keys[i] = KEY_PRESSED;
          }
        }
        break;
      case SDL_MOUSEMOTION:
        x = event.motion.x;
        y = event.motion.y;
        break;
      case SDL_MOUSEBUTTONDOWN:
        sym = event.button.button;
        for (int i = 0; i < MAX_KEYS; i++) {
          if (key_mapping[i] == sym && keys[i] == KEY_EMPTY) {
            keys[i] = KEY_PRESSED;
          }
        }
        break;
      case SDL_MOUSEBUTTONUP:
        sym = event.button.button;
        for (int i = 0; i < MAX_KEYS; i++) {
          if (key_mapping[i] == sym && keys[i] == KEY_HELD) {
            keys[i] = KEY_EMPTY;
          }
        }
        break;
      case SDL_MOUSEWHEEL:
        if (event.motion.x > 0 && keys[ZOOM_IN] == KEY_EMPTY) {
          keys[ZOOM_IN] = KEY_PRESSED;
        }

        if (event.motion.x < 0 && keys[ZOOM_OUT] == KEY_EMPTY) {
          keys[ZOOM_OUT] = KEY_PRESSED;
        }
        break;
    }
  }
}

void Keyboard::UpdateState() {
  if (keys[ZOOM_IN] == KEY_PRESSED) {
    keys[ZOOM_IN] = KEY_EMPTY;
  }

  if (keys[ZOOM_OUT] == KEY_PRESSED) {
    keys[ZOOM_OUT] = KEY_EMPTY;
  }

  for (int i = 0; i < MAX_KEYS; i++) {
    if (keys[i] == KEY_PRESSED) {
      keys[i] = KEY_HELD;
    } else if (keys[i] == KEY_RELEASED) {
      keys[i] = KEY_EMPTY;
    }
  }
}
}
