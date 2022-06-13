#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <array>

class Cube {
public:
    std::array<GLfloat, 108> vertices{
            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
    };

    GLfloat vertices2[108] = {
            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
    };

    GLfloat vertices3[12] = {
        // front face
         0.5f, 0.5f, 0.5f,
         -0.5f, 0.5f, 0.5f,
        //-0.5f, -0.5f,  0.5f,
    };

    GLfloat vertices4[72] = {
        // face one
        -0.5f,  0.0f, -0.5f, 
        -0.5f,  1.0f, -0.5f, 
        0.5f, 0.0f, -0.5f, 
        0.5f, 1.0f, -0.5f, 

        // face two (4)
        0.5f, 0.0f, -0.5f, 
        0.5f, 1.0f, -0.5f, 
        0.5f, 0.0f, 0.5f, 
        0.5f, 1.0f, 0.5f, 

        // face three (8)
        0.5f, 0.0f, 0.5f, 
        0.5f, 1.0f, 0.5f, 
        -0.5f, 0.0f, 0.5f, 
        -0.5f, 1.0f, 0.5f, 

        // face four (12) top
        -0.5f, 1.0f, -0.5f, 
        0.5f, 1.0f, -0.5f, 
        -0.5f, 1.0f, 0.5f, 
        0.5f, 1.0f, 0.5f, 

        // face five (16) bottom
        -0.5f, 0.0f, -0.5f, 
        0.5f, 0.0f, -0.5f, 
        -0.5f, 0.0f, 0.5f, 
        0.5f, 0.0f, 0.5f, 

        // face six (20)
        -0.5f, 0.0f, 0.5f, 
        -0.5f, 1.0f, 0.5f, 
        -0.5f, 0.0f, -0.5f, 
        -0.5f, 1.0f, -0.5f, 
    };

    GLuint indices[3] = {
        0, 1, 
        //1, 2, 3
    };

    GLuint indices2[36] = {
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
};