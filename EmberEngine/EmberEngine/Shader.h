#pragma once
#include "OpenGLLibraries.h"
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>

class Shader
{
private:
	bool validProgram;
	bool validFragment;
	bool validVertex;
	bool valid() { return validFragment && validVertex && validProgram; }

	std::string getShaderContent(const char* path);

	GLuint shaderProgram;
	GLuint fragShaderLoc;
	GLuint vertShaderLoc;

	void createProgram();
	void setFragmentShader(const char* path);
	void setVertexShader(const char* path);

	bool getShaderCompileState(GLuint shader);

public:
	Shader(const char* fragmentShaderPath, const char* vertexShaderPath);
	
	void Cleanup();
	void Use();

	GLuint GetProgramLoc() { return shaderProgram; }
};

