#include <SDL2/SDL.h>

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

namespace input {

enum KEYSTATE {
  KEY_EMPTY = 0,
  KEY_PRESSED = 1,
  KEY_HELD = 2,
  KEY_RELEASED = 3
};

class Keyboard {
 public:
  KEYSTATE quit;
  KEYSTATE esc;
  KEYSTATE next_turn;
  KEYSTATE up;
  KEYSTATE down;
  KEYSTATE left;
  KEYSTATE right;
  KEYSTATE zoom_in;
  KEYSTATE zoom_out;

  void ProcessInput();
  void UpdateState();

 private:
  void ChangeKey(SDL_Keycode, KEYSTATE);
};
}

#endif  // KEYBOARD_H_
