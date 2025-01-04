//
// Created by Vlad Boroday on 2025-01-03.
//

#include "GameObject.h"

std::shared_ptr<SE::GameObject> SE::GameObject::Create()
{
	return Create("new GameObject");
}

std::shared_ptr<SE::GameObject> SE::GameObject::Create(pcstr name)
{
	std::shared_ptr<SE::GameObject> result = std::make_shared<SE::GameObject>();

	result->_name.Format(name);
	result->AddComponent<Transform>();

	return result;
}
