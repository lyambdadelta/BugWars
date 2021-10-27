#include "pch.h"
#include "Game.h"
#include "GameBase/Log.h"
#include "Tank.h"
#include "Bug.h"
#include "Bullet.h"

Game* g_Game;

Game::Game()
	: GameBase({ [] {return new Tank; },
				 [] {return new Bug; },
				 [] {return new Bullet; } })
{
	g_Game = this;
}

void Game::OnUpdate(float dt)
{
	PIXScopedEvent(PIX_COLOR_INDEX(5), __FUNCTION__);
	for (int i = 0; i < objects.size(); i++) {
		if (!objects[i]->disabled)
			objects[i]->Update(dt);
	}
}

void Game::OnRender() const
{
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->visible)
			DoRender(objects[i]);
	}
}

void Game::AddObject(GameObject* object)
{
	objects.push_back(object);
	if (object->GetRTTI() == Bug::s_RTTI)
		Log("I'm a bug");
}

void Game::OnBugsSpawned()
{
	for (auto obj : this->objects) {
		obj->disabled = false;
	}
}
