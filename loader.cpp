//*
#include "Load.h"

int GetSavesAmmount(char *file);
void TxtDraw(string *str,short sizew,short sizeh,HDC hdc,RECT *rect);
int GetSaves(int page,string *str,int amt);
string CurSel(HDC hdc,HWND hwnd,int OnPage,string *str);
void LoadSave(string file);

UNIVERSAL *accessory;

#define TXT_SIZEW 10
#define TXT_SIZEH 20
#define LOADER_W 200
#define LOADER_H 500


LRESULT CALLBACK Procedure(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	static int Ammount = 0;
	static int SavesCount = 0;
	static int page = 0;
	static bool once = false;
	static int OnPage = 0;
	switch(msg)
	{
	case WM_CREATE:
		{
			accessory->loader.hwnd = hwnd;
			Ammount = LOADER_H/TXT_SIZEW-1;
			SavesCount = GetSavesAmmount(SVS_ADDR);
			SetTimer(hwnd,NULL,50,NULL);
			once = true;
		}
		break;

	case WM_TIMER:
		{
			if (once == true)
			{
				once = false;
				HDC hdc;
				RECT rect;
				string str;
				string word = "";
				GetClientRect(hwnd,&rect);
				HBITMAP hbmp = CreateCompatibleBitmap(GetDC(hwnd),rect.right,rect.bottom);
				hdc = CreateCompatibleDC(GetDC(hwnd));
				SelectObject(hdc,hbmp);

				OnPage = GetSaves(page,&str,Ammount);
				FillRect(hdc,&rect,(HBRUSH)2);
				word = CurSel(hdc,hwnd,OnPage,&str);
				TxtDraw(&str,TXT_SIZEW,TXT_SIZEH,hdc,&rect);

				BitBlt(GetDC(hwnd),0,0,rect.right,rect.bottom,hdc,0,0,SRCCOPY);
				DeleteObject(hbmp);
				DeleteDC(hdc);

				if (word != "")
				{
					LoadSave(word);

				}

				once = true;
			}
		}
		break;

	case WM_CLOSE:
		{
			DestroyWindow(hwnd);
		}
		break;

		

	case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		break;


	}

	return DefWindowProc(hwnd,msg,wParam,lParam);
}


void LoadSave(string file)
{
	ifstream ifile;
	string word;
	string lang;

	word = SVS_ADDR;
	word += file;
	word += ".txt";
	ifile.open(word);
	Data.flags.StoryAddress = "main";


	if (!ifile.is_open())
	{
		MessageBox(NULL,file.c_str(),"error",MB_OK);
		return;
	}


	while (ifile.good())
	{
		ifile >> word;
		LoadSaveInners(&ifile, &lang, &accessory->game.games.data,&word);

	}

	ifile.close();
	
	accessory->game.games.textbar.r = 1;
	accessory->game.games.textbar.g = 1;
	accessory->game.games.textbar.b = 1;
	accessory->game.games.textbar.v = 0.50;
	accessory->game.games.textbar.image.address = "openedbook.bmp";
	accessory->game.games.textbar.image.w = 1;
	accessory->game.games.textbar.image.h = 1;
	accessory->game.games.textbar.image.cols = 1;
	accessory->game.games.textbar.image.rows = 1;
	accessory->game.games.textbar.rect.left = 0;
	accessory->game.games.textbar.rect.top = WIN_HEI-400;
	accessory->game.games.textbar.rect.right = WIN_WID;
	accessory->game.games.textbar.rect.bottom = 150;
	accessory->game.games.data.player.name = file;

	
	accessory->game.games.language = lang;
}


string CurSel(HDC hdc,HWND hwnd,int OnPage,string *str)
{
	
	if (GetForegroundWindow() != hwnd)
		return "";
	RECT Rect;
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(hwnd,&p);
	
	if (!(p.x < LOADER_W && p.x > 0 && p.y < LOADER_H && p.y > 0))
	{
		return "";
	}


	int which = p.y/(TXT_SIZEH+5);
	

	Rect.top = which*(TXT_SIZEH+5);
	Rect.bottom = which*(TXT_SIZEH+5) + (TXT_SIZEH+5);
	Rect.right = LOADER_W;


	if (which < OnPage)
	{
		FillRect(hdc,&Rect,(HBRUSH)(COLOR_WINDOW + 2));
	}
	else
		return "";
	if (GetKeyState(VK_LBUTTON) & 0x8000)
	{
		int a = 0,b = 0,c = 0;
		while (a < str->length())
		{
			if (str->at(a) == '\n')
			{
				if (b == which)
					break;
				b++;
				c = a;
			}
			a++;
		}
		if (c == 0)
			c--;
		return str->substr(c+1,a-c-1);
	}
	return "";

}


