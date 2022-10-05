#include "raylib.h"
#include "raymath.h"

class Character
{
public:
	Vector2 GetWorldPos() { return worldPos; }
	
	void tick(float deltaTime);
	Character(float winWidth, float winHeight);
	void UndoMovment();

private:
	Texture2D texture{ LoadTexture("resources/characters/knight_idle_spritesheet.png") };
	Texture2D idle{ LoadTexture("resources/characters/knight_idle_spritesheet.png") };
	Texture2D run{ LoadTexture("resources/characters/knight_run_spritesheet.png") };
	Vector2 screenPos{};
	Vector2 worldPos{};

	Vector2 worldPosLastFrame{};

	//1 : facing right -1 : facing left
	float rightLeft{ 1.f };
	//animation running time
	float runningTime{};
	int frame{};
	int maxFrames{ 6 };
	float updateTime{ 1.f / 12.f };
	float moveSpeed{ 4.0f };

	float width{};
	float height{};

	float scale{ 4.f };
};
