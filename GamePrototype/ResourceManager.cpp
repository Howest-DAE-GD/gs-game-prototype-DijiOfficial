#include "pch.h"
#include "ResourceManager.h"
//#include "Renderer.h"

#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
//#include <SDL_mixer.h> 

Texture* ResourceManager::LoadTexture(const std::string& file)
{
	const auto it = m_TexturesUPtrUMap.find(file);
	if (it != m_TexturesUPtrUMap.cend())
	{
		return it->second.get();
	}

	// Store it if it's not already loaded
	m_TexturesUPtrUMap[file] = std::make_unique<Texture>(file);
	return m_TexturesUPtrUMap[file].get();
}

Texture* ResourceManager::LoadTexture(const std::string& text, Font* font, const Color4f& textColor)
{
	const auto it = m_TexturesUPtrUMap.find(text);
	if (it != m_TexturesUPtrUMap.cend())
	{
		return it->second.get();
	}

	m_TexturesUPtrUMap[text] = std::make_unique<Texture>(text, font->GetFont(), textColor);
	return m_TexturesUPtrUMap[text].get();
}

Font* ResourceManager::LoadFont(const std::string& file, unsigned int size)
{
    // check if texture is already loaded
    const auto range = m_FontsUPtrUMap.equal_range(file);
    for (auto it = range.first; it != range.second; ++it)
    {
        if (it->second.first == size)
        {
            return it->second.second.get();
        }
    }

    // Store it if it's not already loaded
    auto font = std::make_unique<Font>(file, size);
    Font* fontPtr = font.get();
    m_FontsUPtrUMap.emplace(file, std::make_pair(size, std::move(font)));

    return fontPtr;
}
