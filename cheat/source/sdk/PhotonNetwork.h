#pragma once
#include "sdk.h"

namespace SDK
{
	// PhotonUnityNetworking.Photon.Pun.PhotonNetwork
	struct PhotonNetwork
	{
	};

	DECLARE_FUNCTION_POINTER(PhotonNetwork_GetPing, int(*)(MethodInfo* methodInfo), 0x37DD200)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_JoinRandomRoom, bool(*)(MethodInfo* methodInfo), 0x37DEB40)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_LeaveRoom, bool(*)(bool becomeInactive, MethodInfo* methodInfo), 0x37DF110)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_Get_IsMasterClient, bool(*)(MethodInfo* methodInfo), 0x37EDA00)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_Get_MasterClient, Player* (*)(MethodInfo* methodInfo), 0x37EDE00)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_Get_InRoom, bool(*)(MethodInfo* methodInfo), 0x37ED7D0)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_Get_IsConnected, bool(*)(MethodInfo* methodInfo), 0x37ED910)
	DECLARE_FUNCTION_POINTER(PhotonNetwork_Set_NickName, void (*)(String* nickName, MethodInfo* methodInfo), 0x37EFB40)
}
