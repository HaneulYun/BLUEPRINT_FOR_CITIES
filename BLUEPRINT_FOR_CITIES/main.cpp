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

int main(int argc, char* argv[])
{
	//char name[] = "BLUEPRINT_FOR_CITIES";
	//App* app = App::create(argc, argv); // single tone
	//app->initialize(100, 100, 800, 600, name);
	//return app->run();

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

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint programID = LoadShaders("StandardShading.vertexshader", "StandardShading.fragmentshader");
	GLuint matrixID = glGetUniformLocation(programID, "MVP");
	GLuint viewMatrixID = glGetUniformLocation(programID, "V");
	GLuint modelMatrixID = glGetUniformLocation(programID, "M");

	GLuint texture = loadBMP_custom("resources/T_PolygonCity_Texture_01_A.bmp");
	GLuint textureID = glGetUniformLocation(programID, "myTextureSampler");

	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals;
	bool res = loadOBJ("resources/SM_Env_Tree_03_Internal.obj", vertices, uvs, normals);

	for (auto& v : vertices)
		v /= 400.f;

	mat4 projection = perspective(radians(45.f), 4.f / 3.f, 0.1f, 100.f);
	mat4 view = lookAt(vec3(4, 3, 3), vec3(0, 0, 0), vec3(0, 1, 0));
	mat4 model = mat4(1.f);
	mat4 mvp = projection * view * model;

	//static const GLfloat g_vertex_buffer_data[] = {
	//	-1.0f,-1.0f,-1.0f,
	//	-1.0f,-1.0f, 1.0f,
	//	-1.0f, 1.0f, 1.0f,
	//	 1.0f, 1.0f,-1.0f,
	//	-1.0f,-1.0f,-1.0f,
	//	-1.0f, 1.0f,-1.0f,
	//	 1.0f,-1.0f, 1.0f,
	//	-1.0f,-1.0f,-1.0f,
	//	 1.0f,-1.0f,-1.0f,
	//	 1.0f, 1.0f,-1.0f,
	//	 1.0f,-1.0f,-1.0f,
	//	-1.0f,-1.0f,-1.0f,
	//	-1.0f,-1.0f,-1.0f,
	//	-1.0f, 1.0f, 1.0f,
	//	-1.0f, 1.0f,-1.0f,
	//	 1.0f,-1.0f, 1.0f,
	//	-1.0f,-1.0f, 1.0f,
	//	-1.0f,-1.0f,-1.0f,
	//	-1.0f, 1.0f, 1.0f,
	//	-1.0f,-1.0f, 1.0f,
	//	 1.0f,-1.0f, 1.0f,
	//	 1.0f, 1.0f, 1.0f,
	//	 1.0f,-1.0f,-1.0f,
	//	 1.0f, 1.0f,-1.0f,
	//	 1.0f,-1.0f,-1.0f,
	//	 1.0f, 1.0f, 1.0f,
	//	 1.0f,-1.0f, 1.0f,
	//	 1.0f, 1.0f, 1.0f,
	//	 1.0f, 1.0f,-1.0f,
	//	-1.0f, 1.0f,-1.0f,
	//	 1.0f, 1.0f, 1.0f,
	//	-1.0f, 1.0f,-1.0f,
	//	-1.0f, 1.0f, 1.0f,
	//	 1.0f, 1.0f, 1.0f,
	//	-1.0f, 1.0f, 1.0f,
	//	 1.0f,-1.0f, 1.0f
	//};

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);

	//static const GLfloat g_color_buffer_data[] = {
	//0.583f,  0.771f,  0.014f,
	//0.609f,  0.115f,  0.436f,
	//0.327f,  0.483f,  0.844f,
	//0.822f,  0.569f,  0.201f,
	//0.435f,  0.602f,  0.223f,
	//0.310f,  0.747f,  0.185f,
	//0.597f,  0.770f,  0.761f,
	//0.559f,  0.436f,  0.730f,
	//0.359f,  0.583f,  0.152f,
	//0.483f,  0.596f,  0.789f,
	//0.559f,  0.861f,  0.639f,
	//0.195f,  0.548f,  0.859f,
	//0.014f,  0.184f,  0.576f,
	//0.771f,  0.328f,  0.970f,
	//0.406f,  0.615f,  0.116f,
	//0.676f,  0.977f,  0.133f,
	//0.971f,  0.572f,  0.833f,
	//0.140f,  0.616f,  0.489f,
	//0.997f,  0.513f,  0.064f,
	//0.945f,  0.719f,  0.592f,
	//0.543f,  0.021f,  0.978f,
	//0.279f,  0.317f,  0.505f,
	//0.167f,  0.620f,  0.077f,
	//0.347f,  0.857f,  0.137f,
	//0.055f,  0.953f,  0.042f,
	//0.714f,  0.505f,  0.345f,
	//0.783f,  0.290f,  0.734f,
	//0.722f,  0.645f,  0.174f,
	//0.302f,  0.455f,  0.848f,
	//0.225f,  0.587f,  0.040f,
	//0.517f,  0.713f,  0.338f,
	//0.053f,  0.959f,  0.120f,
	//0.393f,  0.621f,  0.362f,
	//0.673f,  0.211f,  0.457f,
	//0.820f,  0.883f,  0.371f,
	//0.982f,  0.099f,  0.879f
	//};
	//
	//GLuint colorbuffer;
	//glGenBuffers(1, &colorbuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	//static const GLfloat g_uv_buffer_data[] = {
	//	0.000059f, 0.000004f,
	//	0.000103f, 0.336048f,
	//	0.335973f, 0.335903f,
	//	1.000023f, 0.000013f,
	//	0.667979f, 0.335851f,
	//	0.999958f, 0.336064f,
	//	0.667979f, 0.335851f,
	//	0.336024f, 0.671877f,
	//	0.667969f, 0.671889f,
	//	1.000023f, 0.000013f,
	//	0.668104f, 0.000013f,
	//	0.667979f, 0.335851f,
	//	0.000059f, 0.000004f,
	//	0.335973f, 0.335903f,
	//	0.336098f, 0.000071f,
	//	0.667979f, 0.335851f,
	//	0.335973f, 0.335903f,
	//	0.336024f, 0.671877f,
	//	1.000004f, 0.671847f,
	//	0.999958f, 0.336064f,
	//	0.667979f, 0.335851f,
	//	0.668104f, 0.000013f,
	//	0.335973f, 0.335903f,
	//	0.667979f, 0.335851f,
	//	0.335973f, 0.335903f,
	//	0.668104f, 0.000013f,
	//	0.336098f, 0.000071f,
	//	0.000103f, 0.336048f,
	//	0.000004f, 0.671870f,
	//	0.336024f, 0.671877f,
	//	0.000103f, 0.336048f,
	//	0.336024f, 0.671877f,
	//	0.335973f, 0.335903f,
	//	0.667969f, 0.671889f,
	//	1.000004f, 0.671847f,
	//	0.667979f, 0.335851f
	//};

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(vec2), &uvs[0] , GL_STATIC_DRAW);

	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

	glUseProgram(programID);
	GLuint lightID = glGetUniformLocation(programID, "LightPosition_worldspace");

	do {
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);

		computeMatricesFromInputs();
		mat4 projectionMatrix = getProjectionMatrix();
		mat4 viewMatrix = getViewMatrix();
		mat4 modelMatrix = mat4(1.f);
		mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

		glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);
		glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
		glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);

		vec3 lightPos = vec3(4, 4, 4);
		glUniform3f(lightID, lightPos.x, lightPos.y, lightPos.z);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		glUniform1i(textureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

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
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

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

	} // 만약 ESC 키가 눌러졌는지 혹은 창이 닫혔는지 체크 체크
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);


	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &textureID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}