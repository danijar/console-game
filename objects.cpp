#pragma once
#include "include.h"
#include "renderer.cpp"

struct Position
{
	Position() : x(0), y(0) {}
	bool operator==(const Position &other) const {
    	return ((x == other.x) && (y == other.y));
  	}
	void Set(int x, int y) { this->x = x; this->y = y; }
	int x, y;
};

struct Object
{
	Object() : Visual(' '), Collision(false), Moving(false) {}
	virtual void Update() = 0;
	Position Pos;
	char Visual;
	bool Collision, Moving;
};

struct Static : public Object
{
	Static(int x = 0, int y = 0, char visual = '\xDB')
	{
		Visual = visual;
		Collision = true;
		Pos.Set(x, y);
	}
	void Update() {}
};

struct Player : public Object
{
	Player(int x = 0, int y = 0)
	{
		Visual = 'O';
		Collision = true;
		Moving = true;
		Pos.Set(x, y);
	}
	void Update()
	{
		if((GetAsyncKeyState(VK_LEFT) ) || (GetAsyncKeyState(0x41))) Pos.x--;
		if((GetAsyncKeyState(VK_RIGHT)) || (GetAsyncKeyState(0x44))) Pos.x++;
		if((GetAsyncKeyState(VK_UP)   ) || (GetAsyncKeyState(0x57))) Pos.y--;
		if((GetAsyncKeyState(VK_DOWN) ) || (GetAsyncKeyState(0x53))) Pos.y++;
	}
};

struct Monster : public Object
{
	Monster(int x = 0, int y = 0) : dir(true), distance(0)
	{
		Visual = 'X';
		Collision = true;
		Moving = true;
		Pos.Set(x, y);
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

struct Water : public Object
{
	Water(int x = 0, int y = 0) : animation(new char[4]), frame(0), slow(5)
	{
		Collision = true;
		Pos.Set(x, y);

		animation[0] = 'W';
		animation[1] = 'V';
		animation[2] = '|';
		animation[3] = 'V';
	}
	void Update()
	{
		if(frame / slow > 4-1) frame = 0;
		if(frame % slow == 0) Visual = animation[frame / slow];
		frame++;
	};
	char* animation;
	int frame;
	int slow;
};

class Objects
{
public:
	Objects(Renderer* renderer) : renderer(renderer), player(new Player(0, 0))
	{
		objects.push_back(player);
	}
	void Update()
	{
		renderer->Clear();
		for(auto i = objects.begin(); i != objects.end(); ++i)
		{
			auto pos_old = (*i)->Pos;

			(*i)->Update();

			if((*i)->Moving)
			{
				if((*i)->Pos.x < 0)     			(*i)->Pos.x = 0;
				if((*i)->Pos.x > renderer->X() - 1) (*i)->Pos.x = renderer->X() - 1;
				if((*i)->Pos.y < 0)     			(*i)->Pos.y = 0;
				if((*i)->Pos.y > renderer->Y() - 1) (*i)->Pos.y = renderer->Y() - 1;

				for(auto j = objects.begin(); j != objects.end(); ++j)
				{
					if(i == j) continue;
					if((*j)->Collision)
					{
						if((*j)->Pos == (*i)->Pos)
						{
							(*i)->Pos = pos_old;
							break;
						}
					}
				}
			}
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
			case '1':
				objects.push_back(new Static(x, y, '\xB0'));
				break;
			case '2':
				objects.push_back(new Static(x, y, '\xB1'));
				break;
			case '3':
				objects.push_back(new Static(x, y, '\xB2'));
				break;
			case '4':
				objects.push_back(new Static(x, y, '\xDB'));
				break;
			case 'A':
				objects.push_back(new Monster(x, y));
				break;
			case 'W':
				objects.push_back(new Water(x, y));
				break;
			case 'O':
				player->Pos.Set(x, y);
				break;
			}
			i++;
		}
	}
private:
	Renderer *renderer;
	Player *player;
	vector<Object*> objects;
};