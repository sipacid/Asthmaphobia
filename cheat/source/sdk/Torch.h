#pragma once
#include "sdk.h"

namespace SDK
{
	struct PropFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		void* Field0; // PhotonObjectInteract
		bool KinematicOnStart;
		bool HostOnlyPhysics;
		float RequiredImpactForce;
		bool Field4;
		void* ImpactClips; // AudioClip[]
		void* OnImpact; // UnityEvent
	};

	struct LayerMask
	{
		int32_t m_Mark;
	};

	struct Ray
	{
		Vector3 m_Origin;
		Vector3 m_Direction;
	};

	struct RaycastHit
	{
		Vector3 m_Point;
		Vector3 m_Normal;
		UINT m_FaceID;
		float m_Distance;
		Vector2 m_UV;
		int m_Collider;
	};

	struct EquipmentFields
	{
		PropFields PropFields;
		void* Field0; // StoreItem
		bool Field1;
		bool Field2;
		bool Field3;
		bool Field4;
		Vector3 Field5; // Vector3
		Vector3 Field6; // Vector3
		LayerMask Field7; // LayerMask
		float Field8;
		float Field9;
		bool Field10;
		Transform* Field11; // Transform
		Transform* Field12; // Transform
		Transform* Field13; // Transform
		void* Field14; // Renderer[]
		Vector3 Field15; // Vector3
		Vector3 Field16; // Vector3
		bool Field17;
		bool Field18;
		bool Field19;
		bool Field20;
		void* Field21; // Tripod
		bool Field22;
		bool Field23;
		bool Field24;
		void* Field25; // Noise
		void* Field26; // AudioClip
		void* Field27; // AudioClip
		bool Field28;
		bool Field29;
		bool Field30;
		bool Field31;
		void* Field32; // Sequence
		bool Field33;
		float Field34; // range 0.0f - 3f
		void* Field35; // TierSocket
		Ray Field36; // Ray
		RaycastHit Field37; // RaycastHit
		String* Field38; // String
		String* Field39; // String
	};

	struct TorchFields
	{
		EquipmentFields EquipmentFields;
		Light* Field0; // Light
		int32_t Field1; // Torch.???; torchType: normal, blacklight, infrared
		void* GlowRends; // Renderer[]
		void* UVSensor; // Sensor
		Transform* VRBeltAttach; // Transform
		LevelController* Field5; // LevelController
		Transform* Field6; // Transform
		float Field7;
		float Field8;
		bool Field9;
	};

	struct Torch
	{
		void* Clazz; // TorchClass
		void* Monitor; // MonitorData
		TorchFields Fields;
	};

	DECLARE_FUNCTION_POINTER(Torch_Update, void(*)(Torch* torch, MethodInfo* methodInfo), 0x5D1850);
}
