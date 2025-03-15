#pragma once
#include "sdk.h"

namespace SDK
{
	struct ExitLevel
	{
	};

	DECLARE_METHOD_POINTER(ExitLevel_Exit, void(*)(ExitLevel* exitLevel, void* photonMessageInfo, MethodInfo* methodInfo), "Assembly-CSharp", "", "ExitLevel", "Exit", 1);
	DECLARE_METHOD_POINTER(ExitLevel_ThereAreAlivePlayersOutsideTheTruck, bool(*)(ExitLevel* exitLevel, MethodInfo* methodInfo), "Assembly-CSharp", "", "ExitLevel", "ThereAreAlivePlayersOutsideTheTruck", 0);
}
