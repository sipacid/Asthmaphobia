#pragma once
#include "sdk.h"

namespace SDK
{
	struct GameObject
	{
	};

	// UnityEngine.CoreModule.UnityEngine.GameObject
	struct GameObjectArray
	{
		void* Clazz; // GameObjectArrayClass
		void* Monitor; // MonitorData
		void* Bounds; // Il2CppArrayBounds
		void* MaxLength; // Il2CppArraySizeT
		GameObject* Vector[65535];
	};

	DECLARE_FUNCTION_POINTER(GameObject_Get_Transform, Transform* (*)(GameObject* gameObject, MethodInfo* methodInfo), 0x4790750);
	DECLARE_FUNCTION_POINTER(GameObject_FindGameObjectsWithTag, GameObjectArray* (*)(String* tag, MethodInfo* methodInfo), 0x478FD00);
	DECLARE_FUNCTION_POINTER(GameObject_Set_Layer, void* (*)(GameObject* gameObject, int layer, MethodInfo* methodInfo), 0x47907E0);
}
