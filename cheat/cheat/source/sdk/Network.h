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
		String* UnityPlayerID; // string
		int Experience;
		int Level;
		int Prestige;
		Player* Player; // Player
		float PlayerVolume;
		String* AccountName; // string
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
		bool hasBroughtItems;
		int32_t totalEquipmentCost;
		void* OnBlockMuteStateChanged;
	};

	struct NetworkPlayerSpot
	{
		void* Clazz; // Network.PlayerSpotClass
		void* Monitor; // MonitorData
		NetworkPlayerSpotFields Fields;
	};

	struct NetworkPlayerSpotArray
	{
		void* Clazz; // EvidenceArrayClass
		void* Monitor; // MonitorData
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

	struct ListNetworkPlayerSpot
	{
		void* Clazz; // List<Network.PlayerSpot>Class
		void* Monitor; // MonitorData
		ListNetworkPlayerSpotFields Fields;
	};

	struct NetworkFields
	{
		MonoBehaviourPunCallbacksFields MonoBehaviourPunCallbacksFields; // MonoBehaviourPunCallbacksFields derived class field
		Player* LocalPlayer;
		ListNetworkPlayerSpot* NetworkPlayerSpots; // List<Network.PlayerSpot>
		void* Field2; // UnityEvent
		void* Field3; // UnityEvent
		void* Field4; // UnityEvent
		void* Field5; // Network.???
		void* Field6; // Network.???
		void* Field7; // Network.???
		void* Field8; // Network.???
		void* Field9; // UnityEvent
		void* Field10; // ???
		void* Field12; // ???
		void* Field13; // ???
		void* Field14; // ???
		void* Field15; // ???
		void* Field16; // ???
		void* Field17; // ???
		void* Field18; // ???
		bool Field11;
	};

	struct Network
	{
		void* Clazz; // NetworkClass
		void* Monitor; // MonitorData
		NetworkFields Fields;
	};

	DECLARE_FUNCTION_POINTER(Network_Get_Network, Network* (*)(MethodInfo* methodInfo), 0x1CE66D0);
}
