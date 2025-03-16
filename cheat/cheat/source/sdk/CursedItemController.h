#pragma once
#include "sdk.h"

namespace SDK
{
	enum class CursedItemType : int32_t
	{
		None,
		TarotCards,
		OuijaBoard,
		HauntedMirror,
		MusicBox,
		SummoningCircle,
		VoodooDoll,
		MonkeyPaw
	};

	// CursedItemEnum[]
	struct CursedItemEnumArray
	{
		void* Clazz;
		void* Monitor;
		void* Bounds; // Il2CppArrayBounds
		void* MaxLength; // Il2CppArraySizeT
		CursedItemType Vector[65535];
	};

	struct __declspec(align(8)) ListCursedItemEnumFields
	{
		CursedItemEnumArray* Items;
		int32_t Size;
		int32_t Version;
		void* SyncRoot; // Object
	};

	// List<CursedItemEnum>
	struct ListCursedItemEnum
	{
		void* Clazz;
		void* Monitor;
		ListCursedItemEnumFields Fields;
	};

	struct CursedItemControllerFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		void* OuijaBoard; // OuijaBoard
		void* MusicBox; // MusicBox
		void* TarotCards; // TarotCards
		void* SummoningCircle; // SummoningCircle
		void* HauntedMirror; // HauntedMirror
		void* VoodooDoll; // VoodooDoll
		void* MonkeyPaw; // MonkeyPaw
		void* OuijaBoardSpawnSpots; // Transform[]
		void* MusicBoxSpawnSpots; // Transform[]
		void* TarotCardsSpawnSpots; // Transform[]
		void* SummoningCircleSpawnSpots; // Transform[]
		void* HauntedMirrorSpawnSpots; // Transform[]
		void* VoodooDollSpawnSpots; // Transform[]
		void* MonkeyPawSpawnSpots; // Transform[]
		ListCursedItemEnum* CursedItems; // List<???>
	};

	struct CursedItemController
	{
		void* Clazz;
		void* Monitor;
		CursedItemControllerFields Fields;
	};

	DECLARE_METHOD_POINTER(CursedItemController_Awake, void(*)(CursedItemController* cursedItemController, MethodInfo* methodInfo), "Assembly-CSharp", "", "CursedItemsController",
	                       "Awake", 0);
}
