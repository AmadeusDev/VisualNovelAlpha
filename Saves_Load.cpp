#include "Load.h"
void Frame_Load(LOAD *load,FRAME *frame);
void Anime_load(SBUTTON *anime,LOAD *load);

void Saves_Load(LOAD *load,SAVES *save)
{
	string temp;
	string word;

	while (load->ifile.good())
	{
		load->ifile >> word;

		
		if (word == "/*")
			while (word != "*/")
				load->ifile >> word;

		temp = "image:";
		if (temp == word)
		{
			short	id = 0;
			load->ifile >> word;
			id = atoi(word.c_str());
			load->ifile >> word;
			save->pic[id].address = word;
			load->ifile >> word;
			save->pic[id].cols = atoi(word.c_str());
			load->ifile >> word;
			save->pic[id].rows = atoi(word.c_str());
			load->ifile >> word;
			save->pic[id].w = atoi(word.c_str());
			load->ifile >> word;
			save->pic[id].h = atoi(word.c_str());
			save->pic[id].chos = 2;
			save->pic[id].index = CreateOpenGLPIC(2, &save->pic[id]);
		}

		temp = "frame:";
		if (temp == word)
		{
			short	id = 0;
			load->ifile >> word;
			id = atoi(word.c_str());
			Frame_Load(load,&save->frame[id]);
		
		
		}


	}


}


void Frame_Load(LOAD *load,FRAME *frame)
{
	string temp;
	string word;

	frame->mirror = 1;
	frame->next_menu = -1;
	frame->set = -2;
	frame->w = 0;
	frame->h = 0;
	frame->sound = "";
	frame->SaveAdresa = "";
	//MessageBox(NULL,convert(frame->next_menu).c_str(),"test",MB_OK);
	while (word != "konec:")
	{
		load->ifile >> word;

		if (word == "sound:")
		{
			load->ifile >> word;
			frame->sound = word;

		}

		if (word == "obraz:")
		{
			load->ifile >> word;
			frame->pic = atoi(word.c_str());

		}

		if (word == "Story_coor:")
		{
			load->ifile >> word;
			frame->Story.folder = atoi(word.c_str());
			load->ifile >> word;
			frame->Story.file = atoi(word.c_str());
		}

		if (word == "OtevøítKnihu:")
		{
			load->ifile >> word;
			frame->SaveAdresa = word;
		}

		if (word == "OøíznoutObrázek:")
		{
			load->ifile >> word;
			frame->oøíznout.left = GetRealVal(word);
			load->ifile >> word;
			frame->oøíznout.top = GetRealVal(word);
			load->ifile >> word;
			frame->oøíznout.right = GetRealVal(word);
			load->ifile >> word;
			frame->oøíznout.bottom = GetRealVal(word);
		}

		if (word == "idS:")
		{
			load->ifile >> word;
			frame->idS = atoi(word.c_str());
		}

		if (word == "Map_coor:")
		{
			load->ifile >> word;
			frame->Map.folder = atoi(word.c_str());
			load->ifile >> word;
			frame->Map.file = atoi(word.c_str());
		}

		if (word == "idM:")
		{
			load->ifile >> word;
			frame->idM = atoi(word.c_str());

		}

		if (word == "Person_coor:")
		{
			load->ifile >> word;
			frame->Person.folder = atoi(word.c_str());
			load->ifile >> word;
			frame->Person.file = atoi(word.c_str());
		}
		
		temp = "pùvodní:";
		if (temp == word)
		{
			load->ifile >> word;
			frame->previous = atoi(word.c_str());

		}

		temp = "set:";
		if (temp == word)
		{
			load->ifile >> word;
			frame->set = atoi(word.c_str());

		}

		temp = "anime:";
		if (temp == word)
		{
			load->ifile >> word;
			Anime_load(&frame->button[atoi(word.c_str())],load);
		}

		temp = "dìlitelw:";
		if (temp == word)
		{
			load->ifile >> word;
			frame->dividerw = (float)atoi(word.c_str())/100;

		}

		temp = "dìlitelh:";
		if (temp == word)
		{
			load->ifile >> word;
			frame->dividerh = (float)atoi(word.c_str())/100;

		}

		temp = "další_menu:";
		if (temp == word)
		{
			load->ifile >> word;
			frame->next_menu = atoi(word.c_str());
		}

		temp = "další:";
		if (temp == word)
		{
			load->ifile >> word;
			frame->next = atoi(word.c_str());

		}

		temp = "doba:";
		if (temp == word)
		{
			load->ifile >> word;
			frame->time = atoi(word.c_str());

		}

		temp = "druh:";
		if (temp == word)
		{
			load->ifile >> word;
			frame->kind = atoi(word.c_str());
		}

		temp = "RS:";
		if (temp == word)
		{
			load->ifile >> word;
			frame->RS = (float)atoi(word.c_str())/100;
		}

		temp = "GS:";
		if (temp == word)
		{
			load->ifile >> word;
			frame->GS = (float)atoi(word.c_str())/100;

		}

		temp = "w:";
		if (temp == word)
		{
			load->ifile >> word;
			frame->w = atoi(word.c_str());
		}

		temp = "h:";
		if (temp == word)
		{
			load->ifile >> word;
			frame->h = atoi(word.c_str());
		}

		temp = "zrcadlení:";
		if (temp == word)
		{
			load->ifile >> word;
			frame->mirror = (-1)*atoi(word.c_str());
		}

		temp = "text:";
		if (temp == word)
		{
			Load_Text(&frame->text,load);
		}

		temp = "BS:";
		if (temp == word)
		{
			load->ifile >> word;
			frame->BS = (float)atoi(word.c_str())/100;

		}

		temp = "VS:";
		if (temp == word)
		{
			load->ifile >> word;
			frame->VS = (float)atoi(word.c_str())/100;

		}

		temp = "centrumx:";
		if (temp == word)
		{
			load->ifile >> word;
			frame->centerx = atoi(word.c_str());

		}

		temp = "centrumy:";
		if (temp == word)
		{
			load->ifile >> word;
			frame->centery = atoi(word.c_str());

		}

		temp = "posunx:";
		if (temp == word)
		{
			load->ifile >> word;
			frame->dvx = atoi(word.c_str());

		}

		temp = "posuny:";
		if (temp == word)
		{
			load->ifile >> word;
			frame->dvy = atoi(word.c_str());

		}

		temp = "úhel:";
		if (temp == word)
		{
			load->ifile >> word;
			frame->angle = atoi(word.c_str());

		}
	
	}


}


