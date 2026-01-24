#include <raylib/raylib.h>
#include <vector>

#ifndef ENGINE
#define ENGINE

#include "animal.h"


class Engine {
private:
	int animalsSize = 100;
	Animal* animals;
public:
	void Init()
	{
		// allocate the animal buffer
		animals = (Animal*)malloc(animalsSize * sizeof(Animal));
		// make sure all the memory is properly initialized
		for (int i = 0; i < animalsSize; i++)
		{
			animals[i] = CreateNewAnimal();
		}
	}
	int GetAnimalSize()
	{
		return animalsSize;
	}

	void* GetAnimals()
	{
		return (void*)animals;
	}
};

#endif
