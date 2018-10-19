#include <gl/freeglut.h>
#include "ObjectCamera.h"

#define PI 3.141592

ObjectCamera::ObjectCamera() : eye({ 0.0, 0.0, 0.0 }), at({ 0.0, 0.0, -100.0 }), up({ 0.0, 1.0, 0.0 })
{
	rotation = { 0, 90, 0 };
}

ObjectCamera::~ObjectCamera()
{
}

void ObjectCamera::initialize()
{
	position = { 0, 0, 800};
	rotation = { 0, 90, 0};
}

void ObjectCamera::update()
{
	Object::update();

	eye = { position.x, position.y, position.z };
	atX = eyeX + cosf(rotation.y * PI / 180);
	atY = eyeY + sinf(rotation.x * PI / 180);
	atZ = eyeZ - sinf(rotation.y * PI / 180) - cosf(rotation.x * PI / 180);
	upX = sinf(rotation.z * PI / 180);
	upY = cosf(rotation.z * PI / 180);
}

void ObjectCamera::preRender()
{
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	if (!hierarchyLevel)
		glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, atX, atY, atZ, upX, upY, upZ);
}

void ObjectCamera::render()
{
	preRender();
	postRender();
}

void ObjectCamera::release()
{
}