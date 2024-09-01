#pragma once
#include "sdk.h"

namespace SDK
{
	// PhotonUnityNetworking.Photon.Pun.PhotonNetwork
	struct PhotonNetwork
	{
	};

	DECLARE_FUNCTION_POINTER(PhotonNetwork_GetPing, int(*)(MethodInfo* methodInfo), 0x3585750)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_JoinRandomRoom, bool(*)(MethodInfo* methodInfo), 0x3587090)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_LeaveRoom, bool(*)(bool becomeInactive, MethodInfo* methodInfo), 0x3587660)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_Get_IsMasterClient, bool(*)(MethodInfo* methodInfo), 0x3595F20)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_Get_MasterClient, Player* (*)(MethodInfo* methodInfo), 0x3596320)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_Get_InRoom, bool(*)(MethodInfo* methodInfo), 0x3595CF0)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_Get_IsConnected, bool(*)(MethodInfo* methodInfo), 0x3595E30)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_Set_NickName, void (*)(String* nickName, MethodInfo* methodInfo), 0x3598060)
}
