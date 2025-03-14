/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"
#include "rlgl.h"
#include <stdio.h>

#include <stdarg.h>
#include <string.h>

#include "resource_dir.h"



#include <stdarg.h>
#include <string.h>
typedef struct {
    int resX;
    int resY;
    bool fullscreen;
    bool vsync;
} VideoConfig;

typedef enum {
    Log_DEBUG,
    INFO,
    WARN,
    ERROR
} VerbosityLevel;

typedef struct {
    VerbosityLevel level;
    const char* module;
} DebugChannel;

void DebugLog(char* channelm, char* message);

	// utility header for SearchAndSetResourceDir

void DrawCubeTexture(Texture2D texture, Vector3 position, float width, float height, float length, Color color); // Draw cube textured

void DebugLog(DebugChannel channel, VerbosityLevel level, const char* module, const char* format, ...) {
    if (level >= channel.level && strcmp(module, channel.module) == 0) {
        va_list args;
        va_start(args, format);
        vfprintf(stderr, format, args);
        va_end(args);
    }
}

void DrawCubeTexture(Texture2D texture, Vector3 position, float width, float height, float length, Color color)
{
    float x = position.x;
    float y = position.y;
    float z = position.z;

    // Set desired texture to be enabled while drawing following vertex data
    rlSetTexture(texture.id);

    // Vertex data transformation can be defined with the commented lines,
    // but in this example we calculate the transformed vertex data directly when calling rlVertex3f()
    //rlPushMatrix();
        // NOTE: Transformation is applied in inverse order (scale -> rotate -> translate)
        //rlTranslatef(2.0f, 0.0f, 0.0f);
        //rlRotatef(45, 0, 1, 0);
        //rlScalef(2.0f, 2.0f, 2.0f);

    rlBegin(RL_QUADS);
    rlColor4ub(color.r, color.g, color.b, color.a);
    // Front Face
    rlNormal3f(0.0f, 0.0f, 1.0f);       // Normal Pointing Towards Viewer
    rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width / 2, y - height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
    rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width / 2, y - height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad
    rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width / 2, y + height / 2, z + length / 2);  // Top Right Of The Texture and Quad
    rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width / 2, y + height / 2, z + length / 2);  // Top Left Of The Texture and Quad
    // Back Face
    rlNormal3f(0.0f, 0.0f, -1.0f);     // Normal Pointing Away From Viewer
    rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width / 2, y - height / 2, z - length / 2);  // Bottom Right Of The Texture and Quad
    rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - width / 2, y + height / 2, z - length / 2);  // Top Right Of The Texture and Quad
    rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width / 2, y + height / 2, z - length / 2);  // Top Left Of The Texture and Quad
    rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + width / 2, y - height / 2, z - length / 2);  // Bottom Left Of The Texture and Quad
    // Top Face
    rlNormal3f(0.0f, 1.0f, 0.0f);       // Normal Pointing Up
    rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width / 2, y + height / 2, z - length / 2);  // Top Left Of The Texture and Quad
    rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width / 2, y + height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
    rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width / 2, y + height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad
    rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width / 2, y + height / 2, z - length / 2);  // Top Right Of The Texture and Quad
    // Bottom Face
    rlNormal3f(0.0f, -1.0f, 0.0f);     // Normal Pointing Down
    rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - width / 2, y - height / 2, z - length / 2);  // Top Right Of The Texture and Quad
    rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width / 2, y - height / 2, z - length / 2);  // Top Left Of The Texture and Quad
    rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + width / 2, y - height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
    rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width / 2, y - height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad
    // Right face
    rlNormal3f(1.0f, 0.0f, 0.0f);       // Normal Pointing Right
    rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width / 2, y - height / 2, z - length / 2);  // Bottom Right Of The Texture and Quad
    rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width / 2, y + height / 2, z - length / 2);  // Top Right Of The Texture and Quad
    rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width / 2, y + height / 2, z + length / 2);  // Top Left Of The Texture and Quad
    rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + width / 2, y - height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
    // Left Face
    rlNormal3f(-1.0f, 0.0f, 0.0f);    // Normal Pointing Left
    rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width / 2, y - height / 2, z - length / 2);  // Bottom Left Of The Texture and Quad
    rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width / 2, y - height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad
    rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - width / 2, y + height / 2, z + length / 2);  // Top Right Of The Texture and Quad
    rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width / 2, y + height / 2, z - length / 2);  // Top Left Of The Texture and Quad
    rlEnd();
    //rlPopMatrix();

    rlSetTexture(0);
}


