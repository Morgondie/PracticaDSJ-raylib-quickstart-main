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

//#include "resource_dir.h"
#include <iostream>
//Puntos h
#include "GameObject.h"
#include "resource_dir.h"
#include <vector>
#include "MemoryManager.h"
#include "AudioManager.h"

#include "lua.hpp"
#include <lua.hpp>
 
//
extern "C" {
#include "md5.h"
}

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
} VerbosityLevel;  // esta es mi maquina de estados?

typedef struct {
    VerbosityLevel level;
    const char* module;
} DebugChannel;

Color brushColor = { 0, 0, 0, 255 };

int Clear(lua_State* L)
{
        int r = (float)lua_tonumber(L, 1) / 255;
        int g = (float)lua_tonumber(L, 2) / 255;
        int b = (float)lua_tonumber(L, 3) / 255;
		ClearBackground(Color{static_cast<unsigned char>(r), static_cast<unsigned char>(g),static_cast<unsigned char>(b), 255 });
       
    
    return 0;
}

int SetBrushColor(lua_State* L)
{
        int r = (int)lua_tonumber(L, 1);
        int g = (int)lua_tonumber(L, 2);
        int b = (int)lua_tonumber(L, 3);
		brushColor = { static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b), 255 };
    return 0;
}

int DrawCircle(lua_State* L)
{
	int x = (int)lua_tonumber(L, 1);
	int y = (int)lua_tonumber(L, 2);
	int radius = (int)lua_tonumber(L, 3);
	DrawCircle(x, y, radius, brushColor);

    return 0;
}

int DrawRect(lua_State* L)
{
	int x = (int)lua_tonumber(L, 1);
	int y = (int)lua_tonumber(L, 2);
	int width = (int)lua_tonumber(L, 3);
	int height = (int)lua_tonumber(L, 4);
	DrawRectangle(x, y, width, height, brushColor);
	return 0;
}

int DrawLine(lua_State* L)
{
	int x1 = (int)lua_tonumber(L, 1);
	int y1 = (int)lua_tonumber(L, 2);
	int x2 = (int)lua_tonumber(L, 3);
	int y2 = (int)lua_tonumber(L, 4);
	DrawLine(x1, y1, x2, y2, brushColor);
	return 0;
}

int lua_mymodule(lua_State* L)
{
	static const luaL_Reg myModule[] =
	{
	{ "Clear", Clear },
	{ "SetBrushColor", SetBrushColor },
	{ "DrawCircle", DrawCircle },
	{ "DrawRect", DrawRect },
	{ "DrawLine", DrawLine },
	{ NULL, NULL }
	};
	luaL_newlib(L, myModule);
	return 1;
}

void luaDraw(lua_State* L, float dt)
{
    lua_getglobal(L, "Draw");
    if (lua_isfunction(L, -1))
    {
        //Log(L"Calling draw function from lua");
        lua_pushnumber(L, dt);
        if (lua_pcall(L, 1, 0, 0) != 0)
        {
			std::cout << "Error running draw function: " << lua_tostring(L, -1) << std::endl;
        }
    }
}



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
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
    luaL_requiref(L, "SimpleDraw", lua_mymodule, 1);
	lua_pop(L, 1);

	if (luaL_dofile(L, "main.lua"))
	{
		std::cout << "Error running script: " << lua_tostring(L, -1) << std::endl;
	}


	char* input = "Hello World";
	uint8_t result[16];
    md5String(input, result);
    for (int i = 0; i < 16; i++)
    {
		printf("%02x", result[i]);
    }
	char hash[33];
   /* for (int  i = 0; i < 16; i++)
    {
        sprintf(&)hash[i * 2], "%02x", result[i]);
    }*/
	puts("");

     //DebugChannel channel = { DEBUG, "main" };

    //DebugLog(channel, DEBUG, "main", "This is a debug message from %s module\n", "main");
    /*DebugLog(channel, INFO, "main", "This is an info message from %s module\n", "main");
    DebugLog(channel, WARN, "main", "This is a warning message from %s module\n", "main");
    DebugLog(channel, ERROR, "main", "This is an error message from %s module\n", "main");*/
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

	GameObject* myobj = new GameObject();
	myobj->init();
	myobj->setVelocity({ 100, 100 });
    GameObject* otro = new GameObject();
    otro->init({100, 100}, {250,100},BLUE);

	GameObject*k = GameObject::Spawn({ 200,200 }, { 100,100 }, "test");   

	std::vector<GameObject*> gameObjects;



    for (int i = 0; i < 10; i++)
    {
		GameObject*k = GameObject::Spawn({ 5.0f*i,5.0f*i }, { 100,5.0f*i }, "test");
		gameObjects.push_back(k);
    }

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
	camera.position = { 4,0,2 };
	camera.target = { 0,0,0 };
	camera.up = { 0,1,0 };
	camera.fovy = 45;
	camera.projection = CAMERA_PERSPECTIVE;

	AudioManager::getInstance()->LoadBackgroundMusic("MaskedKing.mp3");
	AudioManager::getInstance()->PlayBGM();


	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		AudioManager::getInstance()->Update();
		UpdateCamera(&camera, CAMERA_FREE);

        for (int i = 0; i < gameObjects.size(); i++)
        {
			if (gameObjects[i]->enabled)  
				k->enabled = i % 2 == 0;
                			gameObjects[i]->update();
        }

		// drawing
		BeginDrawing();

		myobj->update();
		otro->update();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		ClearBackground(LIGHTGRAY);

		// draw some text using the default font
		//DrawText("Hello Raylib", 200,200,20,WHITE);

		// draw our texture to the screen
		DrawTexture(wabbit, 400, 200, WHITE);
		
		BeginMode3D(camera);
		//DrawCube((Vector3) { 0, 0, 0 }, 1, 1, 1, RED);

        DrawCubeTexture(cubeTex, { 0, 0, 0 }, 2, 2, 2, WHITE);
        {

        }
		DrawGrid(1, 1);

		EndMode3D();

		myobj->draw();
		otro->draw();
		
        for (int i = 0; i < gameObjects.size(); i++)
        {
            gameObjects[i]->draw();
        }
		MemoryManager::getInstance()->alloc(123);
		luaDraw(L, GetFrameTime());

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);

	lua_close(L);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
