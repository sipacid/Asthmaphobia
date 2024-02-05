#pragma once
#include "sdk.h"

namespace SDK
{
	struct LevelController;

	struct GameControllerFields
	{
		MonoBehaviourPunCallbacksFields MonoBehaviourPunCallbacksFields; // MonoBehaviourPunCallbacks derived class field
		void* Field0; // UnityEvent
		void* Field1; // UnityEvent
		void* Field2; // UnityEvent
		void* Field3; // UnityEvent
		void* Field4; // UnityEvent
		void* Field5; // ???
		void* Field6; // UnityEvent
		void* Field7; // UnityEvent
		void* Field8; // ???
		void* Field9; // ???
		void* Field10; // ???
		float Field11;
		void* Field12; // SpeechRecognitionController
		LevelController* LevelController; // LevelController
		void* Field14; // MultiplayerController
		bool Field15;
		int Field16;
		void* Field17; // Material
		bool Field18;
		void* Field19; // SpeechRecognizer
	};

	struct GameController
	{
		void* Clazz; // GameControllerClass
		void* Monitor; // MonitorData
		GameControllerFields Fields;
	};

	DECLARE_FUNCTION_POINTER(GameController_Exit, void(*)(GameController* gameController, void* photoMessageInfo, MethodInfo* methodInfo), 0x18B5B60);
	DECLARE_FUNCTION_POINTER(GameController_GetAveragePlayerInsanity, float(*)(GameController* gameController, MethodInfo* methodInfo), 0x18B5CD0);
}
