#pragma once

namespace SDK
{
	enum class ObjectiveStatus : int32_t
	{
		None,
		Completed,
		Failed,
	};

	enum class ObjectiveType : int32_t
	{
		BlowoutCandle,
		DetectParabolicSound,
		EMFGhost,
		EscapeHunt,
		GhostPhoto,
		IdentifyGhost,
		MotionSensorGhost,
		PreventHunt,
		SanityBelow25,
		SmudgeGhost,
		SmudgeHunt,
		WitnessEvent,
		DnaEvidence,
		CompleteInTimeLimit,
		GhostVideo,
		UniquePhotos,
		UniqueVideos,
		UniqueSounds,
	};

	struct ObjectiveValuesFields
	{
		char padding_0x00[0x08];
		ObjectiveType Type;
		String* LocalisedKey;
		// more
	};

	struct ObjectiveValues
	{
		void* Clazz;
		void* Monitor;
		ObjectiveValuesFields Fields;
	};

	struct ObjectiveFields
	{
		ObjectiveValues* ObjectiveValues;
		String* Text;
		ObjectiveStatus ObjectiveStatus;
		int Field0;
	};

	struct Objective
	{
		void* Clazz;
		void* Monitor;
		ObjectiveFields Fields;
	};

	struct ObjectiveArray
	{
		void* Clazz;
		void* Monitor;
		void* Bounds; // Il2CppArrayBounds
		void* MaxLength; // Il2CppArraySizeT
		Objective* Vector[65535];
	};

	struct __declspec(align(8)) ListObjectiveFields
	{
		ObjectiveArray* Items;
		int32_t Size;
		int32_t Version;
		void* SyncRoot; // Object
	};

	struct ListObjective
	{
		void* Clazz;
		void* Monitor;
		ListObjectiveFields Fields;
	};

	struct ObjectiveManagerFields
	{
		char padding_0x00[0x18];
		void* SmallMap;
		void* MediumMap;
		void* LargeMap;
		void* SmallMapBone;
		void* MediumMapBone;
		void* LargeMapBone;
		void* AllSideObjectiveValues;
		void* Field0;
		void* Field1;
		ListObjective* ListOfObjectives;
		// more
	};

	struct ObjectiveManager
	{
		void* Clazz;
		void* Monitor;
		ObjectiveManagerFields Fields;
	};

	DECLARE_METHOD_POINTER(ObjectiveManager_Update, void(*)(ObjectiveManager* objectiveManager, MethodInfo* methodInfo), "Assembly-CSharp", "",
	                       "ObjectiveManager", "Update", 0)

	DECLARE_METHOD_POINTER(ObjectiveManager_CompleteObjectiveSynced, void(*)(ObjectiveManager* objectiveManager, ObjectiveType type, MethodInfo* methodInfo), "Assembly-CSharp", "",
	                       "ObjectiveManager", "CompleteObjectiveSynced", 1)
}
