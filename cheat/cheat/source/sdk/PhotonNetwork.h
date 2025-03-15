#pragma once
#include "sdk.h"

namespace SDK
{
	// PhotonUnityNetworking.Photon.Pun.PhotonNetwork
	struct PhotonNetwork
	{
	};

	DECLARE_METHOD_POINTER(PhotonNetwork_Get_IsConnected, bool(*)(MethodInfo* methodInfo), "PhotonUnityNetworking", "Photon.Pun", "PhotonNetwork", "get_IsConnected", 0)

	DECLARE_METHOD_POINTER(PhotonNetwork_Set_NickName, void (*)(String* nickName, MethodInfo* methodInfo), "PhotonUnityNetworking", "Photon.Pun", "PhotonNetwork", "set_NickName",
	                       1)

	DECLARE_METHOD_POINTER(PhotonNetwork_Get_IsMasterClient, bool(*)(MethodInfo* methodInfo), "PhotonUnityNetworking", "Photon.Pun", "PhotonNetwork", "get_IsMasterClient", 0)

	DECLARE_METHOD_POINTER(PhotonNetwork_Get_MasterClient, Player* (*)(MethodInfo* methodInfo), "PhotonUnityNetworking", "Photon.Pun", "PhotonNetwork", "get_MasterClient", 0)

	DECLARE_METHOD_POINTER(PhotonNetwork_Get_InRoom, bool(*)(MethodInfo* methodInfo), "PhotonUnityNetworking", "Photon.Pun", "PhotonNetwork", "get_InRoom", 0)

	DECLARE_METHOD_POINTER(PhotonNetwork_GetPing, int(*)(MethodInfo* methodInfo), "PhotonUnityNetworking", "Photon.Pun", "PhotonNetwork", "GetPing", 0)

	DECLARE_METHOD_POINTER(PhotonNetwork_JoinRandomRoom, bool(*)(MethodInfo* methodInfo), "PhotonUnityNetworking", "Photon.Pun", "PhotonNetwork", "JoinRandomRoom", 0)

	DECLARE_METHOD_POINTER(PhotonNetwork_LeaveRoom, bool(*)(bool becomeInactive, MethodInfo* methodInfo), "PhotonUnityNetworking", "Photon.Pun", "PhotonNetwork", "LeaveRoom", 1)
}
