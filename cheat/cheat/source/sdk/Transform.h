#pragma once
#include "sdk.h"

namespace SDK
{
	// UnityEngine.CoreModule.UnityEngine.Transform
	struct Transform
	{
	};

	DECLARE_FUNCTION_POINTER(Transform_Get_Position, Vector3(*)(Transform* transform, MethodInfo* methodInfo), 0x46FA6B0)
	DECLARE_FUNCTION_POINTER(Transform_Set_Position, void(*)(Transform* transform, Vector3 position, MethodInfo* methodInfo), 0x46FAF00)

	DECLARE_FUNCTION_POINTER(Transform_Get_Right, Vector3(*)(Transform* transform, MethodInfo* methodInfo), 0x46FA700)
	DECLARE_FUNCTION_POINTER(Transform_Get_Up, Vector3(*)(Transform* transform, MethodInfo* methodInfo), 0x46FA870)
	DECLARE_FUNCTION_POINTER(Transform_Get_Forward, Vector3(*)(Transform* transform, MethodInfo* methodInfo), 0x46FA150)

	DECLARE_FUNCTION_POINTER(Transform_Get_Rotation, Quaternion(*)(Transform* transform, MethodInfo* methodInfo), 0x46FA820)
	DECLARE_FUNCTION_POINTER(Transform_Set_Rotation, void(*)(Transform* transform, Quaternion rotation, MethodInfo* methodInfo), 0x46FAFA0)

	DECLARE_FUNCTION_POINTER(Transform_Get_Parent, Transform*(*)(Transform* transform, MethodInfo* methodInfo), 0x46F83A0)
	DECLARE_FUNCTION_POINTER(Transform_Set_Parent, void(*)(Transform* transform, Transform* parent, MethodInfo* methodInfo), 0x46FADF0)
}
