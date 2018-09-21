#include "GUIApplication.h"
#include "imgui.h"

void GUIApplication::startup()
{
}

void GUIApplication::shutdown()
{
}

void GUIApplication::update(float dt)
{
}

void GUIApplication::draw()
{
	ImGui::Text("Hello, world %d", 123);
	if (ImGui::Button("Save"))
	{
		// do stuff
	}
	
	
}
