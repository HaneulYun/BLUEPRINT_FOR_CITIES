#include <iostream>
#include "picking.h"
#include "App.h"

extern GLFWwindow* window;
extern glm::vec3 position;

int MousePicker::RECURSION_COUNT = 200;
float MousePicker::RAY_RANGE = 600;

bool TestRayOBBIntersection(glm::vec3 ray_origin, glm::vec3 ray_direction, glm::vec3 aabb_min, glm::vec3 aabb_max, glm::mat4 ModelMatrix, float& intersection_distance)
{
	// Intersection method from Real-Time Rendering and Essential Mathematics for Games

	float tMin = 0.0f;
	float tMax = 100000.0f;

	glm::vec3 OBBposition_worldspace(ModelMatrix[3].x, ModelMatrix[3].y, ModelMatrix[3].z);

	glm::vec3 delta = OBBposition_worldspace - ray_origin;

	// Test intersection with the 2 planes perpendicular to the OBB's X axis
	{
		glm::vec3 xaxis(ModelMatrix[0].x, ModelMatrix[0].y, ModelMatrix[0].z);
		float e = glm::dot(xaxis, delta);
		float f = glm::dot(ray_direction, xaxis);

		if (fabs(f) > 0.001f) { // Standard case

			float t1 = (e + aabb_min.x) / f; // Intersection with the "left" plane
			float t2 = (e + aabb_max.x) / f; // Intersection with the "right" plane
			// t1 and t2 now contain distances betwen ray origin and ray-plane intersections

			// We want t1 to represent the nearest intersection, 
			// so if it's not the case, invert t1 and t2
			if (t1 > t2) {
				float w = t1; t1 = t2; t2 = w; // swap t1 and t2
			}

			// tMax is the nearest "far" intersection (amongst the X,Y and Z planes pairs)
			if (t2 < tMax)
				tMax = t2;
			// tMin is the farthest "near" intersection (amongst the X,Y and Z planes pairs)
			if (t1 > tMin)
				tMin = t1;

			// And here's the trick :
			// If "far" is closer than "near", then there is NO intersection.
			// See the images in the tutorials for the visual explanation.
			if (tMax < tMin)
				return false;

		}
		else { // Rare case : the ray is almost parallel to the planes, so they don't have any "intersection"
			if (-e + aabb_min.x > 0.0f || -e + aabb_max.x < 0.0f)
				return false;
		}
	}


	// Test intersection with the 2 planes perpendicular to the OBB's Y axis
	// Exactly the same thing than above.
	{
		glm::vec3 yaxis(ModelMatrix[1].x, ModelMatrix[1].y, ModelMatrix[1].z);
		float e = glm::dot(yaxis, delta);
		float f = glm::dot(ray_direction, yaxis);

		if (fabs(f) > 0.001f) {

			float t1 = (e + aabb_min.y) / f;
			float t2 = (e + aabb_max.y) / f;

			if (t1 > t2) { float w = t1; t1 = t2; t2 = w; }

			if (t2 < tMax)
				tMax = t2;
			if (t1 > tMin)
				tMin = t1;
			if (tMin > tMax)
				return false;

		}
		else {
			if (-e + aabb_min.y > 0.0f || -e + aabb_max.y < 0.0f)
				return false;
		}
	}


	// Test intersection with the 2 planes perpendicular to the OBB's Z axis
	// Exactly the same thing than above.
	{
		glm::vec3 zaxis(ModelMatrix[2].x, ModelMatrix[2].y, ModelMatrix[2].z);
		float e = glm::dot(zaxis, delta);
		float f = glm::dot(ray_direction, zaxis);

		if (fabs(f) > 0.001f) {

			float t1 = (e + aabb_min.z) / f;
			float t2 = (e + aabb_max.z) / f;

			if (t1 > t2) { float w = t1; t1 = t2; t2 = w; }

			if (t2 < tMax)
				tMax = t2;
			if (t1 > tMin)
				tMin = t1;
			if (tMin > tMax)
				return false;

		}
		else {
			if (-e + aabb_min.z > 0.0f || -e + aabb_max.z < 0.0f)
				return false;
		}
	}

	intersection_distance = tMin;
	return true;
}

