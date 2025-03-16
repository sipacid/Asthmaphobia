#pragma once
#include "sdk.h"

namespace SDK
{
	struct Component
	{
	};

	DECLARE_METHOD_POINTER(Component_Get_Transform, Transform* (*)(Component* component, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Component",
	                       "get_transform", 0);

	DECLARE_METHOD_POINTER(Component_Get_GameObject, GameObject * (*)(Component* component, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Component",
	                       "set_transform", 1);
}
