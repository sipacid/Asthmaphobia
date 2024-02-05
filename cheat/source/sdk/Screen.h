#pragma once
#include "sdk.h"

namespace SDK
{
	// UnityEngine.CoreModule.UnityEngine.Screen
	struct Screen
	{
	};

	DECLARE_FUNCTION_POINTER(Screen_Get_CurrentResolution, Resolution(*)(void* methodInfo), 0x4319330);
}
