#include "odkazy.h"
void BtnFrm(MENUS *menus,BUTTON *btn,SAVES save[]);
void Bsc_Frame(UNIVERSAL *access,FRAMES *frames,SAVES saves[],RECT *rect);
void Frame_PostFce(UNIVERSAL *access,FRAME *frame,FRAMES *frames,SAVES saves[]);
void frm_tm(UNIVERSAL *access,FRAMES *frames,SAVES saves[]);
void set_anime(GAME *game, SBUTTON *button, short cnt, RECT *rect);
int FindOutKey();
void SaveKey(char *address,int place,int key);
bool kind(UNIVERSAL *access,FRAMES *frames,SAVES saves[]);
void ZmìnitKnihu(UNIVERSAL *access, string Adresa);
int NaèístMinulouPozici(UNIVERSAL *access, string jméno);


void Frames(UNIVERSAL *access,FRAMES *frames,SAVES saves[],RECT *rect)
{
	if (!frames->active)
		return;

	
	if (frames->frame < 0 && frames->frame >= 1000)
		return;

	if (frames->save < 0)
		return;

	if (!frames->snd && saves[frames->save].frame[frames->frame].sound != "")
	{
		PlaySoundFile(access,saves[frames->save].frame[frames->frame].sound);
		frames->snd = true;
	}

	Bsc_Frame(access,frames,saves,rect);

}


void Bsc_Frame(UNIVERSAL *access,FRAMES *frames,SAVES saves[],RECT *rect)
{
	SAVES *save;
	FRAME *frame;

	save = &saves[frames->save];
	frame = &save->frame[frames->frame];

	if (frames->time < 0)
		frames->time = saves[frames->save].frame[frames->frame].time;

	frm_tm(access,frames,saves);
	if (rect != NULL)
	{
		rect->left += frame->dvx;
		rect->top += frame->dvy;
	}
	/*
	if (frame->text.text != "" && frame->text.text.length() < 1000000)
		Text_Draw(access->graph.buffer,&frame->text,rect);
	//*/
	int cnt = NULL;
	while (cnt < ANM_CNT)
	{
		if (frame->button[cnt].active)
			set_anime(&access->game,&frame->button[cnt],cnt,rect);

		cnt++;
	}

}


void set_anime(GAME *game,SBUTTON *button,short cnt,RECT *rect)
{
	game->anime[cnt].frames.active = true;
	game->anime[cnt].frames.kind = -1;
	game->anime[cnt].frames.kevent = -1;
	game->anime[cnt].frames.frame = button->frame;
	game->anime[cnt].frames.save = button->save;
	game->anime[cnt].frames.time = -1;
	game->anime[cnt].frames.reverse = button->reverse;

	if (button->x < 0)
		game->anime[cnt].image.left = rect->left - button->x;
	else
		game->anime[cnt].image.left = button->x;


	if (button->y < 0)
		game->anime[cnt].image.top = rect->top - button->y;
	else
		game->anime[cnt].image.top = button->y;

	game->anime[cnt].image.right = button->w;
	game->anime[cnt].image.bottom = button->h;
	game->anime[cnt].rect.left = button->x;
	game->anime[cnt].rect.top = button->y;
	game->anime[cnt].rect.right = button->w;
	game->anime[cnt].rect.bottom = button->h;
	game->anime[cnt].typ = button->type;
	game->anime[cnt].pic = button->pic;

}


void frm_tm(UNIVERSAL *access,FRAMES *frames,SAVES saves[])
{

	FRAME *frame;
	SAVES *save;

	save = &saves[frames->save];
	frame = &save->frame[frames->frame];

	if (frames->time > 0 && !kind(access,frames,saves))
		frames->time--;
	else
	{
		if (frame->SaveAdresa != "")
			ZmìnitKnihu(access, frame->SaveAdresa);

		ChangeFrame(frames, frame->next);

		Frame_PostFce(access,frame,frames,saves);
		if (frames->frame == 1000)
		{
			frames->active = false;
		}
		else
			frames->time = save->frame[frames->frame].time;
	}


}


void Frame_PostFce(UNIVERSAL *access,FRAME *frame,FRAMES *frames,SAVES saves[])
{
	if (frame->set != -2)
	{
		if (frame->set == -1)
			access->game.sets.frame.active = false;

		if (!(frame->set < 0))
		{
			SETS *sets;
			sets = &access->game.sets;
			sets->id = frame->set;
			sets->frame.frame = sets->set[sets->id].frame;
			sets->frame.save = sets->set[sets->id].save;
			memcpy(&sets->rect,&sets->set[sets->id].rect,sizeof(RECT));
			sets->frame.reverse = 1;
			sets->first = true;
			access->game.sets.frame.active = true;
		}

	}

	if (frame->next_menu >= 0)
	{
		access->game.menus.id = frame->next_menu;
		access->game.sets.frame.active = false;
		access->game.menus.snd = false;
	}




}


