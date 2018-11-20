#include <stdio.h>
#include <stdlib.h>

#include "texture.hpp"

TextureIDData TextureManager::loadBMP(const std::string path, GLuint programID)
{
	auto iter = textureDatas.find(path);
	if (iter == textureDatas.end())
	{
		printf("Reading image %s\n", path.c_str());

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
		width = *(int*)&(header[0x12]);
		height = *(int*)&(header[0x16]);

		if (imageSize == 0)
			imageSize = width * height * 3;
		if (dataPos == 0)
			dataPos = 54;

		data = new unsigned char[imageSize];

		fread(data, 1, imageSize, file);

		fclose(file);

		textureDatas.insert(std::pair<std::string, TextureIDData>(path, {}));

		glGenTextures(1, &textureDatas[path].textureID);
		glBindTexture(GL_TEXTURE_2D, textureDatas[path].textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
		delete[] data;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);

		textureDatas[path].textureSID = glGetUniformLocation(programID, "myTextureSampler");
	}
	return textureDatas[path];
}