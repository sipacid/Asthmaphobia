#pragma once
#include "sdk.h"

namespace SDK
{
	struct MapController;

	struct MapControllerFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		void* PlayerIcons; // List<RectTransform>
		ListPlayer* Players;
		void* AllFloors;
		int32_t Index;
		float IconScale;
		float PlayerIconScale;
		void* MotionSensorData; // MotionSensorData
		GameController* GameController;
		void* DefaultFloor; // LevelRoom.?????
		Vector3 PlayerIconOffset;
		Camera* MapCamera;
	};

	struct MapController
	{
		void* Clazz;
		void* Monitor;
		MapControllerFields Fields;
	};

	DECLARE_METHOD_POINTER(MapController_Start, void(*)(MapController* mapController, MethodInfo* methodInfo), "Assembly-CSharp", "", "MapController", "Start", 0);
}
