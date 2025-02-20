#pragma once
#include "sdk.h"

namespace SDK
{
	enum class GhostEvidence : int32_t
	{
		None,
		EMF,
		SpiritBox,
		Ultraviolet,
		GhostOrb,
		GhostWritingBook,
		Temperature,
		DotsProjector
	};

	struct GhostEvidenceArray
	{
		void* Clazz; // GhostEvidenceArrayClass
		void* Monitor; // MonitorData
		void* Bounds; // Il2CppArrayBounds
		void* MaxLength; // Il2CppArraySizeT
		GhostEvidence Vector[65535];
	};

	struct __declspec(align(8)) ListGhostEvidenceFields
	{
		GhostEvidenceArray* Items;
		int32_t Size;
		int32_t Version;
		void* SyncRoot; // Object
	};

	struct ListGhostEvidence
	{
		void* Clazz; // ListGhostEvidenceClass
		void* Monitor; // MonitorData
		ListGhostEvidenceFields Fields;
	};
}
