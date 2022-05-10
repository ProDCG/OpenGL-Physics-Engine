#ifndef DATA_H
#define DATA_H

class Data {
public:
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	void updateTime(float dt) {
		Data::deltaTime = dt;
	}
};

#endif