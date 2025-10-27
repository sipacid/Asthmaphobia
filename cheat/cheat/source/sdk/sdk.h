#pragma once
#include "source/common.h"
#include <functional>
#include <Windows.h>
#include <Psapi.h>
#include <iostream>

#include "source/memory/memory.h"
#include "source/logger/logger.h"

namespace IL2CPP
{
	// IL2CPP Typedefs
	using il2cpp_domain_get_t = void* (*)();
	using il2cpp_domain_assembly_open_t = void* (*)(void* domain, const char* name);
	using il2cpp_assembly_get_image_t = void* (*)(void* assembly);
	using il2cpp_class_from_name_t = void* (*)(void* image, const char* namespaze, const char* name);
	using il2cpp_class_get_method_from_name_t = void* (*)(void* klass, const char* name, int argsCount);
	using il2cpp_string_new_utf16_t = void* (*)(const wchar_t* str, int len);

	// Function pointers
	inline il2cpp_domain_get_t il2cpp_domain_get = nullptr;
	inline il2cpp_domain_assembly_open_t il2cpp_domain_assembly_open = nullptr;
	inline il2cpp_assembly_get_image_t il2cpp_assembly_get_image = nullptr;
	inline il2cpp_class_from_name_t il2cpp_class_from_name = nullptr;
	inline il2cpp_class_get_method_from_name_t il2cpp_class_get_method_from_name = nullptr;
	inline il2cpp_string_new_utf16_t il2cpp_string_new_utf16 = nullptr;

	// Cached domain and assembly image
	inline void* domain = nullptr;
	inline void* assemblyImage = nullptr;

	inline bool InitIL2CPP()
	{
		const HMODULE gameAssembly = GetModuleHandleW(L"GameAssembly.dll");
		if (!gameAssembly)
		{
			LOG_ERROR("Failed to get GameAssembly.dll handle");
			return false;
		}

		il2cpp_domain_get = reinterpret_cast<il2cpp_domain_get_t>(GetProcAddress(gameAssembly, "il2cpp_domain_get"));
		il2cpp_domain_assembly_open = reinterpret_cast<il2cpp_domain_assembly_open_t>(GetProcAddress(gameAssembly, "il2cpp_domain_assembly_open"));
		il2cpp_assembly_get_image = reinterpret_cast<il2cpp_assembly_get_image_t>(GetProcAddress(gameAssembly, "il2cpp_assembly_get_image"));
		il2cpp_class_from_name = reinterpret_cast<il2cpp_class_from_name_t>(GetProcAddress(gameAssembly, "il2cpp_class_from_name"));
		il2cpp_class_get_method_from_name = reinterpret_cast<il2cpp_class_get_method_from_name_t>(GetProcAddress(gameAssembly, "il2cpp_class_get_method_from_name"));
		il2cpp_string_new_utf16 = reinterpret_cast<il2cpp_string_new_utf16_t>(GetProcAddress(gameAssembly, "il2cpp_string_new_utf16"));

		if (!il2cpp_domain_get)
			LOG_ERROR("Failed to get il2cpp_domain_get");
		if (!il2cpp_domain_assembly_open)
			LOG_ERROR("Failed to get il2cpp_domain_assembly_open");
		if (!il2cpp_assembly_get_image)
			LOG_ERROR("Failed to get il2cpp_assembly_get_image");
		if (!il2cpp_class_from_name)
			LOG_ERROR("Failed to get il2cpp_class_from_name");
		if (!il2cpp_class_get_method_from_name)
			LOG_ERROR("Failed to get il2cpp_class_get_method_from_name");
		if (!il2cpp_string_new_utf16)
			LOG_ERROR("Failed to get il2cpp_string_new_utf16");

		return il2cpp_domain_get && il2cpp_domain_assembly_open && il2cpp_assembly_get_image &&
			il2cpp_class_from_name && il2cpp_class_get_method_from_name && il2cpp_string_new_utf16;
	}

	inline bool InitDomain()
	{
		if (!domain)
		{
			domain = il2cpp_domain_get();
			if (!domain)
			{
				LOG_ERROR("Failed to get IL2CPP domain");
				return false;
			}
			LOG_DEBUG("Got IL2CPP domain");
		}

		void* assembly = il2cpp_domain_assembly_open(domain, "Assembly-CSharp");
		if (!assembly)
		{
			LOG_ERROR("Failed to open Assembly-CSharp");
			return false;
		}
		LOG_DEBUG("Opened Assembly-CSharp");

		assemblyImage = il2cpp_assembly_get_image(assembly);
		if (!assemblyImage)
		{
			LOG_ERROR("Failed to get assembly image");
			return false;
		}
		LOG_DEBUG("Got assembly image");

		return true;
	}

	template <typename T>
	T GetMethodPointer(const char* assemblyName, const char* namespaceName, const char* className, const char* methodName, int argsCount = 0)
	{
		void* image = assemblyImage;
		if (strcmp(assemblyName, "Assembly-CSharp") != 0)
		{
			void* assembly = il2cpp_domain_assembly_open(domain, assemblyName);
			if (!assembly)
				return nullptr;

			image = il2cpp_assembly_get_image(assembly);
			if (!image)
				return nullptr;
		}

		void* klass = il2cpp_class_from_name(image, namespaceName, className);
		if (!klass)
			return nullptr;

		void* method = il2cpp_class_get_method_from_name(klass, methodName, argsCount);
		if (!method)
			return nullptr;

		// Get the actual method pointer from the MethodInfo
		struct MethodInfo
		{
			void* methodPointer; /* other fields */
		};
		void* methodPointer = static_cast<MethodInfo*>(method)->methodPointer;

		return reinterpret_cast<T>(methodPointer);
	}

