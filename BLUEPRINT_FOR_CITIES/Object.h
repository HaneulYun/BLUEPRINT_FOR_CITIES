#pragma once
#include <list>
#include <glm/glm.hpp>
#include "shader.hpp"
#include "texture.hpp"
#include "objloader.hpp"

class Object
{
protected:
	glm::vec3 position{};
	glm::vec3 rotation{};
	glm::vec3 scale{ 1 };
	glm::vec3 color{ 1 };

	glm::mat4 mat{ 1 };
	glm::vec4 transformedVector{ 0 };

	std::list<Object*> child;
	int hierarchyLevel{ 0 };

	bool bVisible{ true };

public:
	static ShaderManager shagerManager;
	static TextureManager textureManager;
	static MeshManager meshManager;

public:
	Object();
	virtual ~Object();

	virtual void initialize();
	virtual void update();
	virtual void preRender();
	void postRender();
	virtual void render();
	virtual void release();

	void addChild(Object* _child);
	void deleteChild(Object* _child);

	void setPosition(float _x, float _y, float _z);
	void setPosition(const glm::vec3 _position);
	void setRotation(float _x, float _y, float _z);
	void setRotation(const glm::vec3 _rotation);
	void setScale(float _s);
	void setScale(float _x, float _y, float _z);
	void setScale(const glm::vec3 _scale);
	void setColor(float _r, float _g, float _b);
	void setColor(const glm::vec3 _color);
	void setVisible(const bool _b);

	glm::vec3 getPosition() const;
	glm::vec3 getRotation() const;
	glm::vec3 getScale() const;
	glm::vec3 getColor() const;
	bool getVisible() const;

	void adjustPosition(float _x, float _y, float _z);
	void adjustPosition(const glm::vec3 _position);
	void adjustRotation(float _x, float _y, float _z);
	void adjustRotation(const glm::vec3 _rotation);
	void adjustScale(float _x, float _y, float _z);
	void adjustScale(const glm::vec3 _scale);
	void adjustColor(float _r, float _g, float _b);
	void adjustColor(const glm::vec3 _color);

	inline bool operator==(const Object& rhs)
	{
		return this == &rhs;
	}
};