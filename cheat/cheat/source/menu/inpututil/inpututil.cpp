#include <algorithm>
#include <array>
#include <unordered_map>
#include <cstring>
#include <Windows.h>

#include "../../../libraries/imgui/imgui.h"
#include "InputUtil.h"

struct Key
{
	constexpr Key(const char* name, const int code) : Name{name}, Code{code}
	{
	}

	const char* Name;
	int Code;
};

// indices must match KeyBind::KeyCode enum
static constexpr Key KEY_MAP[] = {
	{"'", VK_OEM_7},
	{",", VK_OEM_COMMA},
	{"-", VK_OEM_MINUS},
	{".", VK_OEM_PERIOD},
	{"/", VK_OEM_2},
	{"0", '0'},
	{"1", '1'},
	{"2", '2'},
	{"3", '3'},
	{"4", '4'},
	{"5", '5'},
	{"6", '6'},
	{"7", '7'},
	{"8", '8'},
	{"9", '9'},
	{";", VK_OEM_1},
	{"=", VK_OEM_PLUS},
	{"A", 'A'},
	{"ADD", VK_ADD},
	{"B", 'B'},
	{"BACKSPACE", VK_BACK},
	{"C", 'C'},
	{"CAPSLOCK", VK_CAPITAL},
	{"D", 'D'},
	{"DECIMAL", VK_DECIMAL},
	{"DELETE", VK_DELETE},
	{"DIVIDE", VK_DIVIDE},
	{"DOWN", VK_DOWN},
	{"E", 'E'},
	{"END", VK_END},
	{"ENTER", VK_RETURN},
	{"F", 'F'},
	{"F1", VK_F1},
	{"F10", VK_F10},
	{"F11", VK_F11},
	{"F12", VK_F12},
	{"F2", VK_F2},
	{"F3", VK_F3},
	{"F4", VK_F4},
	{"F5", VK_F5},
	{"F6", VK_F6},
	{"F7", VK_F7},
	{"F8", VK_F8},
	{"F9", VK_F9},
	{"G", 'G'},
	{"H", 'H'},
	{"HOME", VK_HOME},
	{"I", 'I'},
	{"INSERT", VK_INSERT},
	{"J", 'J'},
	{"K", 'K'},
	{"L", 'L'},
	{"LALT", VK_LMENU},
	{"LCTRL", VK_LCONTROL},
	{"LEFT", VK_LEFT},
	{"LSHIFT", VK_LSHIFT},
	{"M", 'M'},
	{"MOUSE1", 0},
	{"MOUSE2", 1},
	{"MOUSE3", 2},
	{"MOUSE4", VK_XBUTTON1},
	{"MOUSE5", VK_XBUTTON2},
	{"MULTIPLY", VK_MULTIPLY},
	{"MWHEEL_DOWN", 0},
	{"MWHEEL_UP", 0},
	{"N", 'N'},
	{"NONE", 0},
	{"NUMPAD_0", VK_NUMPAD0},
	{"NUMPAD_1", VK_NUMPAD1},
	{"NUMPAD_2", VK_NUMPAD2},
	{"NUMPAD_3", VK_NUMPAD3},
	{"NUMPAD_4", VK_NUMPAD4},
	{"NUMPAD_5", VK_NUMPAD5},
	{"NUMPAD_6", VK_NUMPAD6},
	{"NUMPAD_7", VK_NUMPAD7},
	{"NUMPAD_8", VK_NUMPAD8},
	{"NUMPAD_9", VK_NUMPAD9},
	{"O", 'O'},
	{"P", 'P'},
	{"PAGE_DOWN", VK_NEXT},
	{"PAGE_UP", VK_PRIOR},
	{"Q", 'Q'},
	{"R", 'R'},
	{"RALT", VK_RMENU},
	{"RCTRL", VK_RCONTROL},
	{"RIGHT", VK_RIGHT},
	{"RSHIFT", VK_RSHIFT},
	{"S", 'S'},
	{"SPACE", VK_SPACE},
	{"SUBTRACT", VK_SUBTRACT},
	{"T", 'T'},
	{"TAB", VK_TAB},
	{"U", 'U'},
	{"UP", VK_UP},
	{"V", 'V'},
	{"W", 'W'},
	{"X", 'X'},
	{"Y", 'Y'},
	{"Z", 'Z'},
	{"[", VK_OEM_4},
	{"\\", VK_OEM_5},
	{"]", VK_OEM_6},
	{"`", VK_OEM_3},
};

namespace InputUtil
{
	static std::unordered_map<int, ImGuiKey> keyCodeCache;
	static bool cacheInitialized = false;

