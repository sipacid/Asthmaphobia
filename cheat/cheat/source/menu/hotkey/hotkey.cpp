#define IMGUI_DEFINE_MATH_OPERATORS
#include "../../../libraries/imgui/imgui.h"
#include "../../../libraries/imgui/imgui_internal.h"
#include <Windows.h>
#include "hotkey.h"
#include "../inpututil/inpututil.h"
#include <unordered_map>
#include <chrono>

struct KeyToggleState
{
	bool wasPressed = false;
	bool isFirstPress = true;
	std::chrono::steady_clock::time_point lastPressTime{};
	static constexpr auto DEBOUNCE_TIME = std::chrono::milliseconds(50);
};

static std::unordered_map<int, KeyToggleState> keyToggleStates;

inline bool IsKeyCurrentlyPressed(int keyCode) noexcept
{
	return (GetKeyState(keyCode) & 0x8000) != 0;
}

bool ImGuiCustom::CheckBindKey(const KeyBindToggle& keyToggle, bool& func)
{
	const int currentKey = keyToggle.ToInt();
	auto& state = keyToggleStates[currentKey];

	const auto now = std::chrono::steady_clock::now();
	const bool currentKeyState = IsKeyCurrentlyPressed(currentKey);

	if (currentKeyState && !state.wasPressed &&
		(now - state.lastPressTime) > KeyToggleState::DEBOUNCE_TIME)
	{
		state.lastPressTime = now;

		if (!state.isFirstPress)
		{
			func = !func;
		}
		else
		{
			state.isFirstPress = false;
		}
	}

	state.wasPressed = currentKeyState;
	return func;
}

bool ImGuiCustom::CheckBindKey(const KeyBindToggle& keyToggle)
{
	const int currentKey = keyToggle.ToInt();
	auto& state = keyToggleStates[currentKey];

	const auto now = std::chrono::steady_clock::now();
	const bool currentKeyState = IsKeyCurrentlyPressed(currentKey);

	bool shouldToggle = false;

	if (currentKeyState && !state.wasPressed &&
		(now - state.lastPressTime) > KeyToggleState::DEBOUNCE_TIME)
	{
		state.lastPressTime = now;

		if (!state.isFirstPress)
		{
			shouldToggle = true;
		}
		else
		{
			state.isFirstPress = false;
		}
	}

	state.wasPressed = currentKeyState;
	return shouldToggle;
}

bool ImGuiCustom::CheckHoldBindKey(const KeyBindToggle& keyToggle)
{
	const int currentKey = keyToggle.ToInt();
	return IsKeyCurrentlyPressed(currentKey);
}

bool ImGuiCustom::CheckStateBindKey(const KeyBindToggle& keyToggle)
{
	const int currentKey = keyToggle.ToInt();

	static std::unordered_map<int, bool> toggleStates;
	static std::unordered_map<int, bool> wasPressed;

	const bool isKeyPressed = IsKeyCurrentlyPressed(currentKey);
	bool& keyWasPressed = wasPressed[currentKey];
	bool& toggleState = toggleStates[currentKey];

	if (isKeyPressed && !keyWasPressed)
	{
		toggleState = !toggleState;
		keyWasPressed = true;
	}
	else if (!isKeyPressed)
	{
		keyWasPressed = false;
	}

	return toggleState;
}

struct KeyState
{
	ImGuiKey Key = ImGuiKey_None;
	bool WaitingForKey = false;
	bool* BoundBool = nullptr;
};

static std::unordered_map<std::string, KeyState> keyBindStates;
static bool initialized = false;

void ImGuiCustom::Hotkey(const char* id, KeyBind& keyBind, bool* boundBool, float samelineOffset, const ImVec2& size) noexcept
{
	KeyState& state = keyBindStates[id];

	if (!initialized || state.Key == ImGuiKey_None)
	{
		state.Key = InputUtil::KeyCodeToImGuiKey(keyBind.ToInt());
		initialized = true;
	}

	const std::string buttonLabel = state.WaitingForKey ? "Press a key..." : ImGui::GetKeyName(state.Key);

	if (ImGui::Button(buttonLabel.c_str(), size))
	{
		state.WaitingForKey = true;
	}

	if (state.WaitingForKey)
	{
		bool keyFound = false;

		if (ImGui::IsKeyPressed(ImGuiKey_Escape))
		{
			state.WaitingForKey = false;
			keyFound = true;
		}

		if (!keyFound)
		{
			constexpr int keyRangeStart = ImGuiKey_NamedKey_BEGIN;
			constexpr int keyRangeEnd = ImGuiKey_NamedKey_END;

			for (int i = keyRangeStart; i < keyRangeEnd && !keyFound; ++i)
			{
				const auto key = static_cast<ImGuiKey>(i);

				if (key == ImGuiKey_MouseLeft ||
					key == ImGuiKey_MouseRight ||
					key == ImGuiKey_MouseMiddle)
				{
					continue;
				}

				if (ImGui::IsKeyPressed(key))
				{
					keyBind.SetToPressedKey();
					state.Key = key;
					state.BoundBool = boundBool;
					if (boundBool) *boundBool = true;
					state.WaitingForKey = false;
					keyFound = true;
				}
			}
		}
	}
}

void ImGuiCustom::Hotkey(const char* id, KeyBindToggle& keyBindToggle, bool* boundBool, float samelineOffset, const ImVec2& size) noexcept
{
	// Simply call the base version since KeyBindToggle inherits from KeyBind
	Hotkey(id, static_cast<KeyBind&>(keyBindToggle), boundBool, samelineOffset, size);
}
