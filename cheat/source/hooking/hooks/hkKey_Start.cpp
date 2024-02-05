#include "source/common.h"
#include "source/feature/miscellaneous/autokey/autokey.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkKey_Start(SDK::Key* key, SDK::MethodInfo* methodInfo)
{
	DEBUG_LOG("Called Key_Start");
	if (!globalRunning)
		return SDK::Key_Start_ptr(key, methodInfo);

	dynamic_cast<Features::Miscellaneous::AutoKey*>(featureManager->GetFeatureByName("Miscellaneous::AutoKey"))->OnKey_Start(key, methodInfo);
}
