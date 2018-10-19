#pragma once
#include <vector>
#include "Vector3.h"
#include "Object.h"

class ObjectFromOBJ : public Object
{
	unsigned char beginMode;

	std::vector<Vector3> vertices;
	std::vector<Vector3> uvs;
	std::vector<Vector3> normals;

public:
	ObjectFromOBJ();
	~ObjectFromOBJ();

	void initialize();
	void update();
	void render();
	void release();

	bool loadOBJ( const char * path);

	void setBeginMode(unsigned char mode);
	unsigned char getBeginMode() const;
};