#pragma once
#include "sdk.h"

namespace SDK
{
	enum class GhostType : int32_t
	{
		Spirit,
		Wraith,
		Phantom,
		Poltergeist,
		Banshee,
		Jinn,
		Mare,
		Revenant,
		Shade,
		Demon,
		Yurei,
		Oni,
		Yokai,
		Hantu,
		Goryo,
		Myling,
		Onryo,
		TheTwins,
		Raiju,
		Obake,
		Mimic,
		Moroi,
		Deogen,
		Thaye,
	};

	struct GhostTraits
	{
		GhostType GhostType_; // GhostType
		GhostType MimicType; // GhostType
		ListGhostEvidence* GhostEvidenceList; // List<GhostEvidence> ???
		ListGhostEvidence* Field3; // List<GhostEvidence> ???
		int32_t Field4;
		bool Field5;
		String* Name;
		int32_t Field7;
		int Field8;
		bool Field9;
		int32_t Field10;
		int32_t Field11;
		bool Field12;
	};
}
