#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>

const char* vertexSource = R"glsl(
		#version 150 core
		in vec2 position;
		in float color;

		out vec3 Color;
		
		void main()
		{
			Color = vec3(color);
			gl_Position = vec4(position.x, -position.y, 0.0, 1.0);
		}
		)glsl";
const char* fragmentSource = R"glsl(
		#version 150 core
		out vec4 outColor;
		in vec3 Color;
		void main()
		{
			outColor = vec4(vec3(1.0) - Color, 1.0);
		}
		)glsl";

float verts[] = {
	-0.5f,  0.5f, 0.25f, 0.0f, 0.0f, // Top-left
	 0.5f,  0.5f, 0.5f, 1.0f, 0.0f, // Top-right
	 0.5f, -0.5f, 0.75f, 0.0f, 1.0f, // Bottom-right
	-0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // Bottom-left
};

GLuint elements[] = {
	0, 1, 2,
	2, 3, 0
};

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(400, 200, "Ember", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), 
		elements, GL_STATIC_DRAW);
	
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLint statusVert;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &statusVert);
	if (statusVert != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
		std::cout << buffer << std::endl;
		return -999;
	}
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragmentSource, NULL);
	glCompileShader(fragShader);

	GLint statusFrag;
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &statusFrag);
	if (statusFrag != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(fragShader, 512, NULL, buffer);
		std::cout << buffer << std::endl;
		return -1000;
	}

	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragShader);
	glBindFragDataLocation(program, 0, "outColor");
	glLinkProgram(program);
	glUseProgram(program);

	GLint posAttrib = glGetAttribLocation(program, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
		5 * sizeof(float), 0);

	GLint colAttrib = glGetAttribLocation(program, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 1, GL_FLOAT, GL_FALSE,
		5 * sizeof(float), (void*)(2 * sizeof(float)));

	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	glfwTerminate();
}
