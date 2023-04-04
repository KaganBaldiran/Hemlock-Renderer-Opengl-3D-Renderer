#pragma once
#include "Helper_classes.h"

typedef unsigned int uint;
typedef short int int16;
typedef short unsigned int uint16;

struct GLFWwindow;


#ifndef INITIALIZE
#define INITIALIZE 1

#if INITIALIZE

  
  void WindowSizeRecall(GLFWwindow* window, vec2<int> menu_size);


  GLFWwindow* initializeWindow(int windowwidth, int windowheight, const char* windowname);


  void DeinitializeWindow();






#endif // INITIALIZE

#endif // !1







