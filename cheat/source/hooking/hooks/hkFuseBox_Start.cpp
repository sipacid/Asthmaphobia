#include "source/common.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkFuseBox_Start(SDK::FuseBox* fuseBox, SDK::MethodInfo* methodInfo)
{
	DEBUG_LOG("Called FuseBox_Start");
	if (!globalRunning)
		return SDK::FuseBox_Start_ptr(fuseBox, methodInfo);

	GameState::fuseBox = fuseBox;
	SDK::FuseBox_Start_ptr(fuseBox, methodInfo);
}
