//--------------------------------------------------------------------------------------
// File: BasicHLSL11.cpp
//
// This sample shows a simple example of the Microsoft High-Level Shader Language (HLSL)
// with Direct3D 11 using the DUXT framework.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "stdafx.h"

#include "MeshBuilders.h"
#include "Bone.h"

#include <random>

#include "InstancingTestVS_bytecode.h"
#include "InstancingTestPS_bytecode.h"

#include <omp.h>

#pragma warning( disable : 4100 )

using namespace DirectX;

//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------
CDXUTDialogResourceManager  g_DialogResourceManager; // manager for shared resources of dialogs
CModelViewerCamera          g_Camera;               // A model viewing camera
CDXUTDirectionWidget        g_LightControl;
CD3DSettingsDlg             g_D3DSettingsDlg;       // Device settings dialog
CDXUTDialog                 g_HUD;                  // manages the 3D   
CDXUTDialog                 g_SampleUI;             // dialog for sample specific controls
XMMATRIX                    g_mCenterMesh;
float                       g_fLightScale;
int                         g_nNumActiveLights;
int                         g_nActiveLight;
bool                        g_bShowHelp = false;    // If true, it renders the UI control text

CDXUTTextHelper*            g_pTxtHelper = nullptr;

ID3D11SamplerState*         g_pSamLinear = nullptr;

struct CB_VS_PER_OBJECT
{
	XMFLOAT4X4 m_View;
	XMFLOAT4X4 m_Proj;
};
UINT                        g_iCBVSPerObjectBind = 0;

struct CB_PS
{
	XMFLOAT4 m_UniformDiffuse;
	XMFLOAT4 m_CameraPosition;
	XMFLOAT3 m_LightDirection;
	float m_Shininess;
	float m_Ambient;
};
UINT						g_iCBPSBind = 0;

struct SkinningData
{
	XMUINT4 m_BlendIndices;
	XMFLOAT4 m_BlendWeights;
};

struct InstanceData
{
	XMMATRIX m_World;
	XMMATRIX m_Transforms[4];
};

ID3D11Buffer*               g_pcbVSPerObject = nullptr;
ID3D11Buffer*               g_pcbPS = nullptr;

ID3D11Buffer*				g_pVB = nullptr;
ID3D11Buffer*				g_pVBSkinning = nullptr;
ID3D11Buffer*				g_pVBPerInstance = nullptr;
ID3D11Buffer*				g_pIB = nullptr;
DXGI_FORMAT g_IBFormat;

UINT						g_nIndices = 0;
UINT						g_nInstances = 1024;
const float					g_CylinderHeight = 150.0f;
const float					g_CylinderRadius = 20.0f;
std::vector<InstanceData>	g_instanceData;

ID3D11InputLayout*			g_pVertexInputLayout = nullptr;

ID3D11VertexShader*			g_pVertexShader = nullptr;
ID3D11PixelShader*			g_pPixelShader = nullptr;

//--------------------------------------------------------------------------------------
// Hard coded skeleton
//--------------------------------------------------------------------------------------
struct Skeleton
{
	enum BoneIndex
	{
		kBoneIndex_Root = 0,
		kBoneIndex_First,
		kBoneIndex_Second,

		kBoneIndex_TermIndex,
	};

	Bone Bones[kBoneIndex_TermIndex];

	Skeleton()
	{
		Bones[kBoneIndex_Root].pParent = nullptr;
		Bones[kBoneIndex_Root].BaseTranslation = XMFLOAT3(g_CylinderHeight * 0.5f, 0.0f, 0.0f);
		Bones[kBoneIndex_Root].BaseRotation = XMFLOAT3(0.0f, 0.0f, XM_PIDIV2);
		Bones[kBoneIndex_Root].BaseScaling = XMFLOAT3(1.0f, 1.0f, 1.0f);
		Bones[kBoneIndex_Root].pChildren.push_back(&Bones[kBoneIndex_First]);
		Bones[kBoneIndex_Root].RelativeTransform = XMMatrixIdentity();

		Bones[kBoneIndex_First].pParent = &Bones[kBoneIndex_Root];
		Bones[kBoneIndex_First].BaseTranslation = XMFLOAT3(g_CylinderHeight * 0.5f, 0.0f, 0.0f);
		Bones[kBoneIndex_First].BaseRotation = XMFLOAT3(0.0f, XM_PI, 0.0f);
		Bones[kBoneIndex_First].BaseScaling = XMFLOAT3(1.0f, 1.0f, 1.0f);
		Bones[kBoneIndex_First].pChildren.push_back(&Bones[kBoneIndex_Second]);
		Bones[kBoneIndex_First].RelativeTransform = XMMatrixIdentity();

		Bones[kBoneIndex_Second].pParent = &Bones[kBoneIndex_First];
		Bones[kBoneIndex_Second].BaseTranslation = XMFLOAT3(g_CylinderHeight * 0.5f, 0.0f, 0.0f);
		Bones[kBoneIndex_Second].BaseRotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
		Bones[kBoneIndex_Second].BaseScaling = XMFLOAT3(1.0f, 1.0f, 1.0f);
		Bones[kBoneIndex_Second].RelativeTransform = XMMatrixIdentity();

		ComputeBasePoseInverse(Bones[kBoneIndex_Root]);
	}
};

