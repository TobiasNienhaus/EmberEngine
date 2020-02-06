#pragma once
#include "OpenGLLibraries.h"

class Model
{
private:
	const GLfloat* verts;
	const int vertexCount;

	const GLuint* elements;
	const int elementCount;

	GLuint vbo;
	GLuint vao;
	GLuint ebo;

	void initBuffers();

public:
	Model(const GLfloat* verts, const GLuint* elements, int vertexCount, int elementCount);
};

