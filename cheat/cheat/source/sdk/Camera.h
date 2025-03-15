#pragma once
#include "sdk.h"

namespace SDK
{
	// UnityEngine.CoreModule.UnityEngine.Camera
	struct Camera
	{
	};

	DECLARE_METHOD_POINTER(Camera_WorldToScreenPoint, Vector3(*)(Camera* camera, Vector3 worldPoint, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Camera", "WorldToScreenPoint", 1);
}