std::vector<Skeleton> g_Skeletons(g_nInstances);

//--------------------------------------------------------------------------------------
// UI control IDs
//--------------------------------------------------------------------------------------
#define IDC_TOGGLEFULLSCREEN    1
#define IDC_TOGGLEREF           2
#define IDC_CHANGEDEVICE        3
#define IDC_TOGGLEWARP          4

//--------------------------------------------------------------------------------------
// Forward declarations 
//--------------------------------------------------------------------------------------
bool CALLBACK ModifyDeviceSettings(DXUTDeviceSettings* pDeviceSettings, void* pUserContext);
void CALLBACK OnFrameMove(double fTime, float fElapsedTime, void* pUserContext);
LRESULT CALLBACK MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing,
	void* pUserContext);
void CALLBACK OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);
void CALLBACK OnGUIEvent(UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext);

bool CALLBACK IsD3D11DeviceAcceptable(const CD3D11EnumAdapterInfo *AdapterInfo, UINT Output, const CD3D11EnumDeviceInfo *DeviceInfo,
	DXGI_FORMAT BackBufferFormat, bool bWindowed, void* pUserContext);
HRESULT CALLBACK OnD3D11CreateDevice(ID3D11Device* pd3dDevice, const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc,
	void* pUserContext);
HRESULT CALLBACK OnD3D11ResizedSwapChain(ID3D11Device* pd3dDevice, IDXGISwapChain* pSwapChain,
	const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
void CALLBACK OnD3D11ReleasingSwapChain(void* pUserContext);
void CALLBACK OnD3D11DestroyDevice(void* pUserContext);
void CALLBACK OnD3D11FrameRender(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dImmediateContext, double fTime,
	float fElapsedTime, void* pUserContext);

void InitApp();
void RenderText();


//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	// Enable run-time memory check for debug builds.
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// DXUT will create and use the best device
	// that is available on the system depending on which D3D callbacks are set below

	// Set DXUT callbacks
	DXUTSetCallbackDeviceChanging(ModifyDeviceSettings);
	DXUTSetCallbackMsgProc(MsgProc);
	DXUTSetCallbackKeyboard(OnKeyboard);
	DXUTSetCallbackFrameMove(OnFrameMove);

	DXUTSetCallbackD3D11DeviceAcceptable(IsD3D11DeviceAcceptable);
	DXUTSetCallbackD3D11DeviceCreated(OnD3D11CreateDevice);
	DXUTSetCallbackD3D11SwapChainResized(OnD3D11ResizedSwapChain);
	DXUTSetCallbackD3D11FrameRender(OnD3D11FrameRender);
	DXUTSetCallbackD3D11SwapChainReleasing(OnD3D11ReleasingSwapChain);
	DXUTSetCallbackD3D11DeviceDestroyed(OnD3D11DestroyDevice);

	InitApp();
	DXUTInit(true, true, nullptr); // Parse the command line, show msgboxes on error, no extra command line params
	DXUTSetCursorSettings(true, true); // Show the cursor and clip it when in full screen
	DXUTCreateWindow(L"BasicHLSL11");
	DXUTCreateDevice(D3D_FEATURE_LEVEL_9_2, true, 800, 600);
	DXUTMainLoop(); // Enter into the DXUT render loop

	return DXUTGetExitCode();
}


