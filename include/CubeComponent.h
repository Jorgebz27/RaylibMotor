#pragma once
#include "Component.h"

class CubeComponent : public Component
{
public:
	~CubeComponent() override = default;

	void Start() override;
	void Update(float deltaTime) override;
	void Draw(float deltaTime) override;
};

