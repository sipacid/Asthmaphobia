#include "menu.h"

#include "libraries/imgui/imgui.h"
#include "resources/fonts/RobotoMonoMediumFont.h"

using namespace Asthmaphobia;

static void SetTheme()
{
	auto& style = ImGui::GetStyle();
	const auto& io = ImGui::GetIO();

	io.Fonts->AddFontFromMemoryCompressedTTF(RobotoMonoMediumFont_compressed_data, RobotoMonoMediumFont_compressed_size, 16.0f);

	style.Alpha = 1.0f;
	style.WindowPadding = ImVec2(6, 6);
	style.WindowBorderSize = 0.0f;
	style.FrameRounding = 2.0f;

	const auto colors = style.Colors;
	colors[ImGuiCol_TitleBg] = ImVec4(0.020f, 0.020f, 0.020f, 1.0f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.020f, 0.020f, 0.020f, 1.0f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.038f, 0.038f, 0.038f, 1.00f);

	colors[ImGuiCol_PopupBg] = ImVec4(0.038f, 0.038f, 0.038f, 1.00f);

	colors[ImGuiCol_Button] = ImVec4(0.4f, 0.0f, 0.4f, 1.0f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.5f, 0.0f, 0.5f, 1.0f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.6f, 0.0f, 0.6f, 1.0f);

	colors[ImGuiCol_Header] = ImVec4(0.4f, 0.0f, 0.4f, 1.0f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.5f, 0.0f, 0.5f, 1.0f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.6f, 0.0f, 0.6f, 1.0f);

	colors[ImGuiCol_Tab] = ImVec4(0.4f, 0.0f, 0.4f, 1.0f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.5f, 0.0f, 0.5f, 1.0f);
	colors[ImGuiCol_TabActive] = ImVec4(0.6f, 0.0f, 0.6f, 1.0f);

	colors[ImGuiCol_FrameBg] = ImVec4(0.4f, 0.0f, 0.4f, 1.0f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.5f, 0.0f, 0.5f, 1.0f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.6f, 0.0f, 0.6f, 1.0f);

	colors[ImGuiCol_Separator] = ImVec4(0.4f, 0.0f, 0.4f, 1.0f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.5f, 0.0f, 0.5f, 1.0f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.6f, 0.0f, 0.6f, 1.0f);

	colors[ImGuiCol_ResizeGrip] = ImVec4(0.4f, 0.0f, 0.4f, 1.0f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.5f, 0.0f, 0.5f, 1.0f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.6f, 0.0f, 0.6f, 1.0f);

	colors[ImGuiCol_SliderGrab] = ImVec4(0.95f, 0.95f, 0.95f, 1.0f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

	colors[ImGuiCol_CheckMark] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
}

void Menu::Initialize()
{
	SetTheme();
	menu.Initialized = true;

	LOG_DEBUG("Menu initialized.");
}

void Menu::Render()
{
	constexpr ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
	constexpr int menuWidth = 600;
	constexpr int menuHeight = 600;

	ImGui::SetNextWindowSize(ImVec2(menuWidth * dpiScale, menuHeight * dpiScale), ImGuiCond_Once);
	ImGui::Begin(cheatName, nullptr, windowFlags);

#ifdef _DEBUG
	ImGui::ShowDemoWindow();
#endif

	if (ImGui::BeginTabBar("##tabBarMain"))
	{
		GetFeatureManagerInstance().OnMenu();

		if (ImGui::BeginTabItem("Settings"))
		{
			if (ImGui::Button("License"))
			{
				ImGui::OpenPopup("License Information");
			}

			if (ImGui::BeginPopupModal("License Information", nullptr, ImGuiWindowFlags_NoResize))
			{
				ImGui::BeginChild("LicenseText", ImVec2(500 * dpiScale, 300 * dpiScale), false, ImGuiWindowFlags_NoCollapse);
				ImGui::TextWrapped(
					"MIT License\n\n"
					"Copyright (c) 2024-2025 sipacid\n\n"
					"Permission is hereby granted, free of charge, to any person obtaining a copy "
					"of this software and associated documentation files (the \"Software\"), to deal "
					"in the Software without restriction, including without limitation the rights "
					"to use, copy, modify, merge, publish, distribute, sublicense, and/or sell "
					"copies of the Software, and to permit persons to whom the Software is "
					"furnished to do so, subject to the following conditions:\n\n"
					"The above copyright notice and this permission notice shall be included in all "
					"copies or substantial portions of the Software.\n\n"
					"THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR "
					"IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, "
					"FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE "
					"AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER "
					"LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, "
					"OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE "
					"SOFTWARE.");
				ImGui::EndChild();

				if (ImGui::Button("Close"))
				{
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}

			if (ImGui::Button("Unload cheat"))
			{
				globalRunning = false;
			}

			ImGui::Text("Built on: %s %s", buildDate, buildTime);
			ImGui::Text("%s", creditsText);

			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}

	ImGui::End();
}

void Menu::Toggle()
{
	menu.Open = !menu.Open;

	if (menu.Open)
	{
		previousCursorLockMode = SDK::Cursor_Get_LockState_ptr(nullptr);
		SDK::Cursor_Set_Visible_ptr(true, nullptr);
		SDK::Cursor_Set_LockState_ptr(SDK::CursorLockMode::None, nullptr);
	}
	else
	{
		if (previousCursorLockMode != SDK::CursorLockMode::None)
			SDK::Cursor_Set_Visible_ptr(false, nullptr);

		SDK::Cursor_Set_LockState_ptr(previousCursorLockMode, nullptr);
	}
}
