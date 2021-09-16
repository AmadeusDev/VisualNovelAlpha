#include "game.h"

bool MapProcessing(UNIVERSAL *access,MAP *map)
{
	SAVES *saves = NULL;
	if (!(map->save > -1 && map->save < SVS_CNT))
		return false;

	saves = &access->game.save[map->save];

	if (saves->coor.folder != map->SvCoor.folder ||
		saves->coor.file != map->SvCoor.file ||
		saves->Kniha != Data.flags.StoryAddress)
	{
		Load_Svs(access, saves, &map->SvCoor);
		saves->Kniha = Data.flags.StoryAddress;
	}
	buttonClicked(access,map->btn,BTN_CNT,&access->game.keys);
	return true;

}

void MapGraphics(UNIVERSAL *access,MAP *map,bool before)
{
	for (int a = 0;a < BTN_CNT;a++)
	{
		if (before == map->btn[a].kind % 2)
		{
			buttonDraw(access,&map->btn[a],1,&access->graph,&map->image,access->game.save);
			Frames(access,&map->btn[a].frames,access->game.save,&map->btn[a].rect);
			PostChanges(&map->btn[a]);
		}
	}

}