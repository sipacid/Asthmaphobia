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
		float FadeInTime = 0.3f;
		float FadeOutTime = 0.3f;
		float Alpha = 0.0f;
		float SlideOffset = 50.0f;
	};

	inline std::vector<Notification> notifications;

	/// Add a notification to render.
	/// @param message		The notification message you want to display.
	/// @param type			The type of notification. Info, Warning or Error.
	/// @param lifeTime		The time the notification should be visible for.
	inline void AddNotification(const std::string& message, const NotificationType type, const float lifeTime)
	{
		Notification notification;
		notification.Message = message;
		notification.Type = type;
		notification.LifeTime = lifeTime;
		notification.Alpha = 0.0f;
		notification.SlideOffset = 50.0f;
		notifications.push_back(notification);
	}

	/// Updates the properties of all notifications. Remove if necessary.
	inline void UpdateNotifications()
	{
		const auto deltaTime = ImGui::GetIO().DeltaTime;
		std::erase_if(notifications, [deltaTime](Notification& notification)
		{
			notification.LifeTime -= deltaTime;

			// Fade in
			if (notification.LifeTime > notification.LifeTime - notification.FadeInTime)
			{
				notification.Alpha = (std::min)(1.0f, notification.Alpha + deltaTime / notification.FadeInTime);
			}

			// Fade out
			if (notification.LifeTime < notification.FadeOutTime)
			{
				notification.Alpha = (std::max)(0.0f, notification.LifeTime / notification.FadeOutTime);
			}

			// Slide animation
			notification.SlideOffset = (std::max)(0.0f, notification.SlideOffset - deltaTime * 200.0f);

			return notification.LifeTime <= 0.0f;
		});
	}

	/// Renders all notifications.
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

			ImGui::SetNextWindowPos(
				ImVec2(screenSize.x - 10.0f - notification.SlideOffset, 10.0f + 50.0f * index),
				ImGuiCond_Always,
				ImVec2(1.0f, 0.0f)
			);

			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, notification.Alpha);
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
			ImGui::PopStyleVar();
		}
	}
}
