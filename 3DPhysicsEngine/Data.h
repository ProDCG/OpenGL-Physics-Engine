#pragma once

extern class Data {

public:
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	void updateTime();
};