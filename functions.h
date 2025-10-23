#ifndef FUNCTIONS
#define FUNCTIONS

#include "definitions.h"

/*
Reset the number of circles, effectively resetting the array holding the circles

@param int*             Variable holding the size of the array passed
*/
void resetAllCircles(int* circlesArraySize);


/*
Undo adding the last circle to the array

@param int*             Variable holding the size of the array passed
*/
void undoLastCircle(int* circlesArraySize);

/*
Create a new circle where the right mouse button was clicked with the exception
of the first click (4 are added as required for a spline).

@param struct Circle*   Array holding all the Circle(s) created so far
@param int*             Variable holding the size of the array passed
*/
void addNewCircleOnClick(struct Circle* circles, int* circlesArraySize);

/*
Draw each and every circle in the array of circles with lines connecting
consecutive circles.

@param struct Circle*   Array holding all the Circle(s) created so far
@param int*             Variable holding the size of the array passed
*/
void drawCirclesInArray(struct Circle* circles, int* circlesArraySize);

/*
When the mouse's left button is held down, move the circle it clicked on along
with it. Stop when released.

@param struct Circle*   Array holding all the Circle(s) created so far
@param int*             Variable holding the size of the array passed
*/
void movePoints(struct Circle* circles, int* circlesArraySize);

/*
Draw a segment of the spline connecting 2 points p1 and p2, controlled also by
p0 and p3 (every 4 points determine a segment).

@param struct Circle*   Array holding all the Circle(s) created so far
@param int*             Variable holding the size of the array passed
*/
void drawSplineSegment(struct Circle* circles, int* circlesArraySize);

#endif