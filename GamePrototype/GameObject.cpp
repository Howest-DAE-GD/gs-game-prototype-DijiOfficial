#include "pch.h"
#include "GameObject.h"
#include "Scene.h"

GameObject::GameObject(Scene* scene) 
	: m_Owner{ scene } 
{

};
