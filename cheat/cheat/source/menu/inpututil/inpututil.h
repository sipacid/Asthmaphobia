#pragma once
#include <string>
#include "../../../libraries/imgui/imgui.h"

namespace InputUtil
{
	ImGuiKey KeyCodeToImGuiKey(int code) noexcept;
}

class KeyBind
{
public:
	enum KeyCode : unsigned char
	{
		APOSTROPHE = 0,
		COMMA,
		MINUS,
		PERIOD,
		SLASH,
		KEY_0,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		SEMICOLON,
		EQUALS,
		A,
		ADD,
		B,
		BACKSPACE,
		C,
		CAPSLOCK,
		D,
		DECIMAL,
		DEL,
		DIVIDE,
		DOWN,
		E,
		END,
		ENTER,
		F,
		F1,
		F10,
		F11,
		F12,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		G,
		H,
		HOME,
		I,
		INSERT,
		J,
		K,
		L,
		LALT,
		LCTRL,
		LEFT,
		LSHIFT,
		M,
		MOUSE1,
		MOUSE2,
		MOUSE3,
		MOUSE4,
		MOUSE5,
		MULTIPLY,
		MOUSEWHEEL_DOWN,
		MOUSEWHEEL_UP,
		N,
		NONE,
		NUMPAD_0,
		NUMPAD_1,
		NUMPAD_2,
		NUMPAD_3,
		NUMPAD_4,
		NUMPAD_5,
		NUMPAD_6,
		NUMPAD_7,
		NUMPAD_8,
		NUMPAD_9,
		O,
		P,
		PAGE_DOWN,
		PAGE_UP,
		Q,
		R,
		RALT,
		RCTRL,
		RIGHT,
		RSHIFT,
		S,
		SPACE,
		SUBTRACT,
		T,
		TAB,
		U,
		UP,
		V,
		W,
		X,
		Y,
		Z,
		LEFTBRACKET,
		BACKSLASH,
		RIGHTBRACKET,
		BACKTICK,

		MAX
	};

	KeyBind() : keyCode_(NONE)
	{
	}

	explicit KeyBind(const std::string& keybind) : KeyBind(keybind.c_str())
	{
	}

	explicit KeyBind(KeyCode keyCode) noexcept;
	explicit KeyBind(const char* keyName) noexcept;

	bool operator==(const KeyCode keyCode) const noexcept { return this->keyCode_ == keyCode; }
	friend bool operator==(const KeyBind& a, const KeyBind& b) noexcept { return a.keyCode_ == b.keyCode_; }

	[[nodiscard]] const char* ToString() const noexcept;
	[[nodiscard]] int ToInt() const noexcept;
	[[nodiscard]] bool IsPressed() const noexcept;
	[[nodiscard]] bool IsDown() const noexcept;
	[[nodiscard]] bool IsSet() const noexcept { return keyCode_ != NONE; }

	bool SetToPressedKey() noexcept;

private:
	KeyCode keyCode_ = NONE;
};

class KeyBindToggle : public KeyBind
{
public:
	using KeyBind::KeyBind;

	void HandleToggle() noexcept;
	[[nodiscard]] bool IsToggled() const noexcept { return toggledOn_; }

private:
	bool toggledOn_ = true;
};
