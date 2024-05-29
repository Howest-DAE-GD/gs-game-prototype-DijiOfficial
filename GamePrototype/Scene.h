#pragma once
#include "Level.h"
#include "Player.h"
#include "Camera.h"

class Scene final
{
public:
    Scene() = default;
    ~Scene() = default;

    Scene(const Scene& other) = delete;
    Scene(Scene&& other) = delete;
    Scene& operator=(const Scene& other) = delete;
    Scene& operator=(Scene&& other) = delete;

    template<typename T, typename... Args,
        typename = std::enable_if_t<std::is_base_of_v<GameObject, T>>>
    void AddGameObject(Args&&... args)
    {
        m_GameObjects.push_back(std::make_unique<T>(this, std::forward<Args>(args)...));
    }

    template<typename T, typename... Args,
        typename = std::enable_if_t<std::is_base_of_v<GameObject, T>>>
    auto CreateGameObjects(Args&&... args) -> T*
    {
        m_GameObjects.push_back(std::make_unique<T>(this, std::forward<Args>(args)...));
        return static_cast<T*>(m_GameObjects.back().get());
    }

    void Update();
    void Render() const;
    void Reset();
    // Function to get a pointer to a GameObject by its type
    template <typename T>
    T* GetGameObject() const
    {
        for (auto& gameObject : m_GameObjects)
        {
            if (auto casted = dynamic_cast<T*>(gameObject.get()))
            {
                return casted;
            }
        }
        return nullptr;
    }

    void Remove(GameObject* object);

    std::unique_ptr<GameObject> RemoveAndReturnGameObject(GameObject* obj)
    {
        auto it = std::find_if(m_GameObjects.begin(), m_GameObjects.end(),
            [obj](const std::unique_ptr<GameObject>& gameObject)
            {
                return gameObject.get() == obj;
            });

        if (it != m_GameObjects.end())
        {
            std::unique_ptr<GameObject> removedObject = std::move(*it);
            m_GameObjects.erase(it);
            return removedObject;
        }
        return nullptr;
    }

    void AddExistingGameObject(std::unique_ptr<GameObject> obj)
    {
        m_GameObjects.push_back(std::move(obj));
    }

private:
    std::vector<std::unique_ptr<GameObject>> m_GameObjects;

    void CommandInit() const;
};

