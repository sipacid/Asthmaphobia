#pragma once
#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <Windows.h>

#include "gamestate.h"
#include "config/config.h"
#include "feature/feature.h"
#include "helper/helper.h"
#include "logger/logger.h"
#include "renderer/renderer.h"
#include "memory.h"
#include "notifications/notifications.h"

namespace Asthmaphobia
{
	inline HMODULE globalModule{};
	inline bool globalRunning{true};
	inline float dpiScale = GetDpiForSystem() / 96.0f;

	inline auto cheatName =
#ifdef _DEBUG
		"[DEV] Asthmaphobia";
#else
		"Asthmaphobia";
#endif

	inline auto buildDate = __DATE__;
	inline auto buildTime = __TIME__;
	inline auto creditsText = "Made with love by Evelien [sipacid.com]";
}
