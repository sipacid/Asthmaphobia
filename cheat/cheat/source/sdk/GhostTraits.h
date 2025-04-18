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
		GhostType InitialGhostType; // GhostType
		GhostType GhostType; // GhostType
		ListGhostEvidence* Evidences; // List<GhostEvidence> ???
		ListGhostEvidence* FullEvidences; // List<GhostEvidence> ???
		int32_t GhostAge;
		bool IsMale;
		String* GhostName;
		int32_t GhostFirstNameID;
		int32_t GhostLastNameID;
		bool IsShy;
		int32_t DeathLength;
		int32_t FavouriteRoomID;
		bool IsWhisper;
	};
}
