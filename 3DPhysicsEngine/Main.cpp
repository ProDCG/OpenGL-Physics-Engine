#include <filesystem>
namespace fs = std::filesystem;

#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdint.h>

#include "Texture.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"
#include "Data.h"
#include "Engine.h"
#include "DeleteWrapper.h"
#include "Rigidbody.h"

void input_processor(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int32_t width, int32_t height);
int32_t map_vals(int32_t initialVal, int32_t oldMin, int32_t oldMax, int32_t newMin, int32_t newMax);
int32_t randomVal(int32_t min, int32_t max);
std::vector<GLuint>	arrayToVec(GLuint arr[]);

Data DATA;

const unsigned int width = 1920;
const unsigned int height = 1080;

float rotational_multiplier = 15.0f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

GLfloat cube_vert3[] = {
	// front face
	-0.5f, -0.5f,  0.5f, // bottom left
	-0.5f,  0.5f,  0.5f, // top left
	 0.5f, -0.5f,  0.5f, // bottom right
	 0.5f,  0.5f,  0.5f, // top right

	// right face
	 0.5f, -0.5f,  0.5f, // bottom left
	 0.5f,  0.5f,  0.5f, // top left
	 0.5f, -0.5f, -0.5f, // bottom right
	 0.5f,  0.5f, -0.5f, // top right

	// back face
	 0.5f, -0.5f, -0.5f, // bottom left
	 0.5f,  0.5f, -0.5f, // top left
	-0.5f, -0.5f, -0.5f, // bottom right
	-0.5f,  0.5f, -0.5f, // top right

	// left face
	-0.5f, -0.5f, -0.5f, // bottom left
	-0.5f,  0.5f, -0.5f, // top left
	-0.5f, -0.5f,  0.5f, // bottom right
	-0.5f,  0.5f,  0.5f, // top right

	// bottom face
	 0.5f, -0.5f, -0.5f, // bottom left
	 0.5f, -0.5f,  0.5f, // top left
	-0.5f, -0.5f, -0.5f, // bottom right
	-0.5f, -0.5f,  0.5f, // top right

	// top face
	 0.5f,  0.5f, -0.5f, // bottom left
	 0.5f,  0.5f,  0.5f, // top left
	-0.5f,  0.5f, -0.5f, // bottom right
	-0.5f,  0.5f,  0.5f, // top right
};

GLuint cube_indi3[] = {
	// front face
	0, 1, 3,
	0, 2, 3,

	// right face
	4, 5, 7,
	4, 6, 7,

	// back face
	8, 9, 11,
	8, 10, 11,

	// left face
	12, 13, 15,
	12, 14, 15,

	// bottom face
	16, 17, 19,
	16, 18, 19,

	// top face
	20, 21, 23,
	20, 22, 23,
};

