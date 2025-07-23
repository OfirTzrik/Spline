#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include "definitions.h"

// Function declarations
void AddNewCircles(struct Circle* circles, int* circlesArraySize);
void drawCirclesInArray(struct Circle* circles, int* circlesArraySize);
void movePoints(struct Circle* circles, int* circlesArraySize);
void drawSplineSegment(struct Circle* circles, int* circlesArraySize);
float getChordLength(struct Circle p0, struct Circle p1);
Vector2 scaledVector2(float scalar, Vector2 vector2);
Vector2 addVectors2(Vector2 vector2_0, Vector2 vector2_1);

// Entry point
int main(void) {
    // Initialization
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Spline");
    if(!IsWindowReady())
        return -1;
    SetTargetFPS(60);
    srand(time(NULL));
  
    struct Circle circles[MAX_NUM_CIRCLES];
    int circlesArraySize = 0;
  
    while(!WindowShouldClose()) {
        BeginDrawing();
        DrawText("Press SPACE to add new points", 5, 5, 20, BLACK);
        DrawFPS(WINDOW_WIDTH - 80, 5);
        ClearBackground(RAYWHITE);
        
        if(IsKeyPressed(KEY_SPACE)) {
            AddNewCircles(circles, &circlesArraySize);
        }
        movePoints(circles, &circlesArraySize);
        drawCirclesInArray(circles, &circlesArraySize);
        drawSplineSegment(circles, &circlesArraySize);
        
        EndDrawing();
    }

    // Exit Point
    CloseWindow();
    return 0;
}

// Add new circles to the list of circles to construct the spline
void AddNewCircles(struct Circle* circles, int* circlesArraySize) {
    if(*circlesArraySize >= MAX_NUM_CIRCLES) {
        return;
    }
  
    // First 4 required for the spline
    if(*circlesArraySize == 0) {
        for(int i = 0; i < 4; i++) {
            circles[*circlesArraySize] = (Circle) {
                .center.x = 50 + rand() % (WINDOW_WIDTH - 99),
                .center.y = 50 + rand() % (WINDOW_HEIGHT - 99),
                .radius = 10,
                .color = BLUE,
                .selected = false,
            };
            *circlesArraySize += 1;
        }
    } else {
        circles[*circlesArraySize] = (Circle) {
            .center.x = 50 + rand() % (WINDOW_WIDTH - 99),
            .center.y = 50 + rand() % (WINDOW_HEIGHT - 99),
            .radius = 10,
            .color = BLUE,
            .selected = false,
        };
        *circlesArraySize += 1;
    }
}

// Draw each and every circle in the array and draw connections to
// the control points
void drawCirclesInArray(struct Circle* circles, int* circlesArraySize) {
    // Draw the circles numbering labels
    for(int i = 0; i < *circlesArraySize; i++) {
        char buffer[16];
        snprintf(buffer, sizeof buffer, "%d", i);
        DrawText(buffer, circles[i].center.x - 7, circles[i].center.y - 30, 20, BLUE);
        DrawCircle(circles[i].center.x, circles[i].center.y, circles[i].radius, circles[i].color);
    }
    
    // Draw lines connecting consequtive points
    for(int i = 0; i < *circlesArraySize - 1; i++) {
        DrawLine(circles[i].center.x, circles[i].center.y, circles[i+1].center.x, circles[i+1].center.y, BLACK);
    }
}

// Hold and drag to move the points around
void movePoints(struct Circle* circles, int* circlesArraySize) {
    Vector2 mousePosition = GetMousePosition();
    
    for(int i = 0; i < *circlesArraySize; i++) {
        if(CheckCollisionPointCircle(mousePosition, circles[i].center, circles[i].radius) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        circles[i].selected = true;
        if(circles[i].selected) {
        circles[i].center.x = mousePosition.x;
        circles[i].center.y = mousePosition.y;
        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            circles[i].selected = false;
        }
    }
}

// Definition of Centripetal Catmull-Rom spline
// https://en.wikipedia.org/wiki/Centripetal_Catmull%E2%80%93Rom_spline#Definition

// Draw the segment determined by 4 points going through p1 to (and
// through) p2 and direction p0 to p1 and direction p2 to p3
void drawSplineSegment(struct Circle* circles, int* circlesArraySize) {
    struct Circle q = {{0, 0}, 4, BLACK, false};
    
    // Temporary variables for the calculations
    struct Circle a1 = {{0, 0}, 1, BLACK, false};
    struct Circle a2 = {{0, 0}, 1, BLACK, false};
    struct Circle a3 = {{0, 0}, 1, BLACK, false};
    struct Circle b1 = {{0, 0}, 1, BLACK, false};
    struct Circle b2 = {{0, 0}, 1, BLACK, false};
    
    for(int i = 0; i < *circlesArraySize - 3; i++) {
        // Get the 4 points for the current segment
        Circle p0 = circles[i];
        Circle p1 = circles[i+1];
        Circle p2 = circles[i+2];
        Circle p3 = circles[i+3];
        
        float t0 = 0;
        float t1 = t0 + pow(getChordLength(p1, p0), SPLINE_ALPHA);
        float t2 = t1 + pow(getChordLength(p2, p1), SPLINE_ALPHA);
        float t3 = t2 + pow(getChordLength(p3, p2), SPLINE_ALPHA);
        
        // Calculate and draw segment from p1 to p2
        for(float t = t1; t <= t2; t += SPLINE_SAMPLE_RATE) {
            a1.center = addVectors2(scaledVector2((t1-t)/(t1-t0), p0.center), scaledVector2((t-t0)/(t1-t0), p1.center));
            a2.center = addVectors2(scaledVector2((t2-t)/(t2-t1), p1.center), scaledVector2((t-t1)/(t2-t1), p2.center));
            a3.center = addVectors2(scaledVector2((t3-t)/(t3-t2), p2.center), scaledVector2((t-t2)/(t3-t2), p3.center));
            
            b1.center = addVectors2(scaledVector2((t2-t)/(t2-t0), a1.center), scaledVector2((t-t0)/(t2-t0), a2.center));
            b2.center = addVectors2(scaledVector2((t3-t)/(t3-t1), a2.center), scaledVector2((t-t1)/(t3-t1), a3.center));
            
            q.center = addVectors2(scaledVector2((t2-t)/(t2-t1), b1.center), scaledVector2((t-t1)/(t2-t1), b2.center));
            DrawRectangle(q.center.x, q.center.y, q.radius, q.radius, q.color);
        }
    }
}

// Get chord length for the segment in a spline
float getChordLength(struct Circle p0, struct Circle p1) {
    int dx = p0.center.x - p1.center.x;
    int dy = p0.center.y - p1.center.y;
    return sqrt(dx * dx + dy * dy);
}

// Returned a scaled Vector2
Vector2 scaledVector2(float scalar, Vector2 vector2) {
    return (Vector2) {scalar * vector2.x, scalar * vector2.y};
}

// Add two Vector2s
Vector2 addVectors2(Vector2 vector2_0, Vector2 vector2_1) {
    return (Vector2) {vector2_0.x + vector2_1.x, vector2_0.y + vector2_1.y};
}