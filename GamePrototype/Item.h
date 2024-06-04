#pragma once
#include "GameObject.h"
#include "CollisionSingleton.h"
class Player;

class Item : public GameObject
{
public:
	Item(Scene* scene, Player* player, const unsigned int id)
		: GameObject(scene)
		, m_PlayerPtr(player)
		, m_ID{ id }
	{
	};
	~Item() = default;

	Item(const Item& other) = delete;
	Item(Item&& other) = delete;
	Item& operator=(const Item& other) = delete;
	Item& operator=(Item&& other) = delete;

	void Update() override = 0;
	void Render() const override = 0;
	void Reset() override = 0;
	void Drop(const Point2f& pos) { m_IsDropped = true; m_Center = pos; }
	void PickUp();
	unsigned int GetID() const { return m_ID; }

	bool IsDropped() const { return m_IsDropped; }
	bool IsOwned() const { return m_IsOwned; }
	void SetUsed();
	Rectf GetShape() const { return Rectf{ m_Center.x, m_Center.y, 8, 8 }; }
	void SetPos(const Point2f& pos) { m_Center = pos; }

protected:
	Player* GetPlayer() const { return m_PlayerPtr; }
	Point2f m_Center{};

	const unsigned int m_ID;
	bool m_IsOwned = false;
	bool m_IsDropped = false;
	CollisionSingleton& m_CollisionSingleton = CollisionSingleton::GetInstance();
	Player* m_PlayerPtr;
};

class Key final : public Item
{
public:
	Key(Scene* scene, Player* player, const unsigned int id)
		: Item(scene, player, id)
	{
	};
	~Key() = default;

	void Update() override;
	void Render() const override;
	void Reset() override;
};

class FinalKey final : public Item
{
public:
	FinalKey(Scene* scene, Player* player, const unsigned int id)
		: Item(scene, player, id)
	{
	};
	~FinalKey() = default;

	void Update() override;
	void Render() const override;
	void Reset() override;
};