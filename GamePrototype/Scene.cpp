#include "pch.h"
#include "Scene.h"

void Scene::Update()
{
    for (auto& gameObject : m_GameObjects)
    {
        gameObject->Update();
    }
}

void Scene::Render() const
{
    for (const auto& gameObject : m_GameObjects)
    {
		gameObject->Render();
	}
}