	void InitializeKeyCodeCache() noexcept
	{
		if (cacheInitialized) return;

		keyCodeCache.reserve(128);

		keyCodeCache[VK_ESCAPE] = ImGuiKey_Escape;
		keyCodeCache[VK_RETURN] = ImGuiKey_Enter;
		keyCodeCache[VK_TAB] = ImGuiKey_Tab;
		keyCodeCache[VK_BACK] = ImGuiKey_Backspace;
		keyCodeCache[VK_SPACE] = ImGuiKey_Space;

		keyCodeCache[VK_LEFT] = ImGuiKey_LeftArrow;
		keyCodeCache[VK_RIGHT] = ImGuiKey_RightArrow;
		keyCodeCache[VK_UP] = ImGuiKey_UpArrow;
		keyCodeCache[VK_DOWN] = ImGuiKey_DownArrow;

		keyCodeCache[VK_PRIOR] = ImGuiKey_PageUp;
		keyCodeCache[VK_NEXT] = ImGuiKey_PageDown;
		keyCodeCache[VK_HOME] = ImGuiKey_Home;
		keyCodeCache[VK_END] = ImGuiKey_End;
		keyCodeCache[VK_INSERT] = ImGuiKey_Insert;
		keyCodeCache[VK_DELETE] = ImGuiKey_Delete;

		keyCodeCache[VK_CAPITAL] = ImGuiKey_CapsLock;
		keyCodeCache[VK_LSHIFT] = ImGuiKey_LeftShift;
		keyCodeCache[VK_RSHIFT] = ImGuiKey_RightShift;
		keyCodeCache[VK_LCONTROL] = ImGuiKey_LeftCtrl;
		keyCodeCache[VK_RCONTROL] = ImGuiKey_RightCtrl;
		keyCodeCache[VK_LMENU] = ImGuiKey_LeftAlt;
		keyCodeCache[VK_RMENU] = ImGuiKey_RightAlt;
		keyCodeCache[VK_LWIN] = ImGuiKey_LeftSuper;
		keyCodeCache[VK_RWIN] = ImGuiKey_RightSuper;

		keyCodeCache[VK_OEM_1] = ImGuiKey_Semicolon;
		keyCodeCache[VK_OEM_2] = ImGuiKey_Slash;
		keyCodeCache[VK_OEM_3] = ImGuiKey_GraveAccent;
		keyCodeCache[VK_OEM_4] = ImGuiKey_LeftBracket;
		keyCodeCache[VK_OEM_5] = ImGuiKey_Backslash;
		keyCodeCache[VK_OEM_6] = ImGuiKey_RightBracket;
		keyCodeCache[VK_OEM_7] = ImGuiKey_Apostrophe;
		keyCodeCache[VK_OEM_COMMA] = ImGuiKey_Comma;
		keyCodeCache[VK_OEM_MINUS] = ImGuiKey_Minus;
		keyCodeCache[VK_OEM_PERIOD] = ImGuiKey_Period;
		keyCodeCache[VK_OEM_PLUS] = ImGuiKey_Equal;

		for (int i = VK_F1; i <= VK_F24; ++i)
		{
			keyCodeCache[i] = static_cast<ImGuiKey>(ImGuiKey_F1 + (i - VK_F1));
		}

		keyCodeCache[VK_NUMLOCK] = ImGuiKey_NumLock;
		keyCodeCache[VK_SCROLL] = ImGuiKey_ScrollLock;
		keyCodeCache[VK_ADD] = ImGuiKey_KeypadAdd;
		keyCodeCache[VK_SUBTRACT] = ImGuiKey_KeypadSubtract;
		keyCodeCache[VK_MULTIPLY] = ImGuiKey_KeypadMultiply;
		keyCodeCache[VK_DIVIDE] = ImGuiKey_KeypadDivide;
		keyCodeCache[VK_DECIMAL] = ImGuiKey_KeypadDecimal;

		for (int i = 'A'; i <= 'Z'; ++i)
		{
			keyCodeCache[i] = static_cast<ImGuiKey>(ImGuiKey_A + (i - 'A'));
		}

		for (int i = '0'; i <= '9'; ++i)
		{
			keyCodeCache[i] = static_cast<ImGuiKey>(ImGuiKey_0 + (i - '0'));
		}

		for (int i = VK_NUMPAD0; i <= VK_NUMPAD9; ++i)
		{
			keyCodeCache[i] = static_cast<ImGuiKey>(ImGuiKey_Keypad0 + (i - VK_NUMPAD0));
		}

		keyCodeCache[0] = ImGuiKey_MouseLeft;
		keyCodeCache[1] = ImGuiKey_MouseRight;
		keyCodeCache[2] = ImGuiKey_MouseMiddle;
		keyCodeCache[VK_XBUTTON1] = ImGuiKey_MouseX1;
		keyCodeCache[VK_XBUTTON2] = ImGuiKey_MouseX2;

		cacheInitialized = true;
	}

	ImGuiKey KeyCodeToImGuiKey(const int code) noexcept
	{
		InitializeKeyCodeCache();

		if (const auto it = keyCodeCache.find(code); it != keyCodeCache.end())
		{
			return it->second;
		}

		return ImGuiKey_None;
	}
}

static constexpr size_t KEY_MAP_SIZE = sizeof(KEY_MAP) / sizeof(KEY_MAP[0]);
static_assert(KEY_MAP_SIZE == KeyBind::MAX, "KEY_MAP size must match KeyBind::MAX");

KeyBind::KeyBind(const KeyCode keyCode) noexcept : keyCode_{static_cast<std::size_t>(keyCode) < KEY_MAP_SIZE ? keyCode : NONE}
{
}

