#pragma once
class Entity
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

const unsigned char EntityID_Default = 0;
const unsigned char EntityID_Fox = 1;


const Texture2D EntityTexture_Default = LoadTexture(std::filesystem::absolute(".\\x64\\Assets\\sprites\\dev\\32px.png").generic_string().c_str());
const Texture2D EntityTexture_Fox = LoadTexture(std::filesystem::absolute(".\\x64\\Assets\\sprites\\fox\\fox_default.png").generic_string().c_str());