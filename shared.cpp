#include "odkazy.h"
bool eventDetect(BUTTON *btn, KEYS *keys, __int8 type, bool already);
short bkind_detect(BEVENT *bevent,KEYS *keys,short type);
short bKindPos(BUTTON *btn,KEYS *keys,short type);
short bkindboth(BUTTON *btn,KEYS *keys,short type);
void ButtonGraph(BUTTON *btn,GRAPH *graph);
string KeyTrans(short key);

bool activated_spec(BUTTON *btn,bool &already);
void bas_matrix(float matrix[5][5]);
void KopieRectText(RECT *rdst, RECT *rsrc, TEXT *tdst, TEXT *tsrc);


string convert(double num)
{
	char numb[50];
	itoa(num,numb,10);
	return numb;
}

void bas_matrix(float matrix[4][4])
{
	int cnt = NULL;
	memset(matrix,0,4*4);
	matrix[0][0] = 1;
	matrix[1][1] = 1;
	matrix[2][2] = 1;
	matrix[3][3] = 1;
}



void Paint_element(UNIVERSAL *access,GRAPH *graph,IMAGE *simage,HDC hdc,string address,DRECT *drect,short x,short y, short w, short h)
{
	OpenGLTurboKreslení(access, graph, simage, hdc, address, drect, x, y, w, h);
}


bool Rect_get(RECT *rect,POINT *p)
{

	if (p->x > rect->left && p->x < rect->left + rect->right &&
		p->y > rect->top  && p->y < rect->top + rect->bottom )
	{
		return true;
	}
	return false;
}


void buttonClicked(UNIVERSAL *access,BUTTON btn[],short count,KEYS *keys)
{
	int cnt = 0;
	int cnt2 = 0;
	bool already = false;

	while (cnt < _DCNT)
	{
		while (cnt2 < count)
		{
			if (eventDetect(&btn[cnt2],keys,(char)_DCNT - cnt - 1,already))
				already = true;
			cnt2++;
		}
		cnt2 = NULL;



		cnt++;
	}


}

