#pragma once
#include "Singleton.h"

#include <memory>
#include <unordered_map>
#include "Texture.h"

class ResourceManager final : public Singleton<ResourceManager>
{
public:
	//void Init();
	Texture* LoadTexture(const std::string& file);

private:
	friend class Singleton<ResourceManager>;
	ResourceManager() = default;

	std::unordered_map<std::string, std::unique_ptr<Texture>> m_TexturesUPtrUMap;
};