int GetSavesAmmount(char *file)
{
	int cnt = 0;

	return cnt;
}


int GetSaves(int page,string *str,int amt)
{
	WIN32_FIND_DATA data;
	HANDLE			ha;
	int				cnt = 0;
	int				count = 0;
	int				w = LOADER_W/LOADER_AMT;
	int				h = LOADER_H/LOADER_AMT;


	*str = "";
	string addr = SVS_ADDR;
	addr += "*.txt";
	ha = FindFirstFile(addr.c_str(),&data);

	cnt++;
	if (cnt > page*amt)
	{
		*str += data.cFileName;
		str->erase(str->length()-4,4);
		*str += '\n';
	}

	if (page*amt +amt == cnt)
		return cnt - page*amt;

	while (FindNextFile(ha,&data))
	{

		cnt++;
		if (cnt > page*amt)
		{
			*str += data.cFileName;
			str->erase(str->length()-4,4);
			*str += '\n';
		}

		if (page*amt +amt == cnt)
			return cnt - page*amt;

	}

	return cnt - page*amt;
}


void TxtDraw(string *str,short sizew,short sizeh,HDC hdc,RECT *rect)
{
	HFONT	hFont;
	RECT	Rect;
	SetTextColor(hdc, RGB(255,255,255));
	SetBkMode(hdc,TRANSPARENT);

	hFont = CreateFont(sizeh,sizew,1,1,10,FALSE,NULL,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT(""));
	
	SelectObject(hdc,hFont);
	
	Rect.top = rect->top;
	Rect.left = rect->left;

	DrawText(hdc, TEXT(str->c_str()), -1,&Rect, DT_NOCLIP);	
	DeleteObject(hFont);
}


DWORD WINAPI Loader(LPARAM lParam)
{
	static bool toto = false;
	accessory = (UNIVERSAL *)lParam;
	WNDCLASSEX	wc;
	HWND		hwnd;
	MSG			msg;

	memset(&wc,0,sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = (HBRUSH)2;
	wc.lpfnWndProc = Procedure;
	wc.lpszClassName = "LOADER";

	if (!RegisterClassEx(&wc) && toto == false)
		MessageBox(NULL,"FAILED REGISTER TEXTER","ERROR",MB_OK);
	else
		toto = true;

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"LOADER","loader",WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,CW_USEDEFAULT
		,CW_USEDEFAULT,LOADER_W,LOADER_H,0,0,0,0);

	if (!hwnd)
		MessageBox(NULL,"Wnd Create Failed","ERRORR",MB_OK);


	UpdateWindow(hwnd);
	ShowWindow(hwnd,SW_SHOW);

	while (GetMessage(&msg,hwnd,0,0) > NULL)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}

	return 0;
}

void LoadSaveInners(ifstream *ifile, string *lang, INGAME *data,string *word)
{
	if (*word == "language:")
	{
		*ifile >> *word;
		*lang = *word;
	}

	if (*word == "NameOfBook:")
	{
		*ifile >> *word;
		Data.flags.StoryAddress = *word;
	}

	if (*word == "maps:")
	{
		*ifile >> *word;
		data->map.coor.folder = atoi(word->c_str());
		*ifile >> *word;
		data->map.coor.file = atoi(word->c_str());
		*ifile >> *word;
		data->player.map = atoi(word->c_str());
	}

	if (*word == "story:")
	{
		*ifile >> *word;
		data->story.coor.folder = atoi(word->c_str());
		*ifile >> *word;
		data->story.coor.file = atoi(word->c_str());
		*ifile >> *word;
		data->player.story = atoi(word->c_str());
	}

	if (*word == "persons:")
	{
		*ifile >> *word;
		data->persons.coor.folder = atoi(word->c_str());
		*ifile >> *word;
		data->persons.coor.file = atoi(word->c_str());
	}
}