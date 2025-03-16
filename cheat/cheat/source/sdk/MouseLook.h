#pragma once
#include "sdk.h"

namespace SDK
{
	struct MouseLookFields
	{
		float XSensitivity;
		float YSensitivity;
		bool ClampVerticalRotation;
		float MinimumX;
		float MaximumX;
		bool Smooth;
		float SmoothTime;
		bool LockCursor;
		Quaternion m_CharacterTargetRotation;
		Quaternion m_CameraTargetRotation;
		bool m_CursorIsLocked;
		float HorizontalLook;
		float VerticalLook;
	};

	struct MouseLook
	{
		void* Clazz;
		void* Monitor;
		MouseLookFields Fields;
	};
}
