#include "keyboard.h"

#include <stdio.h>

#include <SDL2/SDL.h>

namespace input {

  void Keyboard::ProcessInput() {
    SDL_Event event;

    while(SDL_PollEvent(&event) != 0) {
      switch (event.type) {
        case SDL_QUIT:
          quit = KEY_PRESSED;
          break;
      }
    }
  }

}
