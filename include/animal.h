#pragma once
class Animal
{
public:
	int id;
	int type;

	int spriteid;
	int updatefuncid;

	Vector2 position;
	Vector2 acceleration;

	BoundingBox hitbox;
	BoundingBox smellRadius;

	bool alive;
};