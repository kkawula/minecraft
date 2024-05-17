#pragma once

// Std. Includes
#include <vector>

// GL Includes
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "input/Keyboard.h"

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// Default camera values
const GLfloat YAW         = -90.0f;
const GLfloat PITCH       =  0.0f;
const GLfloat SPEED       =  30.0f;//6.0f;
const GLfloat SENSITIVITY =  0.25f;
const GLfloat ZOOM        =  45.0f;


// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // Constructor with vectors
    Camera( glm::vec3 position = glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3 up = glm::vec3( 0.0f, 1.0f, 0.0f ), GLfloat yaw = YAW, GLfloat pitch = PITCH ) : front( glm::vec3( 0.0f, 0.0f, 1.0f ) ), movementSpeed( SPEED ), mouseSensitivity(SENSITIVITY ), zoom(ZOOM )
    {
        this->position = position;
        this->worldUp = up;
        this->yaw = yaw;
        this->pitch = pitch;
        this->updateCameraVectors( );
    }
    
    // Constructor with scalar values
    Camera( GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch ) : front( glm::vec3( 0.0f, 0.0f, -1.0f ) ), movementSpeed( SPEED ), mouseSensitivity(SENSITIVITY ), zoom(ZOOM )
    {
        this->position = glm::vec3( posX, posY, posZ );
        this->worldUp = glm::vec3( upX, upY, upZ );
        this->yaw = yaw;
        this->pitch = pitch;
        this->updateCameraVectors( );
    }
    
    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix( )
    {
        return glm::lookAt( this->position, this->position + this->front, this->up );
    }
    
    // Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void handleInput(Keyboard keyboard, GLfloat deltaTime)
    {
        GLfloat speedMultiplier = keyboard.isKeyDown(GLFW_KEY_LEFT_SHIFT) ? 2.0f : 1.0f;
        GLfloat velocity = this->movementSpeed * deltaTime * speedMultiplier;

        if(keyboard.isKeyDown(GLFW_KEY_W))
        {
            this->position += this->front * velocity;
        }
        
        if(keyboard.isKeyDown(GLFW_KEY_S))
        {
            this->position -= this->front * velocity;
        }

        if(keyboard.isKeyDown(GLFW_KEY_A))
        {
            this->position -= this->right * velocity;
        }
        
        if(keyboard.isKeyDown(GLFW_KEY_D))
        {
            this->position += this->right * velocity;
        }

        if(keyboard.isKeyDown(GLFW_KEY_SPACE))
        {
            position += worldUp * velocity;
        }

        if(keyboard.isKeyDown(GLFW_KEY_LEFT_CONTROL))
        {
            position -= worldUp * velocity;
        }
    }
    
    // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement( GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true )
    {
        xOffset *= this->mouseSensitivity;
        yOffset *= this->mouseSensitivity;
        
        this->yaw   += xOffset;
        this->pitch += yOffset;
        
        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        if ( constrainPitch )
        {
            if ( this->pitch > 89.0f )
            {
                this->pitch = 89.0f;
            }
            
            if ( this->pitch < -89.0f )
            {
                this->pitch = -89.0f;
            }
        }
        
        // Update Front, Right and Up Vectors using the updated Euler angles
        this->updateCameraVectors( );
    }
    
    // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll( GLfloat yOffset )
    {
        if ( this->zoom >= 1.0f && this->zoom <= 45.0f )
        {
            this->zoom -= yOffset;
        }
        
        if ( this->zoom <= 1.0f )
        {
            this->zoom = 1.0f;
        }
        
        if ( this->zoom >= 45.0f )
        {
            this->zoom = 45.0f;
        }
    }
    
    GLfloat GetZoom( )
    {
        return this->zoom;
    }

    glm::vec3 getPosition(){
        return position;
    }
    
private:
    // Camera Attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    // Euler Angles
    GLfloat yaw;
    GLfloat pitch;

    // Camera options
    GLfloat movementSpeed;
    GLfloat mouseSensitivity;
    GLfloat zoom;

    // Calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors( )
    {
        // Calculate the new Front vector
        glm::vec3 front;
        front.x = cos( glm::radians( this->yaw ) ) * cos( glm::radians( this->pitch ) );
        front.y = sin( glm::radians( this->pitch ) );
        front.z = sin( glm::radians( this->yaw ) ) * cos( glm::radians( this->pitch ) );
        this->front = glm::normalize( front );
        // Also re-calculate the Right and Up vector
        this->right = glm::normalize( glm::cross( this->front, this->worldUp ) );  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        this->up = glm::normalize( glm::cross( this->right, this->front ) );
    }
};