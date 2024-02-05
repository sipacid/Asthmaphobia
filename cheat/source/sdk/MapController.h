#pragma once
#include "sdk.h"

namespace SDK
{
	struct MapControllerFields
	{
		MonoBehaviourFields MonoBehaviourFields; // MonoBehaviour derived class field
		void* PlayerIcons; // List<RectTransform>
		ListPlayer* Players; // List<Player>
		Transform* BasementFloor; // Transform
		Transform* FirstFloor; // Transform
		Transform* SecondFloor; // Transform
		int32_t Index;
		int32_t MinFloorIndex;
		int32_t MaxFloorIndex;
		float IconScale;
		float PlayerIconScale;
		void* MotionSensorData; // MotionSensorData
		GameController* GameController; // GameController
		void* DefaultFloor; // LevelRoom.?????
		Vector3 PlayerIconOffset; // Vector3
		Camera* MapCamera; // Camera
	};

	struct MapController
	{
		void* Clazz; // MapControllerClass
		void* Monitor; // MonitorData
		MapControllerFields Fields;
	};

	DECLARE_FUNCTION_POINTER(MapController_Start, void(*)(MapController* mapController, MethodInfo* methodInfo), 0x196CEE0);
}
