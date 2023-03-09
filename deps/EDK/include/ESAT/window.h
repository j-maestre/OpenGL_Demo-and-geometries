/* Copyright 2014 ESAT. All rights reserved.    #####  #####      #     #####
 * Author: Jose L. Hidalgo <jlhidalgo@esat.es>  #      #         # #      #
 *                                              ###     ###     #   #     #  
 * Window API (main graphics display)           #          #   #     #    #
 *                                              #####  #####  #       #   #
 */

#ifndef ESAT_WINDOW_H
#define ESAT_WINDOW_H 1

namespace ESAT {

  // Initializes the main graphical window
  void WindowInit(unsigned int width, unsigned int height);

  // This function must be called and the end of the frame, all graphical
  // commands will be executed
  void WindowFrame();

  // Destroys the graphical window
  void WindowDestroy();

  // returns true if the window is opened, false if the window was closed
  bool WindowIsOpened();

  unsigned int WindowHeight();
  unsigned int WindowWidth();

  // must be declared by the user in order to use this library
  int main(int, char **);

  void WindowSetMouseVisibility(bool visible);

} /* ESAT */

#endif