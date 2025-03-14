#pragma once
#include "raylib.h"

class GameObject;

class Component
{
public:
	virtual ~Component() = default;
	virtual bool ShouldDraw() const { return shouldDraw; };

private:
	GameObject* owner;
	bool shouldDraw = true;

	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw(float deltaTime) = 0;

	friend class GameObject;
};

