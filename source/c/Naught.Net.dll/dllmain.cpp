#include "stdafx.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	};
	return TRUE;
};

extern "C"
{
	__declspec(dllexport) void __stdcall RVExtension(char *output, int outputSize, const char *inputString); 
};

void __stdcall RVExtension(char *output, int outputSize, const char *inputString)
{
	outputSize -= 1;



	strncpy(output, inputString, outputSize);
};