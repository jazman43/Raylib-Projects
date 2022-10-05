#include "Character.h"







void Character::tick(float deltaTime) {

	worldPosLastFrame = worldPos;

	Vector2 direction{};

	if (IsKeyDown(KEY_A)) direction.x -= 1;

	if (IsKeyDown(KEY_D)) direction.x += 1;

	if (IsKeyDown(KEY_W)) direction.y -= 1;

	if (IsKeyDown(KEY_S)) direction.y += 1;

	if (Vector2Length(direction) != 0.0f)
	{
		worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), moveSpeed));
		direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
		texture = run;
	}
	else
	{
		texture = idle;
	}

	//update animation frame
	runningTime += deltaTime;
	if (runningTime >= updateTime)
	{
		frame++;
		runningTime = 0.f;
		if (frame > maxFrames)
		{
			frame = 0;
		}
	}

	//DrawCharacter
	Rectangle scurce{
		frame * width
		,0.f
		,rightLeft * width
		,height
	};
	Rectangle dest{
		screenPos.x
		,screenPos.y
		,scale * width
		,scale * width
	};

	DrawTexturePro(texture, scurce, dest, Vector2{}, 0.f, WHITE);
}


Character::Character(float winWidth, float winHeight) {
	width = texture.width / maxFrames;

	height = texture.height;

	screenPos = {
		static_cast<float>(winWidth) / 2.0f - scale * (0.5f * width),
		static_cast<float>(winHeight) / 2.0f - scale * (0.5f * height)
	};
}


void Character::UndoMovment() {

	worldPos = worldPosLastFrame;
}