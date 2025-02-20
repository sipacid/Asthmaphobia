#include "source/common.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkFuseBox_Start(SDK::FuseBox* fuseBox, SDK::MethodInfo* methodInfo)
{
	LOG_DEBUG("Called FuseBox_Start");
	SDK::FuseBox_Start_ptr(fuseBox, methodInfo);

	if (globalRunning)
		GameState::fuseBox = fuseBox;
}
