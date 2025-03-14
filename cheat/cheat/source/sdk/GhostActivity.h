#pragma once
#include "sdk.h"

namespace SDK
{
	struct GhostActivity
	{
	};

	DECLARE_FUNCTION_POINTER(GhostActivity_GhostAbility, void(*)(GhostActivity* ghostActivity, MethodInfo* methodInfo), 0x199A2B0);
	DECLARE_FUNCTION_POINTER(GhostActivity_InteractWithARandomDoor, bool(*)(GhostActivity* ghostActivity, MethodInfo* methodInfo), 0x199A4B0);
	DECLARE_FUNCTION_POINTER(GhostActivity_InteractWithARandomProp, void(*)(GhostActivity* ghostActivity, bool a1, MethodInfo* methodInfo), 0x199A610);
	DECLARE_FUNCTION_POINTER(GhostActivity_NormalInteraction, void(*)(GhostActivity* ghostActivity, bool a1, MethodInfo* methodInfo), 0x199AE60);
	DECLARE_FUNCTION_POINTER(GhostActivity_TwinInteraction, void(*)(GhostActivity* ghostActivity, bool a1, MethodInfo* methodInfo), 0x199B310);
}
