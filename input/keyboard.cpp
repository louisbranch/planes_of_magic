#include <SDL2/SDL.h>
#include <stdio.h>
#include "keyboard.h"

KeyState QuitKey;

void InputProcess() {
  SDL_Event event;

  while(SDL_PollEvent(&event) != 0) {
    switch (event.type) {
      case SDL_QUIT:
        QuitKey = KeyPressed;
        break;
    }
  }
}
