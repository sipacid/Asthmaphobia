#pragma once
#include "sdk.h"

namespace SDK
{
	// UnityEngine.CoreModule.UnityEngine.GameObject
	struct GameObjectArray
	{
		void* Clazz; // GameObjectArrayClass
		void* Monitor; // MonitorData
		void* Bounds; // Il2CppArrayBounds
		void* MaxLength; // Il2CppArraySizeT
		void* Vector[65535];
	};

	DECLARE_FUNCTION_POINTER(GameObject_Get_Transform, Transform* (*)(void* gameObject, MethodInfo* methodInfo), 0x4790750);
	DECLARE_FUNCTION_POINTER(GameObject_FindGameObjectsWithTag, GameObjectArray* (*)(String* tag, MethodInfo* methodInfo), 0x478FD00);
}
