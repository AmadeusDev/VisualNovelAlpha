#include "odkazy.h"
void MenuDrawing(UNIVERSAL *access,GRAPH *graph,MENU *menu);
bool SetSim(UNIVERSAL *access,SETS *sets);
void Set_main(UNIVERSAL *access,SETS *sets);
void Changes(UNIVERSAL *access,GAME *game,CHANGE *change);
void Fold_Get(UNIVERSAL *access,WIN32_FIND_DATA *data,SET *set,int &cnt,int minus);
void Set_Kind(UNIVERSAL *access,SET *set);
void UseFolders(UNIVERSAL *access,LOAD *load,SET *set,char *filename,int minus);


void menu(UNIVERSAL *access,MENUS *menu)
{
	static short mId = -1;
	MENU *menus;
	KEYS *keys;
	keys = &access->game.keys;
	menus = &menu->menu[menu->id];

#pragma region |Menu Sounds|

	if (mId != menu->id)
	{
		menu->snd = false;
		mId = menu->snd;
	}

	if (!menu->snd && menus->sound != "")
	{
		PlaySoundFile(access,menus->sound);
		menu->snd = true;
	}

#pragma endregion

	startPnt(&access->graph);
	MenuDrawing(access,&access->graph,&menu->menu[menu->id]);
	SetSim(access,&access->game.sets);
	buttonClicked(access,menus->btn,BTN_CNT,keys);
	MenuFrames(access,menus->btn,BTN_CNT,access->game.save);
}


void MenuFrames(UNIVERSAL *access,BUTTON btn[],short count,SAVES save[])
{
	int cnt = NULL;

	while (cnt < count)
	{

		if (btn[cnt].change.kind >= 0)
		{
			if (btn[cnt].chng.clicked == true)
				Changes(access,&access->game,&btn[cnt].change);

			btn[cnt].chng.clicked = false;
		}

		if (btn[cnt].frames.active == true)
		{
			Frames(access,&btn[cnt].frames,save,&btn[cnt].image);
			PostChanges(&btn[cnt]);
		}
		cnt++;
	}


}


void Changes(UNIVERSAL *access,GAME *game,CHANGE *change)
{
	MENU	*menu;
	SET		*set;
	BUTTON	*button;
	switch(change->kind%10)
	{
		case 0:
			{
				menu = &game->menus.menu[change->in];
				button = &game->menus.menu[change->in].btn[change->which];
			}
		break;
		
		case 1:
			{
				set = &game->sets.set[change->in]; 
				button = &game->sets.set[change->in].btn[change->which];
			}
		break;
	}
	if (change->text != "" && !(change->kind/10))
	{
		button->text.text = change->text;
		button->text.red = change->t_r;
		button->text.blue = change->t_b;
		button->text.green = change->t_g;
		button->text.size = change->t_s;
		button->text.size_w = change->t_sw;
		memcpy(&button->text.meas,&change->tect,sizeof(RECT));
		button->text.before = change->t_bef;
	}

	switch(change->kind/10)
	{
	case 1:
		{
			//*
			SHARING sharing;

			sharing.access = access;
			access->texter.handle = CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)(void*)&Texter,&sharing,NULL,&access->texter.Tid);
			GetExitCodeThread(access->texter.handle,&access->texter.exitCode);
			Sleep(1000);
			access->texter.text = "";
			
			SetForegroundWindow(access->texter.hwnd);
			while (access->texter.text == "" && IsWindow(access->texter.hwnd));
			TerminateThread(access->texter.handle,access->texter.exitCode);

			button->text.text = access->texter.text;
			//*/
		}
		break;
	case 2:
		{
			if (startGame(access,menu))
				AbsStartGame(access,&access->game.games);
		}
		break;
	case 3:
		{
			access->loader.handle = CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)(void*)&Loader,access,NULL,&access->loader.Tid);
			GetExitCodeThread(access->loader.handle,&access->loader.exitCode);
			Sleep(1000);
			
			access->game.games.language = "";
			SetForegroundWindow(access->loader.hwnd);
			while (access->game.games.language == "")
			{
				if (WaitForSingleObject(access->loader.handle,0) == WAIT_OBJECT_0)
				{
					return;
				}
			}

			Sleep(100);
			TerminateThread(access->loader.handle,access->loader.exitCode);
			AbsStartGame(access,&access->game.games);

		}
		break;
	case 4:
			game->games.language = game->menus.menu[game->menus.id].btn[1].text.text;
			AbsStartGame(access,&access->game.games);
		break;
	}
}


void PostChanges(BUTTON *btn)
{
	FRAMES *frames;

	if (btn->frames.kind == CLICKED)
	{
		btn->frames.active = btn->bevent[btn->frames.kevent].bkind[btn->frames.kind].active;
	}

	if (btn->frames.active || btn->frames.kind == -1 || btn->frames.kevent == -1)
		return;
	frames = &btn->frames;
	btn->bevent[frames->kevent].bkind[frames->kind].active = false;
}


