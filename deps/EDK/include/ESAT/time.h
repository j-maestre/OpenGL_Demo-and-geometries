/* Copyright 2015 ESAT. All rights reserved.   #####  #####      #     #####
* Author: Jose L. Hidalgo <jlhidalgo@esat.es>  #      #         # #      #
*                                              ###     ###     #   #     #
* Timming API                                  #          #   #     #    #
*                                              #####  #####  #       #   #
*/

#ifndef ESAT_TIME_H
#define ESAT_TIME_H 1

namespace ESAT {
  // returns time in milliseconds with microsecond preccision
  double Time();


  double RawTime();

  // suspends the execution of the current thread. The time given is in ms.
  // The time suspended is not extremely accurate be careful when calling sleep.
  void Sleep(unsigned int ms);
 }

 #endif // ESAT_TIME_H 