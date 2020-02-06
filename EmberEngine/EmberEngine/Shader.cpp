#include "Shader.h"

Shader::Shader(const char* frag, const char* vert) :
	validFragment(false), validVertex(false), validProgram(false), 
	fragShaderLoc(0), vertShaderLoc(0), shaderProgram(0)
{
	setVertexShader(vert);
	setFragmentShader(frag);
	createProgram();
	std::cout << "Shader creation successful: " << valid() << std::endl;
}

void Shader::Cleanup()
{
	glDeleteProgram(shaderProgram);
	glDeleteShader(fragShaderLoc);
	glDeleteShader(vertShaderLoc);
}

void Shader::createProgram()
{
	if (!validFragment || !validVertex)
	{
		std::cout << "One of the shaders wasn't initialized properly" << std::endl;
		return;
	}
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertShaderLoc);
	glAttachShader(shaderProgram, fragShaderLoc);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
}

void Shader::setFragmentShader(const char* path)
{
	std::cout << "Fragment shader" << std::endl;
	validFragment = false;
	std::string source = getShaderContent(path);
	if (source.empty() || source == "")
	{
		std::cout << "Error when reading Fragment Shader " << path << std::endl;
		return;
	}
	const char* sourceptr = source.c_str();
	fragShaderLoc = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShaderLoc, 1, &sourceptr, NULL);
	glCompileShader(fragShaderLoc);
	if (!getShaderCompileState(fragShaderLoc))
	{
		std::cout << "Error when compiling fragment shader" << std::endl;
		return;
	}

	validFragment = true;
}

void Shader::setVertexShader(const char* path)
{
	std::cout << "Vertex shader" << std::endl;
	validVertex = false;
	std::string source = getShaderContent(path);
	if (source.empty() || source == "")
	{
		std::cout << "Error when reading Vertex Shader " << path << std::endl;
		return;
	}
	const char* sourceptr = source.c_str();
	vertShaderLoc = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShaderLoc, 1, &sourceptr, NULL);
	glCompileShader(vertShaderLoc);
	if (!getShaderCompileState(vertShaderLoc))
	{
		std::cout << "Error when compiling vertex shader" << std::endl;
		return;
	}
	validVertex = true;
}

std::string Shader::getShaderContent(const char* path)
{
	std::string ext = boost::filesystem::extension(path);
	if (ext != ".glsl")
	{
		std::cout << "Invalid filetype for fragment shader " << path << std::endl;
		return "";
	}
	std::ifstream file;
	file.open(path);

	if (!file)
	{
		std::cout << "Unable to open fragment shader at " << path << std::endl;
		return "";
	}

	std::string ret = "";
	while (!file.eof())
	{
		std::string temp = "";
		getline(file, temp);
		ret += temp + "\n";
	}
	file.close();

	std::cout << ret << std::endl;

	return ret;
}

bool Shader::getShaderCompileState(GLuint shader)
{
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(shader, 512, NULL, buffer);
		std::cout << "Error when compiling:\n" << buffer << std::endl;
		return false;
	}
	return true;
}

void Shader::Use()
{
	if (!valid())
		return;
	glUseProgram(shaderProgram);
}