MousePicker::MousePicker(glm::mat4 projection, Terrain* terrain) {
	projectionMatrix = projection;
	viewMatrix = getViewMatrix();
	this->terrain = terrain;
}

glm::vec3 MousePicker::getCurrentTerrainPoint() {
	return currentTerrainPoint;
}

glm::vec3 MousePicker::getCurrentRay() {
	return currentRay;
}

void MousePicker::update() {
	viewMatrix = getViewMatrix();
	currentRay = calculateMouseRay();
	if (intersectionInRange(0, RAY_RANGE, currentRay))
		currentTerrainPoint = binarySearch(0, 0, RAY_RANGE, currentRay);
	else
		currentTerrainPoint = {};
}

glm::vec3 MousePicker::calculateMouseRay() {
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	float mouseX = xpos;
	float mouseY = g_app->getSize().cy - ypos;
	glm::vec2 normalizedCoords = getNormalisedDeviceCoordinates(mouseX, mouseY);
	glm::vec4 clipCoords = glm::vec4(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);
	glm::vec4 eyeCoords = toEyeCoords(clipCoords);
	glm::vec3 worldRay = toWorldCoords(eyeCoords);
	return worldRay;
}

glm::vec3 MousePicker::toWorldCoords(glm::vec4 eyeCoords) {
	glm::mat4 invertedView = glm::inverse(viewMatrix);
	glm::vec4 rayWorld = invertedView * eyeCoords;
	glm::vec3 mouseRay = glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z);
	glm::normalize(mouseRay);
	return mouseRay;
}

glm::vec4 MousePicker::toEyeCoords(glm::vec4 clipCoords) {
	glm::mat4 invertedProjection = glm::inverse(projectionMatrix);
	glm::vec4 eyeCoords = invertedProjection * clipCoords;
	return glm::vec4(eyeCoords.x, eyeCoords.y, -1.f, 0.f);
}

glm::vec2 MousePicker::getNormalisedDeviceCoordinates(float mouseX, float mouseY) {
	float x = (2.0f * mouseX) / g_app->getSize().cx - 1.f;
	float y = (2.0f * mouseY) / g_app->getSize().cy - 1.f;
	return glm::vec2(x, y);
}

glm::vec3 MousePicker::getPointOnRay(glm::vec3 ray, float distance) {
	glm::vec3 start = position;
	glm::vec3 scaledRay = glm::vec3(ray.x * distance, ray.y * distance, ray.z * distance);
	return start + scaledRay;
}

glm::vec3 MousePicker::binarySearch(int count, float start, float finish, glm::vec3 ray) {
	float half = start + ((finish - start) / 2.f);
	if (count >= RECURSION_COUNT) {
		glm::vec3 endPoint = getPointOnRay(ray, half);
		bool exist = terrain->existInner(endPoint.x, endPoint.z);
		if (exist) {
			return endPoint;
		}
		else {
			return {};
		}
	}
	if (intersectionInRange(start, half, ray))
		return binarySearch(count + 1, start, half, ray);
	else
		return binarySearch(count + 1, half, finish, ray);
}

bool MousePicker::intersectionInRange(float start, float finish, glm::vec3 ray) {
	glm::vec3 startPoint = getPointOnRay(ray, start);
	glm::vec3 endPoint = getPointOnRay(ray, finish);
	if (!isUnderGround(startPoint) && isUnderGround(endPoint))
		return true;
	else
		return false;
}

bool MousePicker::isUnderGround(glm::vec3 testPoint) {
	float height = 0;
	if (terrain != nullptr)
	{
		if(terrain->existInner(testPoint.x, testPoint.z))
			height = terrain->getHeightByPosition(testPoint.x, testPoint.z);
	}
	if (testPoint.y < height) {
		return true;
	}
	else {
		return false;
	}
}