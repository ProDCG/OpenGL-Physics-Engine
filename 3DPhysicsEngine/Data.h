#ifndef DATA_H
#define DATA_H

extern class Data {

public:
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	void updateTime();
};

#endif