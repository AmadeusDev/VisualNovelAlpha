#include "game.h"
void Story_kind(UNIVERSAL *access,STORY *story);
int Get_Answer(int OdpCnt, POINT p, ODPOVÌÏ *odp, RECT *rect, UNIVERSAL *access);
bool AnimeInactive(BUTTON anime[], int count);


void GameProcessing(UNIVERSAL *access,GAME *game,GAMES *games)
{
	static short sId = -1;
	static short mId = -1;
	static short last = -1;
	bool toto = false;
	static bool tady = false;
	PLAYER *player;
	STORYLINE *storyline;
	STORY *story;
	storyline = &games->data.story;
	player = &games->data.player;
	MAP *map = &games->data.map.map[player->map];
	
	story = &storyline->story[player->story];

#pragma region |Story sounds|
	
	if (sId != player->story)
	{
		storyline->snd = false;
		sId = player->story;
	}
	
	if (!storyline->snd && story->sound != "")
	{
		PlaySoundFile(access,story->sound);
		storyline->snd = false;
	}

#pragma endregion

#pragma region |Map sounds|

	if (mId != player->map)
	{
		games->data.map.snd = false;
		mId = player->map;
	}

	if (!storyline->snd && story->sound != "")
	{
		PlaySoundFile(access,story->sound);
		storyline->snd = true;
	}

#pragma endregion

	if (last != player->story)
	{
		story->frames.save = story->save;
		story->frames.frame = story->frame;

		if (story->SaveCoor.folder != -1 && story->SaveCoor.file != -1)
		{
			Load_Svs(access, &game->save[story->save], &story->SaveCoor);
		}

		last = player->story;
	}

	Frames(access,&story->frames,access->game.save,NULL);

	if (!(Data.flags.StoryInProgress = MetConditions(access,game,games)))
		return;



#pragma region |naètení postavy|
	
	if (story->conjure.active)
	{
		if (game->save[story->conjure.save].coor.folder != story->conjure.coor.folder ||
			game->save[story->conjure.save].coor.file != story->conjure.coor.file )
		{
			tady = false;
			if (!Load_Svs(access,&game->save[story->conjure.save],&story->conjure.coor))
				toto = false;
			else
				toto = true;
		}
		else
			toto = true;

#pragma endregion

#pragma region |proces postavy|

		if (toto == true)
		{
			if (tady == false || story->person == NULL ||story->person->name != games->data.persons.person[story->conjure.id].name)
			{
				story->person = &games->data.persons.person[story->conjure.id];
				if (story->conjure.save >= 0 && story->conjure.frame >= 0 )
				{
					story->person->frame.frame = story->conjure.frame;
					story->person->frame.save = story->conjure.save;
					story->person->frame.time = -1;
					story->person->frame.active = true;
				}
				else
					story->person->frame.active = false;
				tady = true;
			}
			memcpy(&story->person->rect,&story->conjure.rect,sizeof(RECT));
			Frames(access,&story->person->frame,access->game.save,&story->person->rect);
		}
		else
			story->person = NULL;
	}
	else
		story->person = 0;

#pragma endregion

#pragma region |Pøíbìh|

	Story_kind(access,&games->data.story.story[games->data.player.story]);

	if (storyline->story[player->story].text.text != "")
	{
		games->textbar.text = &storyline->story[player->story].text;
	}

#pragma endregion

}


void Story_kind(UNIVERSAL *access,STORY *story)
{
	PLAYER		*player = &access->game.games.data.player;
	STORYLINE	*storyline = &access->game.games.data.story;
	POINT		*p = NULL;
	RECT		*rect = NULL;
	int			Answ = 0;

	if (story->kind / 1000 == 5)
	{
		if (story->frames.frame == 1000 && AnimeInactive(access->game.anime,ANM_CNT))
			ChangeStory(access, player, storyline, story->kind % 5000);
	}


	if (story->kind/1000 == 8 || story->kind/1000 == 9)
	{
		if (access->game.keys.key[0].once == true)
		{
			if (!story->OdpCnt)
			{
				if (story->kind/1000 == 8)
					ChangeStory(access,player,storyline,story->kind%8000);
				else
					ChangeStory(access,player,storyline,story->kind%9000);
			}
			else
			{
				p = &access->game.keys.mouse;
				rect = &access->game.games.textbar.rect;
				if (p->x > rect->left && p->x < (rect->left+rect->right) &&
					p->y > rect->top  && p->y < (rect->top+rect->bottom)  )
				{
					Answ = Get_Answer(story->OdpCnt,*p,story->odpovìï,rect,access);
					if (0 > Answ)
						return;
					ChangeStory(access,player,storyline,story->odpovìï[Answ].next);

				}
			}
		}
	}


}

