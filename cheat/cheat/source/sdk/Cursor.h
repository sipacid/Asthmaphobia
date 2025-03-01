#pragma once
#include "sdk.h"

namespace SDK
{
	enum class CursorLockMode
	{
		None,
		Locked,
		Confined
	};

	// UnityEngine.CoreModule.UnityEngine.Cursor
	struct Cursor
	{
	};

	DECLARE_FUNCTION_POINTER(Cursor_Set_Visible, void(*)(bool visible, MethodInfo* methodInfo), 0x4776560);
	DECLARE_FUNCTION_POINTER(Cursor_Get_LockState, CursorLockMode(*)(MethodInfo* methodInfo), 0x47764F0);
	DECLARE_FUNCTION_POINTER(Cursor_Set_LockState, void(*)(CursorLockMode mode, MethodInfo* methodInfo), 0x4776520);
}
