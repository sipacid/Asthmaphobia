#pragma once
#include "sdk.h"

namespace SDK
{
	enum class LightType : int32_t
	{
		Spot = 0,
		Directional = 1,
		Point = 2,
		Area = 3,
		Rectangle = 3,
		Disc = 4
	};

	enum class LightShadows : int32_t
	{
		None,
		Hard,
		Soft
	};

	struct Light;

	DECLARE_METHOD_POINTER(Light_Set_Type, void(*)(SDK::Light* light, LightType lightType, SDK::MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Light",
		"set_type", 1)

	DECLARE_METHOD_POINTER(Light_Set_Intensity, void(*)(SDK::Light* light, float intensity, SDK::MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Light",
	                       "set_intensity", 1)

	DECLARE_METHOD_POINTER(Light_Set_Shadows, void(*)(SDK::Light* light, LightShadows lightShadows, SDK::MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Light",
		"set_shadows", 1)
}
