#pragma once
#include "sdk.h"

namespace SDK
{
	struct DeadZoneControllerFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		GameObject* Field0;
		GameObjectArray* DeathRoomObjects;
		Transform* PlayerSpawn;
		Vector3 Field3;
		GameObject* DeadZoneLightObj;
		void* DeadZoneLightSmashAudio; // AudioSource
		GameController* GameController;
	};

	struct DeadZoneController
	{
		void* Clazz;
		void* Monitor;
		DeadZoneControllerFields Fields;
	};

	DECLARE_METHOD_POINTER(DeadZoneController_Awake, void(*)(DeadZoneController* deadZoneController, MethodInfo* methodInfo), "Assembly-CSharp", "", "DeadZoneController", "Awake",
	                       0);
}
