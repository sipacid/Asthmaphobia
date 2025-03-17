#pragma once
#include "sdk/sdk.h"

namespace Asthmaphobia::GameState
{
	inline SDK::Network* network;
	inline SDK::GhostAI* ghostAI;
	inline SDK::MapController* mapController;
	inline SDK::EvidenceController* evidenceController;
	inline SDK::FuseBox* fuseBox;
	inline SDK::DeadZoneController* deadZoneController;
	inline SDK::CursedItemController* cursedItemController;
	inline SDK::EMFData* emfData;
	inline bool isHunting = false;

	inline void Reset()
	{
		ghostAI = nullptr;
		mapController = nullptr;
		evidenceController = nullptr;
		fuseBox = nullptr;
		deadZoneController = nullptr;
		cursedItemController = nullptr;
		emfData = nullptr;
		isHunting = false;
	}
}
