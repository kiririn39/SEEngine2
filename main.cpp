#include "includes.h"
#include "string.h"

void RenderUI(){
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

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	Camera camera = {0};
	camera.position = (Vector3) {50.0f, 50.0f, 50.0f}; // Camera position
	camera.target = (Vector3) {0.0f, 10.0f, 0.0f};     // Camera looking at point
	camera.up = (Vector3) {0.0f, 1.0f, 0.0f};          // Camera up vector (rotation towards target)
	camera.fovy = 45.0f;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type

	Model model = LoadModel("Resources/kenney_toy-car-kit/Models/OBJ format/vehicle-racer.obj");                 // Load model
			
	//Texture2D texture = LoadTexture("Resources/Models/yellowcar/car-tex.png");
	//model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
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

		BeginMode3D(camera);

		DrawModel(model, {0, 0, 0}, 10.0f, WHITE);

		EndMode3D();
		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}