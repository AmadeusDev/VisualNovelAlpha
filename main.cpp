/*
	Špatná detekce odpovìdí!!!
	Dodìlat zobrazování písma do úplného stavu.
	Dodìlat Menu do pùvodního stavu
	Pøidat možnost pøehrávání více MP3 souborù za ráz.
	Vytvoøit inventáø
	Vytvoøit možnost zisku achievementù




*/




#include "odkazy.h"
const char *name = "Visual Novela";
const char *class_name = "game";
UNIVERSAL access;
DATA Data;
string LANGS_ADDR;
/*
int main()
{

	Load(&access,MAIN_ADDR);
	cout << sizeof(FRAME) << endl;
	cout << "access.game.menus.menu[0].btn[0].bevent[_KEY].bkind[ONCE].frame: " << access.game.menus.menu[0].btn[0].bevent[_KEY].bkind[ONCE].frame << endl;
	cout << "access.game.save[0].pic[0].address: " << access.game.save[0].pic[0].address << endl;
	system("PAUSE");
	return 0;
}//*/

//*
LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	static bool once = false;
	switch(msg)
	{
	case WM_CREATE:
	{
		LANGS_ADDR = BSC_WAY;
		Data.opengl.menus = 0;
		Data.opengl.maps = 0;
		Data.opengl.buttons = 0;
		Data.opengl.saves = 0;
		Data.flags.Nullify();
		
		Data.opengl.Mp.Nullify();

		access.mp3.msc = MCIWndCreate(hwnd, GetModuleHandle(NULL), WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR | MCIWNDF_NOMENU, NULL);
		short num = 0;
		if ( num = Load(&access,MAIN_ADDR) < 0) //pokud load vrátí èíslo menší nule vypíše se hláška "failed" s nadpiskem "error"
			MessageBox(NULL,"failed","error",MB_OK);
		if (num > 0)
			MessageBox(NULL,convert(num).c_str(),"failed:",MB_OK); //pokud load vrátí èíslo vìtší nule vypíše se hláška "failed"

		access.detail.twice = false;
		SetTimer(hwnd,0,10,0);
	}
	break;

	case WM_TIMER:
	{
		if (once == false)
		{
			once = true;
			Basics_Setup(&access);
			graph_load(&access);
			access.detail.twice = true;
			//*
			DWORD  Tid;
			CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)(void*)&Timer,NULL,NULL,&Tid);
			//*/
		}
		if (once == true,access.detail.twice == true)
			Proc(&access);
	}
	break;
	case WM_CLOSE:
		{
			memset(access.game.sets.set,0,sizeof(SET)*SET_CNT);
			DestroyWindow(hwnd);
		}
	break;
	case WM_DESTROY:
		{
			memset(access.game.sets.set,0,sizeof(SET)*SET_CNT);
			PostQuitMessage(NULL);
		}
	break;

	default:
		break;
	}

	return DefWindowProc(hwnd,msg,wParam,lParam);
}


int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR cmdLine,int nCmdShow)
{
	MSG msg;
	HWND hwnd;
	WNDCLASSEX wc;
	
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = (HBRUSH)2;
	wc.cbWndExtra = 0;
	wc.hCursor = 0;
	wc.hIcon  = 0;
	wc.hIconSm = 0;
	wc.hInstance = 0;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = class_name;
	wc.lpszMenuName = 0;
	wc.style= 0;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL,"Register failed","error",MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, class_name, name, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 0, 0, WIN_WID, WIN_HEI, NULL, NULL, NULL, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL,"creation failed","error",MB_OK);
		return 0;
	}
	
	GetClientRect(hwnd,&access.wnd.rect);
	access.wnd.hwnd = hwnd;

	UpdateWindow(hwnd);
	ShowWindow(hwnd,nCmdShow);

	while (GetMessage(&msg,hwnd,NULL,NULL) > NULL)
	{

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}


//*/