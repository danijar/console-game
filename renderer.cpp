#pragma once
#include "include.h"

struct Intpointer
{

};

class Renderer
{
public:
	Renderer(int x, int y, char background = '\xFA') : max_x(x), max_y(y), map(new char[x * y]), bg(background)
	{
		Clear();
	}
	~Renderer()
	{
		delete[] map;
	}
	void Clear()
	{
		Clear(bg);
	}
	void Clear(char background)
	{
		memset(map, background, max_x * max_y);
	}
	void Clear(int x, int y)
	{
		max_x = x;
		max_y = y;
		map = new char[x * y];
		Clear();
	}
	void Set(int x, int y, char content)
	{
		if(x > max_x-1 || y > max_y-1) return;
		map[Key(x, y)] = content;
	}
	void Set(int i, char content)
	{
		if(i > max_x-1 * max_y-1) return;
		map[i] = content;
	}
	char Get(int x, int y)
	{
		if(x > max_x || y > max_y) return ' ';
		return map[Key(x, y)];
	}
	void Line(string text)
	{
		lines.push_back(make_pair(text, nullptr));
	}
	void Line(string text, int *var)
	{
		lines.push_back(make_pair(text, var));
	}
	void Render()
	{
		string out = "\n";
		for(auto i = lines.begin(); i != lines.end(); ++i)
		{
			out += ' ' + i->first;
			if(i->second != nullptr) out += to_string(*i->second);
			out += '\n';
		}
		for(int y = 0; y < max_y; ++y)
		{
			out += "\n ";
			for(int x = 0; x < max_x; ++x)
			{
				//out += ' ';
				out += map[Key(x, y)];
			}
		}
		system("cls");
		cout << out;
	}
	int X() { return max_x; }
	int Y() { return max_y; }
private:
	int max_x, max_y;
	char *map;
	char bg;
	vector<pair<string, int*> > lines;
	int Key(int x, int y)
	{
		return y * max_x + x;
	}
};