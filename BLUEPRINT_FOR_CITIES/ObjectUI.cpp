#include <random>

#include <gl/glew.h>
#include <gl/gl.h>
#include <glm/gtx/transform.hpp>

#include "ObjectUI.h"
#include "controls.hpp"

using namespace glm;

ObjectUI::ObjectUI()
{
}

ObjectUI::~ObjectUI()
{
}

void ObjectUI::initialize()
{
	programID = shagerManager.loadShaders("ui.vs", "ui.fs");
	matrixID = glGetUniformLocation(programID, "MVP");
	viewMatrixID = glGetUniformLocation(programID, "V");
	modelMatrixID = glGetUniformLocation(programID, "M");

	textureData = textureManager.loadBMP(urlBMP, programID);

	meshData = meshManager.loadOBJ(urlOBJ);

	glUseProgram(programID);
	lightID = glGetUniformLocation(programID, "LightPosition_worldspace");
}

void ObjectUI::update()
{
}

void ObjectUI::render()
{
	Object::preRender();

	glUseProgram(programID);

	vec3 lightPos = vec3(20 * cos(radian), 20 * sin(radian), 0);
	glUniform3f(lightID, lightPos.x, lightPos.y, lightPos.z);

	mat4 projectionMatrix = getProjectionMatrix();
	mat4 viewMatrix = getViewMatrix();
	mat4 modelMatrix = mat;
	mat4 mvp = getProjectionMatrix() * getViewMatrix() * modelMatrix;
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureData.textureID);

	glUniform1i(textureData.textureSID, 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, meshData.vertexbufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, meshData.uvbufferID);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, meshData.normalbufferID);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, meshData.verticesSize);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	Object::postRender();
}

void ObjectUI::release()
{
	// Cleanup VBO and shader
	glDeleteBuffers(1, &meshData.vertexbufferID);
	glDeleteBuffers(1, &meshData.uvbufferID);
	glDeleteTextures(1, &meshData.normalbufferID);
	glDeleteProgram(programID);
}

void ObjectUI::setBMP(std::string _url)
{
	urlBMP = _url;
}

void ObjectUI::setOBJ(std::string _url)
{
	urlOBJ = _url;
}