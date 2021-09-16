#include "Load.h"
void Load_Menu(GAME *game,LOAD *load);
void Menu_load(LOAD *load,MENU *menu);
bool read(UNIVERSAL *access,char *file_name,char *folder_name);
void ConPaToIm(IMAGE *image,char *name);
void Keys_Load(KEYS *keys,LOAD *load);
void SaveAntiBug(SAVES svs[],int count);
void NullifySaves(SAVES saves[]);


short Load(UNIVERSAL *access,char *folder_name)
{
	Data.opengl.Nullify();

	for (int a = 0; a < FNT_CNT; a++)
		Data.font[a].Nullify();

	short failed = NULL;
	access->load.h = FindFirstFile(folder_name,&access->load.data);

	if (access->load.h == NULL)
		return -1;
	
	if (!read(access,access->load.data.cFileName,folder_name))
		failed++;

	while (FindNextFile(access->load.h,&access->load.data))
	{
		if (!read(access,access->load.data.cFileName,folder_name))
			failed++;

	}

	NullifySaves(access->game.save);

	return failed;
}




void NullifySaves(SAVES saves[])
{
	for ( int a = 3; a < BTN_CNT;a++ )
	{
		saves[a].coor.file = -1;
		saves[a].coor.folder = -1;
	}

}


bool read(UNIVERSAL *access,char *file_name,char *folder_name)
{
	string cnvrt;
	string temp;
	LOAD *load;
	load = &access->load;
	cnvrt = folder_name;
	cnvrt.erase(cnvrt.length()-5,5);
	cnvrt += file_name;
	load->lang = "Èj";
	load->ifile.open(cnvrt);

	if (!load->ifile.is_open())
		return false;

	cnvrt = "";
	getline(load->ifile,cnvrt);

	temp = "MENU";
	if (cnvrt.substr(0,temp.length()) == temp)
	{
		Load_Menu(&access->game,&access->load);

	}

	temp = "SET";
	if (cnvrt.substr(0,temp.length()) == temp)
	{
		Load_sets(&access->game.sets,&access->load);

	}

	temp = "KEYS";
	if (cnvrt.substr(0,temp.length()) == temp)
	{
		Keys_Load(&access->game.keys,&access->load);

	}

	temp = "SAVES";
	if (cnvrt.substr(0, temp.length()) == temp)
	{

		Saves_Load(load, &access->game.save[atoi(cnvrt.substr(temp.length() + 1, cnvrt.length()).c_str())]);

	}

	temp = "FONT";
	if (cnvrt.substr(0, temp.length()) == temp)
	{
		LoadFont(load);
	}
	load->ifile.close();
	return true;
}

void Keys_Load(KEYS *keys,LOAD *load)
{
	string	word;
	short	id;
	while(load->ifile.good())
	{
		load->ifile >> word;
		id = atoi(word.c_str());
		load->ifile >> word;
		if (id < KEY_CNT && id >= 0)
			keys->key[id].which = atoi(word.c_str());
	}

}


void Load_Menu(GAME *game,LOAD *load)
{
	string temp;
	string word;
	short id;


	while (load->ifile.good())
	{
		load->ifile >> word;

		temp = "ingame_menu:";
		if (word == temp)
		{
			load->ifile >> word;
			game->InGameMenu = atoi(word.c_str());
		}

		temp = "menu:";
		if (word == temp)
		{
			load->ifile >> word;
			id = atoi(word.c_str());
			Menu_load(load,&game->menus.menu[id]);
		}

	}

}


void Menu_load(LOAD *load,MENU *menu)
{
	string temp;
	string word;
	short id = 0;

	Proèista(menu->btn,BTN_CNT);

	while (load->ifile.good() && word != "konec:")
	{
		load->ifile >> word;

		
		if (word == "/*")
			while (word != "*/")
				load->ifile >> word;

		if (word == "sound:")
		{
			load->ifile >> word;
			menu->sound = word;
		}

		temp = "pole:";  
		if (word == temp)
		{
			load->ifile >> word;
			id = atoi(word.c_str());
			pole_load(load,&menu->btn[id]);
			word = "";
		}

		temp = "image:";
		if (temp == word)
		{
			load->ifile >> word;
			menu->image.address = word;
			load->ifile >> word;
			menu->image.cols = atoi(word.c_str());
			load->ifile >> word;
			menu->image.rows = atoi(word.c_str());
			load->ifile >> word;
			menu->image.w = atoi(word.c_str());
			load->ifile >> word;
			menu->image.h = atoi(word.c_str());
			menu->image.chos = 1;
			menu->image.index = CreateOpenGLPIC(1, &menu->image);
		}

		temp = "pozadí:";
		if (temp == word)
		{
			load->ifile >> word;
			menu->pozadí.index = CreateOpenGLPIC(0,word);
			menu->pozadí.chos = 0;
			menu->pozadí.cols = 1;
			menu->pozadí.rows = 1;
		}


	}


}


void graph_load(UNIVERSAL *access)
{
	HBITMAP	basics;
	HBITMAP	buffer;


	access->graph.hdc = GetDC(access->wnd.hwnd);
	

	access->graph.basics = CreateCompatibleDC(access->graph.hdc);
	access->graph.buffer = CreateCompatibleDC(access->graph.hdc);

	basics = CreateCompatibleBitmap(access->graph.hdc,access->wnd.rect.right,access->wnd.rect.bottom);
	buffer = CreateCompatibleBitmap(access->graph.hdc,access->wnd.rect.right,access->wnd.rect.bottom);
	
	SelectObject(access->graph.basics,basics);
	SelectObject(access->graph.buffer,buffer);
	
	FillRect(access->graph.basics,&access->wnd.rect,(HBRUSH)WHITE_BRUSH);
	FillRect(access->graph.buffer,&access->wnd.rect,(HBRUSH)WHITE_BRUSH);


	GdiplusStartup(&access->graph.token,&access->graph.GSI,&access->graph.GSO);

	DeleteObject(basics);
	DeleteObject(buffer);
}//*/

void Basics_Setup(UNIVERSAL *access)
{
	access->game.menus.id = NULL;
	SaveAntiBug(access->game.save,SVS_CNT);
	startPnt(&access->graph);

}

void SaveAntiBug(SAVES svs[],int count)
{
	int cnt = NULL;

	while (cnt < count)
	{
		memset(&svs[cnt].coor,-1,sizeof(COOR));
		cnt++;
	}

}

void Proèista(BUTTON btn[],int count)
{
	int cnt = 0;

	while (cnt < count)
	{
		btn[cnt].change.kind = -1;
		cnt++;
	}
}