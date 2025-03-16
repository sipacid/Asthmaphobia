#pragma once
#include "sdk.h"

namespace SDK
{
	DECLARE_METHOD_POINTER(Marshal_PtrToStringAnsi, String* (*)(void* pointer, MethodInfo* methodInfo), "mscorlib", "System.Runtime.InteropServices", "Marshal", "PtrToStringAnsi",
	                       1);
}
