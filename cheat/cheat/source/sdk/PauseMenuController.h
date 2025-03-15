#pragma once
#include "sdk.h"

namespace SDK
{
	struct PauseMenuController
	{
	};

	DECLARE_METHOD_POINTER(PauseMenuController_Leave, void(*)(PauseMenuController* pauseMenuController, MethodInfo* methodInfo), "Assembly-CSharp", "", "PauseMenuController", "Leave", 0);
}
