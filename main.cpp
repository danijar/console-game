#include "include.h"
#include "renderer.cpp"
#include "objects.cpp"

int main()
{
	cout << "Which map do you want to load? ";
	string map;
	getline(cin, map);

	bool open = true;
	while(open)
	{
		Renderer renderer(20, 15);
		renderer.Line("Level: " + map);

		Objects objects(&renderer);
		objects.Load(map + ".txt");

		bool running = true;
		while(running)
		{
			// note: virtual key codes at http://bit.ly/zHw8YZ
			if(GetAsyncKeyState(VK_ESCAPE)) { open = false; break; }

			running = objects.Update();

			renderer.Render();
			Sleep(150);
			// cin.get(); // for screenshots
		}
	}
}