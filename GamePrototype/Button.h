#pragma once
class Texture;
class Scene;

class Button final
{ 
public:
	Button(const Rectf& shape, const std::string& text, const std::string& fontPath, unsigned int ptSize, const Color4f& textColor, const Color4f& textColorSelected);
	Button(const Rectf& shape, const std::string& text, const std::string& fontPath, unsigned int ptSize, const Color4f& textColor);
	Button(const Rectf& shape, const std::string& texturePath);
	~Button() = default;

	void Render() const;

	void InverseSelction() { m_IsSelected = !m_IsSelected; };

private:
	Rectf m_Shape;
	Rectf m_Shape2{};
	Rectf m_ArrowShape;
	Rectf m_BackgroungShape;
	Texture* m_Texture;
	Texture* m_TextureSelected;
	Texture* m_Background;
	Texture* m_Arrow;
	bool m_IsSelected = false;
};
