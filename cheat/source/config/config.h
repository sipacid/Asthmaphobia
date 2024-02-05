#pragma once
#include "source/common.h"

namespace Asthmaphobia
{
	class ConfigManager
	{
	public:
		ConfigManager();
		~ConfigManager();
		static std::string GetConfigDirectoryPath();
		static void LoadConfig();
		static void SaveConfig();

	private:
		static bool ConfigDirectoryExists();
		static void CreateConfigDirectory();
	};

	inline ConfigManager* configManager{};
}
