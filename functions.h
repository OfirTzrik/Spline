#ifndef FUNCTIONS
#define FUNCTIONS

#include "definitions.h"

/*
Description:
Create a new circle where the right mouse button was clicked with the exception
of the first click (4 are added as required for a spline).

Parameters:
@param struct Circle*   = Array holding all the Circle(s) created so far
@param int*             = Variable holding the size of the array passed
*/
void addNewCircleOnClick(struct Circle* circles, int* circlesArraySize);

/*
Description:
Draw each and every circle in the array of circles with lines connecting
consecutive circles.

Parameters:
@param struct Circle*   = Array holding all the Circle(s) created so far
@param int*             = Variable holding the size of the array passed
*/
void drawCirclesInArray(struct Circle* circles, int* circlesArraySize);

/*
Description:
When the mouse's left button is held down, move the circle it clicked on along
with it. Stop when released.

Parameters:
@param struct Circle*   = Array holding all the Circle(s) created so far
@param int*             = Variable holding the size of the array passed
*/
void movePoints(struct Circle* circles, int* circlesArraySize);

/*
Description:
Draw a segment of the spline connecting 2 points p1 and p2, controlled also by
p0 and p3 (every 4 points determine a segment).

Parameters:
@param struct Circle*   = Array holding all the Circle(s) created so far
@param int*             = Variable holding the size of the array passed
*/
void drawSplineSegment(struct Circle* circles, int* circlesArraySize);

/*
Description:
Calculate chord length given 2 points which the spline passes through.

Parameters:
@param struct Circle    = First circle in the segment the spline passes through
@param struct Circle    = First circle in the segment the spline passes through
*/
float getChordLength(struct Circle p0, struct Circle p1);

/*
Description:
Scale a Vector2.

Parameters:
@param float            = Scalar
@param Vector2          = Vector2 to change the scale of
*/
Vector2 scaledVector2(float scalar, Vector2 vector2);

/*
Description:
Add two Vector2 together.

Parameters:
@param Vector2          = First Vector2
@param Vector2          = Second Vector2
*/
Vector2 addVectors2(Vector2 vector2_0, Vector2 vector2_1);

/*
Description:
Create a new circle to be added to the list of circles (helper function for
AddNewCircles).

Parameters:
@param int**            = Size of the array as a double pointer (through AddNewCircles)
@param Vector2          = Point on screen where the mouse left-clicked
@return struct Circle   = The new circle that was created and will be added to the array
*/
struct Circle createCircle(int **circlesArraySize, Vector2 mousePosition);

/*
Description:
Convert an integer to a string.

Parameters:
@param int              = Number to convert to string
@param char*            = Coversion result
*/
void intToString(int num, char *str);

#endif