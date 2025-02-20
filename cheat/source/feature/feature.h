#pragma once
#include "source/common.h"
#include "setting.h"
#include "libraries/imgui/imgui.h"

namespace Asthmaphobia
{
	enum FeatureCategory : uint8_t
	{
		Visuals,
		Players,
		Ghost,
		CursedItems,
		Miscellaneous,
		Movement,
	};

	const char* FeatureTypeToString(FeatureCategory category);

	class Feature
	{
	public:
		explicit Feature(std::string name, std::string description, const FeatureCategory category) : Name(std::move(name)), Description(std::move(description)), Category(category)
		{
			Settings_ = std::make_unique<Settings>();
			EnabledSetting = std::make_shared<Setting>("Enabled", "Enables or disables this feature", false);
			Settings_->AddSetting(EnabledSetting);
		}

		virtual ~Feature() = default;
		virtual void OnEnable() = 0;
		virtual void OnDisable() = 0;
		virtual void OnDraw() = 0;
		virtual void OnMenu() = 0;

		[[nodiscard]] const std::string& GetName() const { return Name; }
		[[nodiscard]] const std::string& GetDescription() const { return Description; }
		[[nodiscard]] FeatureCategory GetCategory() const { return Category; }
		[[nodiscard]] bool IsEnabled() const { return std::get<bool>(EnabledSetting->GetValue()); }
		std::unique_ptr<Settings>& GetSettings() { return Settings_; }

		bool ShouldDrawSection = true;

	protected:
		std::string Name;
		std::string Description;
		FeatureCategory Category;
		std::shared_ptr<Setting> EnabledSetting;
		std::unique_ptr<Settings> Settings_;
	};

	class FeatureManager
	{
	public:
		FeatureManager();
		~FeatureManager();

		void AddFeature(const std::string& name, Feature* feature);
		[[nodiscard]] const std::unordered_map<std::string, Feature*>& GetFeatures() const { return Features; }
		[[nodiscard]] Feature* GetFeatureByName(const std::string& name) const;
		void OnDraw() const;
		void OnMenu() const;

	private:
		std::unordered_map<std::string, Feature*> Features;
	};

	inline FeatureManager* featureManager{};
}
