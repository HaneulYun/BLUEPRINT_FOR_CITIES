#include <random>

#include <gl/glew.h>
#include <gl/gl.h>
#include <glm/gtx/transform.hpp>

#include "ObjectUI.h"
#include "controls.hpp"
#include "GameScene.h"

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
	colorID = glGetUniformLocation(programID, "COLOR_VS");

	meshData = meshManager.loadOBJ(urlOBJ);

	glUseProgram(programID);
}

void ObjectUI::update()
{
}

void ObjectUI::render()
{
	Object::preRender();

	glUseProgram(programID);

	mat4 projectionMatrix = getUIProjectionMatrix();
	mat4 viewMatrix = getViewMatrix();
	mat4 modelMatrix = mat;
	mat4 mvp = projectionMatrix * modelMatrix;
	
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);
	glUniform3f(colorID, color.r, color.g, color.b);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, meshData.vertexbufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, meshData.verticesSize);

	glDisableVertexAttribArray(0);

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