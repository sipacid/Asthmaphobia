#pragma once
#include <cstdint>

#include "sdk.h"

namespace SDK
{
	struct PhysicsCharacterControllerFields
	{
		MonoBehaviourFields MonoBehaviourFields; // MonoBehaviour derived class field
		RaycastHit Field0;
		Vector3 Field1;
		float Field2;
		bool Field3;
		Vector3 Field4;
		bool Field5;
		float Field6;
		int32_t Field7; // LayerMask
		int32_t Field8;
		int32_t Field9; // const
		void* Field10; // RaycastHit[]
		void* Field12; // Collider[]
		RaycastHit Field13;
		Vector3 Field14;
		Vector3 Field15;
		Rigidbody* Rigidbody;
		void* Collider; // CapsuleCollider
		int32_t MaxIterationCount;
		int32_t NumPenetrationProbes;
		float MinMoveDistance;
	};

	struct PhysicsCharacterController
	{
		void* Clazz; // PhysicsCharacterControllerClass
		void* Monitor; // MonitorData
		PhysicsCharacterControllerFields Fields;
	};
}
