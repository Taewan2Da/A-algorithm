#include "Player.h"
#include "Engine/Engine.h"

Player::Player()
	: DrawableActor("e")
{
	color = Color::Yellow;
	position = Vector2(0,0);
}

void Player::Update(float deltaTime)
{
	DrawableActor::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}

	if (Engine::Get().GetKeyDown(VK_RBUTTON))
	{
		position = Engine::Get().MousePosition();
	}
	
}