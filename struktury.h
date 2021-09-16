
#ifdef _WIN32 
#define _CRT_SECURE_NO_DEPRECATE 
#endif

#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <GdiPlus.h>
#include <WinGDI.h>
#include <CommCtrl.h>
#include <Richedit.h>
#include <Vfw.h>
#include <mmsystem.h>

#ifndef MSFTEDIT_CLASS
#define MSFTEDIT_CLASS L"RICHEDIT50W";
#endif


#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"SOIL.lib")
#pragma comment(lib,"glu32.lib")

#include <cstdio>
#include "SOIL/SOIL.h"
#include <gl/gl.h>
#include <gl/glu.h>

#pragma comment(lib, "vfw32.lib") // na mp3
#pragma comment(lib,"comctl32.lib")
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib,"Msimg32.lib")

using namespace Gdiplus;
using namespace std;

#define		IDC_MAIN_EDIT	101

#define		WIN_WID			1366
#define		WIN_HEI			768
#define		BSC_WAY			"hry\\"

#define		MAIN_ADDR		"data\\*.txt"
#define		KEYS_ADDR		"data\\keys.txt"
#define		BGN_ADDR_S		"saves\\1\\*.txt"
#define		SVS_ADDR		"saves\\"
#define		LANGS_TXT		"hry\\*.txt"
#define		KEY_CNT			10
#define		SET_CNT			10
#define		BTN_CNT			20
#define		ANM_CNT			10
#define		SVS_CNT			50
#define		FRM_CNT			100
#define		PIC_CNT			10
#define		MENU_CNT		10
#define		INV_CNT			100
#define		ITM_CNT			400
#define		PSN_CNT			20
#define		GMF_CNT			500		
#define		STR_CNT			200
#define		STR_AMN			5000
#define		ODP_CNT			3
#define		MAP_CNT			20
#define		FNT_CNT			10
#define		CHR_CNT			131072
#define		OGL_ME_CNT		100
#define		OGL_MA_CNT		100
#define		OGL_PE_CNT		100
#define		OGL_SA_CNT		100
#define		OGL_BU_CNT		100
#define		IMG_CNT			500


#define		AOFFSET			50
#define		ERROR			"UNKNOWN"
#define		TEXTS			"texts.txt"
#define		PoèetTextur		4000

enum CONTROLS
{
	KEY_INVENTORY = 1,
	KEY_SAVE = 2,
	KEY_MENU = 3
};


enum LDER
{
	LOADER_W	=	100,
	LOADER_H	=	500,
	LOADER_AMT	=	10,
	LOADER_TS	=	15
};


enum _STATES
{
	STATE_MENU,
	STATE_GAME,

};


enum _DETECT
{
	_KEY,
	_POS,
	_BOTH,
	_DCNT
};


enum _BKIND
{
	ONCE,
	CLICKED,
	BCNT
};

struct DRECT
{
	double top;
	double bottom;
	double left;
	double right;
};


struct MEAS
{
	short					x;
	short					y;
	short					w;
	short					h;
};


struct COND
{
	short					map;
	short					item;
	short					events;

};


struct COOR
{
	short					folder;
	short					file;
};



struct NEXT_MAP
{
	bool					jo;
	char					map;
	bool					nové;
	COOR					coor;
};


struct WINDOWS
{
	HWND					hwnd;
	RECT					rect;
};


struct KEY
{
	int						which;
	short					once;
	short					clicked;
};


struct BKIND
{
	bool					switched;
	bool					active;
	short					save;
	short					frame;
	short					efect;
	short					change;

	void Nullify()
	{
		switched = 0;
		active = 0;
		save = 0;
		frame = 0;
		efect = 0;
		change = 0;
	}
};


struct BEVENT
{
	bool					active;
	short					key;
	BKIND					bkind[2];
};


struct FRAMES
{
	bool					snd;
	short					time;
	short					kind;
	short					kevent;
	short					save;
	short					frame;
	bool					active;
	short					reverse;

	void Nullify()
	{
		snd = 0;
		active = false;
		time = 0;
		kind = 0;
		kevent = 0;
		save = 0;
		frame = 0;
		reverse = 0;
	}
};


struct CONTROL
{
	bool					once;
	bool					clicked;
};


struct TEXT
{
	GLuint					base;
	string					text;
	RECT					meas;
	short					kind;
	short					size;
	short					size_w;
	__int8					red;
	__int8					green;
	__int8					blue;
	bool					before;

