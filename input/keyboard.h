#include <SDL2/SDL.h>

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

namespace input {

enum KEYSTATE { KEY_EMPTY, KEY_PRESSED, KEY_HELD, KEY_RELEASED };

enum KEY { ESC, NEXT, UP, DOWN, LEFT, RIGHT, ZOOM_IN, ZOOM_OUT, QUIT };

class Keyboard {
 public:
  KEYSTATE keys[QUIT];

  void ProcessInput();
  void UpdateState();

 private:
  void ChangeKey(SDL_Keycode, KEYSTATE);
};
}

#endif  // KEYBOARD_H_