void Anime_load(SBUTTON *anime,LOAD *load)
{
	string temp;
	string word;
	anime->active = true;

	anime->reverse = 1;

	while ( load->ifile.good() && word != "konec:")
	{
		load->ifile >> word;

		temp = "x:";
		if (temp == word)
		{
			load->ifile >> word;
			anime->x = atoi(word.c_str());
		
		}

		temp = "y:";
		if (temp == word)
		{
			load->ifile >> word;
			anime->y = atoi(word.c_str());
		
		}

		temp = "w:";
		if (temp == word)
		{
			load->ifile >> word;
			anime->w = atoi(word.c_str());
		
		}

		temp = "h:";
		if (temp == word)
		{
			load->ifile >> word;
			anime->h = atoi(word.c_str());
		
		}

		temp = "obraz:";
		if (temp == word)
		{
			load->ifile >> word;
			anime->pic = atoi(word.c_str());
		
		}

		temp = "zrcadlení:";
		if (temp == word)
		{
			load->ifile >> word;
			anime->reverse = (-2)*atoi(word.c_str())+1;
		}

		temp = "typ:";
		if (temp == word)
		{
			load->ifile >> word;
			anime->type = atoi(word.c_str());
		
		}

		temp = "frame:";
		if (temp == word)
		{
			load->ifile >> word;
			anime->frame = atoi(word.c_str());

		}

		temp = "save:";
		if (temp == word)
		{
			load->ifile >> word;
			anime->save = atoi(word.c_str());

		}


	}


}