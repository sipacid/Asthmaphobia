#pragma once
#include "sdk.h"

namespace SDK
{
	// PhotonUnityNetworking.Photon.Pun.PhotonNetwork
	struct PhotonNetwork
	{
	};

	DECLARE_FUNCTION_POINTER(PhotonNetwork_Get_IsConnected, bool(*)(MethodInfo* methodInfo), 0x3AB3250)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_Set_NickName, void (*)(String* nickName, MethodInfo* methodInfo), 0x3AB5490)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_Get_IsMasterClient, bool(*)(MethodInfo* methodInfo), 0x3AB3340)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_Get_MasterClient, Player* (*)(MethodInfo* methodInfo), 0x3AB3750)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_Get_InRoom, bool(*)(MethodInfo* methodInfo), 0x3AB3110)

	DECLARE_FUNCTION_POINTER(PhotonNetwork_GetPing, int(*)(MethodInfo* methodInfo), 0x3AA2D80)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_JoinRandomRoom, bool(*)(MethodInfo* methodInfo), 0x3AA46C0)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_LeaveRoom, bool(*)(bool becomeInactive, MethodInfo* methodInfo), 0x3AA4C90)
}
