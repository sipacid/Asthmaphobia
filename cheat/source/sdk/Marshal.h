#pragma once
#include "sdk.h"

namespace SDK
{
	// mscorlib.System.Runtime.InteropServices.Marshal
	DECLARE_FUNCTION_POINTER(Marshal_PtrToStringAnsi, String* (*)(void* pointer, MethodInfo* methodInfo), 0x32EB6D0);
}
