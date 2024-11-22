#pragma once
#include "sdk.h"

namespace SDK
{
	// UnityEngine.CoreModule.UnityEngine.Camera
	struct Camera
	{
	};

	DECLARE_FUNCTION_POINTER(Camera_WorldToScreenPoint, Vector3(*)(Camera* camera, Vector3 worldPoint, MethodInfo* methodInfo), 0x46BE4D0);
}
