#include "odkazy.h"

void Proc(UNIVERSAL *access)
{
	Keys_detect(access->wnd.hwnd,&access->game.keys);
	access->detail.twice = false;
	switch(access->game.state)
	{
	case STATE_MENU:
		menu(access,&access->game.menus);
	break;

	case STATE_GAME:
		Game(access,&access->game.games);
	break;

	default:
		MessageBox(NULL,"anythink failed","error",MB_OK);
	break;
	}
	access->detail.twice = true;
}