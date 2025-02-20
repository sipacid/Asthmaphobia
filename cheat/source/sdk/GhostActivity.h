#pragma once
#include "sdk.h"

namespace SDK
{
	struct GhostActivity
	{
	};

	DECLARE_FUNCTION_POINTER(GhostActivity_ForceInteractWithProp, void(*)(GhostActivity* ghostActivity, bool a1, MethodInfo* methodInfo), 0x19BC6A0);
	DECLARE_FUNCTION_POINTER(GhostActivity_GhostAbility, void(*)(GhostActivity* ghostActivity, MethodInfo* methodInfo), 0x19BCFE0);
	DECLARE_FUNCTION_POINTER(GhostActivity_Interact, void(*)(GhostActivity* ghostActivity, MethodInfo* methodInfo), 0x19BDA20);
	DECLARE_FUNCTION_POINTER(GhostActivity_InteractWithARandomDoor, bool(*)(GhostActivity* ghostActivity, MethodInfo* methodInfo), 0x19BD240);
	DECLARE_FUNCTION_POINTER(GhostActivity_InteractWithARandomProp, void(*)(GhostActivity* ghostActivity, bool a1, bool a2, MethodInfo* methodInfo), 0x19BD400);
	DECLARE_FUNCTION_POINTER(GhostActivity_NormalInteraction, void(*)(GhostActivity* ghostActivity, bool a1, MethodInfo* methodInfo), 0x19BDB80);
	DECLARE_FUNCTION_POINTER(GhostActivity_TwinInteraction, void(*)(GhostActivity* ghostActivity, bool a1, MethodInfo* methodInfo), 0x19BE100);
}
