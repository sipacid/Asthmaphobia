#pragma once
#include "sdk.h"

namespace SDK
{
	struct Player;

	struct PlayerStaminaFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		void* OutOfStaminaSource; // AudioSource
		void* OutOfBreathMale; // AudioClip[]
		void* OutOfBreathFemale; // AudioClip[]
		Player* Player;
		bool MaleSoundsOverride;
		bool FemaleSoundsOverride;
		bool IsMoving;
		bool CanSprint;
		bool IsSprinting;
		bool IsWalking;
		bool Draining;
		bool CanDrainStamina;
		bool NewIsSprinting;
		bool NewIsWalking;
		bool StaminaDrained;
		bool Delayed;
		float CurrentStaminaRecharge;
		float CurrentStamina;
		float RestoreDelay;
		void* OnStaminaDrained; // UnityEvent
		void* OnStaminaRestored; // UnityEvent
	};

	struct PlayerStamina
	{
		void* Clazz;
		void* Monitor;
		PlayerStaminaFields Fields;
	};

	DECLARE_METHOD_POINTER(PlayerStamina_Update, void (*)(PlayerStamina* playerStamina, MethodInfo* methodInfo), "Assembly-CSharp", "", "PlayerStamina", "Update", 0);
}
