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


// PONER UN SHADER PARA cambiar tinta imagen

int main ()
{
	int frame = 0, itr=0, cli =0;
	float volume=0.8f;
	bool pause = false;

	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	SetTargetFPS(60);
	srand(time(NULL));

	InitWindow(WIDTH, HEIGTH, "DVD Logo background");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
	HideCursor();
	
	InitAudioDevice();
	Sound bop = LoadSound("bop.mp3");
	SetSoundVolume(bop, volume);


	Image img = LoadImage("dvd_lg.png");
	ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
	Image cpy = ImageCopy(img);
	Texture2D txtr = LoadTextureFromImage(img);
	Color rnbw;

	Font fnt = GetFontDefault();

	
	Logo logo = {0};
	logo.speed = (Vector2){2.5f,2.5f};	
	logo.position = (Vector2){rand() % (int)(GetScreenWidth() - 3*txtr.width*0.2) +txtr.width*0.2/2, rand()% (int)(GetScreenHeight() - 3*txtr.height*0.2) +txtr.height*0.2/2};
	
	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{	
		
		if(IsKeyPressed(KEY_P)) pause = !pause;
		if(IsKeyPressed(KEY_UP)){volume -=0.1f; SetSoundVolume(bop, volume+0.1f);}
		if(IsKeyPressed(KEY_DOWN)){volume +=0.1f; SetSoundVolume(bop, volume-0.1f);}

		if(pause == false){

			//UnloadImage(cpy);                // Unload image-copy data
            //cpy = ImageCopy(img); 

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

			rnbw = ColorFromHSV((float)((int)GetTime()*20%360),1.0f,1.0f);
			ImageColorTint(&cpy, rnbw);

			//Color *pixels = LoadImageColors(cpy);    // Load pixel data from image (RGBA 32bit)
            //UpdateTexture(txtr, pixels);             // Update texture with new image data
            //UnloadImageColors(pixels);
		}
		// drawing
		BeginDrawing(); 

		ClearBackground(BLACK);
		
		
		DrawTextureEx(txtr, logo.position, 0, 0.2, WHITE);
		
		EndDrawing();

		frame = (frame+ 1) % 60;
	}

	UnloadTexture(txtr);     
    UnloadImage(img);  
    UnloadImage(cpy);

	CloseAudioDevice();
	CloseWindow();
	return 0;
}
