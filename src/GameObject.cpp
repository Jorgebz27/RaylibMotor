#include "GameObject.h"

/*unsigned int GameObject::nextId = 1;

GameObject::GameObject()
{
	name = "defaultObject";
	id = 0;
}

GameObject::~GameObject()
{
}

void GameObject::init()
{
	std::cout << "NOOO, es patricio!" << std::endl;
	//valores default
	position = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
	velocity = { 0, 0 };
	color = RED;
	//init(position, velocity);
}

void GameObject::init(Vector2 pos, Vector2 vel)
{
	position = pos;
	velocity = vel;
	color = RED;
}

void GameObject::init(Vector2 pos, Vector2 vel, Color color)
{
	position = pos;
	velocity = vel;
	this->color = color;
}

void GameObject::update()
{
	position.x += velocity.x * GetFrameTime();
	position.y += velocity.y * GetFrameTime();
	if(position.x > GetScreenWidth() || position.x < 0)
	{
		velocity.x *= -1;
	}
	if (position.y > GetScreenHeight() || position.y < 0)
	{
		velocity.y *= -1;
	}
}

void GameObject::draw()
{
	DrawCircle(position.x, position.y, 10, color);
}

GameObject* GameObject::SpawnGO(Vector2 pos, Vector2 vel, std::string _name)
{
	GameObject* go = new GameObject();
	go->init(pos, vel);
	go->name = _name;
	go->color = GREEN;
	go->id = nextId++;
	std::cout << "Spawning " << go->id << ":" << _name << std::endl;
	return go;
}*/

GameObject::GameObject()
{
	id = 0;
	enabled = true;
}

GameObject::~GameObject()
{
}

void GameObject::Start()
{
}

void GameObject::Update(float deltaTime)
{
	for (auto& comp : components)
	{
		comp->Update();
	}
}

void GameObject::Draw(float deltaTime)
{
	for (auto& comp : components)
	{
		if (comp->ShouldDraw())
		{
			comp->Draw();
		}
	}
}

void GameObject::AddComponent(ptrComponent newComp)
{
	components.push_back(newComp);
}

void GameObject::RemoveComponent()
{
}