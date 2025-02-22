#include "hooking.h"

using namespace Asthmaphobia;

Hooking::Hooking()
{
	hooking = this;
}

Hooking::~Hooking()
{
	this->RemoveHooks();
	SetWindowLongPtr(renderer->Window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(this->OriginalWndproc));

	hooking = nullptr;
}

void Hooking::AddHook(const std::string& functionName, PVOID* originalFunction, PVOID hookFunction)
{
	this->hooks_.emplace_back(functionName, originalFunction, hookFunction);
}

void Hooking::ApplyHooks() const
{
	if (DetourTransactionBegin() != NO_ERROR)
	{
		throw std::runtime_error("Failed to begin detour transaction");
	}

	if (DetourUpdateThread(GetCurrentThread()) != NO_ERROR)
	{
		throw std::runtime_error("Failed to update detour thread");
	}

	for (const auto& hook : this->hooks_)
	{
		std::ostringstream oss;
		oss << "Applying hook: " << std::get<0>(hook) << "\n";
		LOG_DEBUG(oss.str());

		const LONG error = DetourAttach(std::get<1>(hook), std::get<2>(hook));
		if (error != NO_ERROR)
		{
			std::ostringstream oss;
			oss << "Failed to attach hook: " << std::get<0>(hook) << " with error code: " << error << "\n";
			LOG_ERROR(oss.str());
		}
	}

	if (DetourTransactionCommit() != NO_ERROR)
	{
		throw std::runtime_error("Failed to commit detour transaction");
	}
}

void Hooking::RemoveHooks() const
{
	if (DetourTransactionBegin() != NO_ERROR)
	{
		throw std::runtime_error("Failed to begin detour transaction");
	}

	if (DetourUpdateThread(GetCurrentThread()) != NO_ERROR)
	{
		throw std::runtime_error("Failed to update detour thread");
	}

	for (const auto& hook : this->hooks_)
	{
		std::ostringstream oss;
		oss << "Restoring hook: " << std::get<0>(hook) << "\n";
		LOG_DEBUG(oss.str());

		const LONG error = DetourDetach(std::get<1>(hook), std::get<2>(hook));
		if (error != NO_ERROR)
		{
			std::ostringstream oss;
			oss << "Failed to detach hook: " << std::get<0>(hook) << " with error code: " << error << "\n";
			LOG_ERROR(oss.str());
		}
	}

	if (DetourTransactionCommit() != NO_ERROR)
	{
		throw std::runtime_error("Failed to commit detour transaction");
	}
}
