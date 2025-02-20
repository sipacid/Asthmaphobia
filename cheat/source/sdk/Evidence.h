#pragma once
#include "sdk.h"

namespace SDK
{
	struct EvidenceFields
	{
		MonoBehaviourPunFields MonoBehaviourPunFields; // MonoBehaviourPun derived class field
		PhotoValues* PhotoValues;
		bool Field1;
		bool ResetTakenPhotoOnEnable;
	};

	struct Evidence
	{
		void* Clazz; // EvidenceClass
		void* Monitor; // MonitorData
		EvidenceFields Fields;
	};

	struct EvidenceArray
	{
		void* Clazz; // EvidenceArrayClass
		void* Monitor; // MonitorData
		void* Bounds; // Il2CppArrayBounds
		void* MaxLength; // Il2CppArraySizeT
		Evidence* Vector[65535];
	};

	struct __declspec(align(8)) ListEvidenceFields
	{
		EvidenceArray* Items;
		int32_t Size;
		int32_t Version;
		void* SyncRoot; // Object
	};

	struct ListEvidence
	{
		void* Clazz; // List<Evidence> Class
		void* Monitor; // MonitorData
		ListEvidenceFields Fields;
	};

	enum class EvidenceType : int32_t
	{
		EMFSpot,
		OuijaBoard,
		Fingerprint,
		Footstep,
		DNA,
		Ghost,
		DeadBody,
		DirtyWater,
		MusicBox,
		TarotCards,
		SummoningCircle,
		HauntedMirror,
		VoodooDoll,
		GhostWriting,
		UsedCrucifix,
		DotsGhost,
		MonkeyPaw,
		None
	};
}
