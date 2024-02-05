#pragma once
#include <unordered_map>
#include <variant>
#include <vector>

#include "libraries/imgui/imgui.h"
#include "libraries/json/json.hpp"

namespace Asthmaphobia
{
	class Setting
	{
	public:
		Setting(std::string name, std::string description, const std::variant<bool, int, float, std::string, ImColor>& value) : Name(std::move(name)),
			Description(std::move(description)),
			Value(value)
		{
		}

		[[nodiscard]] const std::string& GetName() const { return Name; }
		[[nodiscard]] const std::string& GetDescription() const { return Description; }
		std::variant<bool, int, float, std::string, ImColor>& GetValue() { return Value; }
		void SetValue(const std::variant<bool, int, float, std::string, ImColor>& value) { Value = value; }

	private:
		std::string Name;
		std::string Description;
		std::variant<bool, int, float, std::string, ImColor> Value;
	};

	class Settings
	{
	public:
		Settings()
		{
			SettingsVector.reserve(100); // Reserve some space to avoid reallocation.
			SettingsMap = std::unordered_map<std::string, std::size_t>();
		}

		~Settings()
		{
			for (auto& setting : SettingsVector)
			{
				setting.reset();
			}
		}

		void AddSetting(const std::shared_ptr<Setting>& setting)
		{
			SettingsVector.push_back(setting);
			SettingsMap[SettingsVector.back()->GetName()] = SettingsVector.size() - 1;
		}

		[[nodiscard]] const std::vector<std::shared_ptr<Setting>>& GetSettings() const { return SettingsVector; }

		[[nodiscard]] const std::shared_ptr<Setting>& GetSetting(const std::string& name) const
		{
			const auto it = SettingsMap.find(name);
			if (it == SettingsMap.end())
			{
				throw std::invalid_argument("Setting not found: " + name);
			}

			return SettingsVector[it->second];
		}

	private:
		std::vector<std::shared_ptr<Setting>> SettingsVector;
		std::unordered_map<std::string, std::size_t> SettingsMap;
	};
}