//--------------------------------------------------------------------------------------
// Initialize the app 
//--------------------------------------------------------------------------------------
void InitApp()
{
	static const XMVECTORF32 s_vLightDir = { -1.f, 1, -1.f, 0.f };
	XMVECTOR vLightDir = XMVector3Normalize(s_vLightDir);
	g_LightControl.SetLightDirection(vLightDir);

	// Initialize dialogs
	g_D3DSettingsDlg.Init(&g_DialogResourceManager);
	g_HUD.Init(&g_DialogResourceManager);
	g_SampleUI.Init(&g_DialogResourceManager);

	g_HUD.SetCallback(OnGUIEvent); int iY = 10;
	g_HUD.AddButton(IDC_TOGGLEFULLSCREEN, L"Toggle full screen", 0, iY, 170, 23);
	g_HUD.AddButton(IDC_CHANGEDEVICE, L"Change device (F2)", 0, iY += 26, 170, 23, VK_F2);
	g_HUD.AddButton(IDC_TOGGLEREF, L"Toggle REF (F3)", 0, iY += 26, 170, 23, VK_F3);
	g_HUD.AddButton(IDC_TOGGLEWARP, L"Toggle WARP (F4)", 0, iY += 26, 170, 23, VK_F4);

	g_SampleUI.SetCallback(OnGUIEvent); iY = 10;

	omp_set_num_threads(4);
}


//--------------------------------------------------------------------------------------
// Called right before creating a D3D device, allowing the app to modify the device settings as needed
//--------------------------------------------------------------------------------------
bool CALLBACK ModifyDeviceSettings(DXUTDeviceSettings* pDeviceSettings, void* pUserContext)
{
	return true;
}


//--------------------------------------------------------------------------------------
// Handle updates to the scene.  This is called regardless of which D3D API is used
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameMove(double fTime, float fElapsedTime, void* pUserContext)
{
	// Update the camera's position based on user input 
	g_Camera.FrameMove(fElapsedTime);
}


//--------------------------------------------------------------------------------------
// Render the help and statistics text
//--------------------------------------------------------------------------------------
void RenderText()
{
	UINT nBackBufferHeight = DXUTGetDXGIBackBufferSurfaceDesc()->Height;

	g_pTxtHelper->Begin();
	g_pTxtHelper->SetInsertionPos(2, 0);
	g_pTxtHelper->SetForegroundColor(Colors::Yellow);
	g_pTxtHelper->DrawTextLine(DXUTGetFrameStats(DXUTIsVsyncEnabled()));
	g_pTxtHelper->DrawTextLine(DXUTGetDeviceStats());

	// Draw help
	if (g_bShowHelp)
	{
		g_pTxtHelper->SetInsertionPos(2, nBackBufferHeight - 20 * 6);
		g_pTxtHelper->SetForegroundColor(Colors::Orange);
		g_pTxtHelper->DrawTextLine(L"Controls:");

		g_pTxtHelper->SetInsertionPos(20, nBackBufferHeight - 20 * 5);
		g_pTxtHelper->DrawTextLine(L"Rotate model: Left mouse button\n"
			L"Rotate light: Right mouse button\n"
			L"Rotate camera: Middle mouse button\n"
			L"Zoom camera: Mouse wheel scroll\n");

		g_pTxtHelper->SetInsertionPos(550, nBackBufferHeight - 20 * 5);
		g_pTxtHelper->DrawTextLine(L"Hide help: F1\n"
			L"Quit: ESC\n");
	}
	else
	{
		g_pTxtHelper->SetForegroundColor(Colors::White);
		g_pTxtHelper->DrawTextLine(L"Press F1 for help");
	}

	g_pTxtHelper->End();
}


//--------------------------------------------------------------------------------------
// Handle messages to the application
//--------------------------------------------------------------------------------------
LRESULT CALLBACK MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing,
	void* pUserContext)
{
	// Pass messages to dialog resource manager calls so GUI state is updated correctly
	*pbNoFurtherProcessing = g_DialogResourceManager.MsgProc(hWnd, uMsg, wParam, lParam);
	if (*pbNoFurtherProcessing)
		return 0;

	// Pass messages to settings dialog if its active
	if (g_D3DSettingsDlg.IsActive())
	{
		g_D3DSettingsDlg.MsgProc(hWnd, uMsg, wParam, lParam);
		return 0;
	}

	// Give the dialogs a chance to handle the message first
	*pbNoFurtherProcessing = g_HUD.MsgProc(hWnd, uMsg, wParam, lParam);
	if (*pbNoFurtherProcessing)
		return 0;
	*pbNoFurtherProcessing = g_SampleUI.MsgProc(hWnd, uMsg, wParam, lParam);
	if (*pbNoFurtherProcessing)
		return 0;

	g_LightControl.HandleMessages(hWnd, uMsg, wParam, lParam);

	// Pass all remaining windows messages to camera so it can respond to user input
	g_Camera.HandleMessages(hWnd, uMsg, wParam, lParam);

	return 0;
}


