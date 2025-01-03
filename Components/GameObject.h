//
// Created by Vlad Boroday on 2025-01-03.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "includes.h"

namespace SE
{
	class GameObject;

	class Component
	{
	private:
		GameObject* _owner = nullptr;

	public:
		virtual void Start()
		{
		}

		virtual void Update()
		{
		}

		void SetGameObject(GameObject* owner)
		{
			_owner = owner;
		}

		GameObject* GetGameObject() const
		{
			ASSERT(_owner != nullptr);
			return _owner;
		}
	};

	class GameObject
	{
	};
}


#endif //GAMEOBJECT_H
