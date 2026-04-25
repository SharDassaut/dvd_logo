#include "raylib.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define WIDTH 1200
#define HEIGTH 800

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

typedef struct Logo{
	Vector2 position;
	Vector2 speed;
} Logo;

int main(int argc, char **argv)
{
	int frame = 0, itr=0, cli =0;
	float volume=0.6f, tyme;
	bool pause = false;
	float rnbw[] = {255.f,0.f,0.f};
	float normalized_rnbw[3];
	int screenSize[2];

	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	SetTargetFPS(60);
	srand(time(NULL));

	InitWindow(WIDTH, HEIGTH, "DVD Logo background");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetWindowState(FLAG_WINDOW_UNDECORATED);

	if(argc >= 2){
		for(int i= 1; i < argc ; i++){
			if(strcmp(argv[i],"-c") == 0) SetWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
			else if (strcmp(argv[i],"-h") == 0) HideCursor();
		}
	}

	InitAudioDevice();
	Sound bop = LoadSound("res/bop.mp3");
	SetSoundVolume(bop, volume);


	Image img = LoadImage("res/dvd.png");
	Texture2D txtr = LoadTextureFromImage(img);
	

	Font fnt = GetFontDefault();

	Shader shader = LoadShader(0, TextFormat("shaders/tint.fs", GLSL_VERSION));

	int colorLoc = GetShaderLocation(shader, "color");
	int timeLoc = GetShaderLocation(shader, "time");
	int ssLoc = GetShaderLocation(shader, "ScreenSize");
	SetShaderValue(shader, colorLoc, &rnbw, SHADER_UNIFORM_VEC3);

	Logo logo = {0};
	logo.speed = (Vector2){2.5f,2.5f};	
	logo.position = (Vector2){rand() % (int)(GetScreenWidth() - 3*txtr.width*0.2) +txtr.width*0.2/2, rand()% (int)(GetScreenHeight() - 3*txtr.height*0.2) +txtr.height*0.2/2};
	
	// game loop
	int i = 0;
	while (!WindowShouldClose()){
		
		if(IsKeyPressed(KEY_P)) pause = !pause;
		if(IsKeyPressed(KEY_UP)){volume +=0.1f; SetSoundVolume(bop, volume+0.1f);}
		if(IsKeyPressed(KEY_DOWN)){volume -=0.1f; SetSoundVolume(bop, volume-0.1f);}

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
			switch (i){
				case 0:
					rnbw[1]++;
					if(rnbw[1]== 255.f) i=1;
					break;
				case 1:
					rnbw[0]--;
					if(rnbw[0] == 0) i=2;
					break;
				case 2:
					rnbw[2]++;
					if(rnbw[2]== 255.f) i=3;
					break;
				case 3:
					rnbw[1]--;
					if(rnbw[1] == 0) i=4;
					break;
				case 4:
					rnbw[0]++;
					if(rnbw[0]== 255.f) i=5;
					break;
				case 5:
					rnbw[2]--;
					if(rnbw[2] == 0) i=0;
					break;
			}

			for(int k=0; k<3;k++)normalized_rnbw[k] = rnbw[k] / 255.0f;
			SetShaderValue(shader, colorLoc, &normalized_rnbw, SHADER_UNIFORM_VEC3);
			tyme = GetTime();
			SetShaderValue(shader, timeLoc, &tyme,SHADER_ATTRIB_FLOAT);
			screenSize[0]= GetScreenWidth();
			screenSize[1] = GetScreenHeight();
			SetShaderValue(shader, ssLoc, &screenSize, SHADER_ATTRIB_VEC2);

		}
		// drawing
		BeginDrawing(); 
			ClearBackground(BLANK);
			BeginShaderMode(shader);
				DrawTextureEx(txtr, logo.position, 0, 0.2, WHITE);
			EndShaderMode();
		EndDrawing();
	}

	UnloadTexture(txtr);     
    UnloadImage(img);
	UnloadShader(shader);  
	CloseAudioDevice();
	CloseWindow();
	return 0;
}
