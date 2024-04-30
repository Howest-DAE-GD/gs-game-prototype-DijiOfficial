#include <stdexcept>
#include <SDL_ttf.h>
#include "Font.h"

TTF_Font* Font::GetFont() const {
	return m_FontPtr;
}

Font::Font(const std::string& fullPath, unsigned int size) : m_FontPtr(nullptr)
{
	m_FontPtr = TTF_OpenFont(fullPath.c_str(), size);
	if (m_FontPtr == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

//Font::~Font()
//{
//	//TTF_CloseFont(m_FontPtr);
//}
