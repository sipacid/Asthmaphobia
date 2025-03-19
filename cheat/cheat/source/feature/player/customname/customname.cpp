#include "customname.h"

using namespace Asthmaphobia::Features::Player;

CustomName::CustomName() : Feature("Custom name", "Set your own custom in-game nickname", FeatureCategory::Player)
{
	NickNameSetting = std::make_unique<Setting>("Nickname", "Your custom nickname", "Asthmaphobia");
	Settings_->AddSetting(NickNameSetting);

	strcpy_s(NickNameBuffer, std::get<std::string>(NickNameSetting->GetValue()).c_str());
}

void CustomName::OnMenu()
{
	ImGui::InputText("##customName", NickNameBuffer, IM_ARRAYSIZE(NickNameBuffer));
	ImGui::SameLine();
	if (ImGui::Button("Set name##customName"))
	{
		NickNameSetting->SetValue(std::string(NickNameBuffer));
		SDK::PhotonNetwork_Set_NickName_ptr(Helper::StringToSystemString(std::get<std::string>(NickNameSetting->GetValue())), nullptr);
	}
}
