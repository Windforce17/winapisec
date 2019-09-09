// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#define DEF_PROCESS_NAME "notepad.exe"
HINSTANCE g_hInstance = NULL;
HHOOK G_hHook = NULL;
HWND g_hWnd = NULL;
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  dwReason,
                       LPVOID lpReserved
                     )
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
		g_hInstance = hModule;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

LRESULT CALLBACK KeyboardProc(	int nCode,
								WPARAM wParam, 
								LPARAM lParam) 
{
	char szPath[MAX_PATH] = { 0 };
	char* p=NULL;
	if (nCode == 0) {
		//bit 32:0=key press 1=key release
		if (!(lParam & 0x80000000))
		{
			GetModuleFileNameA(NULL, szPath, MAX_PATH);
			p = strrchr(szPath, '\\');
			if (!strcmp(p + 1, "notepad.exe")) {
				char s[2]= { wParam,0 };
				MessageBoxA(NULL, (LPCSTR)s, NULL, MB_OK);
				return CallNextHookEx(G_hHook, nCode, wParam+1, lParam);
			}
		}
	}
	return CallNextHookEx(G_hHook, nCode, wParam+1, lParam);
}
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
__declspec(dllexport) void HookStart()
{
	G_hHook=SetWindowsHookEx(WH_KEYBOARD,KeyboardProc, g_hInstance,0);
}
__declspec(dllexport)void HookStop() {
	if (G_hHook) {
		UnhookWindowsHookEx(G_hHook);
		G_hHook = NULL;
	}
}
#ifdef __cplusplus
}
#endif // __cplusplus