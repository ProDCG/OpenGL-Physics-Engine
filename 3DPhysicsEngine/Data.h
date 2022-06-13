#pragma once

#include "Cube.h"

extern class Data {

public:
	const Cube CUBE;
	
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	void updateTime();
};