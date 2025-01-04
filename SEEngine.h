//
// Created by Vlad Boroday on 2025-01-04.
//

#ifndef SEENGINE_H
#define SEENGINE_H

#include "Components/GameObject.h"
#include <vector>

namespace SE
{
	class Engine
	{
	private:
		std::vector<std::shared_ptr<SE::GameObject> > _gameObjects;
		std::vector<SE::IRenderable*> _renderables;

	public:
		void Init();

		void Tick(fp32 deltaTime);

		void Render();

		void AddRenderable(SE::IRenderable* renderable);

		void RemoveRenderable(SE::IRenderable* renderable);

		void AddGameObject(std::shared_ptr<SE::GameObject> gameObject);

		void RemoveGameObject(SE::GameObject* gameObject);
	};
}

#endif //SEENGINE_H