//--------------------------------------------------------------------------------------
// Handle key presses
//--------------------------------------------------------------------------------------
void CALLBACK OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
	if (bKeyDown)
	{
		switch (nChar)
		{
		case VK_F1:
			g_bShowHelp = !g_bShowHelp; break;
		}
	}
}


//--------------------------------------------------------------------------------------
// Handles the GUI events
//--------------------------------------------------------------------------------------
void CALLBACK OnGUIEvent(UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext)
{
	switch (nControlID)
	{
	case IDC_TOGGLEFULLSCREEN:
		DXUTToggleFullScreen();
		break;
	case IDC_TOGGLEREF:
		DXUTToggleREF();
		break;
	case IDC_TOGGLEWARP:
		DXUTToggleWARP();
		break;
	case IDC_CHANGEDEVICE:
		g_D3DSettingsDlg.SetActive(!g_D3DSettingsDlg.IsActive());
		break;
	}

}


//--------------------------------------------------------------------------------------
// Reject any D3D11 devices that aren't acceptable by returning false
//--------------------------------------------------------------------------------------
bool CALLBACK IsD3D11DeviceAcceptable(const CD3D11EnumAdapterInfo *AdapterInfo, UINT Output, const CD3D11EnumDeviceInfo *DeviceInfo,
	DXGI_FORMAT BackBufferFormat, bool bWindowed, void* pUserContext)
{
	return true;
}