	void Nullify()
	{
		base = -1;
		text = "";
		kind = 0;
		size = 0;
		size_w = 0;
		red = 255;
		green = 255;
		blue = 255;
		before = 0;
		meas.left = 0;
		meas.top = 0;
		meas.right = 0;
		meas.bottom = 0;
	}

};


struct CHANGE
{
	short					kind;
	short					in;
	short					which;
	string					text;
	RECT					tect;
	short					t_bef;
	short					t_r;
	short					t_g;
	short					t_b;
	short					t_v;
	short					t_s;
	short					t_sw;

	void Nullify()
	{
		kind = -1;
		in = -1;
		which = 0;
		t_bef = 0;
		t_r = 0;
		t_g = 0;
		t_b = 0;
		t_v = 0;
		t_s = 0;
		t_sw = 0;

	}
};


struct BUTTON
{
	TEXT					text;
	FRAMES					frames;
	RECT					rect;
	RECT					image;
	DRECT					oøíznout;
	CONTROL					inrect;
	CONTROL					both;
	CHANGE					change;
	CONTROL					chng;
	short					kind;
	short					typ;
	short					spec;
	short					pic;
	float					RS;
	float					GS;
	float					BS;
	float					VS;
	float					dividerw;
	float					dividerh;
	short					angle;
	BEVENT					bevent[_DCNT];

	void Nullify()
	{
		text.Nullify();
		frames.Nullify();
		rect.left = 0;
		rect.top = 0;
		rect.right = 0;
		rect.bottom = 0;
		image.left = 0;
		image.top = 0;
		image.right = 0;
		image.bottom = 0;
		oøíznout.left = 0;
		oøíznout.top = 0;
		oøíznout.right = 0;
		oøíznout.bottom = 0;
		inrect.clicked = 0;
		inrect.once = 0;
		both.clicked = 0;
		both.once = 0;
		change.Nullify();
		chng.clicked = 0;
		chng.once = 0;
		kind = 0;
		typ = 0;
		spec = 0;
		pic = 0;
		RS = 1;
		GS = 1;
		BS = 1;
		VS = 1;
		dividerw = 0;
		dividerh = 0;
		angle = 0;
		for (int a = 0; a < _DCNT; a++)
		{
			bevent[a].active = 0;
			for (int b = 0; b < BCNT;b++)
				bevent[a].bkind[b].Nullify();
			bevent[a].key = 0;
		}
	}

};


struct IMAGE
{
	__int8					cols;
	__int8					rows;
	short					w;
	short					h;
	int						index;
	int						chos;
	string					address;

	void Nullify()
	{
		cols = 0;
		rows = 0;
		w = 0;
		h = 0;
		index = 0;
		chos = 0;
		address = "";
	}
};


struct MENU
{
	string					sound;
	BUTTON					btn[BTN_CNT];
	IMAGE					image;
	IMAGE					pozadí;
};


struct LOAD
{
	ifstream				ifile;
	WIN32_FIND_DATA			data;
	HANDLE					h;
	string					lang;

};


struct SET
{
	BUTTON					btn[BTN_CNT];
	IMAGE					image;
	short					save;
	short					frame;
	short					kind;
	RECT					rect;

};


struct SETS
{
	short					id;
	bool					first;
	SET						set[SET_CNT];
	FRAMES					frame;
	RECT					rect;

};


struct MENUS
{
	MENU					menu[MENU_CNT];
	SETS					set;
	short					id;
	bool					snd;

};

struct KEYS
{
	KEY						key[KEY_CNT];
	POINT					mouse;

};

struct SBUTTON
{
	short					frame;
	short					save;
	short					id;
	short					x;
	short					y;
	short					w;
	short					h;
	short					type;
	short					pic;
	short					reverse;
	bool					active;

};


struct FRAME
{
	bool					Changed;
	string					sound;
	SBUTTON					button[ANM_CNT];
	DRECT					oøíznout;
	string					SaveAdresa;
	short					pic;
	float					RS;
	float					GS;
	float					BS;
	float					VS;
	short					w;
	short					h;
	short					next;
	short					previous;
	short					time;
	short					kind;
	short					part;
	short					dvx;
	short					dvy;
	short					centerx;
	short					centery;
	short					angle;
	short					next_menu;
	float					dividerw;
	float					dividerh;
	short					mirror;
	short					set;
	
	COOR					Story;
	COOR					Map;
	COOR					Person;
	short					idS;
	short					idM;

	TEXT					text;

};


struct SAVES
{

	FRAME					frame[FRM_CNT];
	IMAGE					pic[PIC_CNT];
	bool					snd;
	COOR					coor;
	string					Kniha;
};


