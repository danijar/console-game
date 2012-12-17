#pragma once
#include "include.h"
#include "renderer.cpp"

struct Position
{
	Position() : x(0), y(0) {}
	void Set(int x, int y) { this->x = x; this->y = y; }
	int x, y;
};

struct Object
{
	Position Pos;
	char Visual;
	virtual void Update() = 0;
	void Boundposition(int x, int y)
	{
		if(Pos.x < 0)     Pos.x = 0;
		if(Pos.x > x - 1) Pos.x = x - 1;
		if(Pos.y < 0)     Pos.y = 0;
		if(Pos.y > y - 1) Pos.y = y - 1;
	}
};

struct Player : public Object
{
	Player(int x = 0, int y = 0)
	{
		Visual = 'O';
		Pos.x = x;
		Pos.y = y;
	}
	void Update()
	{
		if(GetAsyncKeyState(VK_LEFT) ) Pos.x--;
		if(GetAsyncKeyState(VK_RIGHT)) Pos.x++;
		if(GetAsyncKeyState(VK_UP)   ) Pos.y--;
		if(GetAsyncKeyState(VK_DOWN) ) Pos.y++;
	}
};

struct Wall : public Object
{
	Wall(int x = 0, int y = 0)
	{
		Visual = '\xDB';
		Pos.x = x;
		Pos.y = y;
	}
	void Update() {}
};

struct Monster : public Object
{
	Monster(int x = 0, int y = 0) : dir(true), distance(0)
	{
		Visual = '\x84';
		Pos.x = x;
		Pos.y = y;
	}
	void Update()
	{
		if(distance >  3) dir = false;
		if(distance < -2) dir = true;
		distance += dir ? 1 : -1;
		Pos.x += dir ? 1 : -1;
	}
private:
	bool dir;
	int distance;
};

class Objects
{
public:
	Objects(Renderer* renderer) : renderer(renderer)
	{
		objects.push_back(new Player(0, 0));
	}
	void Update()
	{
		renderer->Clear();
		for(vector<Object*>::iterator i = objects.begin(); i != objects.end(); ++i)
		{
			(*i)->Update();
			(*i)->Boundposition(renderer->X(), renderer->Y());
			renderer->Set((*i)->Pos.x, (*i)->Pos.y, (*i)->Visual);
		}
	}
	void Load(string Path)
	{
		ifstream file(Path.c_str());
		if(!file.is_open()) return;
		unsigned char ch;

		int max_i = 0, max_y = 0;
		while(!file.eof())
		{
			ch = file.get();
			if(ch == '\n') max_y++;
			else max_i++;
		}
		max_i--; max_y++; // because last char is no line break
		int max_x = max_i / max_y;
		renderer->Clear(max_x, max_y);

		file.clear();
		file.seekg(0, ios::beg);
		int i = 0;
		while(!file.eof())
		{
			ch = file.get();
			if(ch == '\n') continue;
			int x = i % max_x;
			int y = i / max_x;
			switch(ch)
			{
			case '#':
				objects.push_back(new Wall(x, y));
				break;
			case 'X':
				objects.push_back(new Monster(x, y));
				break;
			}
			i++;
		}
	}
private:
	Renderer *renderer;
	vector<Object*> objects;
};