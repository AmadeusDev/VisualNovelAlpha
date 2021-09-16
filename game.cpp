#include "game.h"
void GameGraphStart(UNIVERSAL *access);
void game_graphics(UNIVERSAL *access);
void TxtBarGraph(UNIVERSAL *access,GRAPH *graph,TEXTBAR *txtbar);
void TextWrit(UNIVERSAL *access,GRAPH *graph,GAMES *games);
void PersonShow(UNIVERSAL *access,GRAPH *graph,PERSON *person);
void SaveGame(UNIVERSAL *,GAMES *);
void SwitchToMenu(UNIVERSAL *);
void TextCopy(TEXT *dst, TEXT *src);
void ChangeTxtbar(TEXTBAR *texb, TXTBAR *txb);

void Game(UNIVERSAL *access,GAMES *games)
{
	game_graphics(access);
	GameProcessing(access,&access->game,games);

#pragma region |ovládání z klávesnice|
	
	if (access->game.keys.key[KEY_SAVE].once)
		SaveGame(access,games);

	if (access->game.keys.key[KEY_MENU].once)
		SwitchToMenu(access);

#pragma endregion

}

void SwitchToMenu(UNIVERSAL *access)
{
	MENUS *menus = &access->game.menus;
	menus->id = access->game.InGameMenu;
	menus->snd = false;
	for(int a = 0;a < BTN_CNT;a++)
	{
		if (menus->menu[menus->id].btn[a].text.text == "jazyk")
			menus->menu[menus->id].btn[a].text.text = access->game.games.language;
	}
	access->game.state = STATE_MENU;
}

void SaveGame(UNIVERSAL *access,GAMES *games)
{
	string word;
	CentrumUkládáníANaèítání centrum;

	centrum.Uložení(&access->game);

	MessageBox(NULL,"hra uložena","povedeno",MB_OK);
}

void game_graphics(UNIVERSAL *access)
{
	PLAYER	*player;
	GAMES	*games;
	INGAME	*ingame;
	GRAPH	*graph;
	MAP		*map;
	STORY	*story;
	ingame = &access->game.games.data;
	games = &access->game.games;
	player = &access->game.games.data.player;
	graph = &access->graph;
	map = &games->data.map.map[player->map];
	story = &games->data.story.story[player->story];
	GameGraphStart(access);

#pragma region |Grafika na vykreslování|

	MapGraphics(access,map,1);
	
	if (ingame->story.story[player->story].person && MetConditions(access,&access->game,games))
		PersonShow(access,graph,ingame->story.story[player->story].person);

	Sanime(access,access->game.anime);

	if (story->txtbar.active == 123)
		ChangeTxtbar(&games->textbar, &story->txtbar);

	if (Data.flags.StoryInProgress)
		 TxtBarGraph(access, &access->graph, &games->textbar);
	
	if (games->textbar.text && MetConditions(access,&access->game,games))
		TextWrit(access,&access->graph,games);
	
	MapGraphics(access,map,0);

#pragma endregion

	EndGL(access);
	MapProcessing(access,map);
}


void GameGraphStart(UNIVERSAL *access)
{
	IMAGE *image;
	image = &access->game.games.data.map.map[access->game.games.data.player.map].pozadí;

	InitGL(access);
	startPnt(&access->graph);
	OpenGLTurboKreslení(access, &access->graph, image, access->graph.buffer, image->address,
		0, 0, 0, WIN_WID, WIN_HEI);


}


void TxtBarGraph(UNIVERSAL *access,GRAPH *graph,TEXTBAR *txtbar)
{	
	startPnt(graph);
	graph->matrix[0][0] = txtbar->r;
	graph->matrix[1][1] = txtbar->g;
	graph->matrix[2][2] = txtbar->b;
	graph->matrix[3][3] = txtbar->v;
	txtbar->oøíznout.left = 0.0;
	txtbar->oøíznout.top = 0.0;
	txtbar->oøíznout.right = 0.01;
	txtbar->oøíznout.bottom = 0.01;
	Paint_element(access,graph,&txtbar->image,graph->buffer
		,txtbar->image.address,&txtbar->oøíznout,txtbar->rect.left,txtbar->rect.top,txtbar->rect.right,txtbar->rect.bottom);

}


