#pragma once
class Animal
{
public:
	int id;
	int type;

	Texture2D sprite;

	Vector2 position;
	float mass;
	Vector2 velocity;
	BoundingBox hitbox;
	BoundingBox smellRadius;

	int health;
	int atk;

	bool alive;

	int updatefuncid;

	Animal(int ID, Vector2 pos, float Mass, BoundingBox hbox, BoundingBox SmellRadius, int Health, int Attack, bool Alive) :
		id(ID), position(pos), mass(Mass),
		velocity(newVec2(0, 0)), hitbox(hbox),
		smellRadius(SmellRadius), health(Health), atk(Attack), alive(Alive) {}

	Animal(int ID, Vector2 pos, BoundingBox hbox, BoundingBox SmellRadius, int Health, int Attack, bool Alive) :
		id(ID), position(pos), mass(((float)rand() / (float)RAND_MAX) * 50.0f),
		velocity(newVec2(0, 0)), hitbox(hbox),
		smellRadius(SmellRadius), health(Health), atk(Attack), alive(Alive) {}

	Animal() : id(0), position(), mass(((float)rand() / (float)RAND_MAX) * 50.0f), velocity(), hitbox(),
		smellRadius(), health(), atk(), alive() {}
};