#include <iostream>
#include <filesystem>
#include <raylib.h>

#include <entity.h>

#define MAXANIMAL_AMOUNT = 255
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

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

// update function shit
void ResolveUpdateFunctionID(Entity entity)
{
	/*
	switch (entity.updatefuncid)
	{
	case EntityID_Default:
		//std::cout << "[INFO] prg called updateFunction on ID 0\n";
		break;
	case EntityID_Fox:

		break;
	default:
		std::cout << "Error! unknown updateFunctionID " << entity.updatefuncid << "\n";
		break;
	}
	*/
	if (entity.updatefuncid == EntityID_Fox)
	{
		entity.position.x += 1;
	}

}

// use to render the entites
void RenderEntity(Entity entity)
{
	switch (entity.spriteid)
	{
	case EntityID_Default:
		DrawTexture(EntityTexture_Default, entity.position.x, entity.position.y, WHITE);
		break;
	case EntityID_Fox:
		DrawTexture(EntityTexture_Fox, entity.position.x, entity.position.y, WHITE);
		break;
	}
}

//main function
//--------------------------------------------------------------------------------------//
int main() // MSVC is complaining about how much stack memory I'm using WAAAH WAAH WAAAH
{

	const int * randomseed = new int{ 5534 };
	srand(*randomseed);
	delete randomseed;
	randomseed = nullptr;

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "simvis");

	// load all textures
	EntityTexture_Default = LoadTexture(std::filesystem::absolute(".\\x64\\Assets\\sprites\\dev\\32px.png").generic_string().c_str());
	EntityTexture_Fox = LoadTexture(std::filesystem::absolute(".\\x64\\Assets\\sprites\\fox\\fox_default.png").generic_string().c_str());
	//spriteTexture_default = LoadTexture(std::filesystem::absolute(".\\x64\\Assets\\fop.png").generic_string().c_str());

	Camera2D GameCamera = { 0 };
	GameCamera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
	GameCamera.zoom = 1.0f;
	GameCamera.rotation = 0.0f;
	Vector2 CameraTarget = { 0, 0 };
	float zoomMul = 1.0f;

	Vector2 mousepos; //Vector2(0, 0);
	Entity* animals = new Entity[255];
	for (int i = 0; i < 255; i++)
	{
		animals[i].position.x = 0;
		animals[i].position.y = 0 + i;
		animals[i].updatefuncid = EntityID_Fox;
		animals[i].spriteid = EntityID_Fox;
	}

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		// assign mouse position
		mousepos = GetMousePosition();

		// update animals
		for (int i = 0; i < 255; i++)
		{
			switch (animals[i].updatefuncid)
			{
				case EntityID_Default:
					break;
				case EntityID_Fox:
					animals[i].position.x += 1;
					break;
			}
		}

		// camera Processing
		if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_LEFT_SHIFT)) zoomMul = 1.0f;
		if (IsKeyUp(KEY_LEFT_SHIFT) || IsKeyUp(KEY_LEFT_SHIFT)) zoomMul = 0.1f;

		if (IsKeyDown(KEY_W)) CameraTarget.y -= 1.0;
		if (IsKeyDown(KEY_S)) CameraTarget.y += 1.0;
		if (IsKeyDown(KEY_A)) CameraTarget.x -= 1.0;
		if (IsKeyDown(KEY_D)) CameraTarget.x += 1.0;

		if (IsKeyDown(KEY_EQUAL)) GameCamera.zoom += 1.0f * zoomMul;
		if (IsKeyDown(KEY_MINUS)) GameCamera.zoom -= 1.0f * zoomMul;
		if (IsKeyPressed(KEY_P)) std::cout << GameCamera.zoom << " zoom\n";
		if (IsKeyPressed(KEY_ZERO)) GameCamera.zoom = 1;

		if (GameCamera.zoom <= 0) GameCamera.zoom = 0.1f;
		if (GameCamera.zoom >= 16) GameCamera.zoom = 16.0f;

		GameCamera.target = CameraTarget;

		// begin drawing to the window
		BeginDrawing();
		ClearBackground(BLACK);

			// render to camera
			BeginMode2D(GameCamera);

			// not rendering for some reason??
			//RenderEntities(&animals);

			DrawRectangle(0, 0, 255, 255, RED);

			for (int i = 0; i < 255; i++)
			{
				//DrawTexture(EntityTexture_Fox, animals[i].position.x, animals[i].position.y, WHITE);
				RenderEntity(animals[i]);
			}

			EndMode2D();

		// draw a circle on the mouse
		DrawCircle(GetMouseX(), GetMouseY(), 3, RED);

		DrawText(TextFormat("Camera Pos: x:%02.01f, y:%02.01f", GameCamera.target.x, GameCamera.target.y), 4, 4, 10, WHITE);
		DrawText(TextFormat("Camera Zoom:%02.01f", GameCamera.zoom), 4, 17, 10, WHITE);

		//DrawFPS(4, 4);
		EndDrawing();

		// update the deltaTime
		deltaTime = GetFrameTime();
	}

	delete[] animals;

	CloseWindow();
}