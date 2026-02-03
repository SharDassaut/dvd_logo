/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 1200
#define HEIGTH 800

typedef struct Logo{
	Vector2 position;
	Vector2 speed;
	Vector2 txt_size;
	Color color;
	char *txt;
	float size;
} Logo;

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	SetTargetFPS(60);
	srand(time(NULL));
	// Create the window and OpenGL context
	InitWindow(WIDTH, HEIGTH, "DVD Logo background");
	
	int frame = 0;
	float tmp;
	char c = -1;
	


	Logo logo = {0};
	logo.color = RED;
	logo.size = 200;
	logo.position = (Vector2){rand()% (int)(WIDTH-logo.size*3+1) + logo.size/2, rand()% (int)(HEIGTH-logo.size*3+1) + logo.size/2};
	tmp = rand()% 15 - 7.0 ;
	logo.speed = (Vector2){tmp,tmp};	
	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{	
		logo.txt_size = MeasureTextEx(GetFontDefault(),"DVD", logo.size, 10);
		logo.position.x += logo.speed.x;
		logo.position.y += logo.speed.y;
		if(logo.position.x + logo.txt_size.x >= GetScreenWidth() || logo.position.x <= 0) logo.speed.x *= -1;
		if(logo.position.y + logo.txt_size.y >= GetScreenHeight() || logo.position.y <= 0) logo.speed.y *= -1;
		
		// drawing
		BeginDrawing(); 

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		// draw some text using the default font
		DrawRectangle(logo.position.x, logo.position.y, logo.txt_size.x, logo.txt_size.y, WHITE);
		//DrawText("DVD", logo.position.x, logo.position.y ,logo.size, logo.color);
		DrawTextEx(GetFontDefault(),"DVD", logo.position, logo.size, 10, logo.color);
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
		frame = (frame+ 1) % 60;
	}
	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
