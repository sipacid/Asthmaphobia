#pragma once
#include "sdk.h"

namespace SDK
{
	// UnityEngine.CoreModule.UnityEngine.Light
	struct Light
	{
	};

	struct LightSettings
	{
		float Intensity;
		float BounceIntensity;
		float Range;
		float SpotAngle;
		float ShadowStrength;
		Quaternion Color;
	};

	DECLARE_FUNCTION_POINTER(Light_Get_SpotAngle, float(*)(Light* light, MethodInfo* methodInfo), 0x4308D40)
	DECLARE_FUNCTION_POINTER(Light_Set_SpotAngle, void(*)(Light* light, float spotAngle, MethodInfo* methodInfo), 0x4309350)

	DECLARE_FUNCTION_POINTER(Light_Get_Color, Quaternion(*)(Light* light, MethodInfo* methodInfo), 0x4308930)
	DECLARE_FUNCTION_POINTER(Light_Set_Color, void(*)(Light* light, Quaternion color, MethodInfo* methodInfo), 0x4308EA0)

	DECLARE_FUNCTION_POINTER(Light_Get_Intensity, float(*)(Light* light, MethodInfo* methodInfo), 0x4308AC0)
	DECLARE_FUNCTION_POINTER(Light_Set_Intensity, void(*)(Light* light, float intensity, MethodInfo* methodInfo), 0x4309070)

	DECLARE_FUNCTION_POINTER(Light_Get_BounceIntensity, float(*)(Light* light, MethodInfo* methodInfo), 0x4308860)
	DECLARE_FUNCTION_POINTER(Light_Set_BounceIntensity, void(*)(Light* light, float bounceIntensity, MethodInfo* methodInfo), 0x4308E00)

	DECLARE_FUNCTION_POINTER(Light_Get_Range, float(*)(Light* light, MethodInfo* methodInfo), 0x4308B00)
	DECLARE_FUNCTION_POINTER(Light_Set_Range, void(*)(Light* light, float range, MethodInfo* methodInfo), 0x43090C0)

	DECLARE_FUNCTION_POINTER(Light_Get_ShadowStrength, float(*)(Light* light, MethodInfo* methodInfo), 0x4308CC0)
	DECLARE_FUNCTION_POINTER(Light_Set_ShadowStrength, void(*)(Light* light, float shadowStrength, MethodInfo* methodInfo), 0x43092C0)
}
