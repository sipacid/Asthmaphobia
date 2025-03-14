#pragma once
#include "sdk.h"

namespace SDK
{
	struct LevelValues
	{
	};

	DECLARE_FUNCTION_POINTER(LevelValues_GetInvestigationBonus, int(*)(LevelValues* levelValues, MethodInfo* methodInfo), 0x1C61460);
	DECLARE_FUNCTION_POINTER(LevelValues_IsPerfectGame, bool(*)(LevelValues* levelValues, MethodInfo* methodInfo), 0x1C616C0);
}
