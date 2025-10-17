#include <math.h>
#include "functions.h"

/* Remove all the circles */
void resetAllCircles(int* circlesArraySize) {
	*circlesArraySize = 0;
}

/* Remove the last circle that was added */
void undoLastCircle(int *circlesArraySize) {
    if (*circlesArraySize > 0) {
        (*circlesArraySize)--;
    }
}

/* Add a circle to where the mouse right-clicked */
void addNewCircleOnClick(struct Circle* circles, int* circlesArraySize) {
    Vector2 mousePosition = GetMousePosition();
    if (*circlesArraySize >= MAX_NUM_CIRCLES)
        return;

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        if (*circlesArraySize == 0) { /* Add first 4 points required for a spline */
            Vector2 temps[4] = {{100, 100}, {200, 200}, {300, 300}, {400, 400}};
            int i;
            for (i = 0; i < 4; i++)
                circles[*circlesArraySize] = createCircle(&circlesArraySize, temps[i]);
        } else {
            circles[*circlesArraySize] = createCircle(&circlesArraySize, mousePosition);
        }
    }
}

/* Draw each and every circle in the array and draw connections to the control points */
void drawCirclesInArray(struct Circle* circles, int* circlesArraySize) {
    /* Draw the circles numbering labels */
    int i;
    for (i = 0; i < *circlesArraySize; i++) {
        char buffer[3]; /* Just enough bytes */
        intToString(i, buffer);
        DrawText(buffer, circles[i].center.x - LABEL_OFFSET_X, circles[i].center.y - LABEL_OFFSET_Y, 20, BLUE);
        DrawCircle(circles[i].center.x, circles[i].center.y, RADIUS, BLUE);
    }
    
    /* Draw lines connecting consequtive points */
    for (i = 0; i < *circlesArraySize - 1; i++)
        DrawLine(circles[i].center.x, circles[i].center.y, circles[i + 1].center.x, circles[i + 1].center.y, BLACK);
}

/* Hold and drag to move the points around */
void movePoints(struct Circle* circles, int* circlesArraySize) {
    Vector2 mousePosition = GetMousePosition();
    
    int i;
    for (i = 0; i < *circlesArraySize; i++) {
        if (CheckCollisionPointCircle(mousePosition, circles[i].center, RADIUS) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            circles[i].selected = true;
        if (circles[i].selected)
            circles[i].center = mousePosition;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            circles[i].selected = false;
    }
}

/* Definition of Centripetal Catmull-Rom spline
 https://en.wikipedia.org/wiki/Centripetal_Catmull%E2%80%93Rom_spline#Definition

 Draw the segment determined by 4 points going through p1 to (and
 through) p2 and direction p0 to p1 and direction p2 to p3 */
void drawSplineSegment(struct Circle* circles, int* circlesArraySize) {
    /* Point along the segment */
    Vector2 q;
    
    /* Temporary variables for the finding the point along the segment */
    Vector2 a1;
    Vector2 a2;
    Vector2 a3;
    Vector2 b1;
    Vector2 b2;
    
    int i;
    for (i = 0; i < *circlesArraySize - 3; i++) {
        /* Get the 4 points that determine the shape of the current segment */
        struct Circle p0 = circles[i];
        struct Circle p1 = circles[i + 1];
        struct Circle p2 = circles[i + 2];
        struct Circle p3 = circles[i + 3];
        
        float t0 = 0;
        float t1 = t0 + pow(getChordLength(p1, p0), SPLINE_ALPHA);
        float t2 = t1 + pow(getChordLength(p2, p1), SPLINE_ALPHA);
        float t3 = t2 + pow(getChordLength(p3, p2), SPLINE_ALPHA);
        
        /* Calculate and draw the segment going through p1 and p2 (with p0 and p3)
        Avoid an infinite loop using 0.00001 in the case where two points overlap */
        float t;
        for (t = t1; t <= t2; t += ((t2 - t1) / SPLINE_SAMPLE_RATE) + 0.00001) {
            a1 = addVectors2(scaledVector2((t1 - t) / (t1 - t0), p0.center), scaledVector2((t - t0) / (t1 - t0), p1.center));
            a2 = addVectors2(scaledVector2((t2 - t) / (t2 - t1), p1.center), scaledVector2((t - t1) / (t2 - t1), p2.center));
            a3 = addVectors2(scaledVector2((t3 - t) / (t3 - t2), p2.center), scaledVector2((t - t2) / (t3 - t2), p3.center));
            
            b1 = addVectors2(scaledVector2((t2 - t) / (t2 - t0), a1), scaledVector2((t - t0) / (t2 - t0), a2));
            b2 = addVectors2(scaledVector2((t3 - t) / (t3 - t1), a2), scaledVector2((t - t1) / (t3 - t1), a3));
            
            q = addVectors2(scaledVector2((t2 - t) / (t2 - t1), b1), scaledVector2((t - t1) / (t2 - t1), b2));
            DrawRectangle(q.x, q.y, 5, 5, BLACK);
        }
    }
}

/* Helper functions */

/* Get chord length for the segment in a spline */
float getChordLength(struct Circle p0, struct Circle p1) {
    float dx = p0.center.x - p1.center.x;
    float dy = p0.center.y - p1.center.y;
    return sqrt(dx * dx + dy * dy);
}

/* Returned a scaled Vector2 */
Vector2 scaledVector2(float scalar, Vector2 vector2) {
    Vector2 temp;

    temp.x = scalar * vector2.x;
    temp.y = scalar * vector2.y;

    return temp;
}

/* Add two Vector2s */
Vector2 addVectors2(Vector2 vector2_0, Vector2 vector2_1) {
    Vector2 temp;

    temp.x = vector2_0.x + vector2_1.x;
    temp.y = vector2_0.y + vector2_1.y;

    return temp;
}

/* Create a circle where the mouse was right-clicked and increase count */
struct Circle createCircle(int **circlesArraySize, Vector2 mousePosition) {
    struct Circle temp;

    temp.center.x = mousePosition.x;
    temp.center.y = mousePosition.y;
    temp.selected = false;

    (**circlesArraySize)++;

    return temp;
}

/* Convert an integer to string (used instead of snprint) */
void intToString(int num, char *str) {
    char *i = str;
    char *j;

    /* Take each digit and add it to the string (reversed) */
    if (num == 0)
        *str++ = '0';
    while (num > 0) {
        *str++ = (num % 10) + '0';
        num /= 10;
    }

    /* Reverse the string */
    for (j = str - 1; i < j; i++, j--) {
        char temp = *i;
        *i = *j;
        *j = temp;
    }

    *str = '\0';
}