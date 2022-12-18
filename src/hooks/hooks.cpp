#include <pch.h>
#include <base.h>
#include "../utils/FunctionHook.hpp"

static uintptr_t D3DEndSceneJumpReturn;
static FunctionHook* EndSceneFunctionHookInstance;
//Helper Functions Declarations

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam);
HWND GetProcessWindow();
bool GetD3D9Device(void** pTable, size_t Size);

//Functions

__declspec(naked) void D3DEndSceneDetour(void) {
	__asm {
		call Base::Hooks::EndScene
	//originalInstructions:
		; call edx // we'll call pDevice->EndScene in our hook
		xor ecx,ecx
		test eax, eax

		jmp DWORD PTR [D3DEndSceneJumpReturn]
	}
}

bool Base::Hooks::Init()
{

#if 0
	if (GetD3D9Device((void**)Data::pDeviceTable, D3DDEV9_LEN))
	{
#		if defined(MEM_86)
		mem::detour_t detour_method = mem::MEM_DT_M1;
#		elif defined(MEM_64)
		mem::detour_t detour_method = mem::MEM_DT_M0;
#		endif

		Data::pEndScene = Data::pDeviceTable[42];
		Data::oEndScene = (EndScene_t)mem::in::detour_trampoline((mem::voidptr_t)Data::pEndScene, (mem::voidptr_t)Hooks::EndScene, Data::szEndScene);

		return true;
	}

	return false;
#else
	static constexpr uintptr_t EndSceneCall = 0x0C53E2E;
	DWORD oldprotect;
	constexpr size_t detour_length = 6;
	VirtualProtect((void*)EndSceneCall, detour_length, PAGE_EXECUTE_READWRITE, &oldprotect);
	memset((void*)EndSceneCall, 0x90, detour_length);
	VirtualProtect((void*)EndSceneCall, detour_length, oldprotect, &oldprotect);
	EndSceneFunctionHookInstance = new FunctionHook(EndSceneCall, &D3DEndSceneDetour);
	D3DEndSceneJumpReturn = EndSceneCall + detour_length;
	return EndSceneFunctionHookInstance->create();
#endif
}

bool Base::Hooks::Shutdown()
{
	if (Data::InitImGui)
	{
		ImGui_ImplDX9_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	mem::in::detour_restore(Data::pEndScene, (mem::byte_t*)Data::oEndScene, Data::szEndScene);
	SetWindowLongPtr(Data::hWindow, WNDPROC_INDEX, (LONG_PTR)Data::oWndProc);

	return true;
}

//Helper Functions Definitions

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
	DWORD wndProcId = 0;
	GetWindowThreadProcessId(handle, &wndProcId);

	if (GetCurrentProcessId() != wndProcId)
		return TRUE;

	Base::Data::hWindow = handle;
	return FALSE;
}

HWND GetProcessWindow()
{
	Base::Data::hWindow = (HWND)NULL;
	EnumWindows(EnumWindowsCallback, NULL);
	return Base::Data::hWindow;
}

bool GetD3D9Device(void** pTable, size_t Size)
{
	if (!pTable)
		return false;

	Size *= sizeof(void*);

	IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (!pD3D)
		return false;

	IDirect3DDevice9* pDummyDevice = NULL;

	D3DPRESENT_PARAMETERS d3dpp = {};
	d3dpp.Windowed = false;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	Base::Data::hWindow = GetDesktopWindow();
	d3dpp.hDeviceWindow = Base::Data::hWindow;
	//d3dpp.hDeviceWindow = GetProcessWindow(); // old
	

	HRESULT dummyDeviceCreated = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);

	if (dummyDeviceCreated != S_OK)
	{
		d3dpp.Windowed = !d3dpp.Windowed;
		dummyDeviceCreated = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);

		if (dummyDeviceCreated != S_OK)
		{
			pD3D->Release();
			return false;
		}
	}

	memcpy(pTable, *reinterpret_cast<void***>(pDummyDevice), Size);

	pDummyDevice->Release();
	pD3D->Release();
	return true;
}