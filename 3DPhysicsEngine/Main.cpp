#include <filesystem>
namespace fs = std::filesystem;

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"

void input_processor(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const unsigned int width = 1920;
const unsigned int height = 1080;

float rotational_multiplier = 15.0f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,    0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 10.0f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

GLfloat vertices3[] = {
	-3.0f, -3.0f,  3.0f,     0.83f, 0.70f, 0.44f,    0.0f, 0.0f,
	-3.0f, -3.0f, -3.0f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 3.0f, -3.0f, -3.0f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 3.0f, -3.0f,  3.0f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 10.0f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

GLfloat vertices2[] =
{
	// face one (0)
	-0.5f,  0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
	-0.5f,  1.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,
	0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
	0.5f, 1.0f, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,

	// face two (4)
	0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
	0.5f, 1.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,
	0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
	0.5f, 1.0f, 0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,

	// face three (8)
	0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
	0.5f, 1.0f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,
	-0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
	-0.5f, 1.0f, 0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,

	// face four (12) top
	-0.5f, 1.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
	0.5f, 1.0f, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
	-0.5f, 1.0f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,
	0.5f, 1.0f, 0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,

	// face five (16) bottom
	-0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
	0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
	-0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,
	0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,

	// face six (20)
	-0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
	-0.5f, 1.0f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,
	-0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
	-0.5f, 1.0f, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,
};

GLuint indices2[] = {
	0, 2, 3,
	0, 1, 3,

	4, 6, 7,
	4, 5, 7,

	8, 10, 11,
	8, 9, 11,

	12, 13, 14,
	13, 14, 15,

	16, 17, 18,
	17, 18, 19,

	20, 22, 23,
	20, 21, 23
};

glm::vec3 coords[] = {
	glm::vec3(0.0f, 0.0f, 1.0f),
	glm::vec3(5.0f, 5.0f, 5.0f),
	glm::vec3(-5.0f, -5.0f, -5.0f)
};

GLuint indices3[] = {
	0, 1, 7
};

GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

int main() {
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

	const char* vertexFileAddress = "C:\\Users\\mason\\OneDrive\\School\\High School\\2021-2022\\Adv Progamming Topics\\SemesterProject\\ProjectFiles\\3DPhysicsEngine\\3DPhysicsEngine\\main.vert";
	const char* fragmentFileAddress = "C:\\Users\\mason\\OneDrive\\School\\High School\\2021-2022\\Adv Progamming Topics\\SemesterProject\\ProjectFiles\\3DPhysicsEngine\\3DPhysicsEngine\\main.frag";
	/*Shader shaderProgram("main.vert", "main.frag");*/
	Shader shaderProgram(vertexFileAddress, fragmentFileAddress);

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices2, sizeof(vertices2));

	EBO EBO1(indices2, sizeof(indices2));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	 
	/*VAO VAO2;
	VAO2.Bind();

	VBO VBO2(vertices3, sizeof(vertices3));*/

	// GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string awesomeFacePath = "C:\\Users\\mason\\OneDrive\\School\\High School\\2021-2022\\Adv Progamming Topics\\SemesterProject\\ProjectBuildFiles\\Textures\\brick.png";
	std::string brickPath = "C:\\Users\\mason\\OneDrive\\School\\High School\\2021-2022\\Adv Progamming Topics\\SemesterProject\\ProjectBuildFiles\\Textures\\john.png";
	Texture catTex((awesomeFacePath).c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	catTex.texUnit(shaderProgram, "tex0", 0);

	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
	  
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix", glm::vec3(1.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, sizeof(indices2) / sizeof(int), GL_UNSIGNED_INT, 0);
		//VBO1.ChangePosition(vertices, sizeof(vertices), coords[2]);
		// Binds texture so that is appears in rendering
		catTex.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		
		// Draw primitives, number of indices, datatype of indices, index of indices
		//glDrawElements(GL_TRIANGLES, sizeof(indices2) / sizeof(int), GL_UNSIGNED_INT, 0);
		
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

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	catTex.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void input_processor(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}