bool AnimeInactive(BUTTON anime[], int count)
{
	bool Truth = true;
	for (int a = 0; a < count; a++)
	{
		if (!(anime[a].frames.frame == 1000 || !anime[a].frames.active))
		{
			Truth = false;
		}
	}
	return Truth;
}


void ChangeStory(UNIVERSAL *access,PLAYER *player,STORYLINE *storyline,int imma)
{
	INGAME *data = &access->game.games.data;
	short kind = storyline->story[player->story].kind;
	COOR coor;

	if (imma > 200)
	{
		coor.file = (imma/256)%4096;
		coor.folder = imma/1048576;
		imma = imma/256;
	}
	else
	{
		coor.file = storyline->story[player->story].coor.file;
		coor.folder = storyline->story[player->story].coor.folder;
	}

#pragma region |zmìna pøíbìhu|
	if (kind / 9000 == 1 &&
		( data->story.coor.folder != coor.folder ||
		  data->story.coor.file != coor.file		)  )
	{
		data->story.coor.folder = coor.folder;
		data->story.coor.file = coor.file;
		StoryLoad(access,storyline,access->game.games.language);
	}
	player->story = imma;
#pragma endregion

#pragma region |nulování snímku|
	if (storyline->story[player->story].frames.active)
		memcpy(&player->person.frame,&storyline->story[player->story].frames,sizeof(FRAMES));
#pragma endregion

#pragma region |zmìna mapy|
	
	if (storyline->story[player->story].NextMap.nové == true 
		&& (data->map.coor.file != storyline->story[player->story].NextMap.coor.file ||
			data->map.coor.folder != storyline->story[player->story].NextMap.coor.folder))
	{
		if (data->map.coor.file == storyline->story[player->story].NextMap.coor.file &&
			data->map.coor.folder == storyline->story[player->story].NextMap.coor.folder)

		data->map.coor.file = storyline->story[player->story].NextMap.coor.file;
		data->map.coor.folder = storyline->story[player->story].NextMap.coor.folder; 

		Load_maps(&data->map,access->game.games.language);
	}

	if (storyline->story[player->story].NextMap.jo == true)
	{
		player->map = storyline->story[player->story].NextMap.map;
	}

#pragma endregion

#pragma region|start nového pøíbìhu|
	
	storyline->story[imma].frames.active = true;

#pragma endregion
}


bool MetConditions(UNIVERSAL *access,GAME *game,GAMES *games)
{
	STORY *story;
	PLAYER *player;
	player = &games->data.player;
	story = &games->data.story.story[player->story];

	switch(story->cond)
	{
	case 0:
		if (story->conds.map != player->map)
			return false;
	break;

	default:
		return false;
	}
	return true;
}

int Get_Answer(int OdpCnt,POINT p,ODPOVÌÏ *odp,RECT *rect, UNIVERSAL *access)
{
	int cnt = 0;

	while (cnt < OdpCnt)
	{
		int y = access->game.games.textbar.rect.top;
		double offset = 1.75 - (double)((WIN_HEI - 150) - y)*(0.75 / 265);//*((double)y / 350);
		/*
			if (p->x > r->left && p->x < r->right &&
				p->y - y + story->odpovìï[cnt].text.size*offset > r->top && p->y - y < r->top + story->odpovìï[cnt].text.size - story->odpovìï[cnt].text.size*offset)
		//*/

		if (p.x > odp[cnt].text.meas.left && p.x < (odp[cnt].text.meas.left+odp[cnt].text.meas.right) &&
			p.y - rect->top + odp[cnt].text.size*offset > odp[cnt].text.meas.top  && p.y - rect->top + odp[cnt].text.size*offset < (odp[cnt].text.meas.top+odp[cnt].text.size)   )
		{
			return cnt;
		}
		cnt++;
	}

	return -1;
}