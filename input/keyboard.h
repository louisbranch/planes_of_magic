#ifndef KEYBOARD_H_
#define KEYBOARD_H_

enum KeyState {
  KeyEmpty,
  KeyPressed,
  KeyHeld,
  KeyReleased
};

extern KeyState QuitKey;

void InputProcess();

#endif
