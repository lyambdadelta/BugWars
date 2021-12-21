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

Game::~Game() {
	for (int i = 0; i < this->objects.size(); i++) {
		delete objects[i];
	}
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
	//if (object->GetRTTI() == Bug::s_RTTI)
	//	Log("I'm NOT a bug");
}

void Game::OnBugsSpawned()
{
	for (int i = 1; i < objects.size(); i++) {
		if (objects[i]->GetRTTI() == Bug::s_RTTI) {
			auto bug = static_cast<Bug*>(objects[i]);
			if (!bug->visible || bug->position.Distance(tank->position) > 1300) {
				delete objects[i];
				objects[i] = nullptr;
			}
		}
	}
	this->objects.erase(std::remove(begin(this->objects), end(this->objects), nullptr), end(this->objects));
}
