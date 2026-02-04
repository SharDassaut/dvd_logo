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
} Logo;

int main ()
{
	int frame = 0, itr=0, cli =0;
	float tmp, volume=0.8f;
	char c = -1;
	const char *txt = "DVD";
	bool pause = false;
	int op[] = {0,1,2,3,4,0,5,2};

	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	SetTargetFPS(60);
	srand(time(NULL));

	InitWindow(WIDTH, HEIGTH, "DVD Logo background");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
	HideCursor();
	InitAudioDevice();

	Logo logo = {0};

	Image img = LoadImage("dvd_lg.png");
	ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
	Image cpy = ImageCopy(img);
	Texture2D txtr = LoadTextureFromImage(img);

	//Font fnt = LoadFont("bbn.ttf");
	//Font fnt = LoadFontEx("bbn.ttf", logo.size ,NULL, 0);
	Font fnt = GetFontDefault();

	Sound bop = LoadSound("bop.mp3");

	SetSoundVolume(bop, volume);
	logo.speed = (Vector2){2.5f,2.5f};	
	logo.position = (Vector2){0.0f, 0.0f};
	logo.position = (Vector2){rand() % (int)(GetScreenWidth() - 3*txtr.width*0.2) +txtr.width*0.2/2, rand()% (int)(GetScreenHeight() - 3*txtr.height*0.2) +txtr.height*0.2/2};
	
	int blue = 0;
	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{	
		
		if(IsKeyPressed(KEY_P)) pause = !pause;
		if(IsKeyPressed(KEY_UP)){volume -=0.1f; SetSoundVolume(bop, volume+0.1f);}
		if(IsKeyPressed(KEY_DOWN)){volume +=0.1f; SetSoundVolume(bop, volume-0.1f);}
		if(pause == false){
			logo.position.x += logo.speed.x;
			logo.position.y += logo.speed.y;
			if(logo.position.x + txtr.width*0.2 >= GetScreenWidth() || logo.position.x <= 0){ 
				logo.speed.x *= -1;
				PlaySound(bop);
			}
			if(logo.position.y + txtr.height*0.2 >= GetScreenHeight() || logo.position.y  <= 0) {
				PlaySound(bop);
				logo.speed.y *= -1;
			}


			
		}
		// drawing
		BeginDrawing(); 
		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		DrawTextureEx(txtr, logo.position, 0, 0.2, WHITE);
		
		EndDrawing();

		frame = (frame+ 1) % 60;
	}

	UnloadFont(fnt);
	CloseAudioDevice();
	CloseWindow();
	return 0;
}
