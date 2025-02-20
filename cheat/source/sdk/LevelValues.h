#pragma once
#include "sdk.h"

namespace SDK
{
	struct LevelValues
	{
	};

	DECLARE_FUNCTION_POINTER(LevelValues_GetInvestigationBonus, int(*)(LevelValues* levelValues, MethodInfo* methodInfo), 0x1CC1010);
	DECLARE_FUNCTION_POINTER(LevelValues_IsPerfectGame, bool(*)(LevelValues* levelValues, MethodInfo* methodInfo), 0x1CC1270);
}
