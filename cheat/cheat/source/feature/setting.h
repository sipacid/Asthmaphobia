#pragma once
#include <string_view>
#include <unordered_map>
#include <variant>
#include <vector>
#include "libraries/imgui/imgui.h"
#include "libraries/json/json.hpp"
#include "source/menu/inpututil/InputUtil.h"

namespace Asthmaphobia
{
	struct StringViewHash
	{
		using IsTransparent = void;

		size_t operator()(const std::string_view sv) const
		{
			return std::hash<std::string_view>{}(sv);
		}
	};

	class Setting
	{
	public:
		Setting(std::string name, std::string description,
		        std::variant<bool, int, float, std::string, ImColor, KeyBindToggle> value) noexcept
			: Name(std::move(name)), Description(std::move(description)), Value(std::move(value))
		{
		}

		[[nodiscard]] std::string_view GetName() const noexcept { return Name; }
		[[nodiscard]] std::string_view GetDescription() const noexcept { return Description; }
		[[nodiscard]] const auto& GetValue() const noexcept { return Value; }
		auto& GetValue() noexcept { return Value; }

		void SetValue(const auto& value) noexcept { Value = value; }

	private:
		std::string Name;
		std::string Description;
		std::variant<bool, int, float, std::string, ImColor, KeyBindToggle> Value;
	};

	class Settings
	{
	public:
		Settings()
		{
		}

		void AddSetting(std::shared_ptr<Setting> setting)
		{
			const auto idx = SettingsVector.size();
			SettingsVector.emplace_back(std::move(setting));
			SettingsMap.emplace(SettingsVector.back()->GetName(), idx);
		}

		[[nodiscard]] const auto& GetSettings() const noexcept { return SettingsVector; }

		[[nodiscard]] const auto& GetSetting(const std::string_view name) const
		{
			if (const auto it = SettingsMap.find(name); it != SettingsMap.end())
			{
				return SettingsVector[it->second];
			}
			throw std::invalid_argument("Setting not found");
		}

	private:
		std::vector<std::shared_ptr<Setting>> SettingsVector;
		std::unordered_map<std::string_view, size_t, StringViewHash> SettingsMap;
	};
}
