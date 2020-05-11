#include <Windows.h>

DWORD localPlayer = 0xD2FB94;
DWORD forceJump = 0x51ED780;
DWORD flags = 0x104;
DWORD gameModule;
BYTE flag;

struct vector
{
	float x, y, z;
};

int main()
{
	gameModule = (DWORD)GetModuleHandle("client_panorama.dll");
	localPlayer = *(DWORD*)(gameModule + localPlayer);

	if (localPlayer == NULL)
		while (localPlayer == NULL)
			localPlayer = *(DWORD*)(gameModule + localPlayer);

	while (!GetAsyncKeyState(VK_END))
	{
		flag = *(BYTE*)(localPlayer + flags);

		if (GetAsyncKeyState(VK_SPACE) && flag & (1 << 0))
			*(DWORD*)(gameModule + forceJump) = 6;
	}
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH) {

		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)main, NULL, NULL, NULL);

	}
	return TRUE;
}