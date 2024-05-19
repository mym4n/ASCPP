#include <iostream>
#include <filesystem>
#include <raylib.h>

#include <animal.h>

#define maxanimalAmount = 255
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

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





















//resources
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// ANIMAL SOUNDS
//--------------------------------------------------------------------------------------//
Sound Entity_Default_Chirp;
Sound Entity_Fox_Yip;
// ANIMAL TEXTURES
//--------------------------------------------------------------------------------------//
Texture2D spriteTexture_default; //= LoadTexture("C:\\Users\\under\\source\\repos\\animalsim\\x64\\Debug\\Assets\\fop.png");
Rectangle spriteRectangle_default; //= {0, 0, spriteTexture_default.width, spriteTexture_default.height};

const int funcid_default = 0;
const int funcid_fox = 1;























// animal constructors
//--------------------------------------------------------------------------------------//
static Animal Default(int ID, Vector2 position, Texture2D texture)
{
	BoundingBox Default = BoundingBox(Vector3(-5, -5), Vector3(5, 5));

	Animal df = Animal(ID, position, Default, Default, 100, 10, true);
	df.sprite = texture;
	df.updatefuncid = funcid_default;
	df.type = 0;
	return df;
}

static Animal Fox(int ID, Vector2 position, Texture2D texture)
{
	BoundingBox Default = BoundingBox(Vector3(-5, -5), Vector3(5, 5));

	Animal df = Animal(ID, position, Default, Default, 100, 10, true);
	df.sprite = texture;
	df.updatefuncid = funcid_default;
	df.type = 1;
	return df;
}
// animal types
/*
* 0= default
* 1= fox
*/
















//animal general functions
//--------------------------------------------------------------------------------------//
const float gravaccel = 0.000000000066743015;

void UpdateAnimal(Animal* animal, Animal animals[255])
{
	
	switch (animal->updatefuncid)
	{
	case funcid_default:
		//std::cout << "calling default animal update func.\n";
		
		animal->velocity.x = 0;
		animal->velocity.y = 0;

		animal->velocity.x += 10;
		animal->velocity.y += 10;

		// move the animal
		animal->position.x += animal->velocity.x * deltaTime;
		animal->position.y += animal->velocity.y * deltaTime;

		// reset the position of the fucky fuck ass
		if (animal->position.x >= WINDOW_WIDTH) animal->position.x = 0;
		if (animal->position.y >= WINDOW_HEIGHT) animal->position.y = 0; //std::cout << "check1\n"; 

		if (animal->position.x <= -WINDOW_WIDTH) animal->position.x = WINDOW_WIDTH; //std::cout << "check1\n"; 
		if (animal->position.y <= -WINDOW_HEIGHT) animal->position.y = WINDOW_HEIGHT;// std::cout << "check1\n"; 

		break;
	case funcid_fox:

		// move the animal
		animal->position.x += animal->velocity.x * deltaTime;
		animal->position.y += animal->velocity.y * deltaTime;

		// respect the window width and height
		if (animal->position.x >= WINDOW_WIDTH) animal->position.x = 0;
		if (animal->position.y >= WINDOW_HEIGHT) animal->position.y = 0; //std::cout << "check1\n"; 

		if (animal->position.x <= -WINDOW_WIDTH) animal->position.x = WINDOW_WIDTH; //std::cout << "check1\n"; 
		if (animal->position.y <= -WINDOW_HEIGHT) animal->position.y = WINDOW_HEIGHT;// std::cout << "check1\n"; 
		break;
	default:
		std::cout << "ERROR!! UKNOWN FUNC ID!!\n";
		break;
	}

}


void UpdateAnimals(Animal animals[255])
{
	for (int i = 0; i < 255; i++)
	{
		UpdateAnimal(&animals[i], animals);
		//std::cout << "id " << i << TextFormat(" %02.02f %02.02f", animals[i].velocity.x, animals[i].velocity.y) << "\n";
		//std::cout << "id " << i << TextFormat(" %02.02f %02.02f", animals[i].position.x, animals[i].position.y) << "\n";
	}
}














