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
#include "ChunkManager.h"

#include "player/Player.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"

#include <filesystem>
namespace fs = std::filesystem;

// Properties
int SCREEN_WIDTH, SCREEN_HEIGHT;

//Input devices
Keyboard keyboard = Keyboard();
Mouse mouse = Mouse();

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void ScrollCallback( GLFWwindow *window, double xOffset, double yOffset );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void MouseButtonCallback( GLFWwindow *window, int button, int action, int mods );

bool hasChunkCordsChanged();
void updateMeshes(World &world, ChunkManager &chunkManager);
GLfloat lastX = config::WINDOW_WIDTH / 2.0;
GLfloat lastY = config::WINDOW_HEIGHT / 2.0;

void DoMovement(World &world);

// Camera
glm::vec3 startingPosition = glm::vec3( -0.0f, 100.0f, 0.0f );
Camera camera(startingPosition);

bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

int cordX = 0;
int cordZ = 0;
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
    window.setMouseButtonCallback(MouseButtonCallback);

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

    ChunkManager chunkManager(meshAtlas, camera, world);

    Renderer renderer(meshAtlas);

    // Game loop
    while (!window.ShouldClose()) {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        DoMovement(world);

        if (hasChunkCordsChanged()) {
            chunkManager.updateCords(cordX, cordZ);
        }

        if(!world.getCordsToUpdate().empty()){
            updateMeshes(world, chunkManager);
        }

        glClearColor(0.43f, 0.69f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderer.Render(camera);

        // Swap buffers
        window.swapBuffers();
    }

    glfwTerminate( );
    
    return EXIT_SUCCESS;
}

bool hasChunkCordsChanged() {
    int x = camera.getPosition().x;
    int z = camera.getPosition().z;

    int X = x;
    int Z = z;
    if(x < 0) X++;
    if(z < 0) Z++;
    auto chunkX = X / config::CHUNK_SIZE;
    auto chunkZ = Z / config::CHUNK_SIZE;
    if (x < 0) chunkX--;
    if (z < 0) chunkZ--;

    if (chunkX != cordX || chunkZ != cordZ) {
        cordX = chunkX;
        cordZ = chunkZ;
        return true;
    }
    return false;
}

void updateMeshes(World &world, ChunkManager &chunkManager){
    std::vector<std::pair<int, int>> chunkCordsToUpdate = world.getCordsToUpdate();
    if(!chunkCordsToUpdate.empty())
    {
        for(std::pair<int, int> cords : chunkCordsToUpdate)
        {
            int globalX = cords.first;
            int globalZ = cords.second;
            std::pair<int, int> chunkCords = World::GetChunkCords(globalX, globalZ);
            chunkManager.updateChunkMesh(chunkCords.first, chunkCords.second);

            std::pair<int, int> localCords = World::GetLocalCords(globalX, globalZ);
            if(localCords.first == 0)
                chunkManager.updateChunkMesh(chunkCords.first - 1, chunkCords.second);
            else if(localCords.first == 15)
                chunkManager.updateChunkMesh(chunkCords.first + 1, chunkCords.second);
            if(localCords.second == 0)
                chunkManager.updateChunkMesh(chunkCords.first, chunkCords.second - 1);
            else if(localCords.second == 15)
                chunkManager.updateChunkMesh(chunkCords.first, chunkCords.second + 1);
        }
        world.clearCordsToUpdate();
    }
}

// Moves/alters the camera positions based on user input
void DoMovement(World &world)
{
    player.update(keyboard, mouse, camera, world, deltaTime);
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    keyboard.KeyCallback(window, key, scancode, action, mode);
}

void MouseButtonCallback( GLFWwindow *window, int button, int action, int mods )
{
    mouse.buttonCallback(window, button, action, mods);
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
    
    player.handleMouseMovement(camera, xOffset, yOffset);
}


void ScrollCallback( GLFWwindow *window, double xOffset, double yOffset )
{
    player.handleMouseScroll(camera, yOffset);
}