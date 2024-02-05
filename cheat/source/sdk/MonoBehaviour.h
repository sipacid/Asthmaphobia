#pragma once
#include "sdk.h"

namespace SDK
{
	struct __declspec(align(8)) Object1Fields
	{
		void* m_CachedPtr;
		void* m_CancellationTokenSource;
	};

	struct Component1Fields
	{
		Object1Fields _;
	};

	struct BehaviourFields
	{
		Component1Fields _;
	};

	struct MonoBehaviourFields
	{
		BehaviourFields _;
	};

	struct MonoBehaviour
	{
		void* Clazz; // MonoBehaviourClass
		void* Monitor; // MonitorData
		MonoBehaviourFields Fields;
	};

	struct MonoBehaviourPunFields
	{
		MonoBehaviourFields _;
		void* pvCache;
	};

	struct MonoBehaviourPunCallbacksFields
	{
		MonoBehaviourPunFields _;
	};
}
