#ifndef DEFINITIONS
#define DEFINITIONS

#include "raylib.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define MAX_NUM_CIRCLES 20
#define SPLINE_SAMPLE_RATE 0.07
#define SPLINE_ALPHA 0.5

typedef struct Circle {
  Vector2 center;
  int radius;
  bool selected;
} Circle;

#endif