#pragma once
#include "Subject.h"

class Health final : public Subject
{
public:
	Health(int health);

	void DealDamage(int damage);
	int GetHealth() const { return m_Health; }
	void ResetHealth(int health);

private:
	int m_Health;
};


