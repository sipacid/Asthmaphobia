#pragma once
#include "sdk.h"

namespace SDK
{
	struct GhostActivity
	{
	};

	DECLARE_FUNCTION_POINTER(GhostActivity_ForceInteractWithProp, void(*)(GhostActivity* ghostActivity, bool a1, MethodInfo* methodInfo), 0x1962B00);
	DECLARE_FUNCTION_POINTER(GhostActivity_GhostAbility, void(*)(GhostActivity* ghostActivity, MethodInfo* methodInfo), 0x1963440);
	DECLARE_FUNCTION_POINTER(GhostActivity_Interact, void(*)(GhostActivity* ghostActivity, MethodInfo* methodInfo), 0x1963EA0);
	DECLARE_FUNCTION_POINTER(GhostActivity_InteractWithARandomDoor, bool(*)(GhostActivity* ghostActivity, MethodInfo* methodInfo), 0x19636A0);
	DECLARE_FUNCTION_POINTER(GhostActivity_InteractWithARandomProp, void(*)(GhostActivity* ghostActivity, bool a1, bool a2, MethodInfo* methodInfo), 0x1963870);
	DECLARE_FUNCTION_POINTER(GhostActivity_NormalInteraction, void(*)(GhostActivity* ghostActivity, bool a1, MethodInfo* methodInfo), 0x1964000);
	DECLARE_FUNCTION_POINTER(GhostActivity_TwinInteraction, void(*)(GhostActivity* ghostActivity, bool a1, MethodInfo* methodInfo), 0x1964570);
}
