#pragma once
#include "sdk.h"

namespace SDK
{
	struct LevelRoom;
	struct GhostAI;

	struct GhostInfoFields
	{
		MonoBehaviourPunFields MonoBehaviourPunFields; // MonoBehaviourPun derived class field
		GhostTraits GhostTraits; // GhostTraits
		GhostAI* Ghost; // GhostAI
		LevelRoom* LevelRoom; // LevelRoom
		float Field3;
		bool Field4;
	};

	struct GhostInfo
	{
		void* Clazz; // GhostInfoClass
		void* Monitor; // MonitorData
		GhostInfoFields Fields;
	};
}
