#pragma once
#include "sdk.h"

namespace SDK
{
	struct Player;

	struct PlayerStaminaFields
	{
		MonoBehaviourFields MonoBehaviourFields; // MonoBehaviour derived class field
		void* OutOfStaminaSource; // AudioSource
		void* OutOfBreathMale; // AudioClip[]
		void* OutOfBreathFemale; // AudioClip[]
		Player* Player; // Player
		bool MaleSoundsOverride;
		bool FemaleSoundsOverride;
		bool Field6;
		bool Field7;
		bool Field8;
		bool Field9;
		bool Field10;
		bool Field11;
		bool Field12;
		bool Field13;
		bool Field14;
		bool Field15;
		float Field17;
		float Field18;
		float Field19;
		void* Field20; // UnityEvent
		void* Field21; // UnityEvent
	};

	struct PlayerStamina
	{
		void* Clazz; // PlayerStaminaClass
		void* Monitor; // MonitorData
		PlayerStaminaFields Fields;
	};

	DECLARE_FUNCTION_POINTER(PlayerStamina_Update, void (*)(PlayerStamina* playerStamina, MethodInfo* methodInfo), 0xA3A3D0);
}
