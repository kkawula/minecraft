// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "utils/Shader.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"
#include "render/Renderer.h"
#include "config.h"
#include "mesh/ChunkMeshGenerator.h"
#include "mesh/MeshAtlas.h"
#include "utils/FileSystem.h"
#include "player/Player.h"
#include "input/Keyboard.h"

#include <filesystem>
namespace fs = std::filesystem;

// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

//Keyboard
Keyboard keyboard = Keyboard();

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void ScrollCallback( GLFWwindow *window, double xOffset, double yOffset );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement(World world);

// Camera
glm::vec3 startingPosition = glm::vec3( -0.0f, 100.0f, 0.0f );
Camera camera(startingPosition);
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

Player player(startingPosition);

// The MAIN function, from here we start our application and run our Game loop
int main(int argc, char *argv[])
{
    Window window(config::WINDOW_WIDTH, config::WINDOW_HEIGHT, "Minecraft");
    FileSystem::initialize(argv[0]);


    // Set the required callback functions
    window.setCursorPosCallback(MouseCallback);
    window.setKeyCallback(KeyCallback);
    window.setScrollCallback(ScrollCallback);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    glfwGetFramebufferSize( window.window, &SCREEN_WIDTH, &SCREEN_HEIGHT );

    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );

    // Setup some OpenGL options
    glEnable( GL_DEPTH_TEST );
    
    // enable alpha support
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    World world;

    MeshAtlas meshAtlas;

    ChunkMeshGenerator chunkMeshGenerator(world, meshAtlas);
    chunkMeshGenerator.setupMeshes();

    Renderer renderer(meshAtlas);

    // Game loop
    while (!window.ShouldClose()) {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        DoMovement(world);

        glClearColor(0.43f, 0.69f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderer.Render(camera);

        // Swap buffers
        window.swapBuffers();
    }

    glfwTerminate( );
    
    return EXIT_SUCCESS;
}

void DoMovement(World world)
{
    camera.handleInput(keyboard, deltaTime);
    player.updatePosition(camera);
    std::cout << camera.getPosition().x << " " << camera.getPosition().y << " " << camera.getPosition().z << "\t" << player.position.x << " " << player.position.y << " " << player.position.z << "\n";
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    keyboard.KeyCallback(window, key, scancode, action, mode);
}

void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}


void ScrollCallback( GLFWwindow *window, double xOffset, double yOffset )
{
    camera.ProcessMouseScroll( yOffset );
}