int main() {
	Engine ENGINE;

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

	// introduces window into the current context
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, width, height);
	glfwSwapInterval(1);

	const char* vertexFileAddress = "C:\\Users\\mason\\OneDrive\\School\\High School\\2021-2022\\Adv Progamming Topics\\SemesterProject\\ProjectFiles\\3DPhysicsEngine\\3DPhysicsEngine\\main.vert";
	const char* fragmentFileAddress = "C:\\Users\\mason\\OneDrive\\School\\High School\\2021-2022\\Adv Progamming Topics\\SemesterProject\\ProjectFiles\\3DPhysicsEngine\\3DPhysicsEngine\\main.frag";
	/*Shader shaderProgram("main.vert", "main.frag");*/
	Shader shaderProgram(vertexFileAddress, fragmentFileAddress);

	//indices = std::vector<GLuint>(std::begin(cube_indices), std::end(cube_indices));
	VAO VAO2(arrayToVec(cube_indi3));
	VAO2.Bind();

	VBO VBO2(cube_vert3, sizeof(cube_vert3));

	EBO EBO2(cube_indi3, sizeof(cube_indi3));

	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	
	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();

	//std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	/*std::string awesomeFacePath = "C:\\Users\\mason\\OneDrive\\School\\High School\\2021-2022\\Adv Progamming Topics\\SemesterProject\\ProjectBuildFiles\\Textures\\awesomeface.png";
	std::string brickPath = "C:\\Users\\mason\\OneDrive\\School\\High School\\2021-2022\\Adv Progamming Topics\\SemesterProject\\ProjectBuildFiles\\Textures\\brick.png";
	std::string batmanPath = "C:\\Users\\mason\\OneDrive\\School\\High School\\2021-2022\\Adv Progamming Topics\\SemesterProject\\ProjectBuildFiles\\Textures\\batman.png";

	Texture faceTex((awesomeFacePath).c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	faceTex.texUnit(shaderProgram, "tex0", 0);
	Texture brickTex((brickPath).c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram, "tex0", 0);
	Texture batmanTex((batmanPath).c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	batmanTex.texUnit(shaderProgram, "tex0", 0);*/

	Rigidbody rbList[] = {
		Rigidbody(1.0f, &VAO2)
	};

	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	while (!glfwWindowShouldClose(window)) {

		DATA.updateTime();
		camera.dt = DATA.deltaTime;
		
		//std::cout << "DT: " << DATA.deltaTime << std::endl;

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		

		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader

		/*for (Rigidbody rb : objVec) {
			switch()
		}*/

		for (int i = 0; i < sizeof(rbList) / sizeof(rbList[0]); i++) {
			//rbList[i].textureType->Bind();
			rbList[i].objectType->Bind();  
			shaderProgram.Activate();
			shaderProgram.setVec3("color", glm::vec3(1.0f, 0.0f, 0.0f));
			// sizeof(rbList[i].objectType->indices.data()) / sizeof(rbList[0])
			camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix", rbList[i]);
			//glDrawArrays(GL_TRIANGLES, 0, 36);
			glDrawElements(GL_TRIANGLES, 100, GL_UNSIGNED_INT, 0);
			//rbList[i].setForce(glm::vec3(0.5f, -2.0f, 1.0f));
			//rbList[i].update(DATA.deltaTime);
		} 
			
		//camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix", rbList[0]);

		/*faceTex.Bind();
		VAO2.Bind();

		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix", objList[0]);
		glDrawElements(GL_TRIANGLES, sizeof(cube_indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		objList[0].updatePhysics(DATA.deltaTime);

		brickTex.Bind();
		VAO3.Bind();

		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix", objList[1]);
		glDrawElements(GL_TRIANGLES, sizeof(plane_indices) / sizeof(int), GL_UNSIGNED_INT, 0);*/
		//std::cout << "g: " << objList[0].gravity << std::endl;

		// Draw primitives, number of indices, datatype of indices, index of indices
		/*for (int i = 0; i < 9; i++) {
			camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix", objList[i]);
			glDrawElements(GL_TRIANGLES, sizeof(indices2) / sizeof(int), GL_UNSIGNED_INT, 0);
		}*/

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
		//glm::mat4 model = glm::mat4(1.0f);
		//model = glm::translate(model, coords[0]);
		//model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.3f, 0.5f));

		//// rotational multiplier approach
		//double crntTime = glfwGetTime();
		//rotation = (static_cast<float>(crntTime)) * rotational_multiplier;

		// incrementative approach
		//double crntTime = glfwGetTime();
		//if (crntTime - prevTime >= 1 / 60) {
		//	rotation += 0.05f;
		//	prevTime = crntTime;
		//}
		
		//catTex.Bind();
		//VAO1.Bind();

		//glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//glm::mat4 model = glm::mat4(1.0f);
		//glm::mat4 view = glm::mat4(1.0f);
		//glm::mat4 proj = glm::mat4(1.0f);

		//for (int i = 0; i < /*sizeof(pyr_vertices)*/3; i++) {
		//	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		//	view = glm::translate(view, /*glm::vec3(-2.0f, -0.5f, -10.0f)*/coords[i]);
		//	proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

		//	int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//	int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		//	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		//	int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		//	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		//	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		//}
		
		//glUniform1f(uniID, 0.5f);
		/*catTex.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);*/
	}

	VAO2.Delete();
	VBO2.Delete();
	EBO2.Delete();
	//faceTex.Delete();
	//brickTex.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void input_processor(GLFWwindow* window) {
	/*if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
		objList[0].gravity * -1;
		
	};*/
	/*else if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		rotational_multiplier += 0.05f;
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		rotational_multiplier -= 0.05f;
	}*/
}

void framebuffer_size_callback(GLFWwindow* window, int32_t width, int32_t height) {
	glViewport(0, 0, width, height);
}

int32_t map_vals(int32_t initialVal, int32_t oldMin, int32_t oldMax, int32_t newMin, int32_t newMax) {
	return (initialVal - oldMin) * (newMax + 1 - newMin) / (oldMax - oldMin) + newMin;
}

int32_t randomVal(int32_t min, int32_t max) {
	return map_vals(std::rand(), 0, RAND_MAX, min, max);
}

std::vector<GLuint>	arrayToVec(GLuint arr[]) {
	std::vector<GLuint> newVec;
	for (int i = 0; i < (sizeof(arr) / sizeof(arr[0])); i++) {
		newVec.push_back(arr[i]);
	}
	return newVec;
}