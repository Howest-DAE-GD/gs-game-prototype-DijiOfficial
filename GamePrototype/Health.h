#pragma once
#include "Subject.h"

class Health final : public Subject
{
public:
	Health(int health);

	void DealDamage(int damage);
	int GetHealth() const { return m_Health; }

private:
	int m_Health;
};


