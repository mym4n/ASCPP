#include <iostream>
#include <raylib.h>

class Animal
{
	bool alive;
	Vector2 position;
	Vector2 velocity;
	// use size as a stand in for mass lol
	float size;

	float health;
	float hunger;
	float thirst;
	float otherwant;

	int stamina;
	int speed;
	int strength;

	Texture* sprite;
};



int main()
{
	InitWindow(1280, 720, "A.E.S.");



	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(WHITE);

		EndDrawing();
	}

	CloseWindow();
}