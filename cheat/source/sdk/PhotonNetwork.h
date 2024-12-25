#pragma once
#include "sdk.h"

namespace SDK
{
	// PhotonUnityNetworking.Photon.Pun.PhotonNetwork
	struct PhotonNetwork
	{
	};

	DECLARE_FUNCTION_POINTER(PhotonNetwork_GetPing, int(*)(MethodInfo* methodInfo), 0x3B627D0)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_JoinRandomRoom, bool(*)(MethodInfo* methodInfo), 0x3B64110)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_LeaveRoom, bool(*)(bool becomeInactive, MethodInfo* methodInfo), 0x3B646E0)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_Get_IsMasterClient, bool(*)(MethodInfo* methodInfo), 0x3B72D50)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_Get_MasterClient, Player* (*)(MethodInfo* methodInfo), 0x3B73160)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_Get_InRoom, bool(*)(MethodInfo* methodInfo), 0x3B72B20)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_Get_IsConnected, bool(*)(MethodInfo* methodInfo), 0x3B72C60)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_Set_NickName, void (*)(String* nickName, MethodInfo* methodInfo), 0x3B74EA0)
}
