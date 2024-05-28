#pragma once
#include "Singleton.h"
#include "Scene.h"
#include <string>
#include <map>
#include "InputManager.h"
#include "MainMenu.h"
#include "BossManager.h"
//put all this in cpp if include errors
enum class GameState
{
    INVALID,
    INTRO,
    MAIN_MENU,
    OPTIONS,
    SETTINGS,
    CONTROLS,
    MENU,
    UPGRADES,
    CLASS_SELECTION,
    LEVEL,
    PAUSE,
    WIN,
};

class SceneManager final : public Singleton<SceneManager>
{ 
public:
    Scene* CreateScene(const std::string& name)
    {
        m_Scenes[name] = std::make_unique<Scene>();
		return m_Scenes[name].get();
    };
    Scene* GetScene(const std::string& name) const 
    {
		return m_Scenes.at(name).get();
	};

    void Update()
    {
		if (m_GameState == GameState::LEVEL)
		{
			auto& input = InputManager::GetInstance();
			(void)input.ProcessInput();
		}

		const Uint8* pStates = SDL_GetKeyboardState(nullptr);

		if (pStates[SDL_SCANCODE_RETURN])
			if (m_GameState == GameState::MAIN_MENU)
			{
				int selection = m_Scenes["Menu"]->GetGameObject<MainMenu>()->GetSelectedButton();
				if (selection == 0)
				{
					m_GameState = GameState::LEVEL;
				}
			}

		switch (m_GameState)
		{
		case GameState::INTRO:
			break;
		case GameState::MAIN_MENU:
			m_Scenes["Menu"]->Update();
			break;
		case GameState::OPTIONS:
			break;
		case GameState::SETTINGS:
			break;
		case GameState::CONTROLS:
			break;
		case GameState::MENU:
			break;
		case GameState::UPGRADES:
			break;
		case GameState::CLASS_SELECTION:
			break;
		case GameState::LEVEL:
			m_Scenes["Level"]->Update();
			m_Scenes["Hud"]->Update();

			if (m_Scenes["Level"]->GetGameObject<BossManager>()->IsFinalBossDead())
				m_GameState = GameState::WIN;
			break;
		case GameState::PAUSE:
			break;
		case GameState::WIN:
			break;
		default:
			break;
		}
    }
    void Render() const
    {
		switch (m_GameState)
		{
		case GameState::INTRO:
			break;
		case GameState::MAIN_MENU:
			m_Scenes.at("Menu")->Render();
			break;
		case GameState::OPTIONS:
			break;
		case GameState::SETTINGS:
			break;
		case GameState::CONTROLS:
			break;
		case GameState::MENU:
			break;
		case GameState::UPGRADES:
			break;
		case GameState::CLASS_SELECTION:
			break;
		case GameState::LEVEL:
			glPushMatrix();
			{
				m_Scenes.at("Level")->Render();
			}
			glPopMatrix();

			m_Scenes.at("Hud")->Render();
			break;
		case GameState::PAUSE:
			break;
		default:
			break;
		}
    }

	//void SetGameState(const GameState state) { m_GameState = state; }
	void TranferScene(const std::string& fromScene, const std::string& toScene, GameObject* object)
	{
		std::unique_ptr<GameObject> removedObj = m_Scenes[fromScene]->RemoveAndReturnGameObject(object);
		if (removedObj)
		{
			m_Scenes[toScene]->AddExistingGameObject(std::move(removedObj));
		}
	}
	//void DeleteGameObject(std::string scene, GameObject* object)
	//{
	//	m_Scenes[scene]->Remove(object);
	//}

	//void AddGameObject(std::string scene, GameObject* object)
	//{
	//	m_Scenes[scene]->AddExistingObject(object);
	//}
private:
    std::map<std::string, std::unique_ptr<Scene>> m_Scenes;
	GameState m_GameState = GameState::MAIN_MENU;

};

