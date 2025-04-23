#pragma once

#include "glm/glm.hpp"
// #include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#ifndef GL_INCLUDED
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif

class Model {
    public:
        Model(GLfloat* vertices, GLint vLen, GLfloat r, GLfloat g, GLfloat b, bool bNormals);
        Model(GLfloat* vertices, GLint vLen, GLfloat* colors, bool bNormals);
        ~Model();
        GLuint vaoID;
        GLuint vertexVboID;
        GLuint colorVboID;
        GLuint normalVboID;
        GLuint indicesVboID;
        GLint vertexCount;
        GLfloat shinyness;
        glm::vec3 scale;
        void render();
        void renderUnsafe();
        static GLfloat* cubeVertices(GLfloat w, GLfloat h, GLfloat d);
    private:
        void storeData(GLint index, GLint size, GLint bufferLength, GLfloat* buffer, GLuint& vboID);
        GLfloat* getNormals(GLfloat* vertices, GLint vLen, GLfloat* dest, bool bNormals);
        GLfloat* fillColorArray(GLfloat r, GLfloat g, GLfloat b, GLint len, GLfloat* buffer);
    };
