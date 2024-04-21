#pragma once
#include "utils.h"

#include <vector>
#include <memory>

class Scene;

class GameObject
{
public:
	GameObject(Scene* scene);
	virtual ~GameObject() = default;

	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

	virtual void Update() = 0;
	virtual void Render() = 0;

protected:
	Scene* GetOwner() const { return m_Owner; }
private:
	Scene* m_Owner;
};

