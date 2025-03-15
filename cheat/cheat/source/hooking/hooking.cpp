#include "hooking.h"

using namespace Asthmaphobia;

Hooking& Asthmaphobia::GetHookingInstance()
{
	static auto instance = std::make_unique<Hooking>();
	return *instance;
}

Hooking::~Hooking()
{
	Cleanup();
}

Hooking::HookResult Hooking::ApplyHooks()
{
	std::lock_guard lock(HookMutex);

	if (Hooks.empty())
	{
		return HookResult::Success;
	}

	if (DetourTransactionBegin() != NO_ERROR)
	{
		LOG_ERROR("Failed to begin detour transaction");
		return HookResult::TransactionFailed;
	}

	if (DetourUpdateThread(GetCurrentThread()) != NO_ERROR)
	{
		DetourTransactionAbort();
		LOG_ERROR("Failed to update detour thread");
		return HookResult::TransactionFailed;
	}

	bool anyFailed = false;

	// Apply all inactive hooks
	for (auto& hook : Hooks)
	{
		if (hook.Active)
			continue;

		LOG_DEBUG("Applying hook: " + hook.Name);

		const LONG error = DetourAttach(hook.Original, hook.Hook);
		if (error != NO_ERROR)
		{
			LOG_ERROR("Failed to attach hook: " + hook.Name +
				" with error code: " + std::to_string(error));
			anyFailed = true;
		}
		else
		{
			hook.Active = true;
		}
	}

	if (DetourTransactionCommit() != NO_ERROR)
	{
		LOG_ERROR("Failed to commit detour transaction");
		return HookResult::TransactionFailed;
	}

	return anyFailed ? HookResult::AttachFailed : HookResult::Success;
}

Hooking::HookResult Hooking::RemoveHooks()
{
	std::lock_guard lock(HookMutex);

	// Check if any hooks are active
	if (std::ranges::none_of(Hooks,
	                         [](const HookEntry& entry) { return entry.Active; }))
	{
		return HookResult::Success;
	}

	if (DetourTransactionBegin() != NO_ERROR)
	{
		LOG_ERROR("Failed to begin detour transaction for removal");
		return HookResult::TransactionFailed;
	}

	if (DetourUpdateThread(GetCurrentThread()) != NO_ERROR)
	{
		DetourTransactionAbort();
		LOG_ERROR("Failed to update detour thread for removal");
		return HookResult::TransactionFailed;
	}

	bool anyFailed = false;

	// Detach all active hooks
	for (auto& hook : Hooks)
	{
		if (!hook.Active)
			continue;

		LOG_DEBUG("Removing hook: " + hook.Name);

		const LONG error = DetourDetach(hook.Original, hook.Hook);
		if (error != NO_ERROR)
		{
			LOG_ERROR("Failed to detach hook: " + hook.Name +
				" with error code: " + std::to_string(error));
			anyFailed = true;
		}
		else
		{
			hook.Active = false;
		}
	}

	if (DetourTransactionCommit() != NO_ERROR)
	{
		LOG_ERROR("Failed to commit detour transaction");
		return HookResult::TransactionFailed;
	}

	return anyFailed ? HookResult::DetachFailed : HookResult::Success;
}

Hooking::HookResult Hooking::ToggleHook(const std::string& name, const bool enable)
{
	static std::lock_guard lock(HookMutex);

	// Find the hook
	const auto it = std::ranges::find_if(Hooks,
	                                     [&name](const HookEntry& entry) { return entry.Name == name; });

	if (it == Hooks.end())
	{
		return HookResult::NotFound;
	}

	// Already in desired state
	if (it->Active == enable)
	{
		return HookResult::Success;
	}

	if (DetourTransactionBegin() != NO_ERROR)
	{
		LOG_ERROR("Failed to begin detour transaction for toggle");
		return HookResult::TransactionFailed;
	}

	if (DetourUpdateThread(GetCurrentThread()) != NO_ERROR)
	{
		DetourTransactionAbort();
		LOG_ERROR("Failed to update detour thread for toggle");
		return HookResult::TransactionFailed;
	}

	LONG error;
	if (enable)
	{
		error = DetourAttach(it->Original, it->Hook);
	}
	else
	{
		error = DetourDetach(it->Original, it->Hook);
	}

	if (error != NO_ERROR)
	{
		DetourTransactionAbort();
		LOG_ERROR("Failed to " + std::string(enable ? "attach" : "detach") +
			" hook: " + name + " with error code: " + std::to_string(error));
		return enable ? HookResult::AttachFailed : HookResult::DetachFailed;
	}

	if (DetourTransactionCommit() != NO_ERROR)
	{
		LOG_ERROR("Failed to commit detour transaction for toggle");
		return HookResult::TransactionFailed;
	}

	it->Active = enable;
	return HookResult::Success;
}

void Hooking::Cleanup()
{
	RemoveHooks();

	if (OriginalWndproc && GetRendererInstance().Window)
	{
		SetWindowLongPtr(GetRendererInstance().Window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(this->OriginalWndproc));
	}
}
