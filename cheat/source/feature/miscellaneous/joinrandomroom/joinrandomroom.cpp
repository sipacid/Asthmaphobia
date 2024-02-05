#include "joinrandomroom.h"

using namespace Asthmaphobia::Features::Miscellaneous;

JoinRandomRoom::JoinRandomRoom() : Feature("Join random room", "Join a random room", FeatureCategory::Miscellaneous)
{
	ShouldDrawSection = false;
}

JoinRandomRoom::~JoinRandomRoom() = default;

void JoinRandomRoom::OnEnable()
{
}

void JoinRandomRoom::OnDisable()
{
}

void JoinRandomRoom::OnDraw()
{
}

void JoinRandomRoom::OnMenu()
{
	if (ImGui::Button("Join random room"))
		Run();
}

void JoinRandomRoom::Run()
{
	if (!SDK::PhotonNetwork_Get_IsConnected_ptr(nullptr))
		return;

	if (!SDK::PhotonNetwork_GetPing_ptr(nullptr))
		return;

	if (SDK::PhotonNetwork_Get_InRoom_ptr(nullptr))
		SDK::PhotonNetwork_LeaveRoom_ptr(true, nullptr);
	else
		SDK::PhotonNetwork_JoinRandomRoom_ptr(nullptr);
}
