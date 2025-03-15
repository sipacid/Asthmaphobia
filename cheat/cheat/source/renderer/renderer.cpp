#include "renderer.h"

using namespace Asthmaphobia;

Renderer& Asthmaphobia::GetRendererInstance()
{
	static auto instance = std::make_unique<Renderer>();
	return *instance;
}

Renderer::Renderer()
{
	InitializeSwapChain();
}

Renderer::~Renderer()
{
	Cleanup();
}

void Renderer::SetGameResources(IDXGISwapChain* swapChain, ID3D11Device* device, ID3D11DeviceContext* context)
{
	// Clean up any existing resources first
	if (Swapchain || Device || Context || TargetView)
		Cleanup();

	// Set the game's actual resources
	Swapchain = swapChain;
	Device = device;
	Context = context;

	// These are references, not owned by us, so we don't increment ref count
	GameResourcesInitialized = true;
}

bool Renderer::CreateRenderTargetView()
{
	if (!Swapchain || !Device)
		return false;

	ID3D11Texture2D* pBackBuffer = nullptr;
	HRESULT hr = Swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));

	if (FAILED(hr) || !pBackBuffer)
		return false;

	hr = Device->CreateRenderTargetView(pBackBuffer, nullptr, &TargetView);
	pBackBuffer->Release();

	return SUCCEEDED(hr) && TargetView != nullptr;
}

bool Renderer::InitializeSwapChain()
{
	// Only initialize enough to get the Present function
	WNDCLASSEX wc{0};
	wc.cbSize = sizeof(wc);
	wc.lpfnWndProc = DefWindowProc;
	wc.lpszClassName = TEXT("asthmaphobia");
	wc.hInstance = GetModuleHandle(nullptr);

	if (!RegisterClassEx(&wc))
	{
		return false;
	}

	HWND hwnd = CreateWindowEx(
		0,
		wc.lpszClassName,
		TEXT(""),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		100,
		100,
		nullptr,
		nullptr,
		wc.hInstance,
		nullptr);

	if (!hwnd)
	{
		UnregisterClass(wc.lpszClassName, wc.hInstance);
		return false;
	}

	DXGI_SWAP_CHAIN_DESC description{};
	description.BufferCount = 1;
	description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	description.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	description.OutputWindow = hwnd;
	description.SampleDesc.Count = 1;
	description.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	description.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	description.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	description.Windowed = TRUE;

	D3D_FEATURE_LEVEL level;
	bool success = false;
	IDXGISwapChain* tempSwapchain = nullptr;
	ID3D11Device* tempDevice = nullptr;
	ID3D11DeviceContext* tempContext = nullptr;

	for (const auto& driverType : KDriverType)
	{
		const HRESULT hr = D3D11CreateDeviceAndSwapChain(
			nullptr, driverType, nullptr, 0, nullptr, 0,
			D3D11_SDK_VERSION, &description, &tempSwapchain, &tempDevice, &level, &tempContext);

		if (SUCCEEDED(hr))
		{
			success = true;

			// Just get the Present function
			if (tempSwapchain)
			{
				void** vmt = *reinterpret_cast<void***>(tempSwapchain);
				PresentFunction = static_cast<Id3DPresent>(vmt[8]);
			}

			// Release temporary resources - we'll get the real ones from the game
			if (tempContext) tempContext->Release();
			if (tempDevice) tempDevice->Release();
			if (tempSwapchain) tempSwapchain->Release();

			break;
		}
	}

	// Clean up the temporary window
	DestroyWindow(hwnd);
	UnregisterClass(wc.lpszClassName, wc.hInstance);

	return success && PresentFunction != nullptr;
}

Id3DPresent Renderer::GetPresent() const
{
	return PresentFunction;
}

void Renderer::Cleanup()
{
	if (TargetView)
	{
		TargetView->Release();
		TargetView = nullptr;
	}

	Swapchain = nullptr;
	Device = nullptr;
	Context = nullptr;

	GameResourcesInitialized = false;
}
