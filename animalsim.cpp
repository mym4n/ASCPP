#include <iostream>
#include <filesystem>
#include <raylib.h>

#include <entity.h>
#include <sim.h>

#define MAXANIMAL_AMOUNT = 255
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 960

#define VIEWPORT_WIDTH 640
#define VIEWPORT_HEIGHT 480

float deltaTime = 1.0f;

//necessary functions
//--------------------------------------------------------------------------------------//
float sqrdist(float x1, float x2)
{
	return (x2 - x1) * (x2 - x1);
}

Vector2 sqrdist(Vector2 x1, Vector2 x2)
{
	return newVec2(sqrdist(x1.x, x2.x) , sqrdist(x1.y, x2.y));
}

//main function
//--------------------------------------------------------------------------------------//
int main() // MSVC is complaining about how much stack memory I'm using WAAAH WAAH WAAAH
{

	const int * randomseed = new int{ 5534 };
	srand(*randomseed);
	delete randomseed;

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "AnimalSim");

	// load all textures
	//spriteTexture_default = LoadTexture(std::filesystem::absolute(".\\x64\\Assets\\fop.png").generic_string().c_str());

	RenderTexture2D gameImage_back = LoadRenderTexture(VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
	RenderTexture2D gameImage = LoadRenderTexture(VIEWPORT_WIDTH, VIEWPORT_HEIGHT);

	Vector2 mousepos; //Vector2(0, 0);
	Entity* animals = new Entity[255]();

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		// assign mouse position
		mousepos = GetMousePosition();

		// clear both textures
		BeginTextureMode(gameImage);
		ClearBackground(BLACK);
		//ClearBackground(newColor(mousepos.x, mousepos.y, mousepos.x, 255));
		EndTextureMode();
		BeginTextureMode(gameImage_back);
		ClearBackground(BLACK);
		//ClearBackground(newColor(mousepos.x, mousepos.y, mousepos.x, 255));
		EndTextureMode();


		// flip game texture
		BeginTextureMode(gameImage_back);
		DrawTextureRec(gameImage.texture, { 0, 0, (float)gameImage.texture.width, (float)gameImage.texture.height }, {0, 0}, WHITE);
		EndTextureMode();

		// begin drawing to the window
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTextureEx(gameImage_back.texture, {0, 0}, 0, 2, WHITE);

		// draw a circle on the mouse
		DrawCircle(GetMouseX(), GetMouseY(), 3, RED);

		DrawText(TextFormat("Frame Time:%02.01f ms", GetFrameTime() * 1000), 4, 4, 10, WHITE);
		EndDrawing();

		// update the deltaTime
		deltaTime = GetFrameTime();
	}

	UnloadRenderTexture(gameImage);
	UnloadRenderTexture(gameImage_back);
	delete[] animals;

	CloseWindow();
}