#ifndef DEFINITIONS
#define DEFINITIONS

#include "raylib.h"

#define WINDOW_WIDTH		800
#define WINDOW_HEIGHT		600
#define MAX_NUM_CIRCLES		20
#define RADIUS				10
#define LABEL_OFFSET_X		7
#define LABEL_OFFSET_Y		30
#define SPLINE_SAMPLE_RATE	1000
#define SPLINE_ALPHA		0.5

enum Errors {
	NULL_ARRAY_SIZE		= 10,
	NULL_ARRAY_POINTER	= 20,
	NULL_BUFFER			= 30
};

struct Circle {
    Vector2 center;
    bool selected;
};

#endif