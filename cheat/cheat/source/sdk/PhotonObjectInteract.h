#pragma once
#include "sdk.h"

namespace SDK
{
	struct Door;

	struct PhotonObjectInteractFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		void* Field0; // PhotonView
		void* Field1; // PhotonTransformView
		void* Field2; // VRGrabbable
		Rigidbody* Field3;
		bool Field4;
		bool Field5;
		bool Field6;
		bool Field7;
		bool Field8;
		bool Field9;
		bool Field10;
		void* Field11; // Drawer
		Door* Field12;
		void* Field13; // Collider[]
		void* Field14; // Collider[]
		void* Field15; // Collider[]
		float Field16;
		Transform* Field17;
		void* Field18; // UnityEvent
		void* Field19; // UnityEvent
		void* Field20; // UnityEvent
		void* Field21; // UnityEvent
		void* Field22; // UnityEvent
		void* Field23; // UnityEvent
		void* Field24; // UnityEvent
		void* Field25; // UnityEvent
		void* Field26; // UnityEvent
		bool Field27;
		bool Field28;
		bool Field29;
		GameObject* Field30;
		void* Field31; // List<GameObject>
		Vector3 Field32;
		Quaternion Field33;
		Vector3 Field34;
		Vector3 Field35;
		GameObject* Field36;
		GameObject* Field37;
		Transform* Field38;
	};

	struct PhotonObjectInteract
	{
		void* Clazz;
		void* Monitor;
		PhotonObjectInteractFields Fields;
	};

	DECLARE_METHOD_POINTER(PhotonObjectInteract_Start, void(*)(PhotonObjectInteract* photonObjectInteract, MethodInfo* methodInfo), "Assembly-CSharp", "", "PhotonObjectInteract", "Start", 0);
}