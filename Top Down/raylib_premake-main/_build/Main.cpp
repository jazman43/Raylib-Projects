#include "raylib.h"
#include "raymath.h"

#include "Character.h"


//functions
float WindowSetUp(Vector2);


int main() {


	//veraibles
	//Window set up
	Vector2 windowSize{ 1920,1080 };
	//Map

	Vector2 rpgMapPos{};

	//player
	float movePosDir{ 1 };


	float deltaTime = WindowSetUp(windowSize);
	Texture2D rpgMap = LoadTexture("resources/nature_tileset/OpenWorldMap24x24.png");
	const float mapScale{ 4.f };

	Character knight{windowSize.x, windowSize.y};

	

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);		

		rpgMapPos = Vector2Scale(knight.GetWorldPos(), -1.f);

		DrawTextureEx(rpgMap, rpgMapPos, 0,mapScale, WHITE);

		knight.tick(GetFrameTime());


		//Check map bounds
		if (knight.GetWorldPos().x < 0.f || 
			knight.GetWorldPos().y < 0.f ||
			knight.GetWorldPos().x + windowSize.x > rpgMap.width * mapScale ||
			knight.GetWorldPos().y + windowSize.y > rpgMap.height * mapScale)
		{
			knight.UndoMovment();
		}

		EndDrawing();
	}
	UnloadTexture(rpgMap);
		
	CloseWindow();
}

float WindowSetUp(Vector2 windowSize) {

	InitWindow(windowSize.x, windowSize.y, "Top Dawn");
	SetTargetFPS(60);
	return GetFrameTime();
}

