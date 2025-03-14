#pragma once
#include "sdk.h"

namespace SDK
{
	// UnityEngine.PhysicsModule.UnityEngine.Collider
	struct Collider
	{
	};

	DECLARE_FUNCTION_POINTER(Collider_Get_Enabled, bool(*)(Collider* collider, MethodInfo* methodInfo), 0x476FBA0);
	DECLARE_FUNCTION_POINTER(Collider_Set_Enabled, void(*)(Collider* collider, bool enabled, MethodInfo* methodInfo), 0x476FE30);
}
