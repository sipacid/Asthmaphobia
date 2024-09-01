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
		MonoBehaviourFields MonoBehaviourFields; // MonoBehaviour derived class field
		void* Field0; // PhotonView
		bool IsDead;
		bool Field1;
		int32_t Field2;
		void* Field3; // PlayerCharacter
		void* Field4; // ClosetZone
		void* Field5; // GameObject
		Transform* Field6; // Transform
		void* Field7; // List<KeyInfo>
		Camera* Camera; // Camera
		LevelRoom* LevelRoom; // LevelRoom
		Transform* Field10; // Transform
		void* Field11; // PhotonObjectInteract
		void* Field12; // PhotonObjectInteract
		void* Field13; // GameObject[]
		void* Field14; // GameObject
		int32_t Field15; // LayerMask
		void* Field16; // HeadMountedSocket
		Transform* Field17; // Transform
		Transform* Field18; // Transform
		void* Field19; // GameObject
		void* Field20; // DeadPlayer
		PlayerSanity* PlayerSanity; // PlayerSanity
		void* Field22; // PlayerStats
		void* Field23; // FootstepController
		void* Field24; // JournalController
		void* Field25; // Renderer[]
		bool Field26;
		void* Field27; // PlayerAudio
		void* Field28; // PlayerGraphics
		PlayerStamina* PlayerStamina; // PlayerStamina
		float Field30;
		bool Field31;
		void* Field32; // CharacterController
		void* Field33; // AudioListener
		FirstPersonController* FirstPersonController; // FirstPersonController
		void* Field35; // PCPropGrab
		void* Field36; // DragRigidbodyUse
		void* Field37; // PCCanvas
		void* Field38; // PCCrouch
		void* Field39; // PCMenu
		void* Field40; // PCControls
		PCFlashlight* Field41; // PCFlashlight
		void* Field42; // Animator
		void* Field43; // PlayerInput
		void* Field44; // PCItemSway
		void* Field45; // PCItemSway
		void* Field46; // Transform
		void* Field47; // XRBaseInteractor
		void* Field48; // XRBaseInteractor
		void* Field49; // Transform
		void* Field50; // VRMovementSettings
		void* Field51; // VRBelt
		void* Field52; // XRSocketInteractor
		void* Field53; // XRSocketInteractor
		void* Field54; // TrailerCamera
		void* Field55; // VRLoading
	};

	struct Player
	{
		void* Clazz; // PlayerClass
		void* Monitor; // MonitorData
		PlayerFields Fields;
	};

	struct PlayerArray
	{
		void* Clazz; // PlayerArrayClass
		void* Monitor; // MonitorData
		void* Bounds; // Il2CppArrayBounds
		void* MaxLength; // Il2CppArraySizeT
		Player* Vector[32];
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
		void* Clazz; // List<Player> Class
		void* Monitor; // MonitorData
		ListPlayerFields Fields;
	};

	DECLARE_FUNCTION_POINTER(Player_KillPlayer, void(*)(Player* player, bool a1, MethodInfo* methodInfo), 0x941670)
	DECLARE_FUNCTION_POINTER(Player_RevivePlayer, void(*)(Player* player, MethodInfo* methodInfo), 0x941950)
	DECLARE_FUNCTION_POINTER(Player_StartKillingPlayer, void(*)(Player* player, MethodInfo* methodInfo), 0x941C40)
	DECLARE_FUNCTION_POINTER(Player_StartKillingPlayerNetworked, std::nullptr_t(*)(Player* player, bool a1, void* photonMessageInfo, MethodInfo* methodInfo), 0x941B80)
	DECLARE_FUNCTION_POINTER(Player_Teleport, void(*)(Player* player, Vector3 position, MethodInfo* methodInfo), 0x942660)
	DECLARE_FUNCTION_POINTER(Player_ToggleFreezePlayer, void(*)(Player* player, bool freeze, MethodInfo* methodInfo), 0x942770)
}
