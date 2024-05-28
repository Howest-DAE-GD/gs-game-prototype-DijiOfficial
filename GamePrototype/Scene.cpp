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

void Scene::Remove(GameObject* object)
{
	std::erase_if(m_GameObjects,
		[object](const auto& objUPtr)
		{
			return objUPtr.get() == object;
		}
	);
}
