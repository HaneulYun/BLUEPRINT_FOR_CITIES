#include "App.h"

GLFWwindow* window;

int main(int argc, char* argv[])
{
	char name[] = "BLUEPRINT_FOR_CITIES";
	App* app = App::create();
	app->initialize(0, 0, 1600, 900, name);
	return app->run();
}