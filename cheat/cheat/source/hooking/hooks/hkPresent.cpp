#include "source/common.h"
#include "source/hooking/hooking.h"
#include "source/menu/menu.h"

#include "libraries/imgui/imgui.h"
#include "libraries/imgui/imgui_impl_win32.h"
#include "libraries/imgui/imgui_impl_dx11.h"

using namespace Asthmaphobia;

static void SafeRenderFrame()
{
	__try
	{
		if (menu.Open)
		{
			Menu::Render();
		}

		if (globalRunning)
		{
			GetFeatureManagerInstance().OnDraw();
			Notifications::RenderNotifications();
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		LOG_WARN("Access violation caught in render loop - skipping frame");
	}
}

HRESULT __stdcall Hooks::HkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	auto& hooking = GetHookingInstance();
	auto& renderer = GetRendererInstance();

	if (!menu.Initialized)
	{
		ID3D11Device* device = nullptr;
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void **>(&device))))
		{
			ID3D11DeviceContext* context = nullptr;
			device->GetImmediateContext(&context);

			renderer.SetGameResources(pSwapChain, device, context);

			DXGI_SWAP_CHAIN_DESC description;
			pSwapChain->GetDesc(&description);
			renderer.Window = description.OutputWindow;

			if (!renderer.CreateRenderTargetView())
			{
				LOG_ERROR("Failed to create render target view");
				if (context)
					context->Release();
				return hooking.OriginalPresent(pSwapChain, SyncInterval, Flags);
			}

			ImGui::CreateContext();
			ImGui_ImplWin32_Init(renderer.Window);
			ImGui_ImplDX11_Init(device, context);
			ImGui::GetMainViewport()->PlatformHandleRaw = renderer.Window;
			ImGui::LoadIniSettingsFromDisk((Helper::GetAsthmaphobiaDirectory() + "\\menu.ini").c_str());
			ImGui::GetIO().FontGlobalScale = dpiScale;

			hooking.OriginalWndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(
				renderer.Window,
				GWLP_WNDPROC,
				reinterpret_cast<LONG_PTR>(HkWndProc)));

			Menu::Initialize();

			if (context)
				context->Release();
		}
		else
		{
			return hooking.OriginalPresent(pSwapChain, SyncInterval, Flags);
		}
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	SafeRenderFrame();

	ImGui::EndFrame();
	ImGui::Render();

	ID3D11DeviceContext* context = renderer.GetContext();
	ID3D11RenderTargetView* targetView = renderer.GetTargetView();

	if (context && targetView)
	{
		context->OMSetRenderTargets(1, &targetView, nullptr);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	return hooking.OriginalPresent(pSwapChain, SyncInterval, Flags);
}
