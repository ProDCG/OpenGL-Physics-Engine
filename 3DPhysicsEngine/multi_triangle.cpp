#include <glad.h>
#include <glfw3.h>
// hello world modified code
#include <iostream>
// hello world try part 2
// why isnt this working lmao
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SRC_WIDTH = 800;
const unsigned int SRC_HEIGHT = 800;

const char* vertexShaderSource = "#version 420 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.y, 1.0);\n"
"    vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
"}\0";

const char* fragmentShaderSourceRed = "#version 420 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;\n"
"void main()\n"
"{\n"
//"    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
"    FragColor = vertexColor;\n"
"}\0";

const char* fragmentShaderSourceYellow = "#version 420 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\0";

const char* fragmentShaderSourceGreen = "#version 420 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
"}\0";

const char* fragmentShaderSourceBlue = "#version 420 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
"}\0";

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, "OpenGL Practice", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShaderRed = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int fragmentShaderGreen = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int fragmentShaderBlue = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int shaderProgramRed = glCreateProgram();
    unsigned int shaderProgramYellow = glCreateProgram();
    unsigned int shaderProgramGreen = glCreateProgram();
    unsigned int shaderProgramBlue = glCreateProgram();

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glShaderSource(fragmentShaderRed, 1, &fragmentShaderSourceRed, NULL);
    glCompileShader(fragmentShaderRed);
    glShaderSource(fragmentShaderYellow, 1, &fragmentShaderSourceYellow, NULL);
    glCompileShader(fragmentShaderYellow);
    glShaderSource(fragmentShaderGreen, 1, &fragmentShaderSourceGreen, NULL);
    glCompileShader(fragmentShaderGreen);
    glShaderSource(fragmentShaderBlue, 1, &fragmentShaderSourceBlue, NULL);
    glCompileShader(fragmentShaderBlue);

    // link first object
    glAttachShader(shaderProgramRed, vertexShader);
    glAttachShader(shaderProgramRed, fragmentShaderRed);
    glLinkProgram(shaderProgramRed);

    // link second object
    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramYellow);

    // link third objecct
    glAttachShader(shaderProgramGreen, vertexShader);
    glAttachShader(shaderProgramGreen, fragmentShaderGreen);
    glLinkProgram(shaderProgramGreen);

    // link fourth object
    glAttachShader(shaderProgramBlue, vertexShader);
    glAttachShader(shaderProgramBlue, fragmentShaderBlue);
    glLinkProgram(shaderProgramBlue);

    float vertices[] = {
        -0.75f, 0.75f, 0.0f, // top left
        0.0f, 0.75f, 0.0f, // top center
        0.75f, 0.75f, 0.0f, // top right
        -0.375f, 0.0f, 0.0f, // middle left
        0.375f, 0.0f, 0.0f, // middle right
        -0.75f, -0.75f, 0.0f, // bottom left
        0.0f, -0.75f, 0.0f, // bottom center
        0.75f, -0.75f, 0.0f, // bottom right
    };

    unsigned int indices[] = {
        0, 1, 3, // top left triangle
        1, 2, 4, // top right triangle
        5, 6, 3, // bottom left triangle
        7, 6, 4 // bottom right triangle
    };

    float first_triangle[] = {
        -0.75f, 0.75f, 0.0f, // top left
        0.0f, 0.75f, 0.0f, // top center
        -0.375f, 0.0f, 0.0f // middle left
    };

    float second_triangle[] = {
        0.75f, 0.75f, 0.0f, // top right
        0.0f, 0.75f, 0.0f, // top center
        0.375f, 0.0f, 0.0f // middle right
    };

    float third_triangle[] = {
        0.75f, -0.75f, 0.0f, // bottom right
        0.0f, -0.75f, 0.0f, // bottom center
        0.375f, 0.0f, 0.0f, // middle right
    };

    float fourth_triangle[] = {
        -0.75f, -0.75f, 0.0f, // bottom left
        0.0f, -0.75f, 0.0f, // bottom center
        -0.375f, 0.0f, 0.0f // middle left
    };

    unsigned int VAOs[4], VBOs[4];
    glGenVertexArrays(4, VAOs);
    glGenBuffers(4, VBOs);

    // first triangle
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(first_triangle), first_triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // second triangle
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(second_triangle), second_triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // third triangle
    glBindVertexArray(VAOs[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(third_triangle), third_triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // fourth triangle
    glBindVertexArray(VAOs[3]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(fourth_triangle), fourth_triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramRed);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgramYellow);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgramGreen);
        glBindVertexArray(VAOs[2]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgramBlue);
        glBindVertexArray(VAOs[3]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    else if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}