void buttonDraw(UNIVERSAL *access,BUTTON btn[],short count,GRAPH *graph,IMAGE *image,SAVES save[])
{		
	static bool hmph = false;
	int cnt = NULL;
	FRAME *frame;
	IMAGE *pic;
	short		w;
	short		h;
	bool	already = false;

	while (cnt < BTN_CNT)
	{

#pragma region |Text Before|
		
		if (btn[cnt].text.text != "" && btn[cnt].text.before == true)
		{
			Text_Draw(graph->buffer,&btn[cnt].text,&btn[cnt].rect);

			if (btn[cnt].bevent[_BOTH].bkind[ONCE].switched == true)
			{
				frame = &save[btn[cnt].bevent[_BOTH].bkind[ONCE].save].frame[btn[cnt].bevent[_BOTH].bkind[ONCE].frame];

				//*
				if (frame->kind > 1 && frame->kind < 12)
				{
					//* 
					short key = access->game.keys.key[frame->kind-2].which;
					RECT rect;
					TEXT text;

					//rect.left += 75;
					//text.text = KeyTrans(key);
					/*
					memcpy(&rect, &btn[cnt].rect, sizeof(RECT));
					memcpy(&text, &btn[cnt].text, sizeof(TEXT));//*/
					KopieRectText(&rect, &btn[cnt].rect, &text, &btn[cnt].text);
					text.text = KeyTrans(key);
					//*/

					Text_Draw(graph->buffer,&text,&rect);

				}//*/
			}
		}

#pragma endregion

		startPnt(graph);

		if (activated_spec(&btn[cnt],already))
		{

			if (!btn[cnt].frames.reverse)
				btn[cnt].frames.reverse = 1;
			hmph = true;

			frame = &save[btn[cnt].frames.save].frame[btn[cnt].frames.frame];

			if (frame->pic == -2)
			{
				cnt++;
				continue;
			}

			if (frame->dividerh != 0)
				graph->dividerh = frame->dividerh;

			if (frame->dividerw != 0)
				graph->dividerw = frame->dividerw;

			if (frame->pic >= 0 && frame->part >= 0)
			{
				pic = &save[btn[cnt].frames.save].pic[frame->pic];
			}
			else
			{
				pic = NULL;
			}

			if (frame->RS > 0)
				graph->matrix[0][0] = frame->RS;
			if (frame->GS > 0)
				graph->matrix[1][1] = frame->GS;
			if (frame->BS > 0)
				graph->matrix[2][2] = frame->BS;
			if (frame->VS > 0)
				graph->matrix[3][3] = frame->VS;//*/
				graph->angle = frame->angle;

			if (pic)
			{
				if (frame->w != 0)
					w = frame->w;
				else
					w = pic->w;

				if (frame->h != 0)
					h = frame->h;
				else
					h = pic->h;

				if (frame->previous == true)
				{
					w = btn[cnt].image.right;
					h = btn[cnt].image.bottom;
				}

				OpenGLTurboKreslení(access,graph,pic,graph->buffer,pic->address,&frame->oøíznout,btn[cnt].image.left+frame->centerx,btn[cnt].image.top+frame->centery,w, h);
			}
			else
			{
				if (image != NULL)
					OpenGLTurboKreslení(access,graph,image,graph->buffer,image->address,&btn[cnt].oøíznout,btn[cnt].image.left+frame->centerx,btn[cnt].image.top+frame->centery, btn[cnt].image.right, btn[cnt].image.bottom);
			}
		}
		else
		{
			ButtonGraph(&btn[cnt],graph);
			if (image != NULL && btn[cnt].pic >= 0)
			{
				OpenGLTurboKreslení(access,graph,image,graph->buffer,image->address,&btn[cnt].oøíznout,btn[cnt].image.left,btn[cnt].image.top, btn[cnt].image.right, btn[cnt].image.bottom);
			}
		}

#pragma region |Text after| 

#pragma region |FRAME text|

		SAVES *save;
		FRAME *frame;

		save = &access->game.save[btn[cnt].frames.save];
		frame = &save->frame[btn[cnt].frames.frame];

		if (frame->text.text != "" && frame->text.text.length() < 1000000 && btn[cnt].frames.active)
		{
			RECT rect;

			if (frame->text.meas.left < 0)
				rect.left = btn[cnt].rect.left - frame->text.meas.left;
			else
				rect.left = frame->text.meas.left;

			if (frame->text.meas.top < 0)
				rect.top = btn[cnt].rect.top - frame->text.meas.top;
			else
				rect.left = frame->text.meas.top;

			rect.right = frame->text.meas.right;
			rect.bottom = frame->text.meas.bottom;

			Text_Draw(access->graph.buffer, &frame->text, &rect);
		}
#pragma endregion

		if (btn[cnt].text.text != "" && btn[cnt].text.before == false)
		{
			Text_Draw(graph->buffer,&btn[cnt].text,&btn[cnt].rect);
			
			if (btn[cnt].bevent[_BOTH].bkind[ONCE].switched == true)
			{
				frame = &save[btn[cnt].bevent[_BOTH].bkind[ONCE].save].frame[btn[cnt].bevent[_BOTH].bkind[ONCE].frame];



				if (frame->kind > 1 && frame->kind < 12)
				{
					short key = access->game.keys.key[frame->kind-2].which;
					RECT rect;
					TEXT text;
					memcpy(&rect,&btn[cnt].rect,sizeof(RECT));
					memcpy(&text,&btn[cnt].text,sizeof(TEXT));

					rect.left += 75;
					text.text = KeyTrans(key);
					//Text_Draw(graph->buffer,&btn[cnt].text,&rect);

				}
			}
		}

#pragma endregion

		cnt++;
	}
}


void KopieRectText(RECT *rdst, RECT *rsrc, TEXT *tdst, TEXT *tsrc)
{
	rdst->left = rsrc->left + 75;
	rdst->top = rsrc->top;
	rdst->right = rsrc->right;
	rdst->bottom = rsrc->bottom;

	tdst->base = tsrc->base;
	tdst->red = tsrc->red;
	tdst->blue = tsrc->blue;
	tdst->green = tsrc->green;
	tdst->size = tsrc->size;
	tdst->size_w = tsrc->size_w;
	tdst->before = tsrc->before;
	tdst->kind = tsrc->kind;
	tdst->meas.left = tsrc->meas.left;
	tdst->meas.top = tsrc->meas.top;
	tdst->meas.right = tsrc->meas.right;
	tdst->meas.bottom = tsrc->meas.bottom;
	tdst->text = "";
	tdst->kind = tsrc->kind;
}