struct INVPLACE
{
	short					id;
	short					ammount;

};


struct INVENTORY
{
	INVPLACE				place[INV_CNT];
};


struct PERSON
{
	bool					Changed;
	RECT					rect;
	string					name;
	int						age;
	bool					sex;
	FRAMES					frame;
	INVENTORY				inventory;
	DRECT					oøíznout;
	IMAGE					image[PIC_CNT];
};


struct LD
{
	string					address;
	bool					load;
	COOR					frame;
	COOR					person;
	COOR					item;
	COOR					story;
};


struct ITEM
{
	string					name;
	FRAMES					frames;
};


struct ITEMS
{
	ITEM					item[ITM_CNT];
};

struct ODPOVÌÏ
{
	RECT					rect;
	short					next;
	TEXT					text;
	short					story;
	short					charakters;
	short					frames;
};


struct TXTBAR
{
	int						active;
	DRECT					drect;
	float					RS, GS, BS, VS;
};


struct MAP
{
	bool					Changed;
	string					sound;
	IMAGE					pozadí;
	IMAGE					image;
	DRECT					oøíznout;

	short					save;
	COOR					SvCoor;

	BUTTON					btn[BTN_CNT];

	void Nullify()
	{
		Changed = 0;
		sound = "";
		pozadí.Nullify();
		image.Nullify();
		save = 0;
		SvCoor.file = -1;
		SvCoor.file = -1;
		for (int a = 0; a < BTN_CNT; a++)
			btn[a].Nullify();
	}
};


struct MAPS
{
	MAP						map[MAP_CNT];
	COOR					coor;
	bool					snd;

	void Nullify()
	{
		for (int a = 0; a < MAP_CNT; a++)
			map[a].Nullify();
	}
};

struct STORIES
{
	string					address;
	void Nullify()
	{
		address = "";
	}
};


struct STORIESS
{
	STORIES					Stories[STR_AMN];
	int						count;

	void Nullify()
	{
		for (int a = 0; a < STR_AMN; a++)
			Stories[a].Nullify();
		count = 0;
	}

	bool FindEqual(string address)
	{
		for (int a = 0; a < count; a++)
		{
			if (address == Stories[a].address)
				return true;
		}
		return false;
	}
};


struct PLAYER
{
	PERSON					person;
	short					map;
	short					story;
	string					name;
	STORIESS				stories;
};


struct CONJURE
{
	bool					active;
	short					id;
	short					save;
	short					frame;
	short					condition;
	RECT					rect;
	COOR					coor;
};


struct STORY
{
	bool					Changed;
	string					sound;
	short					kind;
	COOR					coor;
	COOR					SaveCoor;
	COOR					FrameCoor;
	FRAMES					frames;
	short					frame;
	short					save;
	NEXT_MAP				NextMap;
	short					OdpCnt;
	ODPOVÌÏ					odpovìï[ODP_CNT];
	short					map;
	PERSON					*person;
	CONJURE					conjure;
	TEXT					text;
	short					cond;
	COND					conds;
	TXTBAR					txtbar;

	void Nullify()
	{
		memset(this, 0, sizeof(STORY));
	}
};


struct STORYLINE
{
	STORY					story[STR_CNT];
	COOR					coor;
	bool					snd;
	bool					active;

	void Nullify()
	{
		coor.file = 0;
		coor.folder = 0;
		snd = 0;
		active = 0;
		for (int a = 0; a < STR_CNT; a++)
		{
			story[a].Nullify();
		}
	}
};


struct TEXTBAR
{
	bool					active;
	TEXT					*text;
	DRECT					oøíznout;
	float					r;
	float					g;
	float					b;
	float					v;
	RECT					rect;
	IMAGE					image;
};


struct PERSONS
{
	PERSON					person[PSN_CNT];
	COOR					coor;
};


struct INGAME
{
	PLAYER					player;
	PERSONS					persons;
	ITEMS					items;
	MAPS					map;
	STORYLINE				story;
};


struct GAMES
{
	string					language;
	INGAME					data;
	TEXTBAR					textbar;
};


struct TEXTER
{
	HWND					hwnd;
	HWND					hEdit;
	string					text;
	DWORD					Tid;
	HANDLE					handle;
	DWORD					exitCode;
};


struct LOADER
{
	HWND					hwnd;
	HDC						hdc;
	HDC						buffer;
	string					text;
	DWORD					Tid;
	HANDLE					handle;
	DWORD					exitCode;
};

