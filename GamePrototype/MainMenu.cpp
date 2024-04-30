#include "pch.h"

#include "MainMenu.h"
#include "Button.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "TimeSingleton.h"

MainMenu::MainMenu(Scene* scene, const Point2f& viewport)
	: GameObject(scene)
	, m_Shape{ 0, 0, viewport.x, viewport.y }
	, m_Shape2{ 0, viewport.y-1, viewport.x, viewport.y }
	, m_ViewportHeight{ viewport.y }
{
	m_Texture = ResourceManager::GetInstance().LoadTexture("Images/background.png");

	InitializeButtons();
	m_Buttons[0]->InverseSelction();
}

void MainMenu::Update()
{
	const auto dt = TimeSingleton::GetInstance().GetDeltaTime();
	m_Shape.bottom -= 100 * dt;
	m_Shape2.bottom -= 100 * dt;

	if (m_Shape.bottom <= -m_ViewportHeight)
		m_Shape.bottom = m_ViewportHeight - 2;
	if (m_Shape2.bottom <= -m_ViewportHeight)
		m_Shape2.bottom = m_ViewportHeight - 2;
	
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	if (!pStates[SDL_SCANCODE_DOWN] && !pStates[SDL_SCANCODE_S])
		wasDownKey = false;

	if (!pStates[SDL_SCANCODE_UP] && !pStates[SDL_SCANCODE_W])
		wasUpKey = false;

	if ((pStates[SDL_SCANCODE_DOWN] or pStates[SDL_SCANCODE_S]) && !wasDownKey)
	{
		m_Buttons[m_SelectedButton]->InverseSelction();
		m_SelectedButton = abs(m_SelectedButton - 1) % 2;
		m_Buttons[m_SelectedButton]->InverseSelction();
		wasDownKey = true;
	}
	if ((pStates[SDL_SCANCODE_UP] or pStates[SDL_SCANCODE_W]) && !wasUpKey)
	{
		m_Buttons[m_SelectedButton]->InverseSelction();
		m_SelectedButton = (m_SelectedButton + 1) % 2;
		m_Buttons[m_SelectedButton]->InverseSelction();
		wasUpKey = true;
	}
}

void MainMenu::Render() const
{
	m_Texture->Draw(m_Shape);
	m_Texture->Draw(m_Shape2);

	for (const auto& button : m_Buttons)
	{
		button->Render();
	}
}

void MainMenu::InitializeButtons()
{
	m_Buttons.push_back(std::make_unique<Button>(Rectf{ 50.0f, 300.0f, 200.0f, 50.0f }, "Play", "Fonts/zig.ttf", 34, Color4f{ 0.789f, 0.789f, 0.789f, 1.f }, Color4f{ 0.98f, 0.75f, 0.32f, 1.f }));
	m_Buttons.push_back(std::make_unique<Button>(Rectf{ 50.0f, 250.0f, 200.0f, 50.0f }, "Options", "Fonts/zig.ttf", 34, Color4f{ 0.789f, 0.789f, 0.789f, 1.f }, Color4f{ 0.98f, 0.75f, 0.32f, 1.f }));
}
