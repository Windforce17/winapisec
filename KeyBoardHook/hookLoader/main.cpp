#include<Windows.h>
#include<cstdio>
typedef void(*PFN_HOOKSTART)();
typedef void(*PFN_HOOKSTOP)();

int main() {
	HMODULE hDll = NULL;
	PFN_HOOKSTART HookStart = NULL;
	PFN_HOOKSTOP HookStop = NULL;
	char ch = 0;
	hDll = LoadLibrary("KeyHook.dll");
	if (hDll==NULL) return 0;
	HookStart =(PFN_HOOKSTART)GetProcAddress(hDll, "HookStart");
	HookStop = (PFN_HOOKSTOP)GetProcAddress(hDll, "HookStop");
	HookStart();
	printf("press q to quit!\n");
	while (getchar() != 'q');
	HookStop();
	FreeLibrary(hDll);
}