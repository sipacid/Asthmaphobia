#pragma once
#include "sdk.h"

namespace SDK
{
	struct GhostActivity
	{
	};

	DECLARE_METHOD_POINTER(GhostActivity_GhostAbility, void(*)(GhostActivity* ghostActivity, MethodInfo* methodInfo), "Assembly-CSharp", "", "GhostActivity", "GhostAbility", 0);
	DECLARE_METHOD_POINTER(GhostActivity_InteractWithARandomDoor, bool(*)(GhostActivity* ghostActivity, MethodInfo* methodInfo), "Assembly-CSharp", "", "GhostActivity", "InteractWithARandomDoor", 0);
	DECLARE_METHOD_POINTER(GhostActivity_InteractWithARandomProp, void(*)(GhostActivity* ghostActivity, bool a1, MethodInfo* methodInfo), "Assembly-CSharp", "", "GhostActivity", "InteractWithARandomProp", 1);
	DECLARE_METHOD_POINTER(GhostActivity_NormalInteraction, void(*)(GhostActivity* ghostActivity, bool a1, MethodInfo* methodInfo), "Assembly-CSharp", "", "GhostActivity", "NormalInteraction", 1);
	DECLARE_METHOD_POINTER(GhostActivity_TwinInteraction, void(*)(GhostActivity* ghostActivity, bool a1, MethodInfo* methodInfo), "Assembly-CSharp", "", "GhostActivity", "TwinInteraction", 1);
}
