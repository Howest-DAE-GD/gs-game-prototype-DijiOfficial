#pragma once
#include "GameObject.h"
#include "Button.h"

class Texture;

class MainMenu final : public GameObject
{
public:
	MainMenu(Scene* scene, const Point2f& viewport);
	~MainMenu() = default;

	void Update() override;
	void Render() const override;

	int GetSelectedButton() const { return m_SelectedButton; }

private:
	std::vector<std::unique_ptr<Button>> m_Buttons;
	Rectf m_Shape;
	Rectf m_Shape2;
	Texture* m_Texture;
	
	const float m_ViewportHeight;
	int m_SelectedButton = 0;

	bool wasDownKey = false;
	bool wasUpKey = false;

	void InitializeButtons();
};
