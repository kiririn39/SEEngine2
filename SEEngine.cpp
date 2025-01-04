//
// Created by Vlad Boroday on 2025-01-04.
//

#include "SEEngine.h"

SE::Engine* gEngine = nullptr;

void SE::Engine::Init()
{
	if (gEngine != nullptr)
		ASSERT(false); // one instance allowed

	gEngine = this;

	std::shared_ptr<SE::GameObject> cameraObject = SE::GameObject::Create("camera object");
	cameraObject->AddComponent<SE::CameraComponent>();

	cameraObject->GetTransform()->SetPosition({ 50.0f, 50.0f, 50.0f });
	cameraObject->GetTransform()->LookAt({ 0.0f, 10.0f, 0.0f }, SE::UP);

	std::shared_ptr<SE::GameObject> carObject = SE::GameObject::Create("car");
	SE::MeshRendererComponent* mesh = carObject->AddComponent<SE::MeshRendererComponent>();
	carObject->GetTransform()->SetScale(10.0f);
	mesh->Load(RESOURCES_PATH "kenney_toy-car-kit/Models/OBJ format/vehicle-racer.obj");

	_gameObjects.emplace_back(std::move(cameraObject));
	_gameObjects.emplace_back(std::move(carObject));
}

void SE::Engine::Tick(fp32 deltaTime)
{
	for (auto game_object: _gameObjects)
	{
		if (!game_object->IsEnabled())
			continue;

		game_object->Update(deltaTime);
	}

	for (auto game_object: _gameObjects)
	{
		if (game_object->IsScheduledForDestroy())
			game_object->DoDestroy();
		else
			game_object->DoDestroyScheduledComponents();
	}
}

void SE::Engine::Render()
{
	ASSERT(_gameObjects.size() > 0); // not initialized
	SE::CameraComponent* camera = _gameObjects[0]->GetComponent<SE::CameraComponent>();
	ASSERT(camera != nullptr); // camera not present

	camera->BeginRender3D();

	for (auto* renderable: _renderables)
	{
		renderable->Render();
	}

	camera->EndRender3D();
}

void SE::Engine::AddRenderable(SE::IRenderable* renderable)
{
	_renderables.push_back(renderable);
}

void SE::Engine::RemoveRenderable(SE::IRenderable* renderable)
{
	_renderables.erase(std::remove(_renderables.begin(), _renderables.end(), renderable));
}

void SE::Engine::AddGameObject(std::shared_ptr<SE::GameObject> gameObject)
{
	_gameObjects.emplace_back(std::move(gameObject));
}

void SE::Engine::RemoveGameObject(SE::GameObject* gameObject)
{
	std::erase_if(_gameObjects,
		[gameObject](std::shared_ptr<GameObject> item)
		{
			return item.get() == gameObject;
		});
}
