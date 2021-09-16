#include "odkazy.h"


void Sanime(UNIVERSAL *access,BUTTON anime[])
{
	int cnt = NULL;

	while (cnt < ANM_CNT)
	{
		if (anime[cnt].frames.active == true)
		{
			MenuFrames(access,&anime[cnt],1,access->game.save);
		}
		cnt++;
	}
	buttonDraw(access,anime,ANM_CNT,&access->graph,NULL,access->game.save);
}