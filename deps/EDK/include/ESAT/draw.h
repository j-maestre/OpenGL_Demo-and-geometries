/* Copyright 2014 ESAT. All rights reserved.    #####  #####      #     #####
 * Author: Jose L. Hidalgo <jlhidalgo@esat.es>  #      #         # #      #
 *                                              ###     ###     #   #     #
 * Drawing commands                             #          #   #     #    #
 *                                              #####  #####  #       #   #
 */

#ifndef ESAT_DRAW_H
#define ESAT_DRAW_H 1

namespace ESAT {

  // Call this before start sending drawing commands
  void DrawBegin();
  // Call this after all drawing is done
  void DrawEnd();

  void DrawSetStrokeColor(
      unsigned char R,
      unsigned char G, 
      unsigned char B,
      unsigned char Alpha = 255);

  void DrawSetFillColor(
      unsigned char R,
      unsigned char G,
      unsigned char B,
      unsigned char Alpha = 255);

  void DrawClear(
      unsigned char R,
      unsigned char G,
      unsigned char B,
      unsigned char Alpha = 255);

  void DrawLine(float x1,float y1,float x2,float y2);

  // Draws a continuous line (path)
  void DrawPath(float *pairs_of_points, int num_points);

  void DrawSolidPath(float *pairs_of_points, int num_points, bool stroke = true);

  void DrawSetTextFont(const char *name);
  void DrawSetTextSize(float size);
  void DrawSetTextBlur(float blur_radius);
  void DrawText(float x, float y, const char *text);

} /* ESAT */

#endif