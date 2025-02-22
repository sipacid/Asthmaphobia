#pragma once
#include "source/common.h"

namespace Asthmaphobia
{
	class ConfigManager
	{
	public:
		ConfigManager();
		~ConfigManager();
		static void LoadConfig();
		static void SaveConfig();
	};

	inline ConfigManager* configManager{};
}
