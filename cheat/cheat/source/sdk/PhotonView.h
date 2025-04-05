#pragma once
#include "sdk.h"

namespace SDK
{
	struct PhotonView;

	DECLARE_METHOD_POINTER(PhotonView_RequestOwnership, void(*)(PhotonView* photonView, MethodInfo* methodInfo), "PhotonUnityNetworking", "Photon.Pun", "PhotonView",
	                       "RequestOwnership", 0);
}
