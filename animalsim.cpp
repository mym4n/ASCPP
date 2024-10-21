#include <iostream>
#include <thread>
#include <raylib.h>

// animal related structs and classes
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
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
public:
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

// simulation related functions and variables
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
int sync_code = 0; // -1 means close all threads
bool simthread_closed = false;
bool simthread_paused = false;
Animal* animals;
int sizeofanimals = 255;

// DO NOT RUN THIS IF ANIMALS HAS NOT BEEN
// INITIALIZED!! THIS IS DESIGNED TO BE RUN
// GIVEN THAT ANIMALS IS INITIALIZED!!
void SimulationStep()
{
	// sizeofanimals = sizeof(animals) / sizeof(Animal);

	for (int i = 0; i < sizeofanimals; i++)
	{
		if (animals[i].alive)
		{
			animals[i].position.x += 1 * GetFrameTime();
			animals[i].position.y += 1 * GetFrameTime();
		}
	}

}

void SimulationThread()
{
	bool makework = true;
	float deltaTime = 0.0f;
	while (makework)
	{
		deltaTime = GetFrameTime();
		switch (sync_code)
		{
			case -1: // close thread
				makework = false;
				std::cout << "[S_THRD] closing...\n";
				break;
			case 1: // run sim
				// sizeofanimals and animals are what to use
				SimulationStep();
				break;
			case 2: // pause case
				simthread_paused = true;
				//std::cout << "[S_THRD] sim thread paused...\n";
				while (sync_code == 2)
				{
					// do nothing
				}
				//std::cout << "[S_THRD] sim thread unpaused...\n";

				break;
		}

		deltaTime = deltaTime - GetFrameTime();
		if (deltaTime < (1/5))
		{
			WaitTime((1/5) - deltaTime);
		}
	}
	simthread_closed = true;
}

// "render thread"
int main()
{
	InitWindow(1280, 720, "A.E.S.");

	sync_code = 2;
	animals = new Animal[sizeofanimals];
	std::thread simthread(SimulationThread);

	Image animal_img = GenImageColor(32, 32, BLUE);
	Texture animaltxt = LoadTextureFromImage(animal_img);
	UnloadImage(animal_img);

	// initialize animals
	// genes are determined
	// on spawn
	for (int i = 0; i < sizeofanimals; i++)
	{
		animals[i].position = { 0,0 };
		animals[i].alive = true;
		animals[i].size = 1.0f;
		animals[i].sprite = &animaltxt;
		animals[i].velocity = { 0, 0 };
	}

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		// begin drawing to
		// the screen
		BeginDrawing();

		ClearBackground(BLACK);
		for (int i = 0; i < sizeofanimals; i++)
		{
			DrawTexture(*animals[i].sprite, animals[i].position.x, animals[i].position.y, WHITE);

			DrawText(TextFormat("x%0.1f y%0.1f", animals[i].position.x, animals[i].position.y), animals[i].position.x, animals[i].position.y, 4, WHITE);
		}

		DrawFPS(0, 0);
		EndDrawing();
		sync_code = 1;
	}

	sync_code = -1;

	while (simthread_closed != true)
	{
		// do nothing
	}
	simthread.join();
	UnloadTexture(animaltxt);

	CloseWindow();
}