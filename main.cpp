#include "include.h"
#include "renderer.cpp"
#include "objects.cpp"

int main()
{
	cout << "Which map do you want to load? ";
	string map;
	getline(cin, map);

	Renderer renderer(20, 15);
	renderer.Line("Level: " + map);

	Objects objects(&renderer);
	objects.Load(map + ".txt");

	while(1)
	{
		// note: virtual key codes at http://bit.ly/zHw8YZ
		if(GetAsyncKeyState(VK_ESCAPE)) break;

		objects.Update();

		renderer.Render();
		Sleep(100);
		// cin.get();
	}
}