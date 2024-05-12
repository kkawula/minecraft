#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <GL/glew.h>


class VertexBuffer {
private:
    GLuint vboID;

public:
    VertexBuffer(const void* data, GLuint size) {
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    ~VertexBuffer() {
        glDeleteBuffers(1, &vboID);
    }

    void Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
    }

    void Unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
};

#endif // VERTEX_BUFFER_H
