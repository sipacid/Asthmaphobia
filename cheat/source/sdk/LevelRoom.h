#pragma once
#include "sdk.h"

namespace SDK
{
	struct LevelRoomFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		ListPlayer* Players; // List<Player>
		void* Field1; // List<LightSwitch>
		void* Field2; // Door[]
		void* RoomColliders; // List<Collider>
		Transform* Field4; // Transform
		void* AudioReverbZone; // AudioReverbZone
		void* Field6; // LevelRoom.???
		void* Field7; // BoxCollider
		void* Field8; // LevelRoom.???
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
