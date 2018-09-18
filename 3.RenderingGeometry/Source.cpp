
#include "RenderingGeometryApp.h"
#include <stdio.h>
int main()
{ 
	
	//why the fuck do ppl say arrays are passed by reference
	//when they are passing in the pointer to the array
	//b/c reference variables are the same fkng size as the shit they reference..................zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz
	Application *app = new RenderingGeometryApp();
	app->run("draw a plane", 800, 600, false);  
}
