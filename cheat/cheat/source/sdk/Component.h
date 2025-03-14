#pragma once
#include "sdk.h"

namespace SDK
{
	// UnityEngine.CoreModule.UnityEngine.Component
	struct Component
	{
	};

	DECLARE_FUNCTION_POINTER(Component_Get_Transform, Transform* (*)(Component* component, MethodInfo* methodInfo), 0x46E58F0);
	DECLARE_FUNCTION_POINTER(Component_Get_GameObject, GameObject * (*)(Component* component, MethodInfo* methodInfo), 0x46E5840);
}
