#pragma once
#include "sdk.h"

namespace SDK
{
	struct LevelValues
	{
	};

	DECLARE_FUNCTION_POINTER(LevelValues_GetInestigationBonus, int(*)(LevelValues* levelValues, MethodInfo* methodInfo), 0x195D240);
}
