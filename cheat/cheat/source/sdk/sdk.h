#pragma once
#include <functional>
#include <Windows.h>

namespace IL2CPP
{
    // Expand IL2CPP function typedefs
    using il2cpp_domain_get_t = void* (*)();
    using il2cpp_domain_assembly_open_t = void* (*)(void* domain, const char* name);
    using il2cpp_assembly_get_image_t = void* (*)(void* assembly);
    using il2cpp_class_from_name_t = void* (*)(void* image, const char* namespaze, const char* name);
    using il2cpp_class_get_method_from_name_t = void* (*)(void* klass, const char* name, int argsCount);
    using il2cpp_resolve_icall_t = void* (*)(const char* name);

    // Function pointers
    inline il2cpp_domain_get_t il2cpp_domain_get = nullptr;
    inline il2cpp_domain_assembly_open_t il2cpp_domain_assembly_open = nullptr;
    inline il2cpp_assembly_get_image_t il2cpp_assembly_get_image = nullptr;
    inline il2cpp_class_from_name_t il2cpp_class_from_name = nullptr;
    inline il2cpp_class_get_method_from_name_t il2cpp_class_get_method_from_name = nullptr;
    inline il2cpp_resolve_icall_t il2cpp_resolve_icall = nullptr;

    // Cached domain and assembly image
    inline void* domain = nullptr;
    inline void* assemblyImage = nullptr;

    // Initialize IL2CPP API functions
    inline bool InitIL2CPP()
    {
        const HMODULE gameAssembly = GetModuleHandleW(L"GameAssembly.dll");
        if (!gameAssembly)
            return false;

        il2cpp_domain_get = reinterpret_cast<il2cpp_domain_get_t>(GetProcAddress(gameAssembly, "il2cpp_domain_get"));
        il2cpp_domain_assembly_open = reinterpret_cast<il2cpp_domain_assembly_open_t>(GetProcAddress(gameAssembly, "il2cpp_domain_assembly_open"));
        il2cpp_assembly_get_image = reinterpret_cast<il2cpp_assembly_get_image_t>(GetProcAddress(gameAssembly, "il2cpp_assembly_get_image"));
        il2cpp_class_from_name = reinterpret_cast<il2cpp_class_from_name_t>(GetProcAddress(gameAssembly, "il2cpp_class_from_name"));
        il2cpp_class_get_method_from_name = reinterpret_cast<il2cpp_class_get_method_from_name_t>(GetProcAddress(gameAssembly, "il2cpp_class_get_method_from_name"));
        il2cpp_resolve_icall = reinterpret_cast<il2cpp_resolve_icall_t>(GetProcAddress(gameAssembly, "il2cpp_resolve_icall"));

        return il2cpp_domain_get && il2cpp_domain_assembly_open && il2cpp_assembly_get_image && 
               il2cpp_class_from_name && il2cpp_class_get_method_from_name && il2cpp_resolve_icall;
    }

    // Initialize domain and assembly image
    inline bool InitDomain()
    {
        if (!domain)
            domain = il2cpp_domain_get();
        
        if (!domain)
            return false;

        // Get Assembly-CSharp.dll image
        void* assembly = il2cpp_domain_assembly_open(domain, "Assembly-CSharp");
        if (!assembly)
            return false;

        assemblyImage = il2cpp_assembly_get_image(assembly);
        return assemblyImage != nullptr;
    }

    // Get method pointer by assembly name, namespace, class and method name
    template <typename T>
    T GetMethodPointer(const char* assemblyName, const char* namespaceName, const char* className, const char* methodName, int argsCount = 0)
    {
        // If assemblyName is "Assembly-CSharp", use the cached image
        void* image = assemblyImage;
        
        // If we need a different assembly
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
        struct MethodInfo { void* methodPointer; /* other fields */ };
        void* methodPointer = static_cast<MethodInfo*>(method)->methodPointer;
            
        return reinterpret_cast<T>(methodPointer);
    }

    // Get method pointer through ICalls (unity internal calls)
    template <typename T>
    T ResolveICall(const char* icallName)
    {
        return reinterpret_cast<T>(il2cpp_resolve_icall(icallName));
    }

    inline std::vector<std::function<void()>> methodInitializers;

    // Initialize all registered method pointers at once
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
        if (!IL2CPP::InitIL2CPP())
            return false;

        // Give IL2CPP time to initialize fully
        Sleep(1000);

        if (!IL2CPP::InitializeAllMethods())
            return false;

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

// Internal calls
#define DECLARE_ICALL_POINTER(NAME, TYPE, ICALL_NAME) \
using NAME = TYPE; \
inline NAME NAME##_ptr = nullptr; \
inline void Init_##NAME() { \
    NAME##_ptr = IL2CPP::ResolveICall<NAME>(ICALL_NAME); \
    if (!NAME##_ptr) { /* Optional logging */ } \
} \
namespace { struct NAME##_registrar { NAME##_registrar() { IL2CPP::methodInitializers.push_back(Init_##NAME); } }; static NAME##_registrar NAME##_reg; }

// Legacy support
#define DECLARE_FUNCTION_POINTER(NAME, TYPE, ADDRESS) \
using NAME = TYPE; \
inline NAME NAME##_ptr = reinterpret_cast<NAME>(BASE_ADDRESS + ADDRESS);

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
#include "PhotoValues.h"
#include "Evidence.h"
#include "EvidenceController.h"
#include "PhotonNetwork.h"
#include "Network.h"
#include "PhysicsCharacterController.h"
#include "FirstPersonController.h"
#include "Collider.h"
#include "Time.h"
#include "TarotCards.h"
#include "TarotCard.h"
#include "Door.h"
#include "LevelRoom.h"
#include "FuseBox.h"
#include "LevelController.h"
#include "Marshal.h"
#include "LevelValues.h"
#include "DeadZoneController.h"
#include "MouseLook.h"
#include "CursedItem.h"
#include "CursedItemController.h"
