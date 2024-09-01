#pragma once
#include "sdk.h"

namespace SDK
{
	struct ServerManager
	{
	};

	DECLARE_FUNCTION_POINTER(ServerManager_KickPlayerNetworked, void(*)(ServerManager* serverManager, bool a1, void* photonMessageInfo, MethodInfo* methodInfo), 0x7765E0);
}
