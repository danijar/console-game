#pragma once

bool Near(int one, int two, int distance = 1)
{
	bool result = false;
	for(int i = -distance; i <= distance; ++i)
	{
		if(one == two + i)
		{
			result = true;
			break;
		}
	}
	return result;
}
bool Near(Position one, Position two, int distance = 1)
{
	return (Near(one.x, two.x, distance) && Near(one.y, two.y, distance));
}


struct Static : public Object
{
	Static(int x, int y, char visual = '\xDB')
	{
		Visual = visual;
		Collision = true;
		Pos.Set(x, y);
	}
	void Update() {}
	void Collide() {}
};

struct Animation : public Object
{
	Animation(int x, int y, initializer_list<char> chars, int speed = 5) : speed(speed), frame(1), counter(0)
	{
		Collision = true;
		Pos.Set(x, y);
		for(auto i = chars.begin(); i != chars.end(); ++i) frames.push_back(*i);
		Visual = frames[0];
	}
	void Update()
	{
		if(counter++ > speed)
		{
			counter = 0;
			if(frame > frames.size()-1) frame = 0;
			Visual = frames[frame++];
		}
	};
	void Collide() {}
private:
	vector<char> frames;
	const unsigned int speed;
	unsigned int frame, counter;
};

struct Player : public Object
{
	Player(int x = 0, int y = 0) : Score(0)
	{
		Visual = '\xAD';
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
	void Collide() {}
	int Score;
};

struct Orb : public Object
{
	Orb(int x, int y, Player* player) : player(player)
	{
		Visual = '\xB8';
		Pos.Set(x, y);
	}
	void Update()
	{
		if(Pos == player->Pos)
		{
			player->Score++;
			Erase = true;
		}
	}
	void Collide() {}
private:
	Player* player;
};

struct Door : public Object
{
	Door(int x, int y, Player* player) : player(player)
	{
		Visual = '=';
		Collision = true;
		Pos.Set(x, y);
	}
	void Update()
	{
		if(Near(Pos, player->Pos))
		{
			Visual = ' ';
			Collision = false;
		}
		else
		{
			Visual = '=';
			Collision = true;
		}
	}
	void Collide() {}
private:
	Player* player;
};

struct MonsterA : public Object
{
	MonsterA(int x = 0, int y = 0) : dir(true), distance(0)
	{
		Visual = '\x98';
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
	void Collide() {}
private:
	bool dir;
	int distance;
};

struct MonsterB : public Object
{
	MonsterB(int x = 0, int y = 0) : dir(1)
	{
		Visual = '\x98';
		Collision = true;
		Moving = true;
		Pos.Set(x, y);
	}
	void Update()
	{
		if     (dir == 1) Pos.y--;
		else if(dir == 2) Pos.x++;
		else if(dir == 3) Pos.y++;
		else if(dir == 4) Pos.x--;
	}
	void Collide()
	{
		dir++;
		if(dir > 4) dir = 1;
	}
private:
	int dir;
};

struct MonsterC : public Object
{
	MonsterC(int x, int y, Player* player) : player(player), dir(true)
	{
		Visual = '\x98';
		Collision = true;
		Moving = true;
		Pos.Set(x, y);
	}
	void Update()
	{
		if(Near(Pos, player->Pos, 9))
		{
			if(dir)
			{
				if(Pos.x < player->Pos.x) Pos.x++;
				else if(Pos.x > player->Pos.x) Pos.x--;
			}
			else
			{
				if(Pos.y < player->Pos.y) Pos.y++;
				else if(Pos.y > player->Pos.y) Pos.y--;
			}
		}
		dir = !dir;
	}
	void Collide() {}
private:
	Player* player;
	bool dir;
};
