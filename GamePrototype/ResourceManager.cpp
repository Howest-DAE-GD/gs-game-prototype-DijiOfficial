#include "pch.h"
#include "ResourceManager.h"
//#include "Renderer.h"

#include <stdexcept>
#include <SDL_image.h>
//#include <SDL_ttf.h>
//#include <SDL_mixer.h> 

//void ResourceManager::Init()
//{
//	if (TTF_Init() != 0)
//	{
//		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
//	}
//}

Texture* ResourceManager::LoadTexture(const std::string& file)
{
	// check if texture is already loaded
	const auto it = m_TexturesUPtrUMap.find(file);
	if (it != m_TexturesUPtrUMap.cend())
	{
		return it->second.get();
	}

	// Store it if it's not already loaded
	m_TexturesUPtrUMap[file] = std::make_unique<Texture>(file);
	return m_TexturesUPtrUMap[file].get();
}