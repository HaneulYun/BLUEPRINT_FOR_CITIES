// Include GLFW
#include <gl/glew.h>
#include <GLFW/glfw3.h>
extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "InputManager.h"
#include "App.h"
#include "GameScene.h"
#include "controls.hpp"


glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;
glm::mat4 UIProjectionMatrix;

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix() {
	return ProjectionMatrix;
}
glm::mat4 getUIProjectionMatrix() {
	return UIProjectionMatrix;
}


// Initial position : on +Z
glm::vec3 position = glm::vec3( 0, 6, 5 ); 
// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;



void computeMatricesFromInputs(){
	SIZE size = g_app->getSize();

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);



	// Get mouse position
	//double xpos, ypos;
	//glfwGetCursorPos(window, &xpos, &ypos);

	if (g_gameScene->viewMode)
	{
		// Reset mouse position for next frame
		glfwSetCursorPos(window, size.cx / 2, size.cy / 2);

		// Compute new orientation
		horizontalAngle += mouseSpeed * float(size.cx / 2 - g_pInputManager->xpos);
		verticalAngle += mouseSpeed * float(size.cy / 2 - g_pInputManager->ypos);

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	// Up vector
	glm::vec3 up = glm::cross(right, direction);

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
		if (g_pInputManager->curMouseState[GLFW_MOUSE_BUTTON_1] == false)
		{
			if (!g_gameScene->viewMode)
			{
				if (!g_gameScene->pathManager.drawState)//나무그리기
				{
					g_gameScene->propManager.inputProp(g_gameScene->propManager.chooseProp);
				}
				else
				{
					Node* node = new Node();
					node->initialize();
					glm::vec3 v = g_gameScene->mousePicker->currentTerrainPoint;
					if (v != glm::vec3{})
					{
						v.y = g_gameScene->terrain->getHeightByPosition(v.x, v.z);
					}
					node->obj.setPosition(v);
					g_gameScene->pathManager.inputNode(node);
				}
			}
		}
		g_pInputManager->curMouseState[GLFW_MOUSE_BUTTON_1] = true;
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE) {
		g_pInputManager->curMouseState[GLFW_MOUSE_BUTTON_1] = false;
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) {
		if (g_pInputManager->curMouseState[GLFW_MOUSE_BUTTON_2] == false)
		{
			if (!g_gameScene->viewMode)
			{
				if (g_gameScene->pathManager.drawState)
				{
					g_gameScene->pathManager.inputInitialize();
				}
			}
		}
		g_pInputManager->curMouseState[GLFW_MOUSE_BUTTON_2] = true;
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_RELEASE) {
		g_pInputManager->curMouseState[GLFW_MOUSE_BUTTON_2] = false;
	}
	// Move forward
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		position += direction * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		position -= direction * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		position -= right * deltaTime * speed;
	}
	// viewMode
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		if (g_pInputManager->curKeyState[GLFW_KEY_LEFT_CONTROL] == false)
		{
			g_gameScene->viewMode = !g_gameScene->viewMode;
			if (g_gameScene->viewMode)
				glfwSetCursorPos(window, size.cx / 2, size.cy / 2);
				g_gameScene->destroyMode = false;
		}
		g_pInputManager->curKeyState[GLFW_KEY_LEFT_CONTROL] = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE) {
		g_pInputManager->curKeyState[GLFW_KEY_LEFT_CONTROL] = false;
	}
	// destroyMode
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
		if (g_pInputManager->curKeyState[GLFW_KEY_B] == false && !g_gameScene->viewMode)
		{
			g_gameScene->destroyMode = !g_gameScene->destroyMode;
		}
		g_pInputManager->curKeyState[GLFW_KEY_B] = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_B) == GLFW_RELEASE) {
		g_pInputManager->curKeyState[GLFW_KEY_B] = false;
	}
	// drawPath
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		if (g_pInputManager->curKeyState[GLFW_KEY_R] == false && !g_gameScene->viewMode)
		{
			g_gameScene->pathManager.drawState = !g_gameScene->pathManager.drawState;
		}
		g_pInputManager->curKeyState[GLFW_KEY_R] = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE) {
		g_pInputManager->curKeyState[GLFW_KEY_R] = false;
	}
	// straight
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		if (g_pInputManager->curKeyState[GLFW_KEY_O] == false && !g_gameScene->viewMode && g_gameScene->pathManager.drawState)
		{
			g_gameScene->pathManager.drawMode = !g_gameScene->pathManager.drawMode;
		}
		g_pInputManager->curKeyState[GLFW_KEY_O] = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_O) == GLFW_RELEASE) {
		g_pInputManager->curKeyState[GLFW_KEY_O] = false;
	}
	// faster
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		if (g_pInputManager->curKeyState[GLFW_KEY_F] == false)
		{
			g_gameScene->fasterImage.faster = !g_gameScene->fasterImage.faster;
			if (g_gameScene->fasterImage.faster)
				g_gameScene->sun.sunclock = 0.015;
			else
				g_gameScene->sun.sunclock = 0.005;
		}
		g_pInputManager->curKeyState[GLFW_KEY_F] = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE) {
		g_pInputManager->curKeyState[GLFW_KEY_F] = false;
	}
	// pause
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		if (g_pInputManager->curKeyState[GLFW_KEY_P] == false)
		{
			g_gameScene->sun.pause = !g_gameScene->sun.pause;
		}
		g_pInputManager->curKeyState[GLFW_KEY_P] = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE) {
		g_pInputManager->curKeyState[GLFW_KEY_P] = false;
	}
	// tree
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		g_gameScene->propManager.chooseProp = TREE;
	}
	// cloud
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		g_gameScene->propManager.chooseProp = CLOUD;
	}
	// streetlight
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		g_gameScene->propManager.chooseProp = STREETLIGHT;
	}
	// mailBox
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
		g_gameScene->propManager.chooseProp = MAILBOX;
	}
	// hydrant
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
		g_gameScene->propManager.chooseProp = HYDRANT;
	}
	// cone
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
		g_gameScene->propManager.chooseProp = CONE;
	}

	float FoV = initialFoV;// -5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

	// Projection matrix : 45?Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(FoV, 16.0f / 9.0f, 0.1f, 100.0f);
	UIProjectionMatrix = glm::ortho(-800.f, 800.f, -450.f, 450.f, -1.f, 1000.f);

	// Camera matrix
	ViewMatrix       = glm::lookAt(
								position,           // Camera is here
								position+direction, // and looks here : at the same position, plus "direction"
								up                  // Head is up (set to 0,-1,0 to look upside-down)
						   );

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}