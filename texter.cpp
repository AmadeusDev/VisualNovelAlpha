//*
#include "Load.h"
UNIVERSAL	*access;
HWND hEdit;

LRESULT CALLBACK TxtProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_CREATE:
		{
			SetTimer(hwnd,NULL,50,NULL);

		}
		break;
	case WM_TIMER:
		{
			if (GetKeyState(VK_RETURN) & 0x8000)
			{
				char b[MAX_PATH] = "";
				string hmph = "";
				SendMessage(hEdit,WM_GETTEXT,MAX_PATH,(LPARAM)b);
				hmph = b;
				while (hmph.at(hmph.length()-1) == '\n')
					hmph.erase(hmph.length()-1,1);
				access->texter.text = hmph;
			}

		}
		break;
	case WM_DESTROY:
		{

			PostQuitMessage(NULL);
		}
		break;
	case WM_CLOSE:
		{

			DestroyWindow(hwnd);
		}
		break;
	}


	return DefWindowProc(hwnd,msg,wParam,lParam);
}

DWORD WINAPI Texter(LPARAM lParameter)
{
	static bool toto = false;
	SHARING *sharing;
	sharing = (SHARING*)lParameter;
	access = sharing->access;

	WNDCLASSEX	wc;
	HWND		hwnd;
	MSG			msg;

	memset(&wc,0,sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = (HBRUSH)2;
	wc.lpfnWndProc = TxtProc;
	wc.lpszClassName = "TEXTER";

	if (!RegisterClassEx(&wc) && toto == false)
		MessageBox(NULL,"FAILED REGISTER TEXTER","ERROR",MB_OK);
	else
		toto = true;

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"TEXTER","texter",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,240,120,0,0,0,0);

	if (!hwnd)
		MessageBox(NULL,"Wnd Create Failed","ERRORR",MB_OK);


	UpdateWindow(hwnd);
	ShowWindow(hwnd,SW_SHOW);
	access->texter.hwnd = hwnd;
	
LoadLibrary(TEXT("Msftedit.dll"));
InitCommonControls();

	COLORREF neco;
	neco = RGB(0,0,0);
	CHARFORMAT neco2;
	neco2.cbSize = sizeof(CHARFORMAT);
	neco2.crTextColor = RGB(0,255,0);
	neco2.dwMask = CFM_COLOR | CFM_EFFECTS;
	neco2.dwEffects = CFE_PROTECTED;

hEdit = CreateWindowEx(0, "RICHEDIT50W",NULL,
ES_MULTILINE | WS_VISIBLE | WS_CHILD | WS_TABSTOP|ES_AUTOVSCROLL|WS_VSCROLL| ES_WANTRETURN
, 
0,0, 240,120, 
hwnd, (HMENU)IDC_MAIN_EDIT, NULL, NULL);

	SendMessage(hEdit,EM_SETCHARFORMAT,SCF_ALL,(LPARAM)&neco2);
	SendMessage(hEdit,EM_SETBKGNDCOLOR,NULL,(LPARAM)neco);
	while (GetMessage(&msg,hwnd,0,0) > NULL)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}

	return 0;
}

//*/