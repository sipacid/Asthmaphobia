#pragma once
#include "sdk.h"

namespace SDK
{
	// UnityEngine.CoreModule.UnityEngine.Transform
	struct Transform
	{
	};

	DECLARE_FUNCTION_POINTER(Transform_Get_Position, Vector3(*)(Transform* transform, MethodInfo* methodInfo), 0x47A0DD0)
	DECLARE_FUNCTION_POINTER(Transform_Set_Position, void(*)(Transform* transform, Vector3 position, MethodInfo* methodInfo), 0x47A1620)

	DECLARE_FUNCTION_POINTER(Transform_Get_Right, Vector3(*)(Transform* transform, MethodInfo* methodInfo), 0x47A0E20)
	DECLARE_FUNCTION_POINTER(Transform_Get_Up, Vector3(*)(Transform* transform, MethodInfo* methodInfo), 0x47A0F90)
	DECLARE_FUNCTION_POINTER(Transform_Get_Forward, Vector3(*)(Transform* transform, MethodInfo* methodInfo), 0x47A0870)

	DECLARE_FUNCTION_POINTER(Transform_Get_Rotation, Quaternion(*)(Transform* transform, MethodInfo* methodInfo), 0x47A0F40)
	DECLARE_FUNCTION_POINTER(Transform_Set_Rotation, void(*)(Transform* transform, Quaternion rotation, MethodInfo* methodInfo), 0x47A16C0)

	DECLARE_FUNCTION_POINTER(Transform_Get_Parent, Transform*(*)(Transform* transform, MethodInfo* methodInfo), 0x479EAC0)
	DECLARE_FUNCTION_POINTER(Transform_Set_Parent, void(*)(Transform* transform, Transform* parent, MethodInfo* methodInfo), 0x47A1510)
}
