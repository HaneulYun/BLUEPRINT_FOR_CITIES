#include <gl/freeglut.h>
#include "ObjectFromOBJ.h"

ObjectFromOBJ::ObjectFromOBJ() : beginMode{ GL_TRIANGLES }
{
}

ObjectFromOBJ::~ObjectFromOBJ()
{
}

void ObjectFromOBJ::initialize()
{
}

void ObjectFromOBJ::update()
{
}

void ObjectFromOBJ::render()
{
	Object::preRender();

	if (bVisible)
	{
		glBegin(beginMode);
		for (auto& v : vertices)
			glVertex3f(v.x, v.y, v.z);
		//for (int i = 0; i < vertices.size(); ++i)
		//{
		//	glColor3f(uvs[i].x, uvs[i].y, uvs[i].z);
		//	glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
		//}
		glEnd();
	}

	Object::postRender();
}

void ObjectFromOBJ::release()
{
}

void ObjectFromOBJ::setBeginMode(unsigned char mode)
{
	beginMode = mode;
}

unsigned char ObjectFromOBJ::getBeginMode() const
{
	return beginMode;
}

bool ObjectFromOBJ::loadOBJ(const char * path)
{
	printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<Vector3> temp_vertices;
	std::vector<Vector3> temp_uvs;
	std::vector<Vector3> temp_normals;


	FILE * file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return false;
	}

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0) {
			Vector3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			Vector3 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			Vector3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0],
				&vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			if (matches != 9) {
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		Vector3 vertex = temp_vertices[vertexIndex - 1];
		Vector3 uv = temp_uvs[uvIndex - 1];
		Vector3 normal = temp_normals[normalIndex - 1];

		// Put the attributes in buffers
		vertices.push_back(vertex);
		uvs.push_back(uv);
		normals.push_back(normal);

	}

	/// ttttttttttttttttttttttttttttttttttt
	{
	
		const char* imagepath = "resources/chicken.bmp";
		printf("Reading image %s\n", imagepath);
	
		// Data read from the header of the BMP file
		unsigned char header[54];
		unsigned int dataPos;
		unsigned int imageSize;
		unsigned int width, height;
		// Actual RGB data
		unsigned char * data;
	
		// Open the file
		FILE * file = fopen(imagepath, "rb");
		if (!file) { printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath); getchar(); return 0; }
	
		// Read the header, i.e. the 54 first bytes
	
		// If less than 54 bytes are read, problem
		if (fread(header, 1, 54, file) != 54) {
			printf("Not a correct BMP file\n");
			return 0;
		}
		// A BMP files always begins with "BM"
		if (header[0] != 'B' || header[1] != 'M') {
			printf("Not a correct BMP file\n");
			return 0;
		}
		// Make sure this is a 24bpp file
		if (*(int*)&(header[0x1E]) != 0) { printf("Not a correct BMP file\n");    return 0; }
		if (*(int*)&(header[0x1C]) != 24) { printf("Not a correct BMP file\n");    return 0; }
	
		// Read the information about the image
		dataPos = *(int*)&(header[0x0A]);
		imageSize = *(int*)&(header[0x22]);
		width = *(int*)&(header[0x12]);
		height = *(int*)&(header[0x16]);
	
		// Some BMP files are misformatted, guess missing information
		if (imageSize == 0)    imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
		if (dataPos == 0)      dataPos = 54; // The BMP header is done that way
	
		// Create a buffer
		data = new unsigned char[imageSize];
	
		
		// Read the actual data from the file into the buffer
		fread(data, 1, imageSize, file);
	
		std::vector<Color3> colors;
		for (int i = 0; i < width; ++i)
			colors.push_back({float(data[i * 3 + 2]) / 255, float(data[i * 3 + 1]) / 255, float(data[i * 3 + 0]) / 255});
	
		for (int i = 0; i < uvs.size(); ++i)
		{
			uvs[i] = { colors[uvs[i].x * width] };
		}
	
		// Everything is in memory now, the file wan be closed
		fclose(file);
	
		// Create one OpenGL texture
		GLuint textureID;
		glGenTextures(1, &textureID);
	
		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_2D, textureID);
	
		// Give the image to OpenGL
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	
		// OpenGL has now copied the data. Free our own version
		delete[] data;
	
		// Poor filtering, or ...
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	
		// ... nice trilinear filtering.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//glGenerateMipmap(GL_TEXTURE_2D);
	
		// Return the ID of the texture we just created
	}
	/// ttttttttttttttttttttttttttttttttttt

	return true;
}