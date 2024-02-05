#pragma once
#include "sdk.h"

namespace SDK
{
	struct PCDisablePlayerComponentsFields
	{
		MonoBehaviourPunFields MonoBehaviourPunFields;
		void* CharacterModels; // GameObject[]
		void* LeftHandRend; // Renderer
		void* RightHandRend; // Renderer
		void* HandMaterials; // Material[]
		void* PlayerHead; // GameObject
		Camera* ShadowCamera; // Camera
		Player* Player; // PLayer
		void* CharacterModelsHandJoint; // FixedJoint[]
		void* MultiplayerOnlyObjects; // GameObject[]
		Light* ShoulderFlashlightLight; // Light
		bool Field10;
		void* TransformViews; // PhotonTransformView[]
		void* PCCanvas; // Canvas
	};

	struct PCDisablePlayerComponents
	{
		void* Clazz; // PCDisablePlayerComponentsClass
		void* Monitor; // MonitorData
		PCDisablePlayerComponentsFields Fields;
	};

	DECLARE_FUNCTION_POINTER(PCDisablePlayerComponents_Start, void(*)(PCDisablePlayerComponents* pcDisablePlayerComponents, MethodInfo* methodInfo), 0x86B180);
}
