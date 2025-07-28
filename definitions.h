#ifndef DEFINITIONS
#define DEFINITIONS

#include "raylib.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define MAX_NUM_CIRCLES 500
#define RADIUS 10
#define LABEL_OFFSET_X 7
#define LABEL_OFFSET_Y 30
#define SPLINE_SAMPLE_RATE 0.1
#define SPLINE_ALPHA 0.5

typedef struct Circle {
  Vector2 center;
  int radius;
  bool selected;
} Circle;

#endif