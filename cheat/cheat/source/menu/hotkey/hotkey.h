#pragma once
#include "../../../libraries/imgui/imgui.h"
#include "../inpututil/inpututil.h"
#include <unordered_map>
#include <functional>
#include <string>

class KeyBind;
class KeyBindToggle;

namespace ImGuiCustom
{
	void Hotkey(const char* id, KeyBind& keyBind, bool* boundBool, float samelineOffset = 0.0f, const ImVec2& size = {85.0f, 20.0f}) noexcept;
	void Hotkey(const char* id, KeyBindToggle& keyBindToggle, bool* boundBool, float samelineOffset = 0.0f, const ImVec2& size = {85.0f, 20.0f}) noexcept;
	bool CheckBindKey(const KeyBindToggle& keyToggle, bool& func);
	bool CheckBindKey(const KeyBindToggle& keyToggle);
	bool CheckHoldBindKey(const KeyBindToggle& keyToggle);
	bool CheckStateBindKey(const KeyBindToggle& keyToggle);
}

namespace Asthmaphobia
{
	class HotkeyManager
	{
	public:
		static HotkeyManager& GetInstance()
		{
			static HotkeyManager instance;
			return instance;
		}

		struct FeatureToggle
		{
			KeyBindToggle hotkey{KeyBind::NONE};
			std::function<void()> toggleCallback;
			bool* enabledPtr = nullptr;
			bool isCapturing = false;
		};

		void RegisterFeatureToggle(const std::string& featureName, bool* enabledPtr, const KeyBindToggle& hotkey = KeyBindToggle(KeyBind::NONE))
		{
			featureToggles[featureName] = {
				hotkey,
				[enabledPtr]() { if (enabledPtr) *enabledPtr = !*enabledPtr; },
				enabledPtr,
				false
			};
		}

		void SetHotkey(const std::string& featureName, const KeyBindToggle& hotkey)
		{
			if (auto it = featureToggles.find(featureName); it != featureToggles.end())
			{
				it->second.hotkey = hotkey;
			}
		}

		KeyBindToggle GetHotkey(const std::string& featureName) const
		{
			if (auto it = featureToggles.find(featureName); it != featureToggles.end())
			{
				return it->second.hotkey;
			}
			return KeyBindToggle(KeyBind::NONE);
		}

		void ProcessHotkeys()
		{
			for (auto& [name, toggle] : featureToggles)
			{
				if (toggle.hotkey.ToInt() != 0 && ImGuiCustom::CheckBindKey(toggle.hotkey))
				{
					toggle.toggleCallback();
				}
			}
		}

	private:
		std::unordered_map<std::string, FeatureToggle> featureToggles;

		HotkeyManager() = default;
		~HotkeyManager() = default;
		HotkeyManager(const HotkeyManager&) = delete;
		HotkeyManager& operator=(const HotkeyManager&) = delete;
	};
}
