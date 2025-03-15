#pragma once
#include "sdk.h"

namespace SDK
{
	struct ServerManager
	{
	};

	DECLARE_METHOD_POINTER(ServerManager_KickPlayerNetworked, void(*)(ServerManager* serverManager, bool a1, void* photonMessageInfo, MethodInfo* methodInfo), "Assembly-CSharp", "", "ServerManager", "KickPlayerNetworked", 2);
}
