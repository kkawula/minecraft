#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <GL/glew.h>

#include "VertexBuffer.h"

class VertexArray {
private:
    GLuint vaoID;

public:
    VertexArray() {
        glGenVertexArrays(1, &vaoID);
    }

    ~VertexArray() {
        glDeleteVertexArrays(1, &vaoID);
    }

    void Bind() const {
        glBindVertexArray(vaoID);
    }

    void Unbind() const {
        glBindVertexArray(0);
    }

    void AddBuffer(const VertexBuffer& vb, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) {
        Bind();
        vb.Bind();
        glVertexAttribPointer(index, size, type, normalized, stride, pointer);
        glEnableVertexAttribArray(index);
        Unbind();
    }
};

#endif // VERTEX_ARRAY_H

