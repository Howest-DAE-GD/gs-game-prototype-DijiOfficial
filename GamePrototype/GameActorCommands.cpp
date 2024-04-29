#include "pch.h"
#include "GameActorCommands.h"
#include "Player.h"
#include "Level.h"
#include "TimeSingleton.h"
#include "InputManager.h"

Move::Move(GameObject* actor, Movement movement)
	: GameActorCommands{ actor }
	, m_Movement{ movement }
{
	m_PlayerPtr = dynamic_cast<Player*>(GetGameActor());
}

void Move::Execute()
{
	const auto& deltaTime = TimeSingleton::GetInstance().GetDeltaTime();
	auto pos = m_PlayerPtr->GetShape();

	switch (m_Movement)
	{
	case Movement::Up:
		pos.bottom += m_Speed.y * deltaTime;
		break;
	case Movement::Down:
		pos.bottom -= m_Speed.y * deltaTime;
		break;
	case Movement::Left:
		pos.left -= m_Speed.x * deltaTime;
		break;
	case Movement::Right:
		pos.left += m_Speed.x * deltaTime;
		break;
	}

	if (not m_PlayerPtr->IsColliding(pos))
		m_PlayerPtr->SetShape(pos);
}

//HitCommand::HitCommand(GameObject* actor)
//	: GameActorCommands{ actor }
//{
//	m_HealthComponentPtr = GetGameActor()->GetComponent<HealthCounter>();
//}
//
//void HitCommand::Execute()
//{
//	m_HealthComponentPtr->DecreaseHealth();
//}
//
//ScoreCommand::ScoreCommand(GameObject* actorPtr, PointType point)
//	: GameActorCommands{ actorPtr }
//	, m_PointType{ point }
//{
//	m_ScoreComponentPtr = GetGameActor()->GetComponent<ScoreCounter>();
//}
//
//void ScoreCommand::Execute()
//{
//	m_ScoreComponentPtr->IncreaseScore(m_PointType);
//}

Rotate::Rotate(GameObject* actor)
	: GameActorCommands{ actor }
{
	m_PlayerPtr = dynamic_cast<Player*>(GetGameActor());
}

void Rotate::Execute()
{
	const auto& mousePos = InputManager::GetInstance().GetMouseMotion();
	const auto& playerShape = m_PlayerPtr->GetRelativeCenter();

	const double deltaX =  mousePos.x - playerShape.x;
	const double deltaY = mousePos.y - playerShape.y;
	const double angleRad = atan2(deltaY, deltaX);

	const float angleDeg = static_cast<float>(angleRad * (180.0 / M_PI));

	m_PlayerPtr->SetAngle(angleDeg);

}

Attack::Attack(GameObject* actor)
	: GameActorCommands{ actor }
{
	m_PlayerPtr = dynamic_cast<Player*>(GetGameActor());
}

void Attack::Execute()
{
	m_PlayerPtr->Attack();
}