struct OPENGL
{
	bool MáObrázek;
	int W;
	int H;
	GLuint index;
	float m[4][4];
	int w;
	int h;
	int cols;
	int rows;
	string address;
};


struct GAME_DSN
{
	OPENGL	obraz[IMG_CNT];
	string	Kniha;

	void Nullify()
	{
		Kniha = "";
		for (int a = 0; a < IMG_CNT; a++)
		{
			obraz[a].index = -1;
			obraz[a].MáObrázek = false;
		}
	}

	void DeleteGL()
	{
		for (int a = 1; a < IMG_CNT; a++)
		{
			if (obraz[a].index < 1000000)
				glDeleteTextures(1, &obraz[a].index);
		}
	}
};


struct OPENGLY
{
	GAME_DSN Story;
	GAME_DSN svs;
	GAME_DSN Mp;
	GAME_DSN Btns;

	OPENGL menu[OGL_ME_CNT];
	OPENGL map[OGL_MA_CNT];
	OPENGL button[OGL_BU_CNT];
	OPENGL save[OGL_SA_CNT];
	OPENGL font[FNT_CNT];
	int menus;
	int fonts;
	int maps;
	int buttons;
	int saves;

	void Nullify()
	{
		NullifyMenus();
		NullifySaves();
		NullifyButtons();
		NullifyMaps();
		NullifyFonts();
	}

	void NullifyMenus()
	{
		for (int a = 0; a < OGL_ME_CNT; a++)
		{
			menu[a].index = -1;
			menu[a].MáObrázek = false;
		}
		menus = 0;
	}

	void NullifyFonts()
	{
		for (int a = 0; a < FNT_CNT; a++)
		{
			font[a].index = -1;
			font[a].MáObrázek = false;
		}
		fonts = 0;
	}

	void NullifyButtons()
	{
		for (int a = 0; a < OGL_BU_CNT; a++)
		{
			button[a].index = -1;
			button[a].MáObrázek = false;
		}

		buttons = 0;
	}

	void NullifyMaps()
	{
		for (int a = 0; a < OGL_MA_CNT; a++)
		{
			map[a].index = -1;
			map[a].MáObrázek = false;
		}
		maps = 0;
	}

	void NullifySaves()
	{
		for (int a = 0; a < OGL_SA_CNT; a++)
		{
			save[a].index = -1;
			save[a].MáObrázek = false;
		}
		saves = 0;
	}
};


struct GAME
{
	short					InGameMenu;
	MENUS					menus;
	GAMES					games;
	KEYS					keys;
	SAVES					save[SVS_CNT];
	short					state;
	BUTTON					anime[ANM_CNT];
	SETS					sets;
	OPENGLY					opengly;
};


struct GRAPH
{
	HGLRC					hRC;
	HDC						hdc;
	HDC						buffer;
	HDC						basics;
	float					dividerw;
	float					dividerh;
	ULONG_PTR				token;
	GdiplusStartupInput		GSI;
	GdiplusStartupOutput	GSO;
	Graphics				*graph;
	float					matrix[4][4];
	ColorMatrix				clrMatrix;
	ImageAttributes			imgAttr;
	bool					colorMatr;
	short					angle;
};


struct DETAIL
{
	bool					twice;
};


struct MP3
{
	string	address;
	HWND	msc;
};


struct FONTS
{
	IMAGE image;
	string name;
	double W[CHR_CNT];
	void Nullify()
	{
		for (int a = 0; a < CHR_CNT; a++)
			W[a] = 1.0;

		name = "";
		image.cols = 0;
		image.rows= 0;
		image.w = 0;
		image.h = 0;
		image.address = "";
		image.index = -1;
		image.chos = -1;
	}
};

struct VLAJKY
{
	short		story; //wtf!!! ;,,,-(

	bool StoryInProgress;
	string StoryAddress;

	void Nullify()
	{
		StoryInProgress = false;
	}
};

struct DATA
{
	OPENGLY opengl;
	FONTS	font[FNT_CNT];
	VLAJKY flags;
};

#ifndef HEADER_H
#define HEADER_H

extern DATA Data;
extern string LANGS_ADDR;

#endif // !HEADER_H


struct UNIVERSAL 
{
	TEXTER					texter;
	LOADER					loader;
	WINDOWS					wnd;
	GAME					game;
	LOAD					load;
	GRAPH					graph;
	DETAIL					detail;
	MP3						mp3;
};


struct SHARING
{
	UNIVERSAL				*access;
	short					kind;
	short					in;
	short					which;

};