void ButtonGraph(BUTTON *btn,GRAPH *graph)
{
	graph->angle = btn->angle;
	graph->matrix[0][0] = btn->RS;
	graph->matrix[1][1] = btn->GS;
	graph->matrix[2][2] = btn->BS;
	graph->matrix[3][3] = btn->VS;
	graph->dividerw = btn->dividerw;
	graph->dividerh = btn->dividerh;
}

void Text_Draw(HDC hdc,TEXT *text,RECT *rect)
{
	GLDrawText(text, rect);
	/*
	HFONT	hFont;
	RECT	Rect;
	SetTextColor(hdc, RGB(text->red,text->green,text->blue));
	SetBkMode(hdc,TRANSPARENT);

	hFont = CreateFont(text->size,text->size_w,1,1,10,FALSE,NULL,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT(""));
	
	SelectObject(hdc,hFont);
	
	Rect.top = rect->top + text->meas.top;
	Rect.left = rect->left + text->meas.left;
	Rect.right = WIN_WID - 50;
	Rect.bottom = 200;
	DrawText(hdc, TEXT(text->text.c_str()), -1,&Rect, DT_NOCLIP| DT_WORDBREAK);
	DeleteObject(hFont);
	//*/
}


bool activated_spec(BUTTON *btn,bool &already)
{
	int cnt = 3;
	int cnt2 = 0;

	if (btn->frames.active && (btn->frames.kind == -1 || btn->frames.kevent == -1 ))
		return true;

	while (cnt > 0)
	{
		cnt--;
		if (btn->bevent[cnt].active != true)
			continue;

		cnt2 = 0;
		while (cnt2 < BCNT)
		{
			if (btn->bevent[cnt].bkind[cnt2].active && btn->bevent[cnt].bkind[cnt2].switched)
			{
				if (already != true)
				{
					if (!btn->frames.active || btn->frames.kevent < cnt)
					{
						if (btn->bevent[cnt].bkind[cnt2].frame == 3333)
						{

						}

						btn->frames.active = true;
						btn->frames.frame = btn->bevent[cnt].bkind[cnt2].frame;
						btn->frames.save = btn->bevent[cnt].bkind[cnt2].save;
						btn->frames.kind = cnt2;
						btn->frames.kevent = cnt;
						btn->frames.time = -1;

					}

					if (btn->frames.active)
						already = true;

					if (cnt2 == CLICKED && btn->frames.kind == CLICKED)
					{
						btn->frames.active = btn->bevent[cnt].bkind[cnt2].active;
					}
					return true;
				}
				else
					btn->frames.active = false;
			}

			cnt2++;
		}


	}


	return false;
}


bool eventDetect(BUTTON *btn, KEYS *keys, __int8 type, bool already)
{
	short v;
	short v1;
	
	switch((int)type)
	{
	case _KEY:
		{
				
			int cnt = NULL;
			while (cnt < BCNT)
			{
				
				if (already == true)
				{
					btn->bevent[_KEY].bkind[cnt].active = false;
					cnt++;
					continue;
				}

				if ((v = bkind_detect(&btn->bevent[_KEY],keys,cnt)) >= 0)
				{
					btn->bevent[_KEY].bkind[cnt].active = v;
					if (v == true)
						return true;
				}

				if (btn->bevent[_KEY].bkind[cnt].active)
				{
					return false;
				}
				cnt++;
			}

			if (already == true)
				return true;

		}
		break;
	case _POS:
		{
			if (already == true)
			{
				return true;
			}

			int cnt = NULL;
			while (cnt < BCNT)
			{
				if (already == true)
				{
					btn->bevent[_POS].bkind[cnt].active = false;
					cnt++;
					continue;
				}

				if ((v1 = bKindPos(btn,keys,cnt)) >= 0)
				{
					btn->bevent[_POS].bkind[cnt].active = v1;
					if (v1 == true)
						return true;
				}
				cnt++;
			}

			if (already == true)
				return true;

		}
		break;
	case _BOTH:
		{
			if (already == true)
			{
				return true;
			}

			int cnt = NULL;
			while (cnt < BCNT)
			{
				if (already == true)
				{
					btn->bevent[_BOTH].bkind[cnt].active = false;
					cnt++;
					continue;
				}

				if ((v = bkindboth(btn,keys,cnt)) >= 0)
				{
					btn->bevent[_BOTH].bkind[cnt].active = v;
					if (v == true)
						return true;
				}
				cnt++;
			}

			if (already == true)
				return true;

		}
		break;

	default: break;

	}
	
	return false;
}

