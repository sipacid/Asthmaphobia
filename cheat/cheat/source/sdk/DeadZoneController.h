#pragma once
#include "sdk.h"

namespace SDK
{
	struct DeadZoneControllerFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		void* Field0; // GameObject
		void* DeathRoomObjects; // GameObject[]
		Transform* PlayerSpawn; // Transform
		Vector3 Field3; // Vector3
		void* DeadZoneLightObj; // GameObject
		void* DeadZoneLightSmashAudio; // AudioSource
		GameController* GameController; // GameController
	};

	struct DeadZoneController
	{
		void* Clazz; // DeadZoneControllerClass
		void* Monitor; // MonitorData
		DeadZoneControllerFields Fields;
	};

	DECLARE_FUNCTION_POINTER(DeadZoneController_Awake, void(*)(DeadZoneController* deadZoneController, MethodInfo* methodInfo), 0x1BE6E00);
}