bool ReadConfigFromFile(const char* filename, VideoConfig* config) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening config file: %s\n", filename);
        return false;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Remove any leading or trailing whitespace
        line[strcspn(line, "\r\n")] = 0;

        if (strncmp(line, "resx=", 5) == 0) {
            config->resX = atoi(line + 5);
        }
        else if (strncmp(line, "resy=", 5) == 0) {
            config->resY = atoi(line + 5);
        }
        else if (strncmp(line, "fullscreen=", 11) == 0) {
            config->fullscreen = atoi(line + 11);
        }
        else if (strncmp(line, "vsync=", 6) == 0) {
            config->vsync = atoi(line + 6);
        }
    }

    fclose(file);
    return true;
}

int main (int argc, char** argv)
{
     DebugChannel channel = { DEBUG, "main" };

    DebugLog(channel, DEBUG, "main", "This is a debug message from %s module\n", "main");
    DebugLog(channel, INFO, "main", "This is an info message from %s module\n", "main");
    DebugLog(channel, WARN, "main", "This is a warning message from %s module\n", "main");
    DebugLog(channel, ERROR, "main", "This is an error message from %s module\n", "main");
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

    VideoConfig config = { 640, 480, false, false };
    if (!ReadConfigFromFile("config.ini", &config)) {
        fprintf(stderr, "Using default configuration\n");
    }
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    if (config.vsync) {
        SetConfigFlags(FLAG_VSYNC_HINT);
    }

    InitWindow(config.resX, config.resY, "Hello Raylib");

    if (config.fullscreen) {
        ToggleFullscreen();
    }


    //leer argumentos de CLI
    int resX = 640;
    int resY = 480;
    bool wantsfullScrenn = false;

    if (argc > 1)
    {
        for (int i = 0; i < argc; i++)
        {
            //std::cout << "arg " << i << argv[i] << std::endl;
            fprintf(stderr, "arg %i : %s \n", i, argv[i]);
            if (strcmp(argv[i], "-resX") == 0)
            {
                resX = atoi(argv[i + 1]);
            }
            if (strcmp(argv[i], "-resY") == 0)
            {
                resY = atoi(argv[i + 1]);
            }
            if (strcmp(argv[i], "-fullscreen") == 0)
            {
                wantsfullScrenn = true;
            }

        }
    }

	// Create the window and OpenGL context
	InitWindow(resX, resY, "Hello Raylib");


    if (wantsfullScrenn) ToggleFullscreen();

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");

	Texture cubeTex = LoadTexture("tile.png");
	
	Camera3D camera = { 0 };
	camera.position = (Vector3){ 4,0,2 };
	camera.target = (Vector3){ 0,0,0 };
	camera.up = (Vector3){ 0,1,0 };
	camera.fovy = 45;
	camera.projection = CAMERA_PERSPECTIVE;


	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		UpdateCamera(&camera, CAMERA_FREE);

		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		ClearBackground(LIGHTGRAY);

		// draw some text using the default font
		//DrawText("Hello Raylib", 200,200,20,WHITE);

		// draw our texture to the screen
		//DrawTexture(wabbit, 400, 200, WHITE);
		
		BeginMode3D(camera);
		//DrawCube((Vector3) { 0, 0, 0 }, 1, 1, 1, RED);

        DrawCubeTexture(cubeTex, (Vector3) { 0, 0, 0 }, 2, 2, 2, WHITE);
        {

        }
		DrawGrid(10, 1);

		EndMode3D();

		

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
