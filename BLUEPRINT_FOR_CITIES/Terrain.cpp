#include <gl/glew.h>
#include <gl/gl.h>
#include <glm/gtx/transform.hpp>

#include <vector>

#include "Terrain.h"
#include "controls.hpp"
#include "GameScene.h"

using namespace glm;

Terrain::Terrain()
{
}

Terrain::~Terrain()
{
	release();
}

void Terrain::initialize()
{
	programID = shagerManager.loadShaders("terrain.vs", "terrain.fs");
	matrixID = glGetUniformLocation(programID, "MVP");
	viewMatrixID = glGetUniformLocation(programID, "V");
	modelMatrixID = glGetUniformLocation(programID, "M");
	DepthBiasID = glGetUniformLocation(programID, "DepthBiasMVP");
	ShadowMapID = glGetUniformLocation(programID, "shadowMap");

	for (int i = 0; i < 16; ++i)
	{
		std::string str = "lightPosition[";
		str += std::to_string(i);
		str += "]";
		lightPositionID[i] = glGetUniformLocation(programID, str.c_str());
	}
	lightNumID = glGetUniformLocation(programID, "lightNum_vs");

	glUseProgram(programID);
	lightID = glGetUniformLocation(programID, "LightPosition_worldspace");

	std::vector<glm::vec3> out_vertices;
	std::vector<glm::vec3> out_normals;

	for (int z = 0; z < length - 1; z++) {
		for (int x = 0; x < width; x++) {
			//Vec3f normal = _terrain->getNormal(x, z);
			//glNormal3f(normal[0], normal[1], normal[2]);
			if(x)
			{
				out_vertices.push_back({ -terrainWidth / 2.f + float(x) / width * terrainWidth, heights[z][x], -terrainLength / 2.f + float(z) / length * terrainLength });
				out_vertices.push_back({ -terrainWidth / 2.f + float(x) / width * terrainWidth, heights[z][x], -terrainLength / 2.f + float(z) / length * terrainLength });
				out_vertices.push_back({ -terrainWidth / 2.f + float(x - 1) / width * terrainWidth, heights[z + 1][x - 1], -terrainLength / 2.f + float(z + 1) / length * terrainLength });
				out_vertices.push_back({ -terrainWidth / 2.f + float(x) / width * terrainWidth, heights[z + 1][x], -terrainLength / 2.f + float(z + 1) / length * terrainLength });

				out_normals.push_back(normals[z][x]);
				out_normals.push_back(normals[z][x]);
				out_normals.push_back(normals[z + 1][x - 1]);
				out_normals.push_back(normals[z + 1][x]);
			}

			//normal = _terrain->getNormal(x, z + 1);
			//glNormal3f(normal[0], normal[1], normal[2]);
			if (x < width - 1)
			{
				out_vertices.push_back({ -terrainWidth / 2.f + float(x) / width * terrainWidth, heights[z][x], -terrainLength / 2.f + float(z) / length * terrainLength });
				out_vertices.push_back({ -terrainWidth / 2.f + float(x) / width * terrainWidth, heights[z + 1][x],  -terrainLength / 2.f + float(z + 1) / length * terrainLength });

				out_normals.push_back(normals[z][x]);
				out_normals.push_back(normals[z + 1][x]);
			}
		}
	}

	verticesSize = out_vertices.size();
	glGenBuffers(1, &vertexbufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbufferID);
	glBufferData(GL_ARRAY_BUFFER, out_vertices.size() * sizeof(glm::vec3), &out_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalbufferID);
	glBindBuffer(GL_ARRAY_BUFFER, normalbufferID);
	glBufferData(GL_ARRAY_BUFFER, out_normals.size() * sizeof(glm::vec3), &out_normals[0], GL_STATIC_DRAW);

	computedNormals = false;

	depthProgramID = shagerManager.loadShaders("depth.vs", "depth.fs");
	depthMatrixID = glGetUniformLocation(depthProgramID, "depthMVP");
}

void Terrain::update()
{
}

void Terrain::render()
{
	Object::preRender();

	glUseProgram(programID);

	vec3 lightPos = g_gameScene->sun.getLightPos();
	glUniform3f(lightID, lightPos.x, lightPos.y, lightPos.z);

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
	glm::mat4 depthBiasMVP = biasMatrix * depthMVP;
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
	glUniform1d(lightNumID, 16);

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, textureData.textureID);

	//glUniform1i(textureData.textureSID, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, g_gameScene->texture.depthTexture);
	glUniform1i(ShadowMapID, 1);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, normalbufferID);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, verticesSize);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);

	Object::postRender();
}

void Terrain::extractDepthmap()
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

	glBindBuffer(GL_ARRAY_BUFFER, vertexbufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, verticesSize);

	glDisableVertexAttribArray(0);

	Object::postRender();
}

void Terrain::release()
{
	for (int i = 0; i < length; i++)
		delete[] heights[i];
	delete[] heights;

	for (int i = 0; i < length; i++)
		delete[] normals[i];
	delete[] normals;
}

void Terrain::setTerrainSize(int _width, int _length)
{
	terrainWidth = _width;
	terrainLength = _length;
}

