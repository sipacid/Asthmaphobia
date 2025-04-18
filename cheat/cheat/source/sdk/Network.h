#pragma once
#include "sdk.h"

namespace SDK
{
	struct Network;

	struct __declspec(align(8)) NetworkPlayerSpotFields
	{
		bool PlayerReady;
		int PlayerCharacterIndex;
		void* PhotonPlayer; // Photon.Realtime.Player
		String* UnityPlayerID;
		int Experience;
		int Level;
		int Prestige;
		Player* Player;
		float PlayerVolume;
		String* AccountName;
		bool IsKicked;
		bool IsHacker;
		bool IsBlocked;
		void* RoleBadges; // ???[]
		void* Role; // ???
		int PrestigeIndex;
		bool PrestigeTheme;
		void* VotedContract; // Contract
		int32_t PlatformType; // StoreSDKManager.???
		bool HasReceivedPlayerInformation;
		bool PlayerIsBlocked;
		int32_t LegacyLevel;
		int32_t LegacyAccent;
		int32_t LegacyBackground;
		int32_t LegacyColor;
		void* PlayerEquipment;
		bool HasBroughtItems;
		int32_t TotalEquipmentCost;
		void* OnBlockMuteStateChanged;
	};

	// Network.PlayerSpot
	struct NetworkPlayerSpot
	{
		void* Clazz;
		void* Monitor;
		NetworkPlayerSpotFields Fields;
	};

	// Network.PlayerSpot[]
	struct NetworkPlayerSpotArray
	{
		void* Clazz;
		void* Monitor;
		void* Bounds; // Il2CppArrayBounds
		void* MaxLength; // Il2CppArraySizeT
		NetworkPlayerSpot* Vector[32];
	};

	struct __declspec(align(8)) ListNetworkPlayerSpotFields
	{
		NetworkPlayerSpotArray* Items;
		int32_t Size;
		int32_t Version;
		void* SyncRoot; // Object
	};

	// List<Network.PlayerSpot>
	struct ListNetworkPlayerSpot
	{
		void* Clazz;
		void* Monitor;
		ListNetworkPlayerSpotFields Fields;
	};

	struct NetworkFields
	{
		MonoBehaviourPunCallbacksFields MonoBehaviourPunCallbacksFields; // MonoBehaviourPunCallbacksFields derived class field
		Player* LocalPlayer;
		ListNetworkPlayerSpot* PlayersData;
		void* PlayerColors; // Color[]
		void* DefaultPlayerColors; // Color[]
		void* JoinedLobby; // UnityEvent
		void* JoinedRoom; // UnityEvent
		void* LeftRoom; // UnityEvent
		void* Disconnected; // UnityEvent
		void* OnMicrophoneChanged; // Network.???
		void* OnMasterClientSwitchedEvent; // Network.???
		void* OnPlayerLeftRoomEvent; // Network.???
		void* OnPlayerSpotAssigned; // Network.???
		void* OnLocalPlayerSpawned; // UnityEvent
		void* OnSeasonalEventCompleted; // UnityEvent
		void* OnPlayerColorChanged; // UnityEvent
		void* LevelSystem; // LevelSystem
		bool IsChangingScenes;
		String* LastOnlineRoomName;
		void* RecentKickedFromRooms; // HashSet<String>
		bool FailedToConnectToVivox;
		bool IsAttemptingVivoxLogin;
		void* InviteSystem; // Network.InviteSystem
		bool IsChangingRooms;
		String* ChangeToRegionOnDisconnect;
	};

	struct Network
	{
		void* Clazz;
		void* Monitor;
		NetworkFields Fields;
	};

	DECLARE_METHOD_POINTER(Network_Get_Network, Network* (*)(MethodInfo* methodInfo), "Assembly-CSharp", "", "Network", "get_Instance", 0);
}
