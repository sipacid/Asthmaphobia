#pragma once
#include "sdk.h"

namespace SDK
{
	struct GameObject
	{
	};

	// GameObject[]
	struct GameObjectArray
	{
		void* Clazz;
		void* Monitor;
		void* Bounds; // Il2CppArrayBounds
		void* MaxLength; // Il2CppArraySizeT
		GameObject* Vector[65535];
	};

	DECLARE_METHOD_POINTER(GameObject_Get_Transform, Transform* (*)(GameObject* gameObject, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "GameObject",
	                       "get_transform", 0);

	DECLARE_METHOD_POINTER(GameObject_FindGameObjectsWithTag, GameObjectArray* (*)(String* tag, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "GameObject",
	                       "FindGameObjectsWithTag", 1);

	DECLARE_METHOD_POINTER(GameObject_Set_Layer, void* (*)(GameObject* gameObject, int layer, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "GameObject",
	                       "set_layer", 1);
}
