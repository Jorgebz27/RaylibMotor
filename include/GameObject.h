#pragma once
#include "raylib.h"
#include "Component.h"
#include <iostream>
#include <string>
#include <memory>
#include <vector>

typedef std::shared_ptr<Component>  ptrComponent;

class GameObject
{
public:

	bool enabled;
	int id;

	GameObject();
	~GameObject();

	//void init();
	//void init(Vector2 pos, Vector2 vel);
	//void init(Vector2 pos, Vector2 vel, Color color);
	void Start();
	void Update(float deltaTime);
	void Draw(float deltatime);

	//void setVelocity(Vector2 vel) { velocity = vel; }
	//static GameObject* SpawnGO(Vector2 pos, Vector2 vel, std::string _name);

	void AddComponent(ptrComponent newComp);
	void RemoveComponent();

	//si se debe updatear el objeto
	//bool enabled;
	//Vector2 position;
	//Vector2 velocity;
	//Color color;

private:
	//unsigned int id;
	//std::string name;
	//static unsigned int nextId;
	std::vector<ptrComponent> components;

	friend class Component;

};