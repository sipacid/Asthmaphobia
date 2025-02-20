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
		Door* Vector[65535];
	};

	DECLARE_FUNCTION_POINTER(Door_DisableOrEnableCollider, void(*)(Door* door, bool collisionEnabled, MethodInfo* methodInfo), 0x1F6D650);
	DECLARE_FUNCTION_POINTER(Door_DisableOrEnableDoor, void(*)(Door* door, bool a1, bool a2, MethodInfo* methodInfo), 0x1F6D750);
	DECLARE_FUNCTION_POINTER(Door_LockDoorForTime, void(*)(Door* door, float time, bool locked, MethodInfo* methodInfo), 0x1F6DF10);
}
