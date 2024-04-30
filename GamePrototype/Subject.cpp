#include "pch.h"
#include "Subject.h"

void Subject::AddObserver(MessageTypes message, IObserver* observer)
{
	//assert(observer && "GameObject must have observer Component");
	auto it = m_ObserversMap.find(message);
	if (it == m_ObserversMap.end())
		m_ObserversMap[message] = ObserverPtrList();
	
	m_ObserversMap[message].push_front(observer);
}

void Subject::RemoveObserver(MessageTypes message, IObserver* observer)
{
	auto it = m_ObserversMap.find(message);

	if (it != m_ObserversMap.end())
	{
		auto& list = it->second;
		list.remove_if([&observer](IObserver* ptr)
		{
			return ptr == observer;
		});
	}
}

void Subject::Notify(MessageTypes message)
{
	for (auto& observer : m_ObserversMap[message])
		observer->OnNotify(message, this);
}