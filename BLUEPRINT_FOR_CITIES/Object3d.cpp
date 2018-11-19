#include <random>

#include <gl/glew.h>
#include <gl/gl.h>
#include <glm/gtx/transform.hpp>

#include "Object3d.h"

#include "shader.hpp"
#include "texture.hpp"
#include "controls.hpp"
#include "objloader.hpp"

using namespace glm;

Object3d::Object3d()
{
}

Object3d::~Object3d()
{
}

void Object3d::initialize()
{
	programID = LoadShaders("StandardShading.vertexshader", "StandardShading.fragmentshader");
	matrixID = glGetUniformLocation(programID, "MVP");
	viewMatrixID = glGetUniformLocation(programID, "V");
	modelMatrixID = glGetUniformLocation(programID, "M");

	texture = loadBMP_custom(urlBMP.c_str());
	textureID = glGetUniformLocation(programID, "myTextureSampler");

	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals;

	bool res = loadOBJ(urlOBJ.c_str(), vertices, uvs, normals);
	for (auto& v : vertices)
		v /= 400.f;
	verticesSize = vertices.size();

	//mat4 projection = perspective(radians(45.f), 4.f / 3.f, 0.1f, 100.f);
	//mat4 view = lookAt(vec3(4, 3, 3), vec3(0, 0, 0), vec3(0, 1, 0));
	//mat4 model = mat4(1.f);
	//mat4 mvp = projection * view * model;

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

void Object3d::update()
{
	glUseProgram(programID);
}

void Object3d::render()
{
	Object::preRender();

	vec3 lightPos = vec3(40 * cos(radian), 40 * sin(radian), 0);
	glUniform3f(lightID, lightPos.x, lightPos.y, lightPos.z);

	mat4 projectionMatrix = getProjectionMatrix();
	mat4 viewMatrix = getViewMatrix();
	mat4 modelMatrix = mat;
	mat4 mvp = getProjectionMatrix() * getViewMatrix() * modelMatrix;
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glUniform1i(textureID, 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, verticesSize);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	Object::postRender();
}

void Object3d::release()
{
	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteTextures(1, &textureID);
	glDeleteProgram(programID);
}

void Object3d::setBMP(std::string _url)
{
	urlBMP = _url;
}

void Object3d::setOBJ(std::string _url)
{
	urlOBJ = _url;
}