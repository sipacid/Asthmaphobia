#pragma once
#include "sdk.h"

namespace SDK
{
	struct LevelRoomFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		void* Field1; // List<LightSwitch>
		void* Field2; // Door[]
		void* RoomColliders; // List<Collider>
		Transform* Field4; // Transform
		void* AudioReverbZone; // AudioReverbZone
		int32_t Field5;
		void* Field7; // BoxCollider
		int32_t Field6;
		String* RoomName; // String
		float Field10;
		float Field11;
		float Field12;
		float Field13;
		bool Field14;
		bool Field15;
		bool Field16;
		bool Field17;
	};

	struct LevelRoom
	{
		void* Clazz; // LevelRoomClass
		void* Monitor; // Monitor
		LevelRoomFields Fields;
	};
}
