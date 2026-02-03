/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"
#include <stdbool.h>
#define WIDTH 1200
#define HEIGTH 800

typedef struct Logo{
	Vector2 position;
	float speed;
	Color color;
} Logo;

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	SetTargetFPS(60);
	
	// Create the window and OpenGL context
	InitWindow(WIDTH, HEIGTH, "DVD Logo background");
	int x = 0, y = 0, frame = 0;
	bool sum_x = true, sum_y = true;
	char c = -1 ,str1[2] = {c, '\0'};
	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);
		if(sum_x) x+=1;
		else x-=1;
		if(sum_y) y+=1;
		else y-=1;

		if(x == 0) sum_x = true;
		else if(x == WIDTH) sum_x = false;
		if(y == 0) sum_y = true;
		else if (y == HEIGTH) sum_y = false;
		
		if(frame == 0){
			c = (c + 1) % 93;
			str1[0] = c + 33;
		}

		// draw some text using the default font
		DrawText(str1, x,y,20,RED);
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
		frame = (frame+ 1) % 24;
	}
	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
