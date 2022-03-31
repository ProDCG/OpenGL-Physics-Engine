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

void input_processor(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const unsigned int width = 800;
const unsigned int height = 800;

float rotational_multiplier = 15.0f;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

GLfloat pyr_vertices[] = {
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.5f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

GLfloat cub_vertices[] = {
	0.5f
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

glm::vec3 coords[3] = {
	glm::vec3(-2.0f, -0.5f, -10.0f),
	glm::vec3(2.0f,  -0.5f, -10.0f),
	glm::vec3(0.0f, -2.0f, -5.0f)
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

	const char* vertexFileAddress = "C:\\Users\\mason\\OneDrive\\School\\High School\\2021-2022\\Adv Progamming Topics\\SemesterProject\\ProjectFiles\\3DPhysicsEngine\\3DPhysicsEngine\\main.vert";
	const char* fragmentFileAddress = "C:\\Users\\mason\\OneDrive\\School\\High School\\2021-2022\\Adv Progamming Topics\\SemesterProject\\ProjectFiles\\3DPhysicsEngine\\3DPhysicsEngine\\main.frag";
	/*Shader shaderProgram("main.vert", "main.frag");*/
	Shader shaderProgram(vertexFileAddress, fragmentFileAddress);

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(pyr_vertices, sizeof(pyr_vertices));

	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string catPath = "\popcat.jpg";
	std::string catPath2 = "C:\\Users\\mason\\OneDrive\\School\\High School\\2021-2022\\Adv Progamming Topics\\SemesterProject\\ProjectBuildFiles\\Textures\\awesomeface.png";
	std::cout << (catPath2) << std::endl;
	Texture catTex((catPath2).c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	catTex.texUnit(shaderProgram, "tex0", 0);

	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		input_processor(window);
		framebuffer_size_callback(window, width, height);
		//glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProgram.Activate();

		// rotational multiplier approach
		double crntTime = glfwGetTime();
		rotation = (static_cast<float>(crntTime)) * rotational_multiplier;

		// incrementative approach
		//double crntTime = glfwGetTime();
		//if (crntTime - prevTime >= 1 / 60) {
		//	rotation += 0.05f;
		//	prevTime = crntTime;
		//}

		for (int i = 0; i < sizeof(coords); i++) {
			glm::mat4 model = glm::mat4(1.0f);
			glm::mat4 view = glm::mat4(1.0f);
			glm::mat4 proj = glm::mat4(1.0f);

			model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
			view = glm::translate(view, /*glm::vec3(-2.0f, -0.5f, -10.0f)*/coords[i]);
			proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

			int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

			glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		}
		

		glUniform1f(uniID, 0.5f);
		catTex.Bind();
		VAO1.Bind();

		
		glfwSwapBuffers(window);
		glfwPollEvents();
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
	else if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
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
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}