short bkindboth(BUTTON *btn,KEYS *keys,short type)
{
	switch(type)
	{
	case ONCE:

		if (bKindPos(btn,keys,CLICKED) > 0 && bkind_detect(&btn->bevent[_BOTH],keys,ONCE) > 0 && btn->both.clicked == false)
		{
			btn->chng.clicked = btn->bevent[_BOTH].bkind[ONCE].change;
			return true;
		}

	break;

	case CLICKED:
		if (bKindPos(btn,keys,CLICKED) > 0 && bkind_detect(&btn->bevent[_BOTH],keys,CLICKED) > 0)
		{
			return true;
		}
		else
			return false;
	break;

	default: break;

	}

	return -1;
}


short bKindPos(BUTTON *btn,KEYS *keys,short type)
{
	switch(type)
	{
	case ONCE:
		{
			if (btn->inrect.clicked == false)
			{
				if (Rect_get(&btn->rect,&keys->mouse))
				{
					btn->inrect.once = true;
					return true;
				}
			}
			else
			{
				//MessageBox(NULL,"test","test",MB_OK);
				btn->inrect.once = false;
			}
		}
		break;
	case CLICKED:
		{
			btn->inrect.clicked = Rect_get(&btn->rect,&keys->mouse);
			return btn->inrect.clicked;
		}
		break;
	default:
		break;
	}


	return -1;
}


short bkind_detect(BEVENT *bevent,KEYS *keys,short type)
{
	if (bevent->bkind[type].switched != true)
	{
		return false;
	}
	switch(type)
	{
		case ONCE:
			if (keys->key[bevent->key].once)
			{
				return true;
			}
		break;

		case CLICKED:
			if (keys->key[bevent->key].clicked)
			{
				return true;
			}
			else
				return false;
		break;

		default: break;

	}


	return -1;
}


void Keys_detect(HWND hwnd,KEYS *keys)
{
	GetCursorPos(&keys->mouse);
	ScreenToClient(hwnd,&keys->mouse);
	int cnt = NULL;
	while (cnt < KEY_CNT)
	{
		if (GetKeyState(keys->key[cnt].which) & 0x8000)
		{
			if (keys->key[cnt].clicked == false)
				keys->key[cnt].once = true;
			else
				keys->key[cnt].once = false;
			keys->key[cnt].clicked = true;

		}
		else
		{
			keys->key[cnt].clicked = false;
			keys->key[cnt].once = false;
		}
		cnt++;
	}

}


void startPnt(GRAPH *graph)
{
	bas_matrix(graph->matrix);
	graph->angle = NULL;
	graph->dividerw = 1;
	graph->dividerh = 1;
}


void Load_Graph(FRAME *frame,GRAPH *graph)
{
	if (frame->RS != 0)
		graph->matrix[0][0] = frame->RS;
	if (frame->GS != 0)
		graph->matrix[1][1] = frame->GS;
	if (frame->BS != 0)
		graph->matrix[2][2] = frame->BS;
	if (frame->VS != 0)
		graph->matrix[3][3] = frame->VS;
	graph->angle = frame->angle;
	if (frame->dividerh != 0)
	graph->dividerh = frame->dividerh;
	if (frame->dividerw != 0)
	graph->dividerw = frame->dividerw;
}

string findword(string text,int &pos)
{
	int starting_pos = pos;
	int cnt = NULL;



	while (pos < text.length() && (text.at(pos) == ' ' || text.at(pos) == '\n') )
		pos++;

	starting_pos = pos;

	while (pos < text.length() && (text.at(pos) != ' ' && text.at(pos) != '\n')  )
	{
		pos++;
		cnt++;
	}

	if (starting_pos < text.length())
		return text.substr(starting_pos,cnt);
	return "";
}


