#include "includes.h"
#include "Components/GameObject.h"

void RenderUI()
{
	static u64 counter = 0;

	counter++;

	String text;
	pcstr pcstr1 = "Frame counter {}\nCongrats! You created your first window!\n";
	text.Format(pcstr1, counter);

	DrawText(text.Begin(), 190, 200, 20, LIGHTGRAY);
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	std::shared_ptr<SE::GameObject> cameraObject = SE::GameObject::Create("camera object");
	SE::CameraComponent* camera = cameraObject->AddComponent<SE::CameraComponent>();

	std::shared_ptr<SE::GameObject> carObject = SE::GameObject::Create("car");
	SE::MeshRendererComponent* mesh = carObject->AddComponent<SE::MeshRendererComponent>();
	carObject->GetTransform()->SetScale(10.0f);
	mesh->Load(RESOURCES_PATH "kenney_toy-car-kit/Models/OBJ format/vehicle-racer.obj");

	cameraObject->GetTransform()->SetPosition({ 50.0f, 50.0f, 50.0f });
	cameraObject->GetTransform()->LookAt({ 0.0f, 10.0f, 0.0f }, SE::UP);

	// Main game loop
	while (!WindowShouldClose()) // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();
		ClearBackground(RAYWHITE);

		RenderUI();

		camera->BeginRender3D();

		mesh->Render();

		camera->EndRender3D();
		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow(); // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}
