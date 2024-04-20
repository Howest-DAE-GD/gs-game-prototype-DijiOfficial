#pragma once
#include "utils.h"

#include <vector>
#include <memory>

class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;

	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

	virtual void Update() = 0;
	virtual void Render() = 0;
};

