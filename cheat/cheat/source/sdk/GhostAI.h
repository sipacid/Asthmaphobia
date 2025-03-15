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
		GhostState GhostState; // GhostState
		void* PhotonView; // PhotonView
		GhostInfo* GhostInfo; // GhostInfo
		void* NavMeshAgent; // NavMeshAgent
		void* GhostAudio; // GhostAudio
		void* GhostInteraction; // GhostInteraction
		GhostActivity* GhostActivity; // GhostActivity
		void* NormalModel; // GhostModel
		void* HalloweenModel; // GhostModel
		void* HolidayModel; // GhostModel
		void* EasterModel; // GhostModel
		void* GhostModels0; // GhostModel[]
		void* GhostModels1; // GhostModel[]
		bool Field11;
		int32_t ShadowCastingMode; // ShadowCastingMode
		void* Field13; // List<Vector3>
		float Field121;
		void* SanityDrainer; // SanityDrainer
		bool Field14;
		int32_t LayerMask; // LayerMask
		Transform* Transform0; // Transform
		Transform* Transform1; // Transform
		Transform* Transform2; // Transform
		float Speed;
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

	DECLARE_METHOD_POINTER(GhostAI_Appear, void(*)(GhostAI* ghostAI, int a1, MethodInfo* methodInfo), "Assembly-CSharp", "", "GhostAI", "Appear", 1);

	DECLARE_METHOD_POINTER(GhostAI_ChangeState,
	                       void(*)(GhostAI* ghostAI, GhostState ghostState, void* photonObjectInteract, void* photonObjectInteractArray, MethodInfo* methodInfo), "Assembly-CSharp",
	                       "", "GhostAI", "ChangeState", 3);

	DECLARE_METHOD_POINTER(GhostAI_Hunting, void(*)(GhostAI* ghostAI, bool isHunting, int a1, void* PhotonMessageInfo, MethodInfo* methodInfo), "Assembly-CSharp", "", "GhostAI",
	                       "Hunting", 3);

	DECLARE_METHOD_POINTER(GhostAI_Start, void(*)(GhostAI* ghostAI, MethodInfo* methodInfo), "Assembly-CSharp", "", "GhostAI", "Start", 0);

	DECLARE_METHOD_POINTER(GhostAI_Update, void(*)(GhostAI* ghostAI, MethodInfo* methodInfo), "Assembly-CSharp", "", "GhostAI", "Update", 0);
}
