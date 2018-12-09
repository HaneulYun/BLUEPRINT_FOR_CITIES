#include <random>
#include <string.h>

#include <gl/glew.h>
#include <gl/gl.h>
#include <glm/gtx/transform.hpp>

#include "Object3d.h"
#include "controls.hpp"
#include "GameScene.h"

using namespace glm;

Object3d::Object3d()
{

}

Object3d::~Object3d()
{
}

void Object3d::initialize()
{
	programID = shagerManager.loadShaders("shadow.vs", "shadow.fs");
	matrixID = glGetUniformLocation(programID, "MVP");
	viewMatrixID = glGetUniformLocation(programID, "V");
	modelMatrixID = glGetUniformLocation(programID, "M");
	DepthBiasID = glGetUniformLocation(programID, "DepthBiasMVP");
	ShadowMapID = glGetUniformLocation(programID, "shadowMap");

	lightNumID = glGetUniformLocation(programID, "lightNum");
	for (int i = 0; i < 16; ++i)
	{
		std::string str = "lightPosition[";
		str += std::to_string(i);
		str += "]";
		lightPositionID[i] = glGetUniformLocation(programID, str.c_str());
	}

	textureData = textureManager.loadBMP(urlBMP, programID);

	meshData = meshManager.loadOBJ(urlOBJ);

	glUseProgram(programID);
	lightID = glGetUniformLocation(programID, "LightPosition_worldspace");

	// Shadow map
	depthProgramID = shagerManager.loadShaders("depth.vs", "depth.fs");
	depthMatrixID = glGetUniformLocation(depthProgramID, "depthMVP");
}

void Object3d::update()
{
}

void Object3d::render()
{
	Object::preRender();

	glUseProgram(programID);


	mat4 projectionMatrix = getProjectionMatrix();
	mat4 viewMatrix = getViewMatrix();
	mat4 modelMatrix = mat;
	mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;
	mat4 biasMatrix(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
	);

	mat4 depthBiasMVP = biasMatrix * depthMVP;
	vec3 lightPos = g_gameScene->sun.getLightPos();
	glUniform3f(lightID, lightPos.x, lightPos.y, lightPos.z);
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(DepthBiasID, 1, GL_FALSE, &depthBiasMVP[0][0]);
	auto iter = g_gameScene->propManager.streetLight.begin();
	for (int i = 0; i < 16; ++i)
	{
		lightPos = (*iter)->obj.getPosition();
		glUniform3f(lightPositionID[i], lightPos.x, lightPos.y + 0.45, lightPos.z);
		++iter;
	}
	glUniform1i(lightNumID, 16);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureData.textureID);
	glUniform1i(textureData.textureSID, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, g_gameScene->texture.depthTexture);
	glUniform1i(ShadowMapID, 1);

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

void Object3d::extractDepthmap()
{
	Object::preRender();

	glUseProgram(depthProgramID);

	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10, 10, -10, 10, -10, 100);
	glm::mat4 depthViewMatrix = glm::lookAt(g_gameScene->sun.getLightPos(), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 depthModelMatrix = mat;
	depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;
	glUniformMatrix4fv(depthMatrixID, 1, GL_FALSE, &depthMVP[0][0]);

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, textureData.textureID);

	//glUniform1i(textureData.textureSID, 0);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, meshData.vertexbufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, meshData.verticesSize);

	glDisableVertexAttribArray(0);

	Object::postRender();
}

void Object3d::setBMP(std::string _url)
{
	urlBMP = _url;
}

void Object3d::setOBJ(std::string _url)
{
	urlOBJ = _url;
}