#pragma once
#include "raylib.h"
#include <iostream>
#include <string>

class GameObject
{
public:
	GameObject();
	~GameObject();

	void init();
	void init(Vector2 pos, Vector2 vel);
	void init(Vector2 pos, Vector2 vel, Color color);
	void update();
	void draw();
	void setVelocity(Vector2 vel) { velocity = vel; }
	static GameObject* SpawnGO(Vector2 pos, Vector2 vel, std::string _name);

	Vector2 position;
	Vector2 velocity;
	Color color;

private:
	unsigned int id;
	std::string name;
	static unsigned int nextId;

};

