#pragma once
#include "sdk.h"

namespace SDK
{
	struct ExitLevel
	{
	};

	DECLARE_FUNCTION_POINTER(ExitLevel_Exit, void(*)(ExitLevel* exitLevel, void* photonMessageInfo, MethodInfo* methodInfo), 0xD6DF90);
	DECLARE_FUNCTION_POINTER(ExitLevel_ThereAreAlivePlayersOutsideTheTruck, bool(*)(ExitLevel* exitLevel, MethodInfo* methodInfo), 0xD6E680);
}
