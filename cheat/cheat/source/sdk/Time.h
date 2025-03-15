#pragma once
#include "sdk.h"

namespace SDK
{
	// UnityEngine.CoreModule.UnityEngine.Time
	DECLARE_METHOD_POINTER(Time_Get_DeltaTime, float(*)(MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Time", "get_deltaTime", 0);
}