void Terrain::setSize(int _width, int _length)
{
	width = _width;
	length = _length;

	heights = new float*[length];
	for (int i = 0; i < length; ++i)
		heights[i] = new float[width];

	normals = new glm::vec3*[length];
	for (int i = 0; i < length; ++i)
		normals[i] = new glm::vec3[width];
}

Image* Terrain::loadBMP(std::string path)
{
	printf("Reading image %s\n", path.c_str());

	Image* image = new Image;

	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	unsigned int width, height;
	unsigned char * data;

	FILE * file = fopen(path.c_str(), "rb");
	if (!file)
	{
		printf("%s could not be opened.\n", path.c_str());
		getchar();
		return {};
	}
	if (fread(header, 1, 54, file) != 54)
	{
		printf("Not a correct BMP file\n");
		return {};
	}
	if (header[0] != 'B' || header[1] != 'M')
	{
		printf("Not a correct BMP file\n");
		return {};
	}

	if (*(int*)&(header[0x1E]) != 0)
	{
		printf("Not a correct BMP file\n");
		return {};
	}
	if (*(int*)&(header[0x1C]) != 24)
	{
		printf("Not a correct BMP file\n");
		return {};
	}

	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	image->width = width = *(int*)&(header[0x12]);
	image->height = height = *(int*)&(header[0x16]);

	image->pixels = new char*[height];
	for (int i = 0; i < height; ++i)
		image->pixels[i] = new char[width];

	if (imageSize == 0)
		imageSize = width * height * 3;
	if (dataPos == 0)
		dataPos = 54;

	data = new unsigned char[imageSize];

	fread(data, 1, imageSize, file);
	for (int y = 0; y < image->height; y++)
		for (int x = 0; x < image->width; x++)
			image->pixels[y][x] = data[(image->width * y + x) * 3];

	fclose(file);

	return image;
}

void Terrain::loadTerrain(std::string path, float height)
{
	Image* image = loadBMP(path);
	setSize(image->width, image->height);
	for (int y = 0; y < image->height; y++) {
		for (int x = 0; x < image->width; x++) {
			unsigned char color = (unsigned char)image->pixels[y][x];
			float h = height * ((color / 255.0f) - 0.5f);
			setHeight(x, y, h);
		}
	}

	delete image;
	computeNormals();

	initialize();
}

void Terrain::computeNormals()
{
	if (computedNormals) {
		return;
	}

	vec3** normals2 = new vec3*[length];
	for (int i = 0; i < length; i++) {
		normals2[i] = new vec3[width];
	}

	for (int z = 0; z < length; z++) {
		for (int x = 0; x < width; x++) {
			vec3 sum(0.0f, 0.0f, 0.0f);

			vec3 out;
			if (z > 0) {
				out = vec3(0.0f, heights[z - 1][x] - heights[z][x], -1.0f);
			}
			vec3 in;
			if (z < length - 1) {
				in = vec3(0.0f, heights[z + 1][x] - heights[z][x], 1.0f);
			}
			vec3 left;
			if (x > 0) {
				left = vec3(-1.0f, heights[z][x - 1] - heights[z][x], 0.0f);
			}
			vec3 right;
			if (x < width - 1) {
				right = vec3(1.0f, heights[z][x + 1] - heights[z][x], 0.0f);
			}

			if (x > 0 && z > 0) {
				sum += glm::normalize(glm::cross(out, left));
			}
			if (x > 0 && z < length - 1) {
				sum += glm::normalize(glm::cross(left, in));
			}
			if (x < width - 1 && z < length - 1) {
				sum += glm::normalize(glm::cross(in, right));
			}
			if (x < width - 1 && z > 0) {
				sum += glm::normalize(glm::cross(right, out));
			}

			normals2[z][x] = sum;
			normals[z][x] = sum;
		}
	}
}

void Terrain::setHeight(int x, int z, float y)
{
	heights[z][x] = y;
	computedNormals = false;
}

int Terrain::getWidth() const
{
	return width;
}

int Terrain::getLength() const
{
	return length;
}

float Terrain::getHeight(int x, int z) const
{
	return heights[z][x];
}

float Terrain::getHeightByPosition(float x, float z) const
{
	float x_terrain = (x + terrainWidth / 2) / terrainWidth * width;
	float z_terrain = (z + terrainLength / 2) / terrainLength * length;
	float ratioWidth = x_terrain - int(x_terrain);
	float ratioLength = z_terrain - int(z_terrain);
	int over_x = x_terrain + 1 < width ? x_terrain + 1 : x_terrain;
	int over_z = z_terrain + 1 < length ? z_terrain + 1 : z_terrain;

	return (1 - ratioLength) * ((1 - ratioWidth) * getHeight(x_terrain, z_terrain) + ratioWidth * getHeight(over_x, z_terrain)) +
		ratioLength * ((1 - ratioWidth) * getHeight(x_terrain, over_z) + ratioWidth * getHeight(over_x, over_z));
}

bool Terrain::existInner(float x, float z) const
{
	float x_terrain = (x + terrainWidth / 2) / terrainWidth * width;
	float z_terrain = (z + terrainLength / 2) / terrainLength * length;
	if (x_terrain > width - 1 || x_terrain < 0)
		return false;
	if (z_terrain > length - 1 || z_terrain < 0)
		return false;
	return true;
}

glm::vec3 Terrain::getNormal(int x, int z) const
{
	return normals[z][x];
}