KeyBind::KeyBind(const char* keyName) noexcept
{
	bool found = false;
	for (size_t i = 0; i < KEY_MAP_SIZE; ++i)
	{
		if (strcmp(KEY_MAP[i].Name, keyName) == 0)
		{
			keyCode_ = static_cast<KeyCode>(i);
			found = true;
			break;
		}
	}
	if (!found)
		keyCode_ = NONE;
}

const char* KeyBind::ToString() const noexcept
{
	if (keyCode_ == NONE) return "None";
	if (static_cast<size_t>(keyCode_) < KEY_MAP_SIZE)
	{
		return KEY_MAP[static_cast<size_t>(keyCode_)].Name;
	}
	return "Unknown";
}

int KeyBind::ToInt() const noexcept
{
	return KEY_MAP[static_cast<std::size_t>(keyCode_) < KEY_MAP_SIZE ? keyCode_ : NONE].Code;
}

bool KeyBind::IsPressed() const noexcept
{
	if (keyCode_ == NONE)
		return false;

	if (keyCode_ == MOUSEWHEEL_DOWN)
		return ImGui::GetIO().MouseWheel < 0.0f;

	if (keyCode_ == MOUSEWHEEL_UP)
		return ImGui::GetIO().MouseWheel > 0.0f;

	if (keyCode_ >= MOUSE1 && keyCode_ <= MOUSE5)
		return ImGui::IsMouseClicked(KEY_MAP[keyCode_].Code);

	return static_cast<std::size_t>(keyCode_) < KEY_MAP_SIZE &&
		ImGui::IsKeyPressed(InputUtil::KeyCodeToImGuiKey(KEY_MAP[keyCode_].Code), false);
}

bool KeyBind::IsDown() const noexcept
{
	if (keyCode_ == NONE)
		return false;

	if (keyCode_ == MOUSEWHEEL_DOWN)
		return ImGui::GetIO().MouseWheel < 0.0f;

	if (keyCode_ == MOUSEWHEEL_UP)
		return ImGui::GetIO().MouseWheel > 0.0f;

	if (keyCode_ >= MOUSE1 && keyCode_ <= MOUSE5)
		return ImGui::IsMouseDown(KEY_MAP[keyCode_].Code);

	return static_cast<std::size_t>(keyCode_) < KEY_MAP_SIZE &&
		ImGui::IsKeyDown(InputUtil::KeyCodeToImGuiKey(KEY_MAP[keyCode_].Code));
}

bool KeyBind::SetToPressedKey() noexcept
{
	if (ImGui::IsKeyPressed(ImGuiKey_Escape))
	{
		keyCode_ = NONE;
		return true;
	}

	const float wheel = ImGui::GetIO().MouseWheel;
	if (wheel < -0.1f)
	{
		keyCode_ = MOUSEWHEEL_DOWN;
		return true;
	}
	if (wheel > 0.1f)
	{
		keyCode_ = MOUSEWHEEL_UP;
		return true;
	}

	constexpr std::pair<ImGuiMouseButton, KeyCode> mouseButtons[] = {
		{ImGuiMouseButton_Left, MOUSE1},
		{ImGuiMouseButton_Right, MOUSE2},
		{ImGuiMouseButton_Middle, MOUSE3},
		{3, MOUSE4},
		{4, MOUSE5}
	};

	for (const auto& [imguiButton, ourBtn] : mouseButtons)
	{
		if (ImGui::IsMouseClicked(imguiButton))
		{
			keyCode_ = ourBtn;
			return true;
		}
	}

	constexpr KeyCode modifierKeys[] = {LSHIFT, LALT, LCTRL};
	for (const auto key : modifierKeys)
	{
		if (static_cast<size_t>(key) < KEY_MAP_SIZE &&
			(GetKeyState(KEY_MAP[static_cast<size_t>(key)].Code) & 0x8000) != 0)
		{
			keyCode_ = key;
			return true;
		}
	}

	for (int i = ImGuiKey_NamedKey_BEGIN; i < ImGuiKey_NamedKey_END; ++i)
	{
		const auto imguiKey = static_cast<ImGuiKey>(i);
		if (ImGui::IsKeyPressed(imguiKey, false))
		{
			if (imguiKey == ImGuiKey_ModShift || imguiKey == ImGuiKey_ModCtrl ||
				imguiKey == ImGuiKey_ModAlt || imguiKey == ImGuiKey_ModSuper)
			{
				continue;
			}

			for (size_t j = 0; j < KEY_MAP_SIZE; ++j)
			{
				if (InputUtil::KeyCodeToImGuiKey(KEY_MAP[j].Code) == imguiKey)
				{
					keyCode_ = static_cast<KeyCode>(j);

					if (keyCode_ == LCTRL && ImGui::IsKeyDown(ImGuiKey_RightAlt))
					{
						keyCode_ = RALT;
					}
					return true;
				}
			}
		}
	}

	return false;
}

void KeyBindToggle::HandleToggle() noexcept
{
	if (IsPressed())
		toggledOn_ = !toggledOn_;
}
