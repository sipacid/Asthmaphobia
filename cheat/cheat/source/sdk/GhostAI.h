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
		MonoBehaviourPunFields MonoBehaviourPunFields;
		void* StateMachine; // ???
		GhostState CurrentState;
		GhostInfo* GhostInfo;
		void* Agent; // NavMeshAgent
		void* GhostAudio; // GhostAudio
		void* GhostInteraction; // GhostInteraction
		GhostActivity* GhostActivity;
		void* CurrentModel; // GhostModel
		void* HalloweenModel; // GhostModel
		void* HolidayModel; // GhostModel
		void* EasterModel; // GhostModel
		void* MaleGhostModels; // GhostModel[]
		void* FemaleGhostModels; // GhostModel[]
		bool CanSwapModel;
		int32_t CurrentShadowCastingMode; // ShadowCastingMode
		void* GhostBreadcrumbs; // List<Vector3>
		float BreadcrumbTimer;
		void* PlayerSensor; // LOSSensor
		bool GhostIsAppeared;
		Transform* RaycastPoint;
		Transform* HuntingRaycastPoint;
		Transform* FeetRaycastPoint;
		float DefaultSpeed;
		float SaltSpeedMultiplier;
		float IncenseSpeedMultiplier;
		float EventSpeedMultiplier;
		bool HasHuntedRecently;
		bool RemoveInteractionChanceBlock;
		Vector3 LastKnownHuntingLocation;
		GameObject* HuntingPostProcessingVolume;
		bool IsDemonAbilityHunt;
		bool IsHunting;
		bool IsUsingLights;
		bool DelayedBySmudgeStick;
		void* ActiveIncense; // WhiteSage
		float ActiveIncenseDuration;
		bool CanWander;
		bool CanFlashAppear;
		bool IsTrapped;
		Player* BansheeTarget;
		int32_t OnryoCandleBlowoutCounter;
		Vector3 LastInteractionPoint;
		void* NormalFlashValues; // float[]
		void* DeogenFlashValues; // float[]
		void* OniFlashValues; // float[]
		int32_t FlashIndexValue;
		int32_t AppearIndexValue;
		int32_t FlashAmount;
		int32_t ObakeModelIndex;
		int32_t ObakeArrayID;
		void* NormalAppearValues; // float[]
		void* DeogenOniAppearValues; // float[]
		void* PhantomAppearValues; // float[]
		float AppearTimer;
		void* Obake1Values; // int[]
		void* Obake2Values; // int[]
		void* Obake3Values; // int[]
		void* Obake4Values; // int[]
	};

	struct GhostAI
	{
		void* Clazz;
		void* Monitor;
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
