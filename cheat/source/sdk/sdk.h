#pragma once

#define DECLARE_FUNCTION_POINTER(NAME, TYPE, ADDRESS) \
using NAME = TYPE; \
inline NAME NAME##_ptr = reinterpret_cast<NAME>(BASE_ADDRESS + ADDRESS);

namespace SDK
{
	const auto BASE_ADDRESS = reinterpret_cast<uintptr_t>(GetModuleHandleW(L"GameAssembly.dll"));
}

#include "MonoBehaviour.h"
#include "MethodInfo.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "String.h"
#include "Cursor.h"
#include "Transform.h"
#include "Component.h"
#include "Camera.h"
#include "ExitLevel.h"
#include "PauseMenuController.h"
#include "ServerManager.h"
#include "PlayerStamina.h"
#include "PlayerSanity.h"
#include "Player.h"
#include "GameController.h"
#include "MapController.h"
#include "GhostEvidence.h"
#include "GhostTraits.h"
#include "GhostInfo.h"
#include "GhostAI.h"
#include "EMF.h"
#include "PhotoValues.h"
#include "Evidence.h"
#include "EvidenceController.h"
#include "PhotonNetwork.h"
#include "Network.h"
#include "FirstPersonController.h"
#include "Collider.h"
#include "Time.h"
#include "TarotCards.h"
#include "TarotCard.h"
#include "Door.h"
#include "LevelRoom.h"
#include "FuseBox.h"
#include "LevelController.h"
#include "Marshal.h"
#include "LevelValues.h"
#include "DeadZoneController.h"
#include "MouseLook.h"
