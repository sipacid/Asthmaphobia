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

	DECLARE_METHOD_POINTER(Cursor_Set_Visible, void(*)(bool visible, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Cursor", "set_visible", 1);

	DECLARE_METHOD_POINTER(Cursor_Get_LockState, CursorLockMode(*)(MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Cursor", "get_lockState", 0);

	DECLARE_METHOD_POINTER(Cursor_Set_LockState, void(*)(CursorLockMode mode, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Cursor", "set_lockState", 1);
}
