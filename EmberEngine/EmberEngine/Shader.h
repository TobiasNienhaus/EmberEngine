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

	void SetBool(const char* name, bool value) const;
	void SetInt(const char* name, int value) const;
	void SetFloat(const char* name, float value) const;
	void SetFloat(const char* name, float v1, float v2) const;
	void SetFloat(const char* name, float v1, float v2, float v3) const;
	void SetFloat(const char* name, float v1, float v2, float v3, float v4) const;
	void SetMat4(const char* name, glm::mat4 value) const;
};

