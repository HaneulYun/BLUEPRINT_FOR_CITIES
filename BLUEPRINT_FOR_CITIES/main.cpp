#include "App.h"

GLFWwindow* window;

int main(int argc, char* argv[])
{
	char name[] = "BLUEPRINT_FOR_CITIES";
	App* app = App::create();
	app->initialize(100, 100, 800, 600, name);
	return app->run();
}