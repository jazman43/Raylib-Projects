#include "raylib.h"



//veraibles
//window Size
Vector2 windowSize = {1920, 1080};


//anim
struct AnimStruct
{
	Rectangle rec;
	Vector2 pos;
	int frame;
	float updateTime;
	float runningTime;
};

//player
Texture2D scarfy;
float velocity = 0;
const float gravity = 1'000;
const float jumpForce = -600;
bool isInAir{};


//enemys
Texture2D nebula;
Rectangle nebulaRec;
Vector2 nebulaPos;
float nebVel = -300;
const int sizeOfEnemy = 5;


//backgrond
Texture2D farBackGround;
Texture2D midGround;
Texture2D forGround;

//game logic
bool collision{};


//functions
void WindowSetUp();
void MovePlayer();
void GroundCheck(AnimStruct, Vector2, float);
AnimStruct UpdateAnim(AnimStruct, int, float);



int main() {

	WindowSetUp();
	//load texture
	nebula = LoadTexture("resources/12_nebula_spritesheet.png");
	scarfy = LoadTexture("resources/scarfy.png");
	farBackGround = LoadTexture("resources/far-buildings.png");
	float backScroll{};
	midGround = LoadTexture("resources/back-buildings.png");
	float midScroll{};
	forGround = LoadTexture("resources/foreground.png");
	float forScroll{};
	
	

	AnimStruct nebulaData[sizeOfEnemy]{};
	for (int i = 0; i < sizeOfEnemy; i++)
	{
		nebulaData[i].rec.x = 0;
		nebulaData[i].rec.y = 0;
		nebulaData[i].rec.width = nebula.width / 8;
		nebulaData[i].rec.height = nebula.height / 8;
		nebulaData[i].pos.x = 
		nebulaData[i].pos.y = windowSize.y - nebulaData[i].rec.height;
		nebulaData[i].frame = 0;
		nebulaData[i].updateTime = 0.05f;
		nebulaData[i].runningTime = 0;
	}

	for (int x = 0; x < sizeOfEnemy; x++)
	{
		nebulaData[x].pos.x = windowSize.x + x * 650;
	}
	
	float finishLine{ nebulaData[sizeOfEnemy - 1].pos.x };

	
	AnimStruct scarfyData{};	
	scarfyData.rec.x = 0;
	scarfyData.rec.y = 0;
	scarfyData.rec.width = scarfy.width / 6;
	scarfyData.rec.height = scarfy.height;
	scarfyData.pos.x = windowSize.x / 2 - scarfyData.rec.width / 2;
	scarfyData.pos.y = windowSize.y - scarfyData.rec.height;	
	scarfyData.updateTime = 0.08f;


	while (!WindowShouldClose())
	{  
		//delta time
		float dTime = GetFrameTime();
		BeginDrawing();
		ClearBackground(RAYWHITE);

		backScroll -= 20 * dTime;
		if (backScroll <= -farBackGround.width * 6)
		{
			backScroll = 0.0f;
		}
		midScroll -= 40 * dTime;
		if (midScroll <= -midGround.width * 6)
		{
			midScroll = 0.0f;
		}
		forScroll -= 80 * dTime;
		if (forScroll <= -forGround.width *6)
		{
			forScroll = 0.0f;
		} 

		Vector2 farBackPos{backScroll, 0.0f };
		DrawTextureEx(farBackGround, farBackPos, 0, 6, WHITE);
		Vector2 farBack2Pos{ backScroll + farBackGround.width * 6, 0.0f };
		DrawTextureEx(farBackGround, farBack2Pos, 0, 6, WHITE);

		Vector2 midBack1Pos{ midScroll, 0.0f };
		DrawTextureEx(midGround, midBack1Pos, 0, 6, WHITE);
		Vector2 midBack2Pos{ midScroll + midGround.width * 6, 0.0f };
		DrawTextureEx(midGround, midBack2Pos, 0, 6, WHITE);

		Vector2 forBack1Pos{ forScroll, 0.0f };
		DrawTextureEx(forGround, forBack1Pos, 0, 6, WHITE);
		Vector2 forBack2Pos{ forScroll + forGround.width * 6, 0.0f };
		DrawTextureEx(forGround, forBack2Pos, 0, 6, WHITE);
				
		//anim
		for (int i = 0; i < sizeOfEnemy; i++)
		{
			int maxFrame = 7;
			
			nebulaData[i] = UpdateAnim(nebulaData[i],maxFrame,dTime);
				
		}
		int playerMaxFrame = 5;

		if (!isInAir)
		{
			scarfyData = UpdateAnim(scarfyData, playerMaxFrame, dTime);
		}	
		

		GroundCheck(scarfyData, windowSize, dTime);
		MovePlayer();		

		scarfyData.pos.y += velocity * dTime;
		
		//Draw Rectanges
		for (int n = 0; n < sizeOfEnemy; n++)
		{
			nebulaData[n].pos.x += nebVel * dTime;
			
		}
		finishLine += nebVel * dTime;

		
		for (AnimStruct nebula : nebulaData)
		{
			float pad{ 50 };
			Rectangle nebRec{
				nebula.pos.x + pad,
				nebula.pos.y + pad,
				nebula.rec.width - 2*pad,
				nebula.rec.height - 2*pad
			};

			Rectangle scarfyRec{
				scarfyData.pos.x,
				scarfyData.pos.y,
				scarfyData.rec.width,
				scarfyData.rec.height
			};

			if (CheckCollisionRecs(nebRec,scarfyRec))
			{
				collision = true;
			}
			

		}

		if (collision)
		{
			DrawText("GAME OVER!!!", windowSize.x / 3, windowSize.y / 3, 100, PINK);
		}
		else if(scarfyData.pos.x >= finishLine)
		{
			DrawText("You Win!!!", windowSize.x / 3, windowSize.y / 3, 100, GREEN);
		}
		else
		{
			for (int i = 0; i < sizeOfEnemy; i++)
			{
				DrawTextureRec(nebula, nebulaData[i].rec, nebulaData[i].pos, VIOLET);
			}
			DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
		}

		
		

		EndDrawing();
	}
	UnloadTexture(farBackGround);
	UnloadTexture(nebula);
	UnloadTexture(scarfy);
	UnloadTexture(midGround);
	UnloadTexture(forGround);
	CloseWindow();
}



void WindowSetUp() {
	InitWindow(windowSize.x, windowSize.y,"My Game");
	//SetWindowMonitor(0); set to full screen
	if (IsKeyDown(KEY_C)) { ToggleFullscreen(); }
	SetTargetFPS(60);
}

void MovePlayer() {	
	

	if (IsKeyPressed(KEY_SPACE)&&!isInAir)
	{
		velocity += jumpForce;
		
	}

}

void GroundCheck(AnimStruct scarfyD, Vector2 windowS, float dT) {
	//ground check
	if (scarfyD.pos.y >= windowSize.y - scarfyD.rec.height)
	{
		velocity = 0;
		isInAir = false;
	}
	else
	{
		velocity += gravity * dT;
		isInAir = true;
	}
}

AnimStruct UpdateAnim(AnimStruct animData,int maxFrame,float deltaTime) {

	animData.runningTime += deltaTime;

	if (animData.runningTime >= animData.updateTime)
	{
		animData.runningTime = 0;
		animData.rec.x = animData.frame * animData.rec.width;

		animData.frame++;

		if (animData.frame > maxFrame)
		{
			animData.frame = 0;
		}
	}	
	return animData;
}