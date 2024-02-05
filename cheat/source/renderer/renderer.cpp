#include "renderer.h"

using namespace Asthmaphobia;

Renderer::Renderer()
{
	renderer = this;
}

Renderer::~Renderer()
{
	renderer = nullptr;
}

bool Renderer::GetSwapchain(IDXGISwapChain** swapchain, ID3D11Device** device)
{
	WNDCLASSEX wc{0};
	wc.cbSize = sizeof(wc);
	wc.lpfnWndProc = DefWindowProc;
	wc.lpszClassName = TEXT("asthmaphobia");

	if (!RegisterClassEx(&wc))
	{
		return false;
	}

	DXGI_SWAP_CHAIN_DESC description{0};

	description.BufferCount = 1;
	description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	description.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	description.OutputWindow = GetForegroundWindow();
	description.SampleDesc.Count = 1;
	description.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	description.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	description.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	description.Windowed = TRUE;

	D3D_FEATURE_LEVEL level;
	bool success = false;

	for (const auto& driverType : KDriverType)
	{
		HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, driverType, nullptr, 0, nullptr, 0,
		                                           D3D11_SDK_VERSION, &description, swapchain, device, &level,
		                                           nullptr);

		if (SUCCEEDED(hr))
		{
			success = true;
			break;
		}
	}

	DestroyWindow(description.OutputWindow);
	UnregisterClass(wc.lpszClassName, GetModuleHandle(nullptr));

	if (!success)
	{
		return false;
	}

	return true;
}

Id3DPresent Renderer::GetPresent()
{
	IDXGISwapChain* swapchain;
	ID3D11Device* device;

	if (GetSwapchain(&swapchain, &device))
	{
		void** vmt = *reinterpret_cast<void***>(swapchain);

		if (swapchain)
		{
			swapchain->Release();
			swapchain = nullptr;
		}
		if (device)
		{
			device->Release();
			device = nullptr;
		}

		return static_cast<Id3DPresent>(vmt[8]);
	}

	return nullptr;
}
