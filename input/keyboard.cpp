#include "keyboard.h"

#include <stdio.h>

#include <SDL2/SDL.h>

namespace input {

void Keyboard::ProcessInput() {
  SDL_Event event;

  while (SDL_PollEvent(&event) != 0) {
    switch (event.type) {
      case SDL_QUIT:
        keys[QUIT] = KEY_PRESSED;
        break;
      case SDL_KEYUP:
        ChangeKey(event.key.keysym.sym, KEY_RELEASED);
        break;
      case SDL_KEYDOWN:
        ChangeKey(event.key.keysym.sym, KEY_PRESSED);
        break;
    }
  }
}

void Keyboard::ChangeKey(SDL_Keycode code, KEYSTATE state) {
  switch (code) {
    case SDLK_ESCAPE:
      keys[ESC] = state;
      break;
    case SDLK_SPACE:
      keys[NEXT] = state;
      break;
    case SDLK_UP:
      keys[UP] = state;
      break;
    case SDLK_DOWN:
      keys[DOWN] = state;
      break;
    case SDLK_LEFT:
      keys[LEFT] = state;
      break;
    case SDLK_RIGHT:
      keys[RIGHT] = state;
      break;
    case SDLK_EQUALS:
      keys[ZOOM_IN] = state;
      break;
    case SDLK_MINUS:
      keys[ZOOM_OUT] = state;
      break;
  }
}

void Keyboard::UpdateState() {
  for (int i = 0; i < QUIT; i++) {
    if (keys[i] == KEY_PRESSED) {
      keys[i] = KEY_HELD;
    } else if (keys[i] == KEY_RELEASED) {
      keys[i] = KEY_EMPTY;
    }
  }
}
}
