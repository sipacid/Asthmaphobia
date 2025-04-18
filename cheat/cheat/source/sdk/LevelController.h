#pragma once
#include "sdk.h"

namespace SDK
{
	struct LevelControllerFields
	{
		MonoBehaviourPunFields MonoBehaviourPunFields;
		void* SmallMapVariations; // LevelController.SmallMapVariation[]
		LevelRoom* CurrentPlayerRoom;
		LevelRoom* CurrentGhostRoom;
		GhostAI* CurrentGhost;
		DoorArray* Doors;
		void* AllGhostRooms; // LevelRoom[]
		void* AllInteriorRooms; // LevelRoom[]
		void* FuseboxSpawnLocations; // Transform[]
		void* MannequinTeleportSpots; // Transform[]
		LevelRoom* OutsideRoom;
		bool IsOutsideMap;
		FuseBox* FuseBox;
		GameController* GameController;
		void* SoundController; // SoundController
		void* ItemSpawner; // ItemSpawner
		DoorArray* ExitDoors;
		void* LevelAreas; // LevelArea[]
		void* Crucifix; // List<Crucifix>
		void* FireSources; // List<FireSource>
		void* AllEquipment; // List<PhotonObjectInteract>
		void* PossibleMaleFirstNames; // string[]
		void* PossibleFemaleFirstNames; // string[]
		void* PossibleLastNames; // string[]
		void* MainDoorKey; // Key
		void* AllBlockedZones; // BlockedZone[]
		int IntermediateZonesBlocked;
		int ProZonesBlocked;
		int NightmareZonesBlocked;
		void* AllClothDoors; // Transform[]
		void* FPS; // List<float>
	};

	struct LevelController
	{
		void* Clazz;
		void* Monitor;
		LevelControllerFields Fields;
	};
}
