#pragma once
#include "sdk.h"

namespace SDK
{
	struct Key
	{
	};

	DECLARE_FUNCTION_POINTER(Key_Start, void(*)(Key* key, MethodInfo* methodInfo), 0x210CCA0);
	DECLARE_FUNCTION_POINTER(Key_GrabbedKey, void(*)(Key* key, MethodInfo* methodInfo), 0x210CB90);
}
