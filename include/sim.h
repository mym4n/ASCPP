#include <raylib.h>
#include <entity.h>
#include <sim.cpp>
#pragma once

extern void ResolveUpdateFunctionID(Entity entity);

extern void CallUpdateFunctions(Entity entities[]);

extern void RenderEntity(Entity entity);

extern void RenderEntities(Entity entites[]);