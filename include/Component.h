#pragma once
class GameObject;

class Component
{
public:
	virtual ~Component() = default;
	virtual bool ShouldDraw() const { return shouldDraw; };

private:
	GameObject* owner;
	bool shouldDraw = true;

	void Start();
	void Update();
	void Draw();

	friend class GameObject;
};

