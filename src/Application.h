#ifndef MINECRAFT_APPLICATION_H
#define MINECRAFT_APPLICATION_H

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Window.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"

class Application {
private:
    Window window;
    Camera camera;
    Shader shader;
    GLuint VAO, VBO, texture;

public:
    Application() : camera(glm::vec3(0.0f, 0.0f, 3.0f)), shader("path/to/vertex_shader.vs", "path/to/fragment_shader.fs") {
        setupOpenGL();
        setupShaders();
        setupTextures();
    }

    void setupOpenGL() {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void setupShaders() {
        // Setup vertex data, buffers and configure vertex attributes
        GLfloat vertices[] = {
                // Define vertices and texture coordinates
        };
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void setupTextures() {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        // Texture parameters and loading here
    }

    void run() {
        while (!window.shouldClose()) {
            GLfloat currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            window.pollEvents();
            doMovement();

            render();
            window.swapBuffers();
        }
    }

    void render() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use();

        // Bind textures and draw
        glBindVertexArray(VAO);
        // Draw elements here

        glBindVertexArray(0);
    }
};
#endif //MINECRAFT_APPLICATION_H
