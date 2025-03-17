#pragma once
#include "sdk.h"

namespace SDK
{
	struct LineRenderer;

	DECLARE_METHOD_POINTER(LineRenderer_GetPosition, Vector3(*)(LineRenderer* lineRenderer, int32_t index, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine",
	                       "LineRenderer", "GetPosition", 1);
}
