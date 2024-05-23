void ResolveUpdateFunctionID(Entity entity)
{
	switch (entity.updatefuncid)
	{
	case EntityID_Default:
		std::cout << "[INFO] prg called updateFunction on ID 0\n";
		break;
	default:
		std::cout << "Error! unknown updateFunctionID " << entity.updatefuncid << "\n";
		break;
	}
}

void CallUpdateFunctions(Entity entities[])
{
	// learn how to make this warning disapear lol
	int arraysize = sizeof(entities) / sizeof(Entity);

	for (int i = 0; i < arraysize; i++)
	{
		ResolveUpdateFunctionID(entities[i]);
	}
}

void RenderEntity(Entity entity)
{
	switch (entity.spriteid)
	{
		case EntityID_Default:
			DrawTexture(EntityTexture_Default, entity.position.x, entity.position.y, WHITE);
			break;
		case EntityID_Fox:
			DrawTexture(EntityTexture_Fox, entity.position.x, entity.position.y, WHITE);
			break;
	}
}

void RenderEntities(Entity entities[])
{
	// skibidi
	int arraysize = sizeof(entities) / sizeof(Entity);

	for (int i = 0; i < arraysize; i++)
	{
		RenderEntity(entities[i]);
	}
}