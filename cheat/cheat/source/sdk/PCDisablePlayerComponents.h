#pragma once
#include "sdk.h"

namespace SDK
{
	struct PCDisablePlayerComponentsFields
	{
		MonoBehaviourPunFields MonoBehaviourPunFields;
		void* CharacterModels;
		void* LeftHandRend;
		void* RightHandRend;
		void* HandMaterials;
		void* PlayerHead;
		void* ShadowCamera;
		void* Player;
		void* CharacterModelsHandJoints;
		void* MultiplayerOnlyObjects;
		Light* ShoulderFlashLight;
		bool Field0;
		void* TransformViews;
		void* PCCanvas;
	};

	struct PCDisablePlayerComponents
	{
		void* Clazz;
		void* Monitor;
		PCDisablePlayerComponentsFields Fields;
	};

	DECLARE_METHOD_POINTER(PCDisablePlayerComponents_Start, void(*)(SDK::PCDisablePlayerComponents* pcDisablePlayerComponents, SDK::MethodInfo* methodInfo), "Assembly-CSharp", "",
	                       "PCDisablePlayerComponents", "Start", 0)
}
