#pragma once
#include "sdk.h"

namespace SDK
{
	struct LevelValues
	{
	};

	DECLARE_METHOD_POINTER(LevelValues_GetInvestigationBonusReward, int(*)(LevelValues* levelValues, MethodInfo* methodInfo), "Assembly-CSharp", "", "LevelValues",
	                       "GetInvestigationBonusReward", 0);

	DECLARE_METHOD_POINTER(LevelValues_IsPerfectGame, bool(*)(LevelValues* levelValues, MethodInfo* methodInfo), "Assembly-CSharp", "", "LevelValues", "IsPerfectGame", 0);
}
