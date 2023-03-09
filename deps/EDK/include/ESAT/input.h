/* Copyright 2014 ESAT. All rights reserved.    #####  #####      #     #####
 * Author: Jose L. Hidalgo <jlhidalgo@esat.es>  #      #         # #      #
 *                                              ###     ###     #   #     #
 * Input (keyboard, mouse, etc...)              #          #   #     #    #
 *                                              #####  #####  #       #   #
 */

#ifndef ESAT_INPUT_H
#define ESAT_INPUT_H 1z

namespace ESAT {

  // -- Keyboard ----------------------------------------

  enum SpecialKey {
    kSpecialKey_None = 0,
    kSpecialKey_Space,
    kSpecialKey_Enter,
    kSpecialKey_Tab,
    kSpecialKey_Escape,
    kSpecialKey_Delete,
	kSpecialKey_Backspace,
    kSpecialKey_Up,
    kSpecialKey_Down,
    kSpecialKey_Right,
    kSpecialKey_Left,
    kSpecialKey_Control,
    kSpecialKey_Alt,
    kSpecialKey_Shift,
    kSpecialKey_Keypad_0,
    kSpecialKey_Keypad_1,
    kSpecialKey_Keypad_2,
    kSpecialKey_Keypad_3,
    kSpecialKey_Keypad_4,
    kSpecialKey_Keypad_5,
    kSpecialKey_Keypad_6,
    kSpecialKey_Keypad_7,
    kSpecialKey_Keypad_8,
    kSpecialKey_Keypad_9,
    kSpecialKey_F1,
    kSpecialKey_F2,
    kSpecialKey_F3,
    kSpecialKey_F4,
    kSpecialKey_F5,
    kSpecialKey_F6,
    kSpecialKey_F7,
    kSpecialKey_F8,
    kSpecialKey_F9,
    kSpecialKey_F10,
    kSpecialKey_F11,
    kSpecialKey_F12,
  };

  // Key pressed
  bool IsKeyPressed(char key);
  // Key pressed in this frame
  bool IsKeyDown(char key);
  // Key released in this frame
  bool IsKeyUp(char key);

  // SpecialKey pressed
  bool IsSpecialKeyPressed(SpecialKey key);
  // SpecialKey pressed in this frame
  bool IsSpecialKeyDown(SpecialKey key);
  // SpecialKey released in this frame
  bool IsSpecialKeyUp(SpecialKey key);

  // Returns keys pressed in sequence, if there is no keys left
  // it will return 0. The amount of keys recorded without calling
  // this method is limited.
  char GetNextPressedKey();

  // cleans the input buffer
  void ResetBufferdKeyInput();

  // -- Mouse ---------------------------------------------
  double MousePositionX();
  double MousePositionY();
  double MouseWheelX();
  double MouseWheelY();

  // Returns true if currently the button is pressed
  bool MouseButtonPressed(int button_id);
  // Returns true the frame the button is pressed down, false otherwise
  bool MouseButtonDown(int button_id);
  // Returns true the frame the button is released, false otherwise
  bool MouseButtonUp(int button_id);

} /* ESAT */

#endif
