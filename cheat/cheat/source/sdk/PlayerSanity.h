#pragma once
#include "Player.h"
#include "sdk.h"

namespace SDK
{
	struct Player;

	struct PlayerSanityFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		void* View; // PhotonView
		Player* Player;
		float Insanity;
		float SanityUpdateTimer;
		float SanityCheckTimer;
		void* ShadowRenderTexture; // RenderTexture
		bool PlayerIsInLight;
		float DifficultyRate;
		bool IsCursed;
		float NormalSanityRate;
		float SetupSanityRate;
		bool SanityChallengeHasBeenSet;
		void* NearbyFireLights; // List<Candle>
	};

	struct PlayerSanity
	{
		void* Clazz;
		void* Monitor;
		PlayerSanityFields Fields;
	};

	DECLARE_METHOD_POINTER(PlayerSanity_SetInsanity, void(*)(PlayerSanity* playerSanity, int insanity, MethodInfo* methodInfo), "Assembly-CSharp", "", "PlayerSanity",
	                       "SetInsanity", 1);
}
