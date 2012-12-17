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
	Object() : Visual(' '), Collision(false), Moving(false), Erase(false) {}
	virtual void Update() = 0;
	virtual void Collide() {}
	Position Pos;
	char Visual;
	bool Collision, Moving;
	bool Erase;
};

#include "entities.cpp"

class Objects
{
public:
	Objects(Renderer* renderer) : renderer(renderer), player(new Player(0, 0)), objects_size(0)
	{
		objects.push_back(player);
		renderer->Line("Objects: ", &objects_size);
		renderer->Line("Score: ", &player->Score);
	}
	void Update()
	{
		renderer->Clear();
		objects_size = objects.size();
		for(auto i = objects.rbegin(); i != objects.rend(); ++i)
		{
			if((*i)->Erase)
			{
				objects.erase(--i.base());
				continue;
			}
			auto pos_old = (*i)->Pos;
			(*i)->Update();
			if((*i)->Moving)
			{
				if((*i)->Pos.x < 0)     			{ (*i)->Pos.x = 0;				   (*i)->Collide(); }
				if((*i)->Pos.x > renderer->X() - 1) { (*i)->Pos.x = renderer->X() - 1; (*i)->Collide(); }
				if((*i)->Pos.y < 0)     			{ (*i)->Pos.y = 0;				   (*i)->Collide(); }
				if((*i)->Pos.y > renderer->Y() - 1) { (*i)->Pos.y = renderer->Y() - 1; (*i)->Collide(); }
				for(auto j = objects.rbegin(); j != objects.rend(); ++j)
				{
					if(i == j) continue;
					if((*j)->Collision)
					{
						if((*j)->Pos == (*i)->Pos)
						{
							(*i)->Pos = pos_old;
							(*i)->Collide();
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
				objects.push_back(new Static(x, y, '\xB1'));
				break;
			case '2':
				objects.push_back(new Static(x, y, '\xB2'));
				break;
			case '3':
				objects.push_back(new Static(x, y, '\xDB'));
				break;
			case 'A':
				objects.push_back(new MonsterA(x, y));
				break;
			case 'B':
				objects.push_back(new MonsterB(x, y));
				break;
			case 'C':
				objects.push_back(new MonsterC(x, y, player));
				break;
			case 'W':
				objects.push_back(new Animation(x, y, {'W','V'} ));
				break;
			case 'c':
				objects.push_back(new Orb(x, y, player));
				break;
			case '=':
				objects.push_back(new Door(x, y, player));
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
	int objects_size;
};