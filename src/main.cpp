/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"
#include "rlgl.h"
#include "lua.hpp"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "GameObject.h"
#include <vector>
#include "CubeComponent.h"
#include "MemoryManager.h"
#include "AudioManager.h"
#include "WebRequestTest.h"
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


//////////////////////////
//Hacer minimo dos figuras de raylib llamadas con LUA
//////////////////////////

int DrawCircle(lua_State* L)
{
    float x = (float)lua_tonumber(L, 1);
    float y = (float)lua_tonumber(L, 2);
    float radius = (float)lua_tonumber(L, 3);
    float r = (float)lua_tonumber(L, 4);
    float g = (float)lua_tonumber(L, 5);
    float b = (float)lua_tonumber(L, 6);
    Color color = { r, g, b, 255 };
    DrawCircle(x, y, radius, color);
    return 0;
}

int DrawRectangle(lua_State* L)
{
    float x = (float)lua_tonumber(L, 1);
    float y = (float)lua_tonumber(L, 2);
    float w = (float)lua_tonumber(L, 3);
    float h = (float)lua_tonumber(L, 4);
    float r = (float)lua_tonumber(L, 5);
    float g = (float)lua_tonumber(L, 6);
    float b = (float)lua_tonumber(L, 7);
    Color color = { r, g, b, 255 };
    DrawRectangle(x, y, w, h, color);
    return 0;
}

int Clear(lua_State* L)
{
    int r = (float)lua_tonumber(L, 1);
    int g = (float)lua_tonumber(L, 2);
    int b = (float)lua_tonumber(L, 3);
    int a = (float)lua_tonumber(L, 4);

    Color c = { r, g, b, a };

    ClearBackground(c);

    return 0;
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
            printf("Error calling draw function from lua");
            printf(lua_tostring(L, -1));
        }
    }
    else
    {
        printf("Draw function not found in lua");
    }
}

int lua_mymodule(lua_State* L)
{
    static const luaL_Reg myModule[] =
    {
    { "Clear", Clear },
    { "DrawCircle", DrawCircle },
    { "DrawRect", DrawRectangle },
    { NULL, NULL }
    };
    luaL_newlib(L, myModule);
    return 1;
}

int main(int argc, char** argv)
{

    //NO FUNCIONA
    //WebRequestTest webReq;
    //webReq.testWebLua();

    // Tell the window to use vsync and work on high DPI displays
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

    //// Initialize Lua
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    luaL_requiref(L, "SimpleDraw", lua_mymodule, 1);
    lua_pop(L, 1);

    if (luaL_dofile(L, "main.lua"))
    {
        printf("Error cargando el script main.lua");
        printf(lua_tostring(L, -1));
    }
    else
        printf("main.lua file loaded\n");

    VideoConfig config = { 640, 480, 0, 1 };  // valores por defecto
    LoadConfig(&config);

    FILE* configFile = fopen("config.ini", "r");
    if (configFile == NULL)
        printf("No se pudo abrir el archivo config.ini\n");
    else
        printf("Archivo config.ini abierto\n");
    fclose(configFile);

    if (config.vsync) SetConfigFlags(FLAG_VSYNC_HINT);
    if (config.fullscreen) SetConfigFlags(FLAG_FULLSCREEN_MODE);

    // Create the window and OpenGL context
    InitWindow(config.resX, config.resY, "GameEngine");
    if (config.fullscreen) ToggleFullscreen();

    GameObject* go = new GameObject();
    ptrComponent newComp = std::make_shared<CubeComponent>();
    go->AddComponent(newComp);

    std::vector<GameObject*> gameobjects;
    for (int i = 0; i < 100; i++)
    {
        GameObject* go = new GameObject();
        ptrComponent newComp = std::make_shared<CubeComponent>();
        go->AddComponent(newComp);
        gameobjects.push_back(go);
    }

    MemoryManager::getInstance()->alloc(2 * 1024 * 1024 * 1024);

    SetLogLevel(L_DEBUG);

    MyDebugLog(L_DEBUG, "Main", "This is a debug message");
    MyDebugLog(L_INFO, "Main", "This is an info message");
    MyDebugLog(L_WARN, "Main", "This is a warning message");
    MyDebugLog(L_ERROR, "Main", "This is an error message");


    printf("Initializing game subsystem");

    // Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
    SearchAndSetResourceDir("resources");

    // Load a texture from the resources directory
    Texture wabbit = LoadTexture("wabbit_alpha.png");
    Texture cube = LoadTexture("texturacubo.png");


    Camera3D camera = { 0 };
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

        for (auto& go : gameobjects)
        {
            go->Update(GetFrameTime());
        }

        BeginDrawing();

        // Setup the back buffer for drawing (clear color and depth buffers)
        ClearBackground(BLACK);

        BeginMode3D(camera);

        for (auto& go : gameobjects)
        {
            go->Draw(GetFrameTime());
        }

        DrawCubeTexture(cube, { 0, 0, 0 }, 2, 2, 2, WHITE);
        //DrawModel(model, position, 2.0f, WHITE);

        DrawGrid(20, 10);
        //// draw some text using the default font
        //DrawText("Hello Raylib", 200,200,20,WHITE);
        EndMode3D();
        //// draw our texture to the screen
        DrawTexture(wabbit, 400, 200, WHITE);
        //}
        luaDraw(L, GetFrameTime());
        // end the frame and get ready for the next one  (display frame, poll input, etc...)
        EndDrawing();
    }

    // cleanup
    // unload our texture so it can be cleaned up
    UnloadTexture(wabbit);
    UnloadTexture(cube);

    // destroy the window and cleanup the OpenGL context
    CloseWindow();
    return 0;
}
