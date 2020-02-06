#include "OpenGLLibraries.h"
#include <iostream>
#include <chrono>
#include "Shader.h"

#define ROTATE
//const char* img = "kitten.png";
const char* img = "cube.png";

float verts[] = {
	//  Position            Color             Texcoords
		-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
		 0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
		-0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.5f, // center-left
		 0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, // center-right
		 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
};

int side = 0;
int tri = 6;
//#define INCREMENT
//#define SINGLETRI

GLfloat cube[] = {
	//A 0 
	-0.5f, -0.5f,  0.5f, 0.0f, 0.5f,
	//B 1 
	 0.5f, -0.5f,  0.5f, 0.2f, 0.5f,
	//C 2 
	-0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
	//D 3 
	 0.5f,  0.5f,  0.5f, 0.2f, 0.0f,
	//E 4 
	-0.5f, -0.5f, -0.5f, 0.6f, 0.5f,
	//F 5 
	 0.5f, -0.5f, -0.5f, 0.4f, 0.5f,
	//G 6 
	-0.5f,  0.5f, -0.5f, 0.6f, 0.0f,
	//H 7 
	 0.5f,  0.5f, -0.5f, 0.4f, 0.0f,

	//A' 8 
	-0.5f, -0.5f,  0.5f, 0.6f, 1.0f,
	//B' 9 
	 0.5f, -0.5f,  0.5f, 0.4f, 1.0f,
	//C' 10
	-0.5f,  0.5f,  0.5f, 0.8f, 1.0f,
	//D' 11
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
	//G' 12
	-0.5f,  0.5f, -0.5f, 0.8f, 0.5f,
	//H' 13
	 0.5f,  0.5f, -0.5f, 1.0f, 0.5f,
	
	//floor
	-1.0f, -1.0f, -0.5f, 0.0f, 0.0f,
	 1.0f, -1.0f, -0.5f, 1.0f, 0.0f,
	 1.0f,  1.0f, -0.5f, 1.0f, 1.0f,
	 1.0f,  1.0f, -0.5f, 1.0f, 1.0f,
	-1.0f,  1.0f, -0.5f, 0.0f, 1.0f,
	-1.0f, -1.0f, -0.5f, 0.0f, 0.0f
};

GLuint cubeEBO[]
{
	//0
	0, 1, 3,
	0, 3, 2,
	//1
	1, 5, 7,
	1, 7, 3,
	//2
	5, 4, 6,
	5, 6, 7,
	//3
	4, 5, 9,
	9, 4, 8,
	//4
	4, 8, 10,
	4, 10, 12,
	//5
	12, 10, 11,
	12, 11, 13
};

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Ember", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
	
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeEBO), cubeEBO, GL_STATIC_DRAW);

	Shader s = Shader("res/shader/frag.glsl", "res/shader/vert.glsl");
	GLuint program = s.GetProgramLoc();
	s.Use();

	// Specify the layout of the vertex data
	GLint posAttrib = glGetAttribLocation(program, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

	/*GLint colAttrib = glGetAttribLocation(program, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 
		8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));*/

	GLint texAttrib = glGetAttribLocation(program, "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 
		5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	
	GLuint textures[2];
	glGenTextures(2, textures);

	int width, height;
	unsigned char* image;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	image = SOIL_load_image(img, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glUniform1i(glGetUniformLocation(program, "tex"), 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_WRAP_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_WRAP_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	image = SOIL_load_image(img, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glUniform1i(glGetUniformLocation(program, "tex2"), 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_WRAP_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_WRAP_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	auto t_start = std::chrono::high_resolution_clock::now();

	// Set up projection
	glm::mat4 view = glm::lookAt(
		glm::vec3(2.5f, 2.5f, 2.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	);
	GLint uniView = glGetUniformLocation(program, "view");
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

	GLint uniProj = glGetUniformLocation(program, "proj");

	GLint uniColor = glGetUniformLocation(program, "overrideColor");
	glUniform3f(uniColor, 1.0f, 1.0f, 1.0f);

	int count = 0;
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		auto t_now = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
		
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0, 0, .5f));
#ifdef ROTATE
		model = glm::rotate(model, time * glm::radians(66.66f), 
			glm::vec3(0.0f, 0.0f, 1.0f));
#endif
		GLint uniModel = glGetUniformLocation(program, "model");
		glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(program, "time"), time);

		glm::mat4 proj = glm::perspective(45.f,
			800.0f / 600.0f, 0.01f, 10.0f);
		//proj = glm::rotate(proj, glm::radians(360.0f) * 0.333f,
		//	glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

		//glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
#ifdef SINGLETRI
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 
			(void*)(tri * 3 * sizeof(GLuint)));
#else
		glDrawElements(GL_TRIANGLES, 12*3, GL_UNSIGNED_INT, 0);
#endif

		

		glEnable(GL_STENCIL_TEST);
			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
			glStencilMask(0xFF);
			glDepthMask(GL_FALSE);
			glClear(GL_STENCIL_BUFFER_BIT);

			glUniform3f(uniColor, 0.f, 0.f, 0.f);
			glDrawArrays(GL_TRIANGLES, 14, 6);
			glUniform3f(uniColor, 1.f, 1.f, 1.f);

			glStencilFunc(GL_EQUAL, 1, 0xFF);
			glStencilMask(0x00);
			glDepthMask(GL_TRUE);

			model = glm::scale(
				glm::translate(model, glm::vec3(0, 0, -1.5f)),
				glm::vec3(1, 1, -1)
			);
			glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
			glUniform3f(uniColor, 0.3f, 0.3f, 0.3f);
			glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_INT, 0);
			glUniform3f(uniColor, 1.f, 1.f, 1.f);
		glDisable(GL_STENCIL_TEST);

		glfwSwapBuffers(window);
	}

	s.Cleanup();

	glDeleteBuffers(1, &vbo);

	glDeleteVertexArrays(1, &vao);
	glfwTerminate();
}