bool startGame(UNIVERSAL *access,MENU *menu)
{

	ifstream ifile;

	string test;
	test = SVS_ADDR;
	test.erase(test.length()-5,5);
	test += menu->btn[0].text.text;
	test.erase(test.length()-1,1);
	test += ".txt";
	
	if (menu->btn[0].text.text == "jméno")
	{
		MessageBox(NULL,"špatnì zadané jméno","error",MB_OK);
		return false;
	}
	
	if (menu->btn[1].text.text == "jazyk")
	{
		MessageBox(NULL,"špatnì zadaný jazyk","error",MB_OK);
		return false;
	}


	ifile.open(test);
	if (ifile.is_open())
	{
		ifile.close();
		if (MessageBox(NULL,"tato hra je již vytvoøená. chcete jí pøepsat?","warn",MB_OKCANCEL) == IDCANCEL)
			return false;
	}

	ifile.close();
	ofstream ofile;


	ofile.open(test);

	if (!ofile.is_open())
	{
		test += " creation failed";
		MessageBox(NULL,test.c_str(),"error",MB_OK);
	}
	
	ofile << "language: ";
	ofile << menu->btn[1].text.text << endl;
	ofile << "story: ";
	ofile << 0 << " " << 0 << " " << 0 << endl;
	ofile << "persons: ";
	ofile << 0 << " " << 0 << endl;
	ofile << "maps: ";
	ofile << 0 << " " << 0 << " " << 0 << endl;
	ofile << "NameOfBook: main";
	
	ofile.close();

	access->game.games.language = menu->btn[1].text.text; 
	
	
	access->game.games.textbar.r = 1;
	access->game.games.textbar.g = 1;
	access->game.games.textbar.b = 1;
	access->game.games.textbar.v = 0.25;
	access->game.games.textbar.image.address = "openedbook.bmp";
	access->game.games.textbar.image.w = 1;
	access->game.games.textbar.image.h = 1;
	access->game.games.textbar.image.cols = 1;
	access->game.games.textbar.image.rows = 1;
	access->game.games.textbar.rect.left = 0;
	access->game.games.textbar.rect.top = WIN_HEI-350;
	access->game.games.textbar.rect.right = WIN_WID;
	access->game.games.textbar.rect.bottom = 150;

	access->game.games.data.player.name = test.substr(0,test.length()-4);
	return true;
}


void AbsStartGame(UNIVERSAL *access, GAMES *game)
{
	game->textbar.text = 0;
	game->data.player.story = Data.flags.story;

	if (Data.flags.StoryAddress != "main" && Data.flags.StoryAddress != "")
	{
		LANGS_ADDR = BSC_WAY;
		LANGS_ADDR += Data.flags.StoryAddress;
		LANGS_ADDR += "/";
	}
	else
		LANGS_ADDR = BSC_WAY;

	Load_maps(&access->game.games.data.map,access->game.games.language);
	StoryLoad(access,&access->game.games.data.story,access->game.games.language);
	Load_Peer(access,&access->game.games.data.persons,access->game.games.language);
	access->game.state = STATE_GAME;
}

string KeyTrans(short key)
{
	string line;
	ifstream ifile("KeyTranslate.txt");
	if (!ifile.is_open())
		return ERROR;
	int cnt = 0;
	if ( ifile.good() )
		do { getline(ifile,line); cnt++; }while ( cnt < key && ifile.good() );

	if (line == "" || line == "\n" || line == " ")
	{
		ifile.close();
		return ERROR;
	}

	if (cnt != key)
	{
		ifile.close();
		return ERROR;
	}
	
	ifile.close();
	
	return line;

}


bool PlaySoundFile(UNIVERSAL *access,string file)
{
	if (file == "")
		return false;

	if (file.substr(file.length()-4,4) == ".wav")
	{
		PlaySound(file.c_str(),GetModuleHandle(0),SND_FILENAME|SND_ASYNC);
		return true;
	}

	if (file.substr(file.length()-4,4) == ".mp3" && file != access->mp3.address)
	{
		if (IsWindow(access->mp3.msc))
		{
			MCIWndStop(access->mp3.msc);
			DestroyWindow(access->mp3.msc);
		}
		access->mp3.msc = MCIWndCreate(access->wnd.hwnd, GetModuleHandle(NULL), WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR | MCIWNDF_NOMENU, TEXT(file.c_str()));
		MCIWndPlay(access->mp3.msc);
		access->mp3.address = file;
		return true;
	}
	return false;
}

void ChangeFrame(FRAMES *frames,short id)
{
	frames->frame = id;
	frames->snd = false;
}

