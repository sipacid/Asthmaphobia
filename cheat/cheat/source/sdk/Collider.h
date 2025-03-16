#pragma once
#include "sdk.h"

namespace SDK
{
	struct Collider
	{
	};

	DECLARE_METHOD_POINTER(Collider_Get_Enabled, bool(*)(Collider* collider, MethodInfo* methodInfo), "UnityEngine.PhysicsModule", "UnityEngine", "Collider", "get_enabled", 0);

	DECLARE_METHOD_POINTER(Collider_Set_Enabled, void(*)(Collider* collider, bool enabled, MethodInfo* methodInfo), "UnityEngine.PhysicsModule", "UnityEngine", "Collider",
	                       "set_enabled", 1);
}