bool kind(UNIVERSAL *access,FRAMES *frames,SAVES saves[])
{
	FRAME *frame;
	frame = &saves[frames->save].frame[frames->frame];
	int key;

	if (frame->kind > 1 && frame->kind < 12)
	{
		while (GetAsyncKeyState(access->game.keys.key[0].which) & 0x8000);
		while ((key = FindOutKey()) < 0 );
		access->game.keys.key[frame->kind-2].which = key;
		SaveKey(KEYS_ADDR,frame->kind-2,key);
		return 1;
	}

	if (frame->kind/1000 == 1)
	{
		GAME *game = &access->game;
		GAMES *games = &game->games;

		if ( (frame->kind / 100) % 10 )
		{
			if (games->data.story.coor.folder != frame->Story.folder ||
				games->data.story.coor.file != frame->Story.file)
			{
				games->data.story.coor.folder = frame->Story.folder;
				games->data.story.coor.file = frame->Story.file;
				StoryLoad(access,&games->data.story,games->language);
			}

			int imma = 0;
			imma = frame->idS;
			imma += 256*frame->Story.file;
			imma += 1048576*frame->Story.folder;
			ChangeStory(access,&games->data.player,&games->data.story,imma);
		}

		if ( (frame->kind / 100) % 10 )
		{
			if (games->data.map.coor.folder != frame->Map.folder ||
				games->data.map.coor.file != frame->Map.file)
			{
				games->data.map.coor.folder = frame->Map.folder;
				games->data.map.coor.file = frame->Map.file;
				Load_maps(&games->data.map,games->language);
			}
			games->data.player.map = frame->idS;

		}

		if ( (frame->kind / 10) % 10 )
		{
			if (games->data.map.coor.folder != frame->Map.folder ||
				games->data.map.coor.file != frame->Map.file)
			{
				games->data.map.coor.folder = frame->Map.folder;
				games->data.map.coor.file = frame->Map.file;
				Load_Peer(access,&games->data.persons,games->language);
			}
			games->data.player.map = frame->idM;

		}

		if ( frame->kind % 10 )
		{
			if (games->data.persons.coor.folder != frame->Person.folder ||
				games->data.persons.coor.file != frame->Person.file)
			{
				games->data.persons.coor.folder = frame->Person.folder;
				games->data.persons.coor.file = frame->Person.file;
				Load_Peer(access,&games->data.persons,games->language);

			}
			games->data.player.map = frame->idM;

		}
		
	}

	return 0;
}


void SaveKey(char *address,int place,int key)
{
	ifstream ifile;
	string word;
	string text;
	int pos = 0;

	ifile.open(address);


	if (!ifile.is_open())
	{
		return;
	}
	while (ifile.good())
	{
		getline(ifile,word);
		text += word;
		text += '\n';
	}
	text.erase(text.length()-1,1);
	findword(text,pos);
	while (1)
	{
		word = findword(text,pos);
		if (word != convert(place))
			findword(text,pos);
		else
			break;
	}
	word = findword(text,pos);

	text.replace(pos-word.length(),word.length(),convert(key));

	ifile.close();
	ofstream ofile;
	
	ofile.open(address);
	ofile.clear();
	ofile << text;
	ofile.close();
}


int FindOutKey()
{
	int cnt = NULL;

	while (cnt < 256)
	{
		if (GetAsyncKeyState(cnt) & 0x8000)
			return cnt;

		cnt++;
	}

	return -1;
}


void ZmìnitKnihu(UNIVERSAL *access,string Adresa)
{
	PLAYER *player = &access->game.games.data.player;

	CentrumUkládáníANaèítání centrum;

	centrum.Uložení(&access->game);

	Data.flags.StoryAddress = Adresa;
	int a = NaèístMinulouPozici(access, player->name);

	if (a == 0)
	{
		INGAME *gm = &access->game.games.data;
		gm->map.coor.file = 0;
		gm->map.coor.folder = 0;
		gm->story.coor.file = 0;
		gm->story.coor.folder = 0;
		gm->persons.coor.file = 0;
		gm->persons.coor.folder = 0;
		player->map = 0;
		player->story = 0;
	}
	Data.flags.story = player->story;
	AbsStartGame(access, &access->game.games);

}

int NaèístMinulouPozici(UNIVERSAL *access, string jméno)
{
	bool TheCheeseOfTruth = true;
	string word;
	ifstream ifile;

	word = SVS_ADDR;
	word += jméno;
	word += "/";
	if (Data.flags.StoryAddress == "")
		word += "main";
	else
		word += Data.flags.StoryAddress;
	word += "/index.txt";
	ifile.open(word);


	if (!ifile.is_open())
	{
		return false;
	}


	while (ifile.good())
	{
		ifile >> word;
		LoadSaveInners(&ifile, &access->game.games.language, &access->game.games.data, &word);

	}

	return 123;
}