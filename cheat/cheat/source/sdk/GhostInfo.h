#pragma once
#include "sdk.h"

namespace SDK
{
	struct LevelRoom;
	struct GhostAI;

	struct GhostInfoFields
	{
		MonoBehaviourPunFields MonoBehaviourPunFields; // MonoBehaviourPun derived class field
		GhostTraits GhostTraits;
		GhostAI* Ghost;
		LevelRoom* LevelRoom;
		float Field3;
		bool Field4;
	};

	struct GhostInfo
	{
		void* Clazz;
		void* Monitor;
		GhostInfoFields Fields;
	};
}
