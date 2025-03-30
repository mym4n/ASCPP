#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <raylib.h>

enum ent_type
{
	ent_null = 0,
	ent_r = 1,
	ent_g = 2,
	ent_m = 3,
	ent_s = 4
};

struct ent
{
	ent_type type;
};

void render_ent(Texture master_texture_atlas, ent _ent, Vector2 position)
{
	Rectangle r = { 32*(int)_ent.type, 0, 32, 32 };

	//position.y -= 16;
	//position.x -= 16;
	DrawTextureRec(master_texture_atlas, r, position, WHITE);
}

// "render thread"
int main()
{
	InitWindow(1280, 720, "ASCPP");

	bool debug_mode = false;

	Texture master_texture_atlas = LoadTexture("./x64/assets/master_texture_atlas.png");
	int ent_count = 4;
	Vector2* positions = (Vector2*)malloc(ent_count*sizeof(Vector2));
	ent* ents = (ent*)malloc(ent_count*sizeof(ent));
	// Rectangle* rectangles = (Rectangle*)malloc(ent_count*sizeof(Rectangle));

	srand(44); // TODO: make this based off non repeatable state
	for (int i = 0; i < ent_count; i++)
	{
		positions[i] = { (float)GetRandomValue(0, 250), (float)GetRandomValue(0, 250)};
		ents[i].type = (ent_type)GetRandomValue(0, ent_type::ent_s);
	}

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		// get some input why don't you
		if (IsKeyPressed(KeyboardKey::KEY_D)) debug_mode = !debug_mode;

		// begin drawing to
		// the screen
		BeginDrawing();
		ClearBackground(BLACK);

		for (int i = 0; i < ent_count; i++)
		{
			render_ent(master_texture_atlas, ents[i], positions[i]);
		}

		//DrawTexture(master_texture_atlas, 0, 0, WHITE);
		//DrawFPS(0, 0);
		EndDrawing();
	}

	CloseWindow();
}