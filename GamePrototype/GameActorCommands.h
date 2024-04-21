#pragma once
#include "Command.h"
#include <map>

class Player;
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

//class HitCommand final : public GameActorCommands
//{
//
//public:
//	HitCommand(GameObject* actor);
//	~HitCommand() override = default;
//
//	void Execute() override;
//
//private:
//	HealthCounter* m_HealthComponentPtr;
//};
//
//class ScoreCommand final : public GameActorCommands
//{
//
//public:
//	ScoreCommand(GameObject* actorPtr, PointType point);
//	~ScoreCommand() override = default;
//
//	void Execute() override;
//
//private:
//	ScoreCounter* m_ScoreComponentPtr;
//	PointType m_PointType;
//};

