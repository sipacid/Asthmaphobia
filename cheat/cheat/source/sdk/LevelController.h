#pragma once
#include "sdk.h"

namespace SDK
{
	struct LevelControllerFields
	{
		MonoBehaviourPunFields MonoBehaviourPunFields;
		void* Field0; // LevelController.SmallMapVariation[]
		LevelRoom* Field1;
		LevelRoom* Field2;
		GhostAI* GhostAI;
		DoorArray* DoorArray0;
		void* Field5; // LevelRoom[]
		void* Field6; // LevelRoom[]
		void* Field7; // Transform[]
		void* Field8; // Transform[]
		LevelRoom* Field9;
		bool Field10;
		FuseBox* FuseBox;
		GameController* GameController;
		void* SoundController; // SoundController
		void* Field15; // ItemSpawner
		DoorArray* DoorArray1;
		void* Field17; // LevelArea[]
		void* Field18; // List<Crucifix>
		void* Field19; // List<FireSource>
		void* PhotonObjectInteractList; // List<PhotonObjectInteract>
		void* Field20; // string[]
		void* Field21; // string[]
		void* Field22; // string[]
		void* Field23; // Key
		void* Field24; // BlockedZone[]
		int IntermediateZonesBlocked;
		int ProZonesBlocked;
		int NightmareZonesBlocked;
		void* Field29; // Transform[]
		void* Field30; // List<float>
	};

	struct LevelController
	{
		void* Clazz;
		void* Monitor;
		LevelControllerFields Fields;
	};
}
