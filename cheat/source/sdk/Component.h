#pragma once
#include "sdk.h"

namespace SDK
{
	// UnityEngine.CoreModule.UnityEngine.Component
	struct Component
	{
	};

	DECLARE_FUNCTION_POINTER(Component_Get_Transform, Transform * (*)(Component* component, MethodInfo* methodInfo), 0x47A6CC0);
}
