#include "GameObject.hpp"

void GameObject::Start()
{
	for (auto& e : this->components)
	{
		if (!e->isStarted)
		{
			e->Start();

			e->isStarted = true;
		}
	}
}

void GameObject::Update()
{
	for (auto& e : this->components)
	{
		e->Update();
	}

}
