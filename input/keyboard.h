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

  void ProcessInput();
};
}

#endif  // KEYBOARD_H_
