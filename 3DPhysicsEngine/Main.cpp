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
	const char* vertexFileAddress = "C:\\Users\\mason\\OneDrive\\School\\High School\\2021-2022\\Adv Progamming Topics\\SemesterProject\\ProjectFiles\\3DPhysicsEngine\\3DPhysicsEngine\\main.vert";
	const char* fragmentFileAddress = "C:\\Users\\mason\\OneDrive\\School\\High School\\2021-2022\\Adv Progamming Topics\\SemesterProject\\ProjectFiles\\3DPhysicsEngine\\3DPhysicsEngine\\main.frag";
	Shader colorShader(vertexFileAddress, fragmentFileAddress);

	// cube object initializations
	VAO cubeVAO(arrayToVec(CUBE.indices));
	cubeVAO.Bind();

	VBO cubeVBO(CUBE.vertices, sizeof(CUBE.vertices));
	EBO cubeEBO(CUBE.indices, sizeof(CUBE.indices));

	cubeVAO.LinkAttrib(cubeVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	cubeVAO.Unbind();
	cubeVBO.Unbind();
	cubeEBO.Unbind();

	// object array
	Object objList[] = {
		Object(1.0f, &cubeVAO, &colorShader, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 0.0f), false),
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

		for (int i = 0; i < sizeof(objList) / sizeof(objList[0]); i++) {
			// bind the current object type and shader, and then set the color. create a camera matrix based on the object
			objList[i].bindObject();
			objList[i].bindShader();


			camera.Matrix(45.0f, 0.1f, 100.0f, colorShader, "camMatrix", objList[i]);

			// vertice or indice based rendering
			//glDrawArrays(GL_TRIANGLES, 0, 36);
			glDrawElements(GL_TRIANGLES, 100, GL_UNSIGNED_INT, 0);

			// Uncomment for physics simulations
			//objList[i].setForce(glm::vec3(0.5f, -2.0f, 1.0f));
			//objList[i].update(DATA.deltaTime);
		} 

		// swap buffers and handle all GLFW events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// clean up memory
	cubeVAO.Delete();
	cubeVBO.Delete();
	cubeEBO.Delete();
	colorShader.Delete();

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