// use in the texturemode
void RenderAnimal(Animal animal)
{
	//BeginTextureMode(rendertexture);

	DrawTextureRec(animal.sprite, spriteRectangle_default, animal.position, WHITE);

	//EndTextureMode();
}

void RenderAnimals(Animal animals[255])
{
	for (int i = 0; i < 255; i++)
	{
		RenderAnimal(animals[i]);
	}
}

void AnimalSimMode(Animal animals[255], RenderTexture2D gameImage)
{
	// call animal update functions
	UpdateAnimals(animals);

	/*animal.position.x += 1;
	animal.position.y += 1;*/

	// target the rendertexture "gameImage"
	BeginTextureMode(gameImage);

	ClearBackground(BLACK);
	RenderAnimals(animals);

	EndTextureMode();

	
}
















//testing updatefunction
//--------------------------------------------------------------------------------------//
void TestUpdateMode(Animal animals[255], RenderTexture2D gameImage)
{
}

//operating mode codes
//--------------------------------------------------------------------------------------//
const int OPmode_animal_sim = 0;
const int OPmode_testing = 1;




//main function
//--------------------------------------------------------------------------------------//
int main()
{
	const int randomseed = 5534;
	srand(randomseed);

	//const int screenWidth = 640;
	//const int screenHeight = 480;

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "AnimalSim");


	// load all textures
	spriteTexture_default = LoadTexture("C:\\Users\\under\\source\\repos\\animalsim\\x64\\Debug\\Assets\\fop.png"); // HARDCODED!!! CHANGE THIS WHEN YOU FIGURE IT OUT LOL!!!
	spriteRectangle_default = {0, 0, (float)spriteTexture_default.width, -(float)spriteTexture_default.height};
	RenderTexture2D gameImage = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT);

	Vector2 mousepos; //Vector2(0, 0);
	Vector2 temp;
	temp.x = 200;
	temp.y = 200;
	Animal animals[255] = {};

	for (int i = 0; i < 255; i++)
	{
		animals[i] = Default(i,newVec2((float)rand() / (float)RAND_MAX * (float)WINDOW_WIDTH,
									 (float)rand() / (float)RAND_MAX * (float)WINDOW_HEIGHT), spriteTexture_default);
	}

	// set the different operating modes
	int operatingMode = OPmode_animal_sim;
	int random = 0;
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{

		// assign mouse position
		mousepos = GetMousePosition();

		switch (operatingMode)
		{
			case OPmode_animal_sim:
				AnimalSimMode(animals, gameImage);
				break;
			case OPmode_testing:
				TestUpdateMode(animals, gameImage);
				break;
			default:
				throw(operatingMode);
				break;
		}

		// begin drawing to the window
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexture(gameImage.texture, 0, 0, WHITE);

		DrawCircle(GetMouseX(), GetMouseY(), 3, RED);

		//DrawText(TextFormat("%03i, %03i", (int)mousepos.x, (int)mousepos.y), mousepos.x - 26, mousepos.y - 26, 20, WHITE);
		//DrawText(TextFormat("%03i, %03i", (int)animal.position.x, (int)animal.position.y), mousepos.x - 26, mousepos.y - 26, 20, WHITE);
		//DrawText(TextFormat("%03i", animal.updatefuncid), mousepos.x - 26, mousepos.y - 52, 20, WHITE);

		DrawText(TextFormat("Frame Time:%02.01f ms", GetFrameTime() * 1000), 4, 4, 10, WHITE);
		EndDrawing();

		// update the deltaTime
		deltaTime = GetFrameTime();
		//std::cout << deltaTime << "\n";

		//std::cout << rand() << "\n";
	}

	UnloadTexture(spriteTexture_default);

	CloseWindow();
}