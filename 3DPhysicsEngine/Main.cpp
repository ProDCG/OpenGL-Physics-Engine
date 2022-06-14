// OpenGL libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// c++ std libraries
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <stdint.h>
#include <filesystem>
namespace fs = std::filesystem;

// header file imports
#include "Cube.h"
#include "Texture.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"
#include "Data.h"
#include "Engine.h"
#include "DeleteWrapper.h"
#include "Object.h"

// callback functions
void framebuffer_size_callback(GLFWwindow* window, int32_t width, int32_t height);
int32_t map_vals(int32_t initialVal, int32_t oldMin, int32_t oldMax, int32_t newMin, int32_t newMax);
int32_t randomVal(int32_t min, int32_t max);
std::vector<GLuint>	arrayToVec(GLuint arr[]);

// object declaration for global variable usage (deltaTime, object vertices, etc)
Data DATA;
Cube CUBE;

// window resolution
const unsigned int width = 1920;
const unsigned int height = 1080;

int main() {
	// OS-based initializations
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "3D Engine", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// introduces window into the current context and loads opengl
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, width, height);
	glfwSwapInterval(1);

	// get addresses of vertex and fragment files
	const char* vertexFileAddress = "C:\\Users\\mason\\OneDrive\\School\\High School\\2021-2022\\Adv Progamming Topics\\SemesterProject\\ProjectFiles\\3DPhysicsEngine\\3DPhysicsEngine\\opaqObj.vert";
	const char* fragmentFileAddress = "C:\\Users\\mason\\OneDrive\\School\\High School\\2021-2022\\Adv Progamming Topics\\SemesterProject\\ProjectFiles\\3DPhysicsEngine\\3DPhysicsEngine\\opaqObj.frag";
	Shader opaqueShader(vertexFileAddress, fragmentFileAddress);

	vertexFileAddress = "C:\\Users\\mason\\OneDrive\\School\\High School\\2021-2022\\Adv Progamming Topics\\SemesterProject\\ProjectFiles\\3DPhysicsEngine\\3DPhysicsEngine\\projObj.vert";
	fragmentFileAddress = "C:\\Users\\mason\\OneDrive\\School\\High School\\2021-2022\\Adv Progamming Topics\\SemesterProject\\ProjectFiles\\3DPhysicsEngine\\3DPhysicsEngine\\projObj.frag";
	Shader projectionShader(vertexFileAddress, fragmentFileAddress);

	// opaque cube
	VAO cubeVAO(arrayToVec(CUBE.indices));
	cubeVAO.Bind();

	VBO cubeVBO(CUBE.vertices, sizeof(CUBE.vertices));
	EBO cubeEBO(CUBE.indices, sizeof(CUBE.indices));

	cubeVAO.LinkAttrib(cubeVBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);

	cubeVAO.Unbind();
	cubeVBO.Unbind();
	cubeEBO.Unbind();

	// light cube
	VAO lightCubeVAO(arrayToVec(CUBE.indices));
	lightCubeVAO.Bind();

	VBO lightCubeVBO(CUBE.vertices, sizeof(CUBE.vertices));
	EBO lightCubeEBO(CUBE.indices, sizeof(CUBE.indices));

	lightCubeVAO.LinkAttrib(lightCubeVBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	lightCubeVAO.LinkAttrib(lightCubeVBO, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	lightCubeVAO.Unbind();
	lightCubeVBO.Unbind();
	lightCubeEBO.Unbind();

	// object array
	Object objList[] = {
		Object(1.0f, &cubeVAO, &projectionShader, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(0.2f, 0.2f, 0.2f)),
		Object(1.0f, &lightCubeVAO, &opaqueShader, glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)),
	};

	// camera initialization
	glEnable(GL_DEPTH_TEST);
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// update loop
	while (!glfwWindowShouldClose(window)) {

		// update time between each frame
		DATA.updateTime();
		camera.dt = DATA.deltaTime;

		// set background color and clear back and front buffers
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// handle camera inputs
		camera.Inputs(window);

		//for (int i = 0; i < sizeof(objList) / sizeof(objList[0]); i++) {
		//	// bind the current object type and shader, and then set the color. create a camera matrix based on the object
		//	objList[i].bindObject();
		//	objList[i].bindShader();
		//	camera.Matrix(45.0f, 0.1f, 100.0f, colorShader, "camMatrix", objList[i]);

		//	// vertice or indice based rendering
		//	//glDrawArrays(GL_TRIANGLES, 0, 36);
		//	glDrawElements(GL_TRIANGLES, 100, GL_UNSIGNED_INT, 0);

		//	// Uncomment for physics simulations
		//	//objList[i].setForce(glm::vec3(0.5f, -2.0f, 1.0f));
		//	//objList[i].update(DATA.deltaTime);
		//} 

		// light recieving object
		/*opaqueShader.Activate();
		opaqueShader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		opaqueShader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		opaqueShader.setVec3("lightPos", glm::vec3(1.2f, 1.0f, 2.0f));
		opaqueShader.setVec3("viewPos", camera.position);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)camera.width / (float)camera.height, 0.1f, 100.0f);
		opaqueShader.setMat4("projection", projection);
		opaqueShader.setMat4("view", camera.getViewMatrix());
		opaqueShader.setMat4("model", glm::mat4(1.0f));*/
		
		float time = glfwGetTime();
		
		// glow cube
		objList[0].bindObject();
		objList[0].bindShader();
		objList[0].position = glm::vec3(cos(time), sin(time), sin(time));
		objList[0].update(DATA.deltaTime);

		camera.Matrix(45.0f, 0.1f, 100.0f, projectionShader, "camMatrix", objList[0]);
		glDrawElements(GL_TRIANGLES, 100, GL_UNSIGNED_INT, 0);

		// opaque cube
		objList[1].bindObject();
		objList[1].bindShader();
		objList[1].shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		objList[1].shader->setVec3("lightPos", objList[0].position);
		objList[1].shader->setVec3("viewPos", camera.position);

		
		objList[1].update(DATA.deltaTime);

		camera.Matrix(45.0f, 0.1f, 100.0f, opaqueShader, "camMatrix", objList[1]);
		glDrawElements(GL_TRIANGLES, 100, GL_UNSIGNED_INT, 0);

		// swap buffers and handle all GLFW events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// clean up memory
	cubeVAO.Delete();
	cubeVBO.Delete();
	cubeEBO.Delete();
	lightCubeVAO.Delete();
	lightCubeVBO.Delete();
	lightCubeEBO.Delete();
	opaqueShader.Delete();
	projectionShader.Delete();

	// terminate the application
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

// window sizing update
void framebuffer_size_callback(GLFWwindow* window, int32_t width, int32_t height) {
	glViewport(0, 0, width, height);
}

// mapping function and random value generator based on a minimum and maximum
int32_t map_vals(int32_t initialVal, int32_t oldMin, int32_t oldMax, int32_t newMin, int32_t newMax) {
	return (initialVal - oldMin) * (newMax + 1 - newMin) / (oldMax - oldMin) + newMin;
}

int32_t randomVal(int32_t min, int32_t max) {
	return map_vals(std::rand(), 0, RAND_MAX, min, max);
}

// simple conversion
std::vector<GLuint>	arrayToVec(GLuint arr[]) {
	std::vector<GLuint> newVec;
	for (int i = 0; i < (sizeof(arr) / sizeof(arr[0])); i++) {
		newVec.push_back(arr[i]);
	}
	return newVec;
}