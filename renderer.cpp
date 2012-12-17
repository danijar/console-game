#pragma once
#include "include.h"

struct Intpointer
{

};

class Renderer
{
public:
	Renderer(int x, int y, char background = ' ', char border = '\xFA') : max_x(x), max_y(y), map(new char[x * y]), bg(background), bd(border)
	{
		Clear();
	}
	~Renderer()
	{
		delete[] map;
	}
	void Clear()
	{
		memset(map, bg, max_x * max_y);
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
		string text = Header();
		text += Line();
		for(int y = 0; y < max_y; ++y)
		{
			text += "\n ";
			text += bd;
			for(int x = 0; x < max_x; ++x)
			{
				//text += ' ';
				text += map[Key(x, y)];
			}
			text += bd;
		}
		text += Line();
		Show(text);
	}
	void Message(string message)
	{
		string text = Header();
		text += Line();
		text += "\n\n  ";
		text += message;
		text += "\n";
		text += Line();
		
		Show(text);
		cin.get();
	}
	int X() { return max_x; }
	int Y() { return max_y; }
private:
	int max_x, max_y;
	char *map;
	char bg, bd;
	vector<pair<string, int*> > lines;
	string Header()
	{
		string text = "";
		text += '\n';
		for(auto i = lines.begin(); i != lines.end(); ++i)
		{
			text += ' ' + i->first;
			if(i->second != nullptr) text += to_string(*i->second);
			text += '\n';
		}
		return text;
	}
	void Show(string text)
	{
		system("cls");
		cout << text;
	}
	string Line()
	{
		string text = "\n ";
		for(int n = -1; n < max_x + 1; ++n) text += bd;
		return text;
	}
	int Key(int x, int y)
	{
		return y * max_x + x;
	}
};