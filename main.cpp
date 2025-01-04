#include "includes.h"
#include "SEEngine.h"
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

	SE::Engine engine;
	engine.Init();

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

		engine.Tick(GetFrameTime());
		engine.Render();

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow(); // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}
