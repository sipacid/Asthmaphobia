#pragma once
#include "sdk.h"

namespace SDK
{
	struct PCFlashlightFields
	{
		MonoBehaviourPunFields MonoBehaviourPunFields; // MonoBehaviourPun derived class field
		Light* Headlight; // Light
		void* PCPropGrab; // PCPropGrab
		Player* Player; // Player
		void* Source; // AudioSource
		bool Field4;
		Torch* Field5; // Torch
		float Field6;
		float Field7;
		void* Field8; // PCFlashlight.???
		bool Field9;
	};

	struct PCFlashlight
	{
		void* Clazz; // PCFlashlightClass
		void* Monitor; // MonitorData
		PCFlashlightFields Fields;
	};

	DECLARE_FUNCTION_POINTER(PCFlashlight_Update, void(*)(PCFlashlight* pcFlashLight, MethodInfo* methodInfo), 0x94A310);
}
