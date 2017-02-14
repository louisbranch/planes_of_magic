#include <SDL2/SDL.h>

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

namespace input {

enum KEYSTATE { KEY_EMPTY, KEY_PRESSED, KEY_HELD, KEY_RELEASED };

enum KEY {
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

const int MAX_KEYS = QUIT + 1;

class Keyboard {
 public:
  KEYSTATE keys[MAX_KEYS];
  int x;
  int y;

  void ProcessInput();
  void UpdateState();

 private:
  void ChangeKey(SDL_Keycode, KEYSTATE);
};
}

#endif  // KEYBOARD_H_
