#pragma once
#include "Level.h"
#include "Player.h"
#include "Camera.h"

class Scene final
{
public:
    Scene();
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

    void Update();
    void Render() const;

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

private:
    std::vector<std::unique_ptr<GameObject>> m_GameObjects;

    void CommandInit() const;
};

