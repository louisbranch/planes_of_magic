#include "keyboard.h"

#include <stdio.h>

#include <SDL2/SDL.h>

namespace input {

SDL_Keycode key_mapping[MAX_KEYS] = {SDLK_ESCAPE, SDLK_SPACE, SDLK_UP,
                                     SDLK_DOWN,   SDLK_LEFT,  SDLK_RIGHT,
                                     SDLK_EQUALS, SDLK_MINUS};

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
    }
  }
}

void Keyboard::UpdateState() {
  for (int i = 0; i < MAX_KEYS; i++) {
    if (keys[i] == KEY_PRESSED) {
      keys[i] = KEY_HELD;
    } else if (keys[i] == KEY_RELEASED) {
      keys[i] = KEY_EMPTY;
    }
  }
}
}
