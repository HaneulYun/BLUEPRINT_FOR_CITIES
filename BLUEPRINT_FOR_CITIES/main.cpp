//#include "App.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "shader.hpp"
#include "texture.hpp"
#include "controls.hpp"
#include "objloader.hpp"

using namespace glm;

GLFWwindow* window;

std::vector< glm::vec3 > vertices;

GLuint VertexArrayID;

GLuint programID;
GLuint matrixID;
GLuint viewMatrixID;
GLuint modelMatrixID;

GLuint texture;
GLuint textureID;

GLuint lightID;

GLuint vertexbuffer;
GLuint uvbuffer;
GLuint normalbuffer;

int initWindow();
void init();
void update();
void render();
void release();

int main(int argc, char* argv[])
{
	//char name[] = "BLUEPRINT_FOR_CITIES";
	//App* app = App::create(argc, argv); // single tone
	//app->initialize(100, 100, 800, 600, name);
	//return app->run();

	initWindow();
	init();

	do {
		update();
		render();
	} // 만약 ESC 키가 눌러졌는지 혹은 창이 닫혔는지 체크 체크
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	release();
}


int initWindow()
{
	if (!glfwInit())
	{
		fprintf(stderr, "GLFW 초기화 실패\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x 안티에일리어싱
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3 을 쓸 겁니다
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS 가 기분 좋아짐; 꼭 필요한 부분은 아님
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //옛날 OpenGL은 원하지 않아요

	// 새창을 열고, OpenGL 컨텍스트를 생성
	window = glfwCreateWindow(1024, 768, "Tutorial 01", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "GLFW 윈도우를 여는데 실패했습니다. Intel GPU 를 사용한다면, 3.3 지원을 하지 않습니다. 2.1 버전용 튜토리얼을 시도하세요.\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // GLEW 초기화
	glewExperimental = true; // 코어 프로파일을 위해 필요함
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	glEnable(GL_CULL_FACE);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glfwPollEvents();
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
}

void init()
{
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	programID = LoadShaders("StandardShading.vertexshader", "StandardShading.fragmentshader");
	matrixID = glGetUniformLocation(programID, "MVP");
	viewMatrixID = glGetUniformLocation(programID, "V");
	modelMatrixID = glGetUniformLocation(programID, "M");

	texture = loadBMP_custom("resources/T_PolygonCity_Texture_01_A.bmp");
	textureID = glGetUniformLocation(programID, "myTextureSampler");

	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals;
	bool res = loadOBJ("resources/SM_Env_Tree_03_Internal.obj", vertices, uvs, normals);

	for (auto& v : vertices)
		v /= 400.f;

	mat4 projection = perspective(radians(45.f), 4.f / 3.f, 0.1f, 100.f);
	mat4 view = lookAt(vec3(4, 3, 3), vec3(0, 0, 0), vec3(0, 1, 0));
	mat4 model = mat4(1.f);
	mat4 mvp = projection * view * model;

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(vec2), &uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

	glUseProgram(programID);
	lightID = glGetUniformLocation(programID, "LightPosition_worldspace");
}

void update()
{
	glUseProgram(programID);

	computeMatricesFromInputs();
	mat4 projectionMatrix = getProjectionMatrix();
	mat4 viewMatrix = getViewMatrix();
	mat4 modelMatrix = mat4(1.f);
	mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);
}

void render()
{
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	vec3 lightPos = vec3(4, 4, 4);
	glUniform3f(lightID, lightPos.x, lightPos.y, lightPos.z);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glUniform1i(textureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// 2nd attribute buffer : colors
	//glEnableVertexAttribArray(1);
	//glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	//glVertexAttribPointer(
	//	1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
	//	3,                                // size
	//	GL_FLOAT,                         // type
	//	GL_FALSE,                         // normalized?
	//	0,                                // stride
	//	(void*)0                          // array buffer offset
	//);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, vertices.size()); // 12*3 indices starting at 0 -> 12 triangles -> 6 squares

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	// 버퍼들을 교체
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void release()
{
	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &textureID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}