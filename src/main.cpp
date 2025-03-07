/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"
#include "rlgl.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "GameObject.h"
#include <vector>
#include "MemoryManager.h"
#include "AudioManager.h"
//#include <windows.h>
//#include <winhttp.h>

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

extern "C" {
#include "md5.h"
}

typedef struct {
    char* data;
    size_t size;
} ImageData;

typedef struct {
    int resX;
    int resY;
    int fullscreen;
    int vsync;
} VideoConfig;

typedef enum {
    L_DEBUG,
    L_INFO,
    L_WARN,
    L_ERROR
} LogLevel;

typedef struct {
    LogLevel level;
    char channel[50];
    char message[256];
} LogMessage;

LogLevel currentLogLevel = L_DEBUG;

//
void LoadConfig(VideoConfig* config) {
    FILE* file = fopen("config.ini", "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo config.ini\n");
        return;
    }

    char line[128];
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "resx=%d", &config->resX) == 1) continue;
        if (sscanf(line, "resy=%d", &config->resY) == 1) continue;
        if (sscanf(line, "fullscreen=%d", &config->fullscreen) == 1) continue;
        if (sscanf(line, "vsync=%d", &config->vsync) == 1) continue;
    }

    fclose(file);
}

void SetLogLevel(LogLevel level) {
    currentLogLevel = level;
}

void MyPrintLog(LogMessage logMessage) {
    const char* levelStr;
    switch (logMessage.level) {
    case L_DEBUG: levelStr = "DEBUG"; break;
    case L_INFO: levelStr = "INFO"; break;
    case L_WARN: levelStr = "WARN"; break;
    case L_ERROR: levelStr = "ERROR"; break;
    default: levelStr = "UNKNOWN"; break;
    }
    printf("[%s] [%s] %s\n", levelStr, logMessage.channel, logMessage.message);

}
void MyDebugLog(LogLevel level, const char* channel, const char* message) {
    if (level >= currentLogLevel) {
        LogMessage logMessage;
        logMessage.level = level;
        strncpy(logMessage.channel, channel, sizeof(logMessage.channel) - 1);
        strncpy(logMessage.message, message, sizeof(logMessage.message) - 1);
        MyPrintLog(logMessage);
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



int main(int argc, char** argv)
{

    char* input = "hola mundo";
	uint8_t result[16];
	md5String(input, result);

	for (int i = 0; i < 16; i++) {
		printf("%02x", result[i]);
	}
	printf("\n");

    char hash[33];
    for (int i = 0; i < 16; i++)
    {
		sprintf(&hash[i*2], "%02x", (unsigned int)result[i]);
    }
    puts("");
	std::cout << hash << std::endl;

	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

    VideoConfig config = { 640, 480, 0, 1 };  // valores por defecto
    LoadConfig(&config);

    if (config.vsync) {
        SetConfigFlags(FLAG_VSYNC_HINT);
    }
    if (config.fullscreen) {
        SetConfigFlags(FLAG_FULLSCREEN_MODE);
    }

	// Create the window and OpenGL context
    InitWindow(config.resX, config.resY, "GameEngine");
    //SetWindowState(FLAG_FULLSCREEN_MODE);
	//std::vector<GameObject*> gameObjects;

	//for (int i = 0; i < 1000; i++) {
	//	GameObject* go = GameObject::SpawnGO({ 5.0f*i,5.0f*i }, { 300,5.0f*i }, "patricio");
	//	go->enabled = i % 2 == 0;
	//	gameObjects.push_back(go);
	//}

	MemoryManager::getInstance()->alloc(2*1024*1024*1024);

    SetLogLevel(L_DEBUG);

    MyDebugLog(L_DEBUG, "Main", "This is a debug message");
    MyDebugLog(L_INFO, "Main", "This is an info message");
    MyDebugLog(L_WARN, "Main", "This is a warning message");
    MyDebugLog(L_ERROR, "Main", "This is an error message");


    printf("Initializing game subsystem");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

    //GameObject* go = new GameObject();

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");
	Texture cube = LoadTexture("texturacubo.png");

    //Modelo 3d con textura
    //Model model = LoadModel("resources/Angry_Bird_Red.obj");
    //Texture2D texture = LoadTexture("resources/Angry_Bird.png");
    //model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    //Vector3 position = { 0.0f, 0.0f, 0.0f };

	Camera3D camera = {0};
	camera.position = { 4,0,2 };
	camera.target = { 0,0,0 };
	camera.up = { 0,1,0 };
	camera.fovy = 120;
	camera.projection = CAMERA_PERSPECTIVE;

    AudioManager::getInstance()->LoadbgMusic("TECNO1.XM");
	AudioManager::getInstance()->PlaybgMusic();
	
	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		AudioManager::getInstance()->Update();

		UpdateCamera(&camera, CAMERA_FREE);
		// drawing

		//for (int i = 0; i < gameObjects.size(); i++) 
        //{
        //    if(gameObjects[i]->enabled)
		//	    gameObjects[i]->update();
		//}
        //go->Update(GetFrameTime());

		BeginDrawing();

		//go->Draw(GetFrameTime());

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		BeginMode3D(camera);
		//DrawCube((Vector3) { 0, 0, 0 }, 1, 1, 1, RED);

        DrawCubeTexture(cube, {0, 0, 0}, 2, 2, 2, WHITE);
        //DrawModel(model, position, 2.0f, WHITE);

		DrawGrid(20, 10);
		//// draw some text using the default font
		//DrawText("Hello Raylib", 200,200,20,WHITE);
		EndMode3D();
		//// draw our texture to the screen
		DrawTexture(wabbit, 400, 200, WHITE);

		//for (int i = 0; i < gameObjects.size(); i++) {
		//	gameObjects[i]->draw();
		//}

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);
    UnloadTexture(cube);
    //UnloadTexture(texture);
    //UnloadModel(model);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
