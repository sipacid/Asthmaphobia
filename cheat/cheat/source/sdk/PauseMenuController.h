#pragma once
#include "sdk.h"

namespace SDK
{
	struct PauseMenuController
	{
	};

	DECLARE_FUNCTION_POINTER(PauseMenuController_Leave, void(*)(PauseMenuController* pauseMenuController, MethodInfo* methodInfo), 0x1D1D2B0);
}
