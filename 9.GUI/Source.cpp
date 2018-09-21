#include "GUIApplication.h"

int main()
{
	Application* app = new GUIApplication();
	app->run("gui app", 1200, 800, false);
}