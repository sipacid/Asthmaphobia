#pragma once
#include "sdk.h"

namespace SDK
{
	struct Door
	{
	};

	struct DoorArray
	{
		void* Clazz; // DoorArrayClass
		void* Monitor; // MonitorData
		void* Bounds; // Il2CppArrayBounds
		void* MaxLength; // Il2CppArraySizeT
		Door* Vector[32];
	};

	DECLARE_FUNCTION_POINTER(Door_DisableOrEnableCollider, void(*)(Door* door, bool collisionEnabled, MethodInfo* methodInfo), 0x1EE4220);
	DECLARE_FUNCTION_POINTER(Door_DisableOrEnableDoor, void(*)(Door* door, bool a1, bool a2, MethodInfo* methodInfo), 0x1EE4320);
	DECLARE_FUNCTION_POINTER(Door_LockDoorForTime, void(*)(Door* door, float time, bool locked, MethodInfo* methodInfo), 0x1EE4A80);
}
