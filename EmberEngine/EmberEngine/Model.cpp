#include "Model.h"

Model::Model(const GLfloat* verts, const GLuint* elements, int vertexCount, int elementCount) :
	verts(verts), elements(elements),
	vertexCount(vertexCount), elementCount(elementCount)
{
	vao = 0;
	vbo = 0;
	ebo = 0;
}

void Model::initBuffers()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexCount, verts, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementCount, elements, GL_STATIC_DRAW);
}
