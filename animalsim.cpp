#include <iostream>
#include <filesystem>
#include <raylib.h>

#include <animal.h>

#define maxanimalAmount = 255
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





















//resources
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// ANIMAL SOUNDS
//--------------------------------------------------------------------------------------//
Sound Entity_Default_Chirp;
Sound Entity_Fox_Yip;
// ANIMAL TEXTURES
//--------------------------------------------------------------------------------------//
Texture2D spriteTexture_default; //= LoadTexture("C:\\Users\\under\\source\\repos\\animalsim\\x64\\Debug\\Assets\\fop.png");
//Rectangle spriteRectangle_default; //= {0, 0, spriteTexture_default.width, spriteTexture_default.height};

const int funcid_default = 0;
const int funcid_sf = 1;
const int funcid_tt = 2;
const int funcid_st = 3;
const int funcid_fox = 4;























// animal constructors
//--------------------------------------------------------------------------------------//
static Animal Default(int ID, Vector2 position, Texture2D texture)
{
	BoundingBox Default = BoundingBox(Vector3(-5, -5), Vector3(5, 5));

	Animal df = Animal(ID, position, Default, Default, 100, 10, true);
	df.spriteid = funcid_default;
	df.updatefuncid = funcid_default;
	df.type = 0;
	return df;
}

static Animal Fox(int ID, Vector2 position, Texture2D texture)
{
	BoundingBox Default = BoundingBox(Vector3(-5, -5), Vector3(5, 5));

	Animal df = Animal(ID, position, Default, Default, 100, 10, true);
	df.spriteid = funcid_fox;
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













Texture2D SixtyFourPX;
Texture2D ThirtyTwoPX;
Texture2D SixteenPX;

// use in the texturemode
void RenderAnimal(Animal animal)
{
	//BeginTextureMode(rendertexture);

	switch (animal.spriteid)
	{
		case funcid_default:
			DrawTextureRec(spriteTexture_default, {0, 0, (float)spriteTexture_default.width, (float)spriteTexture_default.height}, animal.position, WHITE);
			break;
		case funcid_sf:
			DrawTextureRec(SixtyFourPX, {0, 0, (float)SixtyFourPX.width, (float)SixtyFourPX.height}, animal.position, WHITE);
			break;
		case funcid_tt:
			DrawTextureRec(ThirtyTwoPX, {0, 0, (float)ThirtyTwoPX.width, (float)ThirtyTwoPX.height}, animal.position, WHITE);
			break;
		case funcid_st:
			DrawTextureRec(SixteenPX, {0, 0, (float)SixteenPX.width, (float)SixteenPX.height}, animal.position, WHITE);
			break;
	}


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

	//ClearBackground(BLACK);
	RenderAnimals(animals);

	EndTextureMode();

	
}















//testing updatefunction
//--------------------------------------------------------------------------------------//
void TestUpdateMode(Animal animals[255], RenderTexture2D gameImage)
{
	BeginTextureMode(gameImage);

	DrawTexture(SixtyFourPX, 0, 0, WHITE);
	DrawTexture(ThirtyTwoPX, 64, 0, WHITE);
	DrawTexture(SixteenPX, 96, 0, WHITE);

	EndTextureMode();
}

//operating mode codes
//--------------------------------------------------------------------------------------//
const int OPmode_animal_sim = 0;
const int OPmode_testing = 1;




//main function
//--------------------------------------------------------------------------------------//
int main()
{
	//std::filesystem::path sixtyfour = ;
	std::cout << "f:" << std::filesystem::absolute("/Assets/sprites/dev/64px.png").generic_string() << "\n";

	const int randomseed = 5534;
	srand(randomseed);

	//const int screenWidth = 640;
	//const int screenHeight = 480;

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "AnimalSim");

	// load all textures

	spriteTexture_default = LoadTexture(std::filesystem::absolute(".\\x64\\Assets\\fop.png").generic_string().c_str()); // HARDCODED!!! CHANGE THIS WHEN YOU FIGURE IT OUT LOL!!!
	//spriteRectangle_default = {0, 0, (float)spriteTexture_default.width, -(float)spriteTexture_default.height};

	SixtyFourPX = LoadTexture(std::filesystem::absolute(".\\x64\\Assets\\sprites\\dev\\64px.png").generic_string().c_str());
	ThirtyTwoPX = LoadTexture(std::filesystem::absolute(".\\x64\\Assets\\sprites\\dev\\32px.png").generic_string().c_str());
	SixteenPX = LoadTexture(std::filesystem::absolute(".\\x64\\Assets\\sprites\\dev\\16px.png").generic_string().c_str());

	RenderTexture2D gameImage_back = LoadRenderTexture(VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
	RenderTexture2D gameImage = LoadRenderTexture(VIEWPORT_WIDTH, VIEWPORT_HEIGHT);

	Vector2 mousepos; //Vector2(0, 0);
	Vector2 temp;
	temp.x = 200;
	temp.y = 200;
	Animal animals[255] = {};

	for (int i = 0; i < 255; i++)
	{
		animals[i] = Default(i,newVec2((float)rand() / (float)RAND_MAX * (float)WINDOW_WIDTH,
									 (float)rand() / (float)RAND_MAX * (float)WINDOW_HEIGHT), spriteTexture_default);
		animals[i].spriteid = funcid_tt;
	}

	// set the different operating modes
	int operatingMode = OPmode_animal_sim;
	int random = 0;
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{

		// clear both textures
		BeginTextureMode(gameImage);
		ClearBackground(BLACK);
		EndTextureMode();
		BeginTextureMode(gameImage_back);
		ClearBackground(BLACK);
		EndTextureMode();

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

		// flip game texture
		BeginTextureMode(gameImage_back);
		DrawTextureRec(gameImage.texture, { 0, 0, (float)gameImage.texture.width, (float)gameImage.texture.height }, {0, 0}, WHITE);
		EndTextureMode();

		// begin drawing to the window
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTextureEx(gameImage_back.texture, {0, 0}, 0, 2, WHITE);

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