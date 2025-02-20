#pragma once
#include "libraries/imgui/imgui.h"

namespace Asthmaphobia::Notifications
{
	enum class NotificationType : uint8_t
	{
		Info,
		Warning,
		Error
	};

	struct Notification
	{
		std::string Message;
		NotificationType Type;
		float LifeTime;
	};

	inline std::vector<Notification> notifications;

	inline void AddNotification(const std::string& message, const NotificationType type, const float lifeTime)
	{
		notifications.push_back({.Message = message, .Type = type, .LifeTime = lifeTime});
	}

	inline void UpdateNotifications()
	{
		const auto deltaTime = ImGui::GetIO().DeltaTime;
		std::erase_if(notifications, [deltaTime](Notification& notification)
		{
			notification.LifeTime -= deltaTime;
			return notification.LifeTime <= 0.0f;
		});
	}

	inline void RenderNotifications()
	{
		UpdateNotifications();
		if (notifications.empty())
			return;

		const ImGuiIO& io = ImGui::GetIO();
		const ImVec2 screenSize = io.DisplaySize;

		constexpr ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize;
		for (int index = 0; index < notifications.size(); index++)
		{
			const auto& notification = notifications[index];

			ImGui::SetNextWindowPos(ImVec2(screenSize.x - 10.0f, 10.0f + 50.0f * index), ImGuiCond_Always, ImVec2(1.0f, 0.0f));
			ImGui::Begin(std::format("Notifications##{}", index).c_str(), nullptr, windowFlags);

			ImVec4 textColor;
			switch (notification.Type)
			{
			case NotificationType::Info:
				textColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
				break;
			case NotificationType::Warning:
				textColor = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
				break;
			case NotificationType::Error:
				textColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
				break;
			}

			ImGui::TextColored(textColor, "%s", notification.Message.c_str());
			ImGui::End();
		}
	}
}