//--------------------------------------------------------------------------------------
// Create any D3D11 resources that aren't dependant on the back buffer
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D11CreateDevice(ID3D11Device* pd3dDevice, const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc,
	void* pUserContext)
{
	HRESULT hr;

	auto pd3dImmediateContext = DXUTGetD3D11DeviceContext();
	V_RETURN(g_DialogResourceManager.OnD3D11CreateDevice(pd3dDevice, pd3dImmediateContext));
	V_RETURN(g_D3DSettingsDlg.OnD3D11CreateDevice(pd3dDevice));
	g_pTxtHelper = new CDXUTTextHelper(pd3dDevice, pd3dImmediateContext, &g_DialogResourceManager, 15);

	XMFLOAT3 vCenter(0.25767413f, -28.503521f, 111.00689f);
	FLOAT fObjectRadius = 378.15607f;

	g_mCenterMesh = XMMatrixTranslation(-vCenter.x, -vCenter.y, -vCenter.z);
	XMMATRIX m = XMMatrixRotationY(XM_PI);
	g_mCenterMesh *= m;
	m = XMMatrixRotationX(XM_PI / 2.0f);
	g_mCenterMesh *= m;

	// Compile the shaders using the lowest possible profile for broadest feature level support

	// Best practice would be to compile these offline as part of the build, but it's more convienent for experimentation to compile at runtime.
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	// Disable optimizations to further improve shader debugging
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	// Create a sampler state
	D3D11_SAMPLER_DESC SamDesc;
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.MipLODBias = 0.0f;
	SamDesc.MaxAnisotropy = 1;
	SamDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	SamDesc.BorderColor[0] = SamDesc.BorderColor[1] = SamDesc.BorderColor[2] = SamDesc.BorderColor[3] = 0;
	SamDesc.MinLOD = 0;
	SamDesc.MaxLOD = D3D11_FLOAT32_MAX;
	V_RETURN(pd3dDevice->CreateSamplerState(&SamDesc, &g_pSamLinear));
	DXUT_SetDebugName(g_pSamLinear, "Primary");

	// Setup constant buffers
	D3D11_BUFFER_DESC Desc;
	Desc.Usage = D3D11_USAGE_DYNAMIC;
	Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	Desc.MiscFlags = 0;

	Desc.ByteWidth = sizeof(CB_VS_PER_OBJECT);
	V_RETURN(pd3dDevice->CreateBuffer(&Desc, nullptr, &g_pcbVSPerObject));
	DXUT_SetDebugName(g_pcbVSPerObject, "CB_VS_PER_OBJECT");

	Desc.ByteWidth = ((sizeof(CB_PS) + 15) / 16) * 16;
	V_RETURN(pd3dDevice->CreateBuffer(&Desc, nullptr, &g_pcbPS));
	DXUT_SetDebugName(g_pcbPS, "CB_PS");

	// Setup the camera's view parameters
	static const XMVECTORF32 s_vecEye = { 0.0f, 0.0f, -100.0f, 0.0f };
	g_Camera.SetViewParams(s_vecEye, g_XMZero);
	g_Camera.SetRadius(fObjectRadius * 3.0f, fObjectRadius * 0.5f, fObjectRadius * 10.0f);

	g_HUD.GetButton(IDC_TOGGLEWARP)->SetEnabled(true);

	// ============================
	// Create shaders
	// ============================
	V_RETURN(pd3dDevice->CreateVertexShader(g_InstancingTestVS_bytecode,
		sizeof(g_InstancingTestVS_bytecode),
		nullptr, &g_pVertexShader));
	V_RETURN(pd3dDevice->CreatePixelShader(g_InstancingTestPS_bytecode,
		sizeof(g_InstancingTestPS_bytecode),
		nullptr, &g_pPixelShader));

	// ============================
	// Create mesh
	// ============================
	// define vertices
	std::vector<Vertex> vertices;
	std::vector<std::uint32_t> indices;
	std::vector<SkinningData> skinningData;
	AppendCylinder(g_CylinderRadius, g_CylinderHeight, 32, 19, vertices, indices);

	skinningData.reserve(vertices.size());
	for (const auto& vertex : vertices)
	{
		float w = (8.0f * vertex.m_Position.y / g_CylinderHeight) * 0.5f + 0.5f;
		w = std::min(w, 1.0f);
		w = std::max(w, 0.0f);

		skinningData.push_back({
				{ Skeleton::kBoneIndex_First, Skeleton::kBoneIndex_Second, 0, 0 },
				{ w, 1.0f - w, 0.0f, 0.0f }
		});
	}

	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	Desc.CPUAccessFlags = 0;
	Desc.MiscFlags = 0;
	Desc.ByteWidth = sizeof(Vertex) * vertices.size();

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices.data();
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	// create vb
	V_RETURN(pd3dDevice->CreateBuffer(&Desc, &InitData, &g_pVB));
	DXUT_SetDebugName(g_pVB, "VertexBuffer");

	Desc.ByteWidth = sizeof(SkinningData) * skinningData.size();

	InitData.pSysMem = skinningData.data();
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	V_RETURN(pd3dDevice->CreateBuffer(&Desc, &InitData, &g_pVBSkinning));
	DXUT_SetDebugName(g_pVBSkinning, "VertexBufferForSkinning");

	// define indices
	g_IBFormat = DXGI_FORMAT_R32_UINT;
	g_nIndices = indices.size();

	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	Desc.MiscFlags = 0;
	Desc.CPUAccessFlags = 0;
	Desc.ByteWidth = sizeof(std::uint32_t) * indices.size();

	InitData.pSysMem = indices.data();
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	// create ib
	V_RETURN(pd3dDevice->CreateBuffer(&Desc, &InitData, &g_pIB));
	DXUT_SetDebugName(g_pIB, "IndexBuffer");

	// define vertex layout
	std::vector<D3D11_INPUT_ELEMENT_DESC> layout
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BLENDINDICES", 0, DXGI_FORMAT_R32G32B32A32_UINT, 2, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BLENDWEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 2, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "INSTANCE_WORLD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
		{ "INSTANCE_WORLD", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
		{ "INSTANCE_WORLD", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 32, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
		{ "INSTANCE_WORLD", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 48, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	};

	for (std::uint32_t i = 0; i < ARRAYSIZE(((InstanceData*)nullptr)->m_Transforms) * 4; i++)
	{
		layout.push_back({ "INSTANCE_BONE", i, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 64 + 16 * i, D3D11_INPUT_PER_INSTANCE_DATA, 1 });
	}

	V_RETURN(pd3dDevice->CreateInputLayout(layout.data(), layout.size(),
		g_InstancingTestVS_bytecode, sizeof(g_InstancingTestVS_bytecode),
		&g_pVertexInputLayout));

	// ============================
	// Create data per instance
	// ============================
	Desc.Usage = D3D11_USAGE_DYNAMIC;
	Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	Desc.MiscFlags = 0;
	Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	Desc.ByteWidth = sizeof(InstanceData) * g_nInstances;

	V_RETURN(pd3dDevice->CreateBuffer(&Desc, nullptr, &g_pVBPerInstance));

	// ============================
	// Initialize Skeletons
	// ============================
	std::random_device rd;
	std::mt19937 engine(rd());
	g_instanceData.resize(g_nInstances);

	#pragma omp parallel for
	for (std::int64_t i = 0; i < static_cast<std::int64_t>(g_nInstances); i++)
	{
		float radius = std::uniform_real<float>(0.0f, 1.0f)(engine);
		radius = sqrtf(radius);
		radius *= 1024.0f + 256.0f;
		float angle = std::uniform_real<float>(-XM_PI, XM_PI)(engine);

		g_instanceData[i].m_World =
			XMMatrixTranspose(XMMatrixTranslation(radius, 0.0f, 0.0f) *
			XMMatrixRotationY(angle));
	}

	return S_OK;
}


//--------------------------------------------------------------------------------------
// Create any D3D11 resources that depend on the back buffer
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D11ResizedSwapChain(ID3D11Device* pd3dDevice, IDXGISwapChain* pSwapChain,
	const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	HRESULT hr;

	V_RETURN(g_DialogResourceManager.OnD3D11ResizedSwapChain(pd3dDevice, pBackBufferSurfaceDesc));
	V_RETURN(g_D3DSettingsDlg.OnD3D11ResizedSwapChain(pd3dDevice, pBackBufferSurfaceDesc));

	// Setup the camera's projection parameters
	float fAspectRatio = pBackBufferSurfaceDesc->Width / (FLOAT) pBackBufferSurfaceDesc->Height;
	g_Camera.SetProjParams(XM_PI / 4, fAspectRatio, 2.0f, 4000.0f);
	g_Camera.SetWindow(pBackBufferSurfaceDesc->Width, pBackBufferSurfaceDesc->Height);
	g_Camera.SetButtonMasks(MOUSE_MIDDLE_BUTTON, MOUSE_WHEEL, MOUSE_LEFT_BUTTON);

	g_HUD.SetLocation(pBackBufferSurfaceDesc->Width - 170, 0);
	g_HUD.SetSize(170, 170);
	g_SampleUI.SetLocation(pBackBufferSurfaceDesc->Width - 170, pBackBufferSurfaceDesc->Height - 300);
	g_SampleUI.SetSize(170, 300);

	return S_OK;
}


//--------------------------------------------------------------------------------------
// Render the scene using the D3D11 device
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D11FrameRender(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dImmediateContext, double fTime,
	float fElapsedTime, void* pUserContext)
{
	HRESULT hr;

	// If the settings dialog is being shown, then render it instead of rendering the app's scene
	if (g_D3DSettingsDlg.IsActive())
	{
		g_D3DSettingsDlg.OnRender(fElapsedTime);
		return;
	}

	// Update skeleton matrix
	#pragma omp parallel for
	for (std::int64_t i = 0; i < static_cast<std::int64_t>(g_Skeletons.size()); i++)
	{
		float rate = (i + 7e4f) / 7e4f;
		g_Skeletons[i].Bones[Skeleton::kBoneIndex_Second].RelativeTransform =
			XMMatrixRotationY(-XM_PI * 0.8f * std::sinf(fTime * XM_PI * rate));
		ComputeTransform(g_Skeletons[i].Bones[Skeleton::kBoneIndex_Root]);

		for (int j = 0; j < 3; j++)
		{
			g_instanceData[i].m_Transforms[j] = XMMatrixTranspose(g_Skeletons[i].Bones[j].Transform);
		}
	}

	// initialize buffer
	D3D11_MAPPED_SUBRESOURCE subres;
	V(pd3dImmediateContext->Map(g_pVBPerInstance, 0,
		D3D11_MAP_WRITE_DISCARD, 0, &subres));
	memcpy(subres.pData, g_instanceData.data(),
		g_instanceData.size() * sizeof(InstanceData));
	DXUTGetD3D11DeviceContext()->Unmap(g_pVBPerInstance, 0);

	// Clear the render target and depth stencil
	auto pRTV = DXUTGetD3D11RenderTargetView();
	pd3dImmediateContext->ClearRenderTargetView(pRTV, Colors::MidnightBlue);
	auto pDSV = DXUTGetD3D11DepthStencilView();
	pd3dImmediateContext->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH, 1.0, 0);

	// Get the light direction
	XMVECTOR vLightDir = g_LightControl.GetLightDirection();

	D3D11_MAPPED_SUBRESOURCE MappedResource;

	// Get the projection & view matrix from the camera class
	XMMATRIX mProj = g_Camera.GetProjMatrix();
	XMMATRIX mView = g_Camera.GetWorldMatrix() * g_Camera.GetViewMatrix();

	// VS Per object
	V(pd3dImmediateContext->Map(g_pcbVSPerObject, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource));
	auto pVSPerObject = reinterpret_cast<CB_VS_PER_OBJECT*>(MappedResource.pData);
	XMMATRIX mt = XMMatrixTranspose(mView);
	XMStoreFloat4x4(&pVSPerObject->m_View, mt);
	mt = XMMatrixTranspose(mProj);
	XMStoreFloat4x4(&pVSPerObject->m_Proj, mt);
	pd3dImmediateContext->Unmap(g_pcbVSPerObject, 0);

	// PS constant buffer
	V(pd3dImmediateContext->Map(g_pcbPS, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource));
	auto pPS = reinterpret_cast<CB_PS*>(MappedResource.pData);
	XMStoreFloat4(&pPS->m_CameraPosition, g_Camera.GetEyePt());
	pPS->m_UniformDiffuse = XMFLOAT4(0.1f, 0.3f, 1.0f, 1.0f);
	pPS->m_Ambient = 0.4f;
	pPS->m_Shininess = 30.0f;
	XMStoreFloat3(&pPS->m_LightDirection, vLightDir);
	pd3dImmediateContext->Unmap(g_pcbPS, 0);

	pd3dImmediateContext->VSSetConstantBuffers(g_iCBVSPerObjectBind, 1, &g_pcbVSPerObject);
	pd3dImmediateContext->PSSetConstantBuffers(g_iCBPSBind, 1, &g_pcbPS);

	//Render
	pd3dImmediateContext->PSSetSamplers(0, 1, &g_pSamLinear);

	ID3D11Buffer* pBuffers [] = { g_pVB, g_pVBPerInstance, g_pVBSkinning };
	UINT strides [] = {sizeof(Vertex), sizeof(InstanceData), sizeof(SkinningData)};
	UINT offsets [] = { 0, 0, 0 };
	pd3dImmediateContext->IASetVertexBuffers(0, 3, pBuffers, strides, offsets);
	pd3dImmediateContext->IASetIndexBuffer(g_pIB, g_IBFormat, 0);
	pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	pd3dImmediateContext->IASetInputLayout(g_pVertexInputLayout);

	pd3dImmediateContext->VSSetShader(g_pVertexShader, nullptr, 0);
	pd3dImmediateContext->PSSetShader(g_pPixelShader, nullptr, 0);

	pd3dImmediateContext->DrawIndexedInstanced(g_nIndices, g_nInstances, 0, 0, 0);

	DXUT_BeginPerfEvent(DXUT_PERFEVENTCOLOR, L"HUD / Stats");
	g_HUD.OnRender(fElapsedTime);
	g_SampleUI.OnRender(fElapsedTime);
	RenderText();
	DXUT_EndPerfEvent();
}


//--------------------------------------------------------------------------------------
// Release D3D11 resources created in OnD3D11ResizedSwapChain 
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D11ReleasingSwapChain(void* pUserContext)
{
	g_DialogResourceManager.OnD3D11ReleasingSwapChain();
}


//--------------------------------------------------------------------------------------
// Release D3D11 resources created in OnD3D11CreateDevice 
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D11DestroyDevice(void* pUserContext)
{
	g_DialogResourceManager.OnD3D11DestroyDevice();
	g_D3DSettingsDlg.OnD3D11DestroyDevice();
	DXUTGetGlobalResourceCache().OnDestroyDevice();
	SAFE_DELETE(g_pTxtHelper);

	SAFE_RELEASE(g_pSamLinear);

	SAFE_RELEASE(g_pcbVSPerObject);
	SAFE_RELEASE(g_pcbPS);
	SAFE_RELEASE(g_pVB);
	SAFE_RELEASE(g_pVBPerInstance);
	SAFE_RELEASE(g_pVBSkinning);
	SAFE_RELEASE(g_pIB);
	SAFE_RELEASE(g_pVertexInputLayout);
	SAFE_RELEASE(g_pVertexShader);
	SAFE_RELEASE(g_pPixelShader);
}



