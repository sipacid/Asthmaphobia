#pragma once
#include "sdk.h"

namespace SDK
{
	struct GameObjectArray
	{
		void* Clazz; // GameObjectArrayClass
		void* Monitor; // MonitorData
		void* Bounds; // Il2CppArrayBounds
		void* MaxLength; // Il2CppArraySizeT
		void* Vector[65535];
	};

	DECLARE_FUNCTION_POINTER(GameObject_FindGameObjectsWithTag, GameObjectArray* (*)(String* tag, MethodInfo* methodInfo), 0x47AA9B0);
	DECLARE_FUNCTION_POINTER(GameObject_Get_Transform, Transform*(*)(void* gameObject, MethodInfo* methodInfo), 0x47AB400);
}
