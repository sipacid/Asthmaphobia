#pragma once
#include "Player.h"
#include "sdk.h"

namespace SDK
{
	struct Player;

	struct PlayerSanityFields
	{
		MonoBehaviourFields MonoBehaviourFields; // MonoBehaviour derived class field
		void* View; // PhotonView
		Player* Player; // Player
		float Insanity;
		float Field2;
		float Field3;
		void* ShadowRenderTexture; // RenderTexture
		bool Field5;
		float Field6;
		bool Field7;
		float Field8;
		float Field9;
		bool Field10;
		void* Field11; // List<Candle>
	};

	struct PlayerSanity
	{
		void* Clazz; // PlayerSanityClass
		void* Monitor; // MonitorData
		PlayerSanityFields Fields;
	};

	DECLARE_FUNCTION_POINTER(PlayerSanity_SetInsanity, void(*)(PlayerSanity* playerSanity, int insanity, MethodInfo* methodInfo), 0x9C2B10);
}
