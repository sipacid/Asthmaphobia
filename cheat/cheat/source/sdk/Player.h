#pragma once
#include "sdk.h"

namespace SDK
{
	struct PlayerSanity;
	struct LevelRoom;
	struct FirstPersonController;
	struct PCFlashlight;

	struct PlayerFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		void* View; // PhotonView
		bool IsDead;
		bool IsDyingLocally;
		int32_t ModelID;
		void* PlayerCharacter; // PlayerCharacter
		void* Closet; // ClosetZone
		void* HeadObject; // GameObject
		Transform* TrackedHead; // Transform
		void* Keys; // List<KeyInfo>
		Camera* Camera; // Camera
		LevelRoom* CurrentRoom; // LevelRoom
		Transform* MapIcon; // Transform
		void* RightCurrentHeldObject; // PhotonObjectInteract
		void* LeftCurrentHeldObject; // PhotonObjectInteract
		void* CharacterModels; // GameObject[]
		void* GhostDeathHands; // GameObject
		int32_t GhostRaycastMask; // LayerMask
		void* HeadSock; // HeadMountedSocket
		void* LOSTarget; // PlayerLOSTarget[]
		Transform* AITargetPoint; // Transform
		void* DeadBodyPrefab; // GameObject
		void* DeadPlayer; // DeadPlayer
		PlayerSanity* PlayerSanity; // PlayerSanity
		void* PlayerStats; // PlayerStats
		void* FootstepController; // FootstepController
		void* JournalController; // JournalController
		void* AllRends; // Renderer[]
		bool IsSafeGhostCursed;
		void* PlayerAudio; // PlayerAudio
		void* PlayerGraphics; // PlayerGraphics
		void* PlayerSensors; // PlayerSensors
		PlayerStamina* PlayerStamina; // PlayerStamina
		float MovementSpeed;
		bool MonkeyPawLeaveEffectIsActive;
		void* CharController; // CharacterController
		void* Listener; // AudioListener
		FirstPersonController* FirstPersonController; // FirstPersonController
		void* PCPropGrab; // PCPropGrab
		void* DragRigidbodyUse; // DragRigidbodyUse
		void* PCCanvas; // PCCanvas
		void* PCCrouch; // PCCrouch
		void* PCMenu; // PCMenu
		void* PCControls; // PCControls
		PCFlashlight* PCFlashlight; // PCFlashlight
		void* CharAnim; // Animator
		void* PlayerInput; // PlayerInput
		void* ItemSway; // PCItemSway
		void* LightSway; // PCItemSway
		void* DeadPlayerSpawnPoint; // Transform
		void* LeftHandInteractor; // XRBaseInteractor
		void* RightHandInteractor; // XRBaseInteractor
		void* XROrigin; // Transform
		void* MovementSettings; // VRMovementSettings
		void* VRBelt; // VRBelt
		void* LeftVRBeltDropZone; // XRSocketInteractor
		void* RightVRBeltDropZone; // XRSocketInteractor
		void* TrailerCamera; // TrailerCamera
		void* VRLoading; // VRLoading
	};

	struct Player
	{
		void* Clazz;
		void* Monitor;
		PlayerFields Fields;
	};

	struct PlayerArray
	{
		void* Clazz;
		void* Monitor;
		void* Bounds; // Il2CppArrayBounds
		void* MaxLength; // Il2CppArraySizeT
		Player* Vector[65535];
	};

	struct __declspec(align(8)) ListPlayerFields
	{
		PlayerArray* Items;
		int32_t Size;
		int32_t Version;
		void* SyncRoot; // Object
	};

	struct ListPlayer
	{
		void* Clazz;
		void* Monitor;
		ListPlayerFields Fields;
	};

	DECLARE_METHOD_POINTER(Player_KillPlayer, void(*)(Player* player, bool revive, MethodInfo* methodInfo), "Assembly-CSharp", "", "Player", "KillPlayer", 1)

	DECLARE_METHOD_POINTER(Player_StartKillingPlayer, void(*)(Player* player, MethodInfo* methodInfo), "Assembly-CSharp", "", "Player", "StartKillingPlayer", 0)

	DECLARE_METHOD_POINTER(Player_StartKillingPlayerNetworked,
	                       std::nullptr_t(*)(Player* player, bool revive, bool wasDemonAbilityHunt, void* photonMessageInfo, MethodInfo* methodInfo),
	                       "Assembly-CSharp", "", "Player", "StartKillingPlayerNetworked", 3)

	DECLARE_METHOD_POINTER(Player_Teleport, void(*)(Player* player, Vector3 position, MethodInfo* methodInfo), "Assembly-CSharp", "", "Player", "Teleport", 1)
}
