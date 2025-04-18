#pragma once
#include "sdk.h"

namespace SDK
{
	struct LevelRoomFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		void* LightSwitches; // List<LightSwitch>
		void* Doors; // Door[]
		void* RoomColliders; // List<Collider>
		Transform* MirrorCameraOverride;
		void* AudioReverbZone; // AudioReverbZone
		int32_t RoomType;
		void* EvidenceSpawnOverride; // BoxCollider
		int32_t FloorType;
		String* RoomName;
		float Temperature;
		float MaximumTemperature;
		float MinimumTemperature;
		float CurrentPlayerInRoomTimer;
		bool AllowGhostToRoamOtherFloor;
		bool IsMostlyDarkRoom;
		bool RoomModifierActive;
		bool CanRunPlayerEnter;
	};

	struct LevelRoom
	{
		void* Clazz;
		void* Monitor;
		LevelRoomFields Fields;
	};
}
