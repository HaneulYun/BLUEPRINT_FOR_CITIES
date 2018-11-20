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

ShaderManager Object3d::shagerManager;
TextureManager Object3d::textureManager;
MeshManager Object3d::meshManager;

Object3d::Object3d()
{
}

Object3d::~Object3d()
{
}

void Object3d::initialize()
{
	programID = shagerManager.loadShaders("StandardShading.vertexshader", "StandardShading.fragmentshader");
	matrixID = glGetUniformLocation(programID, "MVP");
	viewMatrixID = glGetUniformLocation(programID, "V");
	modelMatrixID = glGetUniformLocation(programID, "M");

	textureData = textureManager.loadBMP(urlBMP, programID);

	meshData = meshManager.loadOBJ(urlOBJ);

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

void Object3d::release()
{
	// Cleanup VBO and shader
	glDeleteBuffers(1, &meshData.vertexbufferID);
	glDeleteBuffers(1, &meshData.uvbufferID);
	glDeleteTextures(1, &meshData.normalbufferID);
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