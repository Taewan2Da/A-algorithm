#include "DemoLevel.h"
#include "Actor/Player.h"
#include "Actor/Start.h"

//#include "Engine/Engine.h"

DemoLevel::DemoLevel()
{
	AddActor(new Start());
	AddActor(new Player());


}

void DemoLevel::Update(float deltaTime)
{
	
}
