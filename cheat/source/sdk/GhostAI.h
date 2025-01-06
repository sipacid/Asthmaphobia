#pragma once
#include "sdk.h"

namespace SDK
{
	enum class GhostState : int32_t
	{
		Idle,
		Wander,
		Hunting,
		FavoriteRoom,
		Light,
		Door,
		Throwing,
		FuseBox,
		Appear,
		DoorKnock,
		WindowKnock,
		CarAlarm,
		Flicker,
		CCTV,
		RandomEvent,
		GhostAbility,
		Mannequin,
		TeleportObject,
		Interact,
		SummoningCircle,
		MusicBox,
		Dots,
		Salt
	};

	struct GhostAIFields
	{
		MonoBehaviourFields MonoBehaviourFields; // MonoBehaviour derived class field
		void* Field0; // ???
		GhostState Field1; // GhostState
		void* Field2; // PhotonView
		GhostInfo* GhostInfo; // GhostInfo
		void* Field4; // NavMeshAgent
		void* Field5; // GhostAudio
		void* Field6; // GhostInteraction
		void* GhostActivity; // GhostActivity
		void* Field8; // GhostModel
		void* HalloweenModel; // GhostModel
		void* HolidayModel; // GhostModel
		void* EasterModel; // GhostModel
		void* Field9; // GhostModel[]
		void* Field10; // GhostModel[]
		bool Field11;
		void* Field12; // ShadowCastingMode
		void* Field13; // List<Vector3>
		float Field121;
		void* Field131; // SanityDrainer
		bool Field14;
		int32_t Field17; // LayerMask
		Transform* Field18; // Transform
		Transform* Field19; // Transform
		Transform* Field20; // Transform
		float Field21;
		float Field22;
		float Field23;
		bool Field24;
		bool Field25;
		Vector3 Field26; // Vector3
		void* Field27; // GameObject
		bool Field28;
		bool Field29;
		bool Field30;
		bool Field301;
		void* Field31; // WhiteSage
		float Field32;
		bool Field33;
		bool Field34;
		bool Field35;
		Player* BansheeTarget; // Player
		int32_t Field37;
		Vector3 Field38; // Vector3
		void* Field39; // float[]
		void* Field40; // float[]
		void* Field41; // float[]
		int32_t Field42;
		int32_t Field43;
		int32_t Field44;
		int32_t Field45;
		int32_t Field46;
		void* Field47; // float[]
		void* Field48; // float[]
		void* Field49; // float[]
		float Field50;
		void* Field51; // int[]
		void* Field52; // int[]
		void* Field53; // int[]
		void* Field54; // int[]
	};

	struct GhostAI
	{
		void* Clazz; // GhostAIClass
		void* Monitor; // MonitorData
		GhostAIFields Fields;
	};

	DECLARE_FUNCTION_POINTER(GhostAI_Appear, void(*)(GhostAI* ghostAI, int time, MethodInfo* methodInfo), 0x19DE620);
	DECLARE_FUNCTION_POINTER(GhostAI_Start, void(*)(GhostAI* ghostAI, MethodInfo* methodInfo), 0x19E1830);
	DECLARE_FUNCTION_POINTER(GhostAI_Hunting, void(*)(GhostAI* ghostAI, bool isHunting, int a1, void* PhotonMessageInfo, MethodInfo* methodInfo), 0x19DF720);
}
