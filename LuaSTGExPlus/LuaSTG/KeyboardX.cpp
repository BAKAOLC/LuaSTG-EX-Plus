#include "AppFrame.h"
#include <Windows.h>  


#define MAX_KEY 512
HHOOK g_hHook = NULL;
bool g_bKeyStates[MAX_KEY];
/*
struct _KeyboardHook
{
	_KeyboardHook(){
		memset(g_bKeyStates, 0, sizeof(bool)*MAX_KEY);
		g_hHook = SetWindowsHookEx(WH_KEYBOARD , MessageBoxProc, NULL, GetCurrentThreadId());
	}
	~_KeyboardHook(){
		UnhookWindowsHookEx(g_hHook);
	}
};




LRESULT CALLBACK MessageBoxProc(
	INT nCode, WPARAM wParam, LPARAM lParam
	)
{
	if (nCode < 0)
		return CallNextHookEx(g_hHook, nCode, wParam, lParam);

	if (wParam >= 0 && wParam<=MAX_KEY)//当按“F3”键时卸载Hook  
	{

		//UnhookWindowsHookEx(g_hHook);//卸载HOOk函数  
	}
	else
	{
		
	}
	return 0;
}*/