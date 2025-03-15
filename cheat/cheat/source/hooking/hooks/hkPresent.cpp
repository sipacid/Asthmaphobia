#include "source/common.h"
#include "source/hooking/hooking.h"
#include "source/menu/menu.h"

#include "libraries/imgui/imgui.h"
#include "libraries/imgui/imgui_impl_win32.h"
#include "libraries/imgui/imgui_impl_dx11.h"

using namespace Asthmaphobia;

HRESULT __stdcall Hooks::HkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	auto& hooking = GetHookingInstance();
	auto& renderer = GetRendererInstance();

	if (!menu.Initialized)
	{
		ID3D11Device* device = nullptr;
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&device))))
		{
			// Initialize device context
			ID3D11DeviceContext* context = nullptr;
			device->GetImmediateContext(&context);

			// Set the game's resources in the renderer
			renderer.SetGameResources(pSwapChain, device, context);

			// Get the window handle from the swap chain
			DXGI_SWAP_CHAIN_DESC description;
			pSwapChain->GetDesc(&description);
			renderer.Window = description.OutputWindow;

			// Set up render target view
			if (!renderer.CreateRenderTargetView())
			{
				LOG_ERROR("Failed to create render target view");
				if (context) context->Release();
				return hooking.OriginalPresent(pSwapChain, SyncInterval, Flags);
			}

			// Initialize ImGui
			ImGui::CreateContext();
			ImGui_ImplWin32_Init(renderer.Window);
			ImGui_ImplDX11_Init(device, context);
			ImGui::GetMainViewport()->PlatformHandleRaw = renderer.Window;
			ImGui::LoadIniSettingsFromDisk((Helper::GetAsthmaphobiaDirectory() + "\\menu.ini").c_str());
			ImGui::GetIO().FontGlobalScale = dpiScale;

			// Set up window procedure hook
			hooking.OriginalWndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(
				renderer.Window,
				GWLP_WNDPROC,
				reinterpret_cast<LONG_PTR>(HkWndProc)
			));

			// Initialize the menu
			Menu::Initialize();

			// Allow these references to be released
			if (context) context->Release();
		}
		else
		{
			return hooking.OriginalPresent(pSwapChain, SyncInterval, Flags);
		}
	}

	// Start ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// Render menu if open
	if (menu.Open)
	{
		Menu::Render();
	}

	// Render features and notifications
	if (globalRunning)
	{
		GetFeatureManagerInstance().OnDraw();
		Notifications::RenderNotifications();
	}

	// End ImGui frame and render
	ImGui::EndFrame();
	ImGui::Render();

	// Get the device context and render target view from the renderer
	ID3D11DeviceContext* context = renderer.GetContext();
	ID3D11RenderTargetView* targetView = renderer.GetTargetView();

	// Render the ImGui draw data
	if (context && targetView)
	{
		context->OMSetRenderTargets(1, &targetView, nullptr);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	return hooking.OriginalPresent(pSwapChain, SyncInterval, Flags);
}