void TextWrit(UNIVERSAL *access,GRAPH *graph,GAMES *games)
{
	TEXTBAR*		txtbar;
	TEXT*			txt;
	STORY*			story;
	RECT			rect;
	static TEXT		text;
	static TEXT*	before;
	static short	time = 0;
	static short	symbol = 0;

	story = &games->data.story.story[games->data.player.story];

	txtbar = &games->textbar;
	txt = txtbar->text;
	
	if (before != txtbar->text)
	{
		time = 0;
		symbol = 0;
		before = txtbar->text;
	}

	switch(txt->kind/10)
	{
	case 0:
		Text_Draw(graph->buffer,txt,&txtbar->rect);
	break;

	case 1:
		TextCopy(&text, txt);
		if (symbol < txt->text.size())
		{
			if (time < txt->kind%10)
				time++;
			else
			{
				time = NULL;
				symbol++;
			}
		}
		else
		{
			for (int cnt = 0;cnt < story->OdpCnt;cnt++)
			{
				RECT  *r = &story->odpovìï[cnt].text.meas;
				POINT *p = &access->game.keys.mouse;
				int y = access->game.games.textbar.rect.top;
				Text_Draw(graph->buffer,&story->odpovìï[cnt].text,&txtbar->rect);

				double offset = 1.75 - (double)( (WIN_HEI - 150) - y )*(0.75/265);//*((double)y / 350);

				if (p->x > r->left && p->x < r->right && 
					p->y-y + story->odpovìï[cnt].text.size*offset > r->top && p->y-y < r->top + story->odpovìï[cnt].text.size - story->odpovìï[cnt].text.size*offset)
				{
					startPnt(graph);
					graph->matrix[0][0] = 1.0f;
					graph->matrix[1][1] = 1.0f;
					graph->matrix[2][2] = 1.0f;
					graph->matrix[3][3] = 0.25f;
					Paint_element(access,graph,&txtbar->image,graph->buffer
							,txtbar->image.address, &txtbar->oøíznout ,
							r->left,r->top + y,
							r->right,story->odpovìï[cnt].text.size);

				}
			}
		}
		if (access->game.keys.key[0].once && symbol < text.text.length())
		{
			symbol = text.text.length();
			access->game.keys.key[0].once = false;
		}

		text.text = text.text.substr(0,symbol);
		Text_Draw(graph->buffer,&text,&txtbar->rect);
		memset(&text,0,sizeof(TEXT));
	break;

	}

}


void TextCopy(TEXT *dst, TEXT *src)
{
	dst->before = src->before;
	dst->blue = src->blue;
	dst->green = src->green;
	dst->kind = src->kind;
	dst->meas.left = src->meas.left;
	dst->meas.top = src->meas.top;
	dst->meas.right = src->meas.right;
	dst->meas.bottom = src->meas.bottom;
	dst->red = src->red;
	dst->size = src->size;
	dst->size_w = src->size_w;
	dst->text = src->text;
}


void PersonShow(UNIVERSAL *access,GRAPH *graph,PERSON *person)
{
	FRAME *frame;
	int img;


	frame = &access->game.save[person->frame.save].frame[person->frame.frame];
	switch(frame->kind/100)
	{
	case 1:
		img = frame->kind%100;
		if (frame->pic < 0)
		{
			startPnt(graph);
			if (frame->RS)
				graph->matrix[0][0] = frame->RS;
			if (frame->GS)
				graph->matrix[1][1] = frame->GS;
			if (frame->BS)
				graph->matrix[2][2] = frame->BS;
			if (frame->VS)
				graph->matrix[3][3] = frame->VS;
			if (frame->dividerh)
				graph->dividerh = frame->dividerh;
			if (frame->dividerw)
				graph->dividerw = frame->dividerw;

			Paint_element(access,graph,&person->image[img],graph->buffer,person->image[img].address,&person->oøíznout,person->rect.left,person->rect.top,
		person->rect.right,person->rect.bottom);
		}
	break;

	default:
	break;
	}


}
void ChangeTxtbar(TEXTBAR *texb, TXTBAR *txb)
{
	texb->rect.left = txb->drect.left;
	texb->rect.top = txb->drect.top;
	texb->rect.right = txb->drect.right;
	texb->rect.bottom = txb->drect.bottom;

	texb->r = txb->RS;
	texb->g = txb->GS;
	texb->b = txb->BS;
	texb->v = txb->VS;
}