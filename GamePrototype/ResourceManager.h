#pragma once
#include "Singleton.h"

#include <memory>
#include <unordered_map>
#include "Texture.h"

#include "Font.h"
class ResourceManager final : public Singleton<ResourceManager>
{
public:

	Texture* LoadTexture(const std::string& file);
	Texture* LoadTexture(const std::string& text, Font* font, const Color4f& textColor);
	Font* LoadFont(const std::string& file, unsigned int size);

private:
	friend class Singleton<ResourceManager>;
	ResourceManager() = default;

	std::unordered_map<std::string, std::unique_ptr<Texture>> m_TexturesUPtrUMap;
	std::unordered_multimap<std::string, std::pair<unsigned int, std::unique_ptr<Font>>> m_FontsUPtrUMap;

};
