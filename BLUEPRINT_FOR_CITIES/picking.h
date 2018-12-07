#pragma once
#include <glm/glm.hpp>
#include "Terrain.h"
#include "controls.hpp"

bool TestRayOBBIntersection(glm::vec3 ray_origin, glm::vec3 ray_direction, glm::vec3 aabb_min, glm::vec3 aabb_max, glm::mat4 ModelMatrix, float& intersection_distance);

class MousePicker
{
private:
	static int RECURSION_COUNT;
	static float RAY_RANGE;

	glm::vec3 currentRay; // = new Vector3f();

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;

	Terrain* terrain;
	glm::vec3 currentTerrainPoint;

public:
	MousePicker(glm::mat4 projection, Terrain* terrain);

	glm::vec3 getCurrentTerrainPoint();
	glm::vec3 getCurrentRay();

	void update();

private:
	glm::vec3 calculateMouseRay();

	glm::vec3 toWorldCoords(glm::vec4 eyeCoords);
	glm::vec4 toEyeCoords(glm::vec4 clipCoords);
	glm::vec2 getNormalisedDeviceCoordinates(float mouseX, float mouseY);

	glm::vec3 getPointOnRay(glm::vec3 ray, float distance);

	glm::vec3 binarySearch(int count, float start, float finish, glm::vec3 ray);

	bool intersectionInRange(float start, float finish, glm::vec3 ray);

	bool isUnderGround(glm::vec3 testPoint);
};