#pragma once
#include "source/common.h"
#include "setting.h"
#include "libraries/imgui/imgui.h"

namespace Asthmaphobia
{
	enum FeatureCategory : uint8_t
	{
		Player,
		Ghost,
		World,
		CursedItems,
		Visuals,
		Exploits,
		Movement,
	};

	static const std::unordered_map<FeatureCategory, const char*> CATEGORY_TO_STRING = {
		{Player, "Player"},
		{Ghost, "Ghost"},
		{World, "World"},
		{CursedItems, "Cursed items"},
		{Visuals, "Visuals"},
		{Exploits, "Exploits"},
		{Movement, "Movement"}
	};

	class Feature
	{
	public:
		explicit Feature(const std::string_view name, const std::string_view description, const FeatureCategory category)
			: Name(name), Description(description), Category(category), Settings_(std::make_unique<Settings>())
		{
			const auto setting = std::make_shared<Setting>("Enabled", "Enables or disables this feature", false);
			EnabledSetting = setting;
			Settings_->AddSetting(setting);
		}

		Feature(const Feature&) = delete;
		Feature& operator=(const Feature&) = delete;
		Feature(Feature&&) noexcept = default;
		Feature& operator=(Feature&&) noexcept = default;
		virtual ~Feature() = default;

		virtual void OnEnable() = 0;
		virtual void OnDisable() = 0;
		virtual void OnDraw() = 0;
		virtual void OnMenu() = 0;

		[[nodiscard]] const std::string& GetName() const noexcept { return Name; }
		[[nodiscard]] const std::string& GetDescription() const noexcept { return Description; }
		[[nodiscard]] FeatureCategory GetCategory() const noexcept { return Category; }
		[[nodiscard]] bool IsEnabled() const noexcept { return std::get<bool>(EnabledSetting->GetValue()); }
		[[nodiscard]] const Settings* GetSettings() const noexcept { return Settings_.get(); }
		Settings* GetSettings() noexcept { return Settings_.get(); }

		bool ShouldDrawSection = true;

	protected:
		std::string Name;
		std::string Description;
		const FeatureCategory Category;
		std::shared_ptr<Setting> EnabledSetting;
		std::unique_ptr<Settings> Settings_;
	};

	class FeatureManager
	{
		std::unordered_map<std::string, std::unique_ptr<Feature>> Features;

	public:
		FeatureManager(const FeatureManager&) = delete;
		FeatureManager& operator=(const FeatureManager&) = delete;
		FeatureManager(FeatureManager&&) = delete;
		FeatureManager& operator=(FeatureManager&&) = delete;

		FeatureManager();
		~FeatureManager();

		void Cleanup();

		void AddFeature(std::string_view name, std::unique_ptr<Feature> feature);
		[[nodiscard]] const auto& GetFeatures() const noexcept { return Features; }
		[[nodiscard]] Feature* GetFeatureByName(std::string_view name) const;

		template <typename T>
		[[nodiscard]] T* GetFeature(const std::string_view name) const
		{
			if (auto feature = GetFeatureByName(name))
			{
				return dynamic_cast<T*>(feature);
			}
			return nullptr;
		}

		void OnDraw() const;
		void OnMenu() const;
	};

	FeatureManager& GetFeatureManagerInstance();
}
