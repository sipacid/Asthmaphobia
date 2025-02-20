#include "source/common.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkGhostAI_Hunting(SDK::GhostAI* ghostAI, bool isHunting, int a1, void* photonMessageInfo, SDK::MethodInfo* methodInfo)
{
	LOG_DEBUG("Called GhostAI_Hunting");
	if (globalRunning)
	{
		std::string text;
		if (GameState::isHunting == false && isHunting == false)
			text = "Ghost tried to hunt";
		else
			text = isHunting ? "Ghost started hunting" : "Ghost stopped hunting";

		AddNotification(text, Notifications::NotificationType::Info, 5.0f);
		GameState::isHunting = isHunting;
	}

	SDK::GhostAI_Hunting_ptr(ghostAI, isHunting, a1, photonMessageInfo, methodInfo);
}
