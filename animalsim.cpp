#include <iostream>
#include <raylib.h>

struct Genes
{
	float health;
	float hunger;
	float thirst;
	float otherwant;

	int stamina;
	int speed;
	int strength;
};

class Animal
{
	bool alive;
	Vector2 position;
	Vector2 velocity;
	// use size as a stand in for mass lol
	float size;

	// pack this into here
	// because I don't feel like
	// specifying all this bullshit
	Genes gene;

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