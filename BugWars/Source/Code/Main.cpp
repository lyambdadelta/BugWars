#include "pch.h"
#include "GameBase/Framework.h"
#include "Game.h"
#include "GameBase/Log.h"
#include "GameBase/Memory.h"

int main(int argc, const char* argv[])
{
	LogZA("Allocated memory: %zu", g_AllocatedMemory);
	{
		Game game;
		Framework framework;

		if (argc > 1)
			if (!strcmp(argv[1], "-lock60fps"))
				framework.lock60fps = false;

		framework.Run(game);
	}
	LogZA("Allocated memory: %zu", g_AllocatedMemory);
	return 0;
}