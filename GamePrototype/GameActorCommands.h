#pragma once
#include "Command.h"
#include <map>

class Player;
class Level;
enum class PointType;

class GameActorCommands : public Command
{
public:
	explicit GameActorCommands(GameObject* actor) : m_ActorPtr(actor) {};
	~GameActorCommands() override = default;

protected:
	GameObject* GetGameActor() const { return m_ActorPtr; }

private:
	GameObject* m_ActorPtr;
};

class Move final: public GameActorCommands
{
public:
	Move(GameObject* actor, Movement movement);
	~Move() override = default;
		
	void Execute() override;
	
private:
	const Point2f m_Speed{ 300.f, 300.f }; //sets speed as universal, may change it to get it from the actor
	Movement m_Movement;
	Player* m_PlayerPtr;
};

class Rotate final : public GameActorCommands
{
public:
	Rotate(GameObject* actor);
	~Rotate() override = default;

	void Execute() override;
private:
	Player* m_PlayerPtr;
};

class Attack final : public GameActorCommands
{
public:
	Attack(GameObject* actor);
	~Attack() override = default;

	void Execute() override;

private:
	Player* m_PlayerPtr;
};

