#include "keyboard.h"

#include <stdio.h>

#include <SDL2/SDL.h>

namespace input {

void Keyboard::ProcessInput() {
  SDL_Event event;

  while (SDL_PollEvent(&event) != 0) {
    switch (event.type) {
      case SDL_QUIT:
        quit = KEY_PRESSED;
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
      esc = state;
      break;
    case SDLK_SPACE:
      next_turn = state;
      break;
    case SDLK_UP:
      up = state;
      break;
    case SDLK_DOWN:
      down = state;
      break;
    case SDLK_LEFT:
      left = state;
      break;
    case SDLK_RIGHT:
      right = state;
      break;
    case SDLK_EQUALS:
      zoom_in = state;
      break;
    case SDLK_MINUS:
      zoom_out = state;
      break;
  }
}

void Keyboard::UpdateState() {
  if (esc == KEY_PRESSED) {
    esc = KEY_HELD;
  } else if (esc == KEY_RELEASED) {
    esc = KEY_EMPTY;
  }
  if (next_turn == KEY_PRESSED) {
    next_turn = KEY_HELD;
  } else if (next_turn == KEY_RELEASED) {
    next_turn = KEY_EMPTY;
  }
  if (up == KEY_PRESSED) {
    up = KEY_HELD;
  } else if (up == KEY_RELEASED) {
    up = KEY_EMPTY;
  }
  if (down == KEY_PRESSED) {
    down = KEY_HELD;
  } else if (down == KEY_RELEASED) {
    down = KEY_EMPTY;
  }
  if (left == KEY_PRESSED) {
    left = KEY_HELD;
  } else if (left == KEY_RELEASED) {
    left = KEY_EMPTY;
  }
  if (right == KEY_PRESSED) {
    right = KEY_HELD;
  } else if (right == KEY_RELEASED) {
    right = KEY_EMPTY;
  }
  if (zoom_in == KEY_PRESSED) {
    zoom_in = KEY_HELD;
  } else if (zoom_in == KEY_RELEASED) {
    zoom_in = KEY_EMPTY;
  }
  if (zoom_out == KEY_PRESSED) {
    zoom_out = KEY_HELD;
  } else if (zoom_out == KEY_RELEASED) {
    zoom_out = KEY_EMPTY;
  }
}
}
