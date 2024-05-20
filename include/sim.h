#include <raylib.h>
#include <entity.h>
#include <sim.cpp>
#pragma once

extern void ResolveUpdateFunctionID(Entity entity);

extern void CallUpdateFunctions(Entity entities[]);

void test();