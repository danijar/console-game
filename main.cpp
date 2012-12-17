#include "include.h"
#include "renderer.cpp"
#include "objects.cpp"

int main()
{
	Renderer renderer(20, 15);
	Objects objects(&renderer);

	objects.Load("map.txt");

	while(1)
	{
		// note: virtual key codes at http://bit.ly/zHw8YZ
		if(GetAsyncKeyState(VK_ESCAPE)) break;

		objects.Update();

		renderer.Render();
		Sleep(100);
	}
}