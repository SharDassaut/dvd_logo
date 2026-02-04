#include "raylib.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define WIDTH 1200
#define HEIGTH 800

typedef struct Logo{
	Vector2 position;
	Vector2 speed;
	Vector2 txt_size;
	Color color;
	float size;
} Logo;

int main ()
{
	int frame = 0,txt_width;
	float tmp, volume;
	char c = -1;
	const char *txt = "DVD";
	bool pause = false;

	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	SetTargetFPS(60);
	srand(time(NULL));

	InitWindow(WIDTH, HEIGTH, "DVD Logo background");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	//SetWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
	HideCursor();
	InitAudioDevice();

	Logo logo = {0};
	logo.color = (Color){0,0,255,255};
	logo.size = 125;

	//Font fnt = LoadFont("bbn.ttf");
	//Font fnt = LoadFontEx("bbn.ttf", logo.size ,NULL, 0);
	Font fnt = GetFontDefault();
	Sound bop = LoadSound("bop.mp3");
	SetSoundVolume(bop, 0.8f);
	logo.speed = (Vector2){2.0f,2.0f};	

	logo.txt_size = MeasureTextEx(fnt,"DVD", logo.size, 10);
	logo.position = (Vector2){rand()% (int)(WIDTH-logo.txt_size.x*2) + logo.size/2, rand()% (int)(HEIGTH-logo.txt_size.y*2+1) + logo.size/2};

	Vector2 t;
	

	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{	
		
		if(IsKeyPressed(KEY_P)) pause = !pause;
		
		if(pause == false){
			
			logo.position.x += logo.speed.x;
			logo.position.y += logo.speed.y;
			if(logo.position.x + logo.txt_size.x >= GetScreenWidth() || logo.position.x <= 0){ 
				logo.speed.x *= -1;
				PlaySound(bop);
			}
			if(logo.position.y +logo.txt_size.y*0.7 >= GetScreenHeight() || logo.position.y  <= 0) {
				PlaySound(bop);
				logo.speed.y *= -1;
			}
		}
		// drawing
		BeginDrawing(); 
		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		
		//DrawRectangle(logo.position.x, logo.position.y, logo.txt_size.x, logo.txt_size.y*0.70, WHITE);
		t = (Vector2){logo.position.x,logo.position.y - logo.txt_size.y*0.1};
		DrawTextEx(fnt, txt, t, logo.size, 10.0f, logo.color);
		
		EndDrawing();

		frame = (frame+ 1) % 60;
	}

	UnloadFont(fnt);
	CloseAudioDevice();
	CloseWindow();
	return 0;
}
