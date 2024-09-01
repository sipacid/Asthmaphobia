#pragma once
#include "sdk.h"

namespace SDK
{
	struct Key
	{
	};

	DECLARE_FUNCTION_POINTER(Key_Start, void(*)(Key* key, MethodInfo* methodInfo), 0x1BB1AD0);
	DECLARE_FUNCTION_POINTER(Key_GrabbedKey, void(*)(Key* key, MethodInfo* methodInfo), 0x1BB19C0);
}
