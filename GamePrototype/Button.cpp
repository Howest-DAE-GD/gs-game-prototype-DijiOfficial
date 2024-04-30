#include "pch.h"

#include "Button.h"
#include "Texture.h"
#include "Scene.h"
#include "ResourceManager.h"

Button::Button(const Rectf& shape, const std::string& text, const std::string& fontPath, unsigned int ptSize, const Color4f& textColor, const Color4f& textColorSelected)
{
	auto font = ResourceManager::GetInstance().LoadFont(fontPath, ptSize);

	m_Texture = ResourceManager::GetInstance().LoadTexture(text, font, textColor);
	m_TextureSelected = ResourceManager::GetInstance().LoadTexture(text + " ", font, textColorSelected);
	m_Background = ResourceManager::GetInstance().LoadTexture("Images/buttonBackground.png");
	m_Arrow = ResourceManager::GetInstance().LoadTexture("Images/arrowSelect.png");

	m_Shape = Rectf{ shape.left, shape.bottom, m_Texture->GetWidth(), m_Texture->GetHeight() };
	m_Shape2 = Rectf{ shape.left, shape.bottom, m_TextureSelected->GetWidth(), m_TextureSelected->GetHeight() };
	m_ArrowShape = Rectf{ m_Shape.left - (m_Shape.height * 1.2f), m_Shape.bottom + m_Shape.height * 0.125f, m_Shape.height * 0.75f, m_Shape.height * 0.75f };
	m_BackgroungShape = Rectf{ m_Shape.left - (m_Shape.height * 0.3f), m_Shape.bottom - m_Shape.height * 0.2f, m_Shape.width * 2.2f, m_Shape.height * 1.4f };
}

Button::Button(const Rectf& shape, const std::string& text, const std::string& fontPath, unsigned int ptSize, const Color4f& textColor)
{
	auto font = ResourceManager::GetInstance().LoadFont(fontPath, ptSize);

	m_Texture = ResourceManager::GetInstance().LoadTexture(text, font, textColor);
	m_TextureSelected = nullptr;
	m_Background = ResourceManager::GetInstance().LoadTexture("Images/buttonBackground.png");
	m_Arrow = ResourceManager::GetInstance().LoadTexture("Images/arrowSelect.png");

	m_Shape = Rectf{ shape.left, shape.bottom, m_Texture->GetWidth(), m_Texture->GetHeight() };

}

Button::Button(const Rectf& shape, const std::string& texturePath)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(texturePath);
	m_TextureSelected = nullptr;
	m_Background = nullptr;
	m_Arrow = ResourceManager::GetInstance().LoadTexture("Images/arrowSelect.png");

	m_Shape = Rectf{ shape.left, shape.bottom, m_Texture->GetWidth(), m_Texture->GetHeight() };
}


void Button::Render() const
{
	if (m_IsSelected)
	{
		m_Background->Draw(m_BackgroungShape);
		m_Arrow->Draw(m_ArrowShape);

		m_TextureSelected->Draw(m_Shape2);
	}
	else
		m_Texture->Draw(m_Shape);

}
