#pragma once
#include "source/common.h"
#include "setting.h"
#include "libraries/imgui/imgui.h"
#include "source/menu/hotkey/hotkey.h"

namespace Asthmaphobia
{
	const auto MESSAGE_MUST_BE_INGAME = "You must be in-game to use this feature.";
	const auto MESSAGE_MUST_BE_HOST = "You must be host to use this feature.";

	enum FeatureCategory : uint8_t
	{
		Player,
		Ghost,
		World,
		CursedItems,
		Visuals,
		Exploits,
		Movement,
		MenuSettings
	};

	static const std::unordered_map<FeatureCategory, const char*> CATEGORY_TO_STRING = {
		{Player, "Player"},
		{Ghost, "Ghost"},
		{World, "World"},
		{CursedItems, "Cursed items"},
		{Visuals, "Visuals"},
		{Exploits, "Exploits"},
		{Movement, "Movement"},
		{MenuSettings, "Settings"}
	};

	class Feature
	{
	public:
		explicit Feature(const std::string_view name, const std::string_view description, const FeatureCategory category)
			: Name(name), Description(description), Category(category), Settings_(std::make_unique<Settings>())
		{
			const auto enabledSetting = std::make_shared<Setting>("Enabled", "Enables or disables this feature", false);
			EnabledSetting = enabledSetting;
			Settings_->AddSetting(enabledSetting);

			const auto hotkeySetting = std::make_shared<Setting>("Hotkey", "Hotkey to toggle this feature", KeyBindToggle(KeyBind::NONE));
			ToggleHotkeySetting = hotkeySetting;
			Settings_->AddSetting(hotkeySetting);
		}

		Feature(const Feature&) = delete;
		Feature& operator=(const Feature&) = delete;
		Feature(Feature&&) noexcept = default;
		Feature& operator=(Feature&&) noexcept = default;
		virtual ~Feature() = default;

		virtual void OnEnable() = 0;
		virtual void OnDisable() = 0;
		virtual void OnDraw() = 0;
		virtual void OnMenu() = 0;

		static std::unordered_map<std::string, bool>& GetCapturingStates()
		{
			static std::unordered_map<std::string, bool> capturingStates;
			return capturingStates;
		}

		static bool IsAnyFeatureCapturing()
		{
			return std::ranges::any_of(GetCapturingStates() | std::views::values, std::identity{});
		}

		void ProcessHotkeys() const
		{
			if (IsAnyFeatureCapturing())
				return;

			auto& toggleHotkey = std::get<KeyBindToggle>(ToggleHotkeySetting->GetValue());
			if (toggleHotkey.ToInt() != 0 && ImGuiCustom::CheckBindKey(toggleHotkey))
			{
				auto& enabled = std::get<bool>(EnabledSetting->GetValue());
				enabled = !enabled;
			}
		}

		void DrawHotkeySelector() const
		{
			const auto& hotkey = std::get<KeyBindToggle>(ToggleHotkeySetting->GetValue());
			auto& capturingStates = GetCapturingStates();
			bool& isCapturing = capturingStates[Name];

			std::string buttonText = (hotkey.ToInt() == 0) ? ".." : hotkey.ToString();

			if (isCapturing)
			{
				buttonText = "?";
			}

			const float buttonSize = ImGui::GetFrameHeight();
			ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.5f, 0.5f));
			if (ImGui::Button((buttonText + "##hotkey_" + Name).c_str(), ImVec2(buttonSize, buttonSize)))
			{
				isCapturing = !isCapturing;
			}
			ImGui::PopStyleVar();

			if (isCapturing)
			{
				if (ImGui::IsKeyPressed(ImGuiKey_Escape))
				{
					ToggleHotkeySetting->SetValue(KeyBindToggle(KeyBind::NONE));
					isCapturing = false;
				}
				else
				{
					KeyBindToggle newHotkey = hotkey;
					if (newHotkey.SetToPressedKey())
					{
						ToggleHotkeySetting->SetValue(newHotkey);
						isCapturing = false;
					}
				}
			}
		}

		void DrawHotkeyUI() const
		{
			ImGui::SameLine();

			const float availableWidth = ImGui::GetContentRegionAvail().x;
			const float buttonSize = ImGui::GetFrameHeight();
			const float hotkeyWidth = buttonSize + ImGui::GetStyle().ItemSpacing.x;
			const float spacingWidth = availableWidth - hotkeyWidth;

			if (spacingWidth > 0)
				ImGui::Dummy(ImVec2(spacingWidth, 0));

			ImGui::SameLine();
			DrawHotkeySelector();
		}

		[[nodiscard]] const std::string& GetName() const noexcept { return Name; }
		[[nodiscard]] const std::string& GetDescription() const noexcept { return Description; }
		[[nodiscard]] FeatureCategory GetCategory() const noexcept { return Category; }
		[[nodiscard]] virtual bool IsEnabled() const noexcept { return std::get<bool>(EnabledSetting->GetValue()); }
		[[nodiscard]] const Settings* GetSettings() const noexcept { return Settings_.get(); }
		Settings* GetSettings() noexcept { return Settings_.get(); }

	protected:
		std::string Name;
		std::string Description;
		const FeatureCategory Category;
		std::shared_ptr<Setting> EnabledSetting;
		std::shared_ptr<Setting> ToggleHotkeySetting;
		std::unique_ptr<Settings> Settings_;
	};

	class FeatureManager
	{
		std::unordered_map<std::string, std::unique_ptr<Feature>> Features;

	public:
		FeatureManager(const FeatureManager&) = delete;
		FeatureManager& operator=(const FeatureManager&) = delete;
		FeatureManager(FeatureManager&&) = delete;
		FeatureManager& operator=(FeatureManager&&) = delete;

		FeatureManager();
		~FeatureManager();

		void Cleanup();

		void AddFeature(std::string_view name, std::unique_ptr<Feature> feature);
		[[nodiscard]] const auto& GetFeatures() const noexcept { return Features; }
		[[nodiscard]] Feature* GetFeatureByName(std::string_view name) const;

		template <typename T>
		[[nodiscard]] T* GetFeature(const std::string_view name) const
		{
			if (auto feature = GetFeatureByName(name))
			{
				return dynamic_cast<T*>(feature);
			}
			return nullptr;
		}

		void ProcessHotkeys();
		void OnDraw() const;
		void OnMenu() const;
	};

	FeatureManager& GetFeatureManagerInstance();
}