void MenuDrawing(UNIVERSAL *access,GRAPH *graph,MENU *menu)
{
	InitGL(access);
	
	OpenGLTurboKreslení(access, graph, &menu->pozadí, graph->buffer, menu->pozadí.address, 0, 0, 0, WIN_WID, WIN_HEI);
	
	buttonDraw(access,menu->btn,BTN_CNT,&access->graph,&menu->image,access->game.save);

	Sanime(access, access->game.anime);

	SetSim(access,&access->game.sets);

	EndGL(access);
}


bool SetSim(UNIVERSAL *access,SETS *sets)
{
	if (sets->first == true)
	{
		Set_Kind(access,&sets->set[sets->id]);
		sets->first = false;
	}

	if (!sets->frame.active)
		return false;

	Set_main(access,sets);
	MenuFrames(access,sets->set[sets->id].btn,BTN_CNT,access->game.save);
	buttonClicked(access,sets->set[sets->id].btn,BTN_CNT,&access->game.keys);
	buttonDraw(access,sets->set[sets->id].btn,BTN_CNT,&access->graph,&sets->set[sets->id].image,access->game.save);
	return true;
}


void Set_main(UNIVERSAL *access,SETS *sets)
{
	SET *set;
	SAVES *save;
	FRAME *frame;



	save = &access->game.save[sets->frame.save];
	frame = &save->frame[sets->frame.frame];
	set = &sets->set[sets->id];
	Frames(access,&sets->frame,access->game.save,&sets->rect);
	Load_Graph(frame,&access->graph);
	if (frame->pic >= 0)
		Paint_element(access,&access->graph,&save->pic[frame->pic],access->graph.buffer,save->pic[frame->pic].address,&frame->oøíznout,sets->rect.left + frame->centerx,sets->rect.top + frame->centery,save->pic[frame->pic].w,save->pic[frame->pic].h);
}


void Set_Kind(UNIVERSAL *access,SET *set)
{
	static	bool	K1 = false;
	static	bool	K2 = false;
	if (set->kind == 1)
	{
		
		static BUTTON btn;
		memcpy(&btn,&set->btn[0],sizeof(BUTTON));
		memset(set->btn,0,sizeof(BUTTON)*BTN_CNT);
		Proèista(set->btn,BTN_CNT);
		memcpy(&set->btn[0],&btn,sizeof(BUTTON));
		memset(&btn,0,sizeof(BUTTON));
		if (K1 == false)
		{
			UseFolders(access,&access->load,set,LANGS_TXT,0);
			access->game.sets.frame.active = true;
			K1 = true;
		}
		else
		{
			K1 = false;
			access->game.sets.id = -2;
			access->game.sets.frame.active = false;
		}//*/
	}
	if (set->kind == 2)
	{
		
		static BUTTON btn;
		memcpy(&btn,&set->btn[0],sizeof(BUTTON));
		memset(set->btn,0,sizeof(BUTTON)*BTN_CNT);
		Proèista(set->btn,BTN_CNT);
		memcpy(&set->btn[0],&btn,sizeof(BUTTON));
		memset(&btn,0,sizeof(BUTTON));
		if (K2 == false)
		{
			UseFolders(access,&access->load,set,LANGS_TXT,0);
			access->game.sets.frame.active = true;
			K2 = true;
		}
		else
		{
			K2 = false;
			access->game.sets.id = -2;
			access->game.sets.frame.active = false;
		}
	}

}


void UseFolders(UNIVERSAL *access,LOAD *load,SET *set,char *filename,int minus)
{
	int cnt = 0;
	load->h = FindFirstFile(filename,&load->data);
	
	if (!load->h)
		return;

	Fold_Get(access,&load->data,set,cnt,minus);
	cnt++;

	while (FindNextFile(load->h,&load->data))
	{
		Fold_Get(access,&load->data,set,cnt,minus);
		cnt++;
	}
	cnt++;

}


void Fold_Get(UNIVERSAL *access,WIN32_FIND_DATA *data,SET *set,int &cnt,int minus)
{
	string modify;
	modify = data->cFileName;
	if (modify.find(TEXTS) > 100)
	{
		cnt--;
		return;
	}

	if (cnt != 0)
		memmove(&set->btn[cnt],&set->btn[0],sizeof(BUTTON));

	set->btn[cnt].image.top = set->btn[0].image.top + set->btn[0].image.bottom*cnt;
	set->btn[cnt].rect.top = set->btn[0].rect.top + set->btn[0].rect.bottom*cnt;
	set->btn[cnt].text.text = modify.substr(0, modify.length() - string(TEXTS).length());
	set->btn[cnt].change.text = modify.substr(0, modify.length() - string(TEXTS).length());
	set->btn[cnt].text.meas.top = set->btn[0].text.meas.top + set->btn[0].text.meas.bottom*cnt;

	memcpy(&set->btn[cnt].change.tect,&access->game.menus.menu[set->btn[0].change.in].btn[set->btn[0].change.which].text.meas,sizeof(RECT));
}