	inline std::vector<std::function<void()>> methodInitializers;

	inline bool InitializeAllMethods()
	{
		if (!InitDomain())
			return false;

		for (const auto& initializer : methodInitializers)
		{
			initializer();
		}
		return true;
	}
}

namespace SDK
{
	const auto BASE_ADDRESS = reinterpret_cast<uintptr_t>(GetModuleHandleW(L"GameAssembly.dll"));

	inline bool InitializeSDK()
	{
		LOG_DEBUG("Initializing SDK...");

		if (!IL2CPP::InitIL2CPP())
		{
			LOG_ERROR("Failed to initialize IL2CPP");
			return false;
		}
		LOG_DEBUG("IL2CPP initialized");

		LOG_DEBUG("Waiting for game to stabilize...");
		Sleep(1000);

		LOG_DEBUG("Initializing methods...");
		if (!IL2CPP::InitializeAllMethods())
		{
			LOG_ERROR("Failed to initialize methods");
			return false;
		}
		LOG_DEBUG("Methods initialized");

		return true;
	}
}

#define DECLARE_METHOD_POINTER(NAME, TYPE, ASSEMBLY, NAMESPACE, CLASS, METHOD, ARGCOUNT) \
using NAME = TYPE; \
inline NAME NAME##_ptr = nullptr; \
inline void Init_##NAME() { \
    NAME##_ptr = IL2CPP::GetMethodPointer<NAME>(ASSEMBLY, NAMESPACE, CLASS, METHOD, ARGCOUNT); \
    if (!NAME##_ptr) { /* Optional logging */ } \
} \
namespace { struct NAME##_registrar { NAME##_registrar() { IL2CPP::methodInitializers.push_back(Init_##NAME); } }; static NAME##_registrar NAME##_reg; }

// Legacy support
#define DECLARE_FUNCTION_POINTER(NAME, TYPE, ADDRESS) \
using NAME = TYPE; \
inline NAME NAME##_ptr = reinterpret_cast<NAME>(BASE_ADDRESS + ADDRESS);

// Pattern scanning support
// Example:
// DECLARE_PATTERN_POINTER(UpdatePlayerHealth, void(__fastcall*)(Player* player, float newHealth), L"GameAssembly.dll", ".text", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20")
#define DECLARE_PATTERN_POINTER(NAME, TYPE, MODULE, SECTION, PATTERN) \
using NAME = TYPE; \
inline NAME NAME##_ptr = nullptr; \
inline bool NAME##_initialized = false; \
inline void Init_##NAME() { \
    if (NAME##_initialized) return; \
    NAME##_initialized = true; \
    const auto moduleHandle = GetModuleHandleW(MODULE); \
    if (!moduleHandle) return; \
    NAME##_ptr = reinterpret_cast<NAME>(Memory::FindPatternInSection(moduleHandle, SECTION, PATTERN)); \
} \
namespace { struct NAME##_registrar { NAME##_registrar() { IL2CPP::methodInitializers.push_back(Init_##NAME); } }; static NAME##_registrar NAME##_reg; }

// Pattern scanning
// Prefer not to use, is way slower.
#define DECLARE_PATTERN_POINTER_ALL_SECTIONS(NAME, TYPE, MODULE, PATTERN) \
	using NAME = TYPE; \
	inline NAME NAME##_ptr = nullptr; \
	inline bool NAME##_initialized = false; \
	inline void Init_##NAME() { \
		if (NAME##_initialized) return; \
		NAME##_initialized = true; \
		const auto moduleHandle = GetModuleHandleW(MODULE); \
		if (!moduleHandle) return; \
		NAME##_ptr = reinterpret_cast<TYPE>(Memory::FindPatternInAllSections(moduleHandle, PATTERN)); \
	} \
	namespace { struct NAME##_registrar { NAME##_registrar() { IL2CPP::methodInitializers.push_back(Init_##NAME); } }; static NAME##_registrar NAME##_reg; }

#include "MonoBehaviour.h"
#include "MethodInfo.h"
#include "Vector2.h"
#include "Vector3.h"
#include "RaycastHit.h"
#include "Quaternion.h"
#include "String.h"
#include "Cursor.h"
#include "Transform.h"
#include "GameObject.h"
#include "Component.h"
#include "Rigidbody.h"
#include "Camera.h"
#include "ExitLevel.h"
#include "PauseMenuController.h"
#include "ServerManager.h"
#include "PlayerStamina.h"
#include "PlayerSanity.h"
#include "Player.h"
#include "GameController.h"
#include "MapController.h"
#include "GhostEvidence.h"
#include "GhostTraits.h"
#include "GhostInfo.h"
#include "GhostActivity.h"
#include "GhostAI.h"
#include "EMF.h"
#include "EMFData.h"
#include "MediaValues.h"
#include "Evidence.h"
#include "EvidenceController.h"
#include "PhotonNetwork.h"
#include "PhotonObjectInteract.h"
#include "PhotonView.h"
#include "Network.h"
#include "ObjectiveManager.h"
#include "Matrix4x4.h"
#include "PhysicsCharacterController.h"
#include "FirstPersonController.h"
#include "Collider.h"
#include "Time.h"
#include "TarotCards.h"
#include "TarotCard.h"
#include "Door.h"
#include "LevelRoom.h"
#include "LineRenderer.h"
#include "FuseBox.h"
#include "LevelController.h"
#include "Marshal.h"
#include "LevelValues.h"
#include "DeadZoneController.h"
#include "MouseLook.h"
#include "CursedItem.h"
#include "CursedItemController.h"
