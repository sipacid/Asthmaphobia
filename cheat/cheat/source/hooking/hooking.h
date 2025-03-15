#pragma once
#include "source/common.h"
#include "hooks/hooks.h"
#include "libraries/detours/include/detours.h"

namespace Asthmaphobia
{
	class Hooking
	{
		friend Hooks;

		struct HookEntry
		{
			std::string Name;
			void** Original;
			void* Hook;
			bool Active;
		};

		std::vector<HookEntry> Hooks;
		std::mutex HookMutex;

	public:
		explicit Hooking() = default;
		~Hooking();

		enum class HookResult : uint8_t { Success, AlreadyExists, TransactionFailed, AttachFailed, DetachFailed, NotFound };

		template <typename T>
		HookResult AddHook(const std::string& functionName, T** originalFunction, T* hookFunction);

		HookResult ApplyHooks();
		HookResult RemoveHooks();
		HookResult ToggleHook(const std::string& name, bool enable);

		void Cleanup();

		Id3DPresent OriginalPresent{};
		WNDPROC OriginalWndproc{};
	};

	Hooking& GetHookingInstance();

	template <typename T>
	Hooking::HookResult Hooking::AddHook(const std::string& functionName, T** originalFunction, T* hookFunction)
	{
		std::lock_guard lock(HookMutex);

		// Check if hook already exists
		for (const auto& hook : Hooks)
		{
			if (hook.Name == functionName)
			{
				return HookResult::AlreadyExists;
			}
		}

		Hooks.push_back({
			.Name = functionName,
			.Original = reinterpret_cast<void**>(originalFunction),
			.Hook = reinterpret_cast<void*>(hookFunction),
			.Active = false
		});

		return HookResult::Success;
	}
}
