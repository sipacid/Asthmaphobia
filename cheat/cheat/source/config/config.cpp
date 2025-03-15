#include "config.h"

namespace Asthmaphobia::Config
{
	void LoadConfig()
	{
		Helper::CreateAsthmaphobiaDirectory();

		using Json = nlohmann::json;
		const auto configPath = Helper::GetAsthmaphobiaDirectory() + "\\config.json";

		if (!std::filesystem::exists(configPath))
			return;

		std::ifstream f(configPath);
		Json data = Json::parse(f);

		for (const auto& features = GetFeatureManagerInstance().GetFeatures(); const auto& feature : features)
		{
			auto settings = feature.second->GetSettings()->GetSettings();
			auto featureName = feature.first;
			if (!data.contains(featureName))
				continue;

			for (auto& setting : settings)
			{
				const auto settingName = setting->GetName();
				if (!data[featureName].contains(settingName))
					continue;

				switch (const auto settingValue = data[featureName][settingName]; settingValue.type())
				{
				case Json::value_t::boolean:
					setting->SetValue(settingValue.get<bool>());
					break;
				case Json::value_t::number_unsigned:
					setting->SetValue(settingValue.get<int>());
					break;
				case Json::value_t::number_float:
					setting->SetValue(settingValue.get<float>());
					break;
				case Json::value_t::string:
					setting->SetValue(settingValue.get<std::string>());
					break;
				case Json::value_t::object:
					setting->SetValue(ImColor(settingValue["x"].get<float>(), settingValue["y"].get<float>(),
					                          settingValue["z"].get<float>(), settingValue["w"].get<float>()));
					break;
				default:
					throw std::runtime_error("Failed to convert JSON value to appropriate type");
				}
			}
		}

		f.close();
	}

	void SaveConfig()
	{
		const auto configPath = Helper::GetAsthmaphobiaDirectory() + "\\config.json";

		using Json = nlohmann::json;
		Json data;
		for (const auto& features = GetFeatureManagerInstance().GetFeatures(); const auto& feature : features)
		{
			auto settings = feature.second->GetSettings()->GetSettings();
			auto featureName = feature.first;

			Json featureJson;
			for (auto& setting : settings)
			{
				auto settingName = setting->GetName();
				auto settingValue = setting->GetValue();

				Json settingJson;
				if (std::holds_alternative<bool>(settingValue))
				{
					settingJson = std::get<bool>(settingValue);
				}
				else if (std::holds_alternative<int>(settingValue))
				{
					settingJson = std::get<int>(settingValue);
				}
				else if (std::holds_alternative<float>(settingValue))
				{
					settingJson = std::get<float>(settingValue);
				}
				else if (std::holds_alternative<std::string>(settingValue))
				{
					settingJson = std::get<std::string>(settingValue);
				}
				else if (std::holds_alternative<ImColor>(settingValue))
				{
					settingJson = Json{
						{"x", std::get<ImColor>(settingValue).Value.x},
						{"y", std::get<ImColor>(settingValue).Value.y},
						{"z", std::get<ImColor>(settingValue).Value.z},
						{"w", std::get<ImColor>(settingValue).Value.w},
					};
				}
				else
				{
					throw std::runtime_error("Failed to convert setting value to JSON");
				}

				featureJson[settingName] = settingJson;
			}

			data[featureName] = featureJson;
		}

		std::ofstream f(configPath);
		f << data.dump(4);
		f.close();
	}
}
