

void ResolveUpdateFunctionID(Entity entity)
{
	switch (entity.updatefuncid)
	{
	case 0:
		break;
	default:
		std::cout << "Error! unknown updateFunctionID " << entity.updatefuncid << "\n";
		break;
	}
}

void test()
{
	std::cout << "penis\n";
}

void CallUpdateFunctions(Entity entities[])
{
	int arraysize = sizeof(entities) / sizeof(Entity);

	for (int i = 0; i < arraysize; i++)
	{

	}
}