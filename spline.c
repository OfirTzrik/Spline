#include "definitions.h"
#include "functions.h"

/* Entry point */
int main(void) {
    struct Circle circles[MAX_NUM_CIRCLES];
    int circlesArraySize = 0;

    /* Initialization */
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Spline");
    if(!IsWindowReady())
        return -1;
    SetTargetFPS(60);
  
    /* Add circles and move around */
    while(!WindowShouldClose()) {
        addNewCircleOnClick(circles, &circlesArraySize);
        movePoints(circles, &circlesArraySize);

        BeginDrawing();

        /* Content start */
        DrawText("RIGHT-CLICK to add new points", 5, 5, 20, BLACK);
        DrawText("LEFT-CLICK to move points around", 5, 30, 20, BLACK);
        DrawFPS(WINDOW_WIDTH - 80, 5);
        ClearBackground(RAYWHITE);
        drawCirclesInArray(circles, &circlesArraySize);
        drawSplineSegment(circles, &circlesArraySize);
        /* Content end */

        EndDrawing();
    }

    /* Exit point */
    CloseWindow();
    return 0;
}