#pragma once
#include "sdk.h"

namespace SDK
{
	// PhotonUnityNetworking.Photon.Pun.PhotonNetwork
	struct PhotonNetwork
	{
	};

	DECLARE_FUNCTION_POINTER(PhotonNetwork_GetPing, int(*)(MethodInfo* methodInfo), 0x3B4AEE0)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_JoinRandomRoom, bool(*)(MethodInfo* methodInfo), 0x3B4C820)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_LeaveRoom, bool(*)(bool becomeInactive, MethodInfo* methodInfo), 0x3B4CDF0)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_Get_IsMasterClient, bool(*)(MethodInfo* methodInfo), 0x3B5B4A0)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_Get_MasterClient, Player* (*)(MethodInfo* methodInfo), 0x3B5B8B0)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_Get_InRoom, bool(*)(MethodInfo* methodInfo), 0x3B5B270)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_Get_IsConnected, bool(*)(MethodInfo* methodInfo), 0x3B5B3B0)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_Set_NickName, void (*)(String* nickName, MethodInfo* methodInfo), 0x3B5D5F0)
}
