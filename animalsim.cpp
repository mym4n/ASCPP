#include <iostream>
#include <cstdlib>
#include "Engine.cpp"

void Render(int size, Animal* animals)
{
	for (int i = 0; i < size; i++)
	{
		DrawCircle(animals[i].position.x, animals[i].position.y, 10, animals[i].col);
	}
}

int main()
{
	InitWindow(1280, 720, "animalsim");
	Engine engine;
	engine.Init();

	while (!WindowShouldClose())
	{
		if (IsKeyPressed(KEY_ESCAPE)) exit(0);

		BeginDrawing();
		Render(engine.GetAnimalSize(), (Animal*)engine.GetAnimals());
		ClearBackground(BLACK);
		EndDrawing();
	}

	CloseWindow();
}