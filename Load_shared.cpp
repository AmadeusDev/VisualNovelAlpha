#include "Load.h"
void bevent_load(LOAD *load,BEVENT *bevent);
void Load_Change(LOAD *load,CHANGE *change);

void pole_load(LOAD *load,BUTTON *btn)
{
	string temp;
	string word;
	btn->spec = 0;
	btn->dividerw = 1;
	btn->dividerh = 1;
	btn->RS = 1;
	btn->GS = 1;
	btn->BS = 1;
	btn->VS = 1;
	btn->angle = 0;
	btn->change.kind = -1;

	while (word != "stop:" && load->ifile.good())
	{
		load->ifile >> word;
		
		temp = "x:";
		if (temp == word)
		{
			load->ifile >> word;
			btn->rect.left = atoi(word.c_str());
		}

		temp = "obraz_velikost:";
		if (temp == word)
		{
			load->ifile >> word;
			btn->image.left = atoi(word.c_str());
			load->ifile >> word;
			btn->image.top = atoi(word.c_str());
			load->ifile >> word;
			btn->image.right = atoi(word.c_str());
			load->ifile >> word;
			btn->image.bottom = atoi(word.c_str());
		}

		temp = "OøíznoutObrázek:";
		if (temp == word)
		{
			load->ifile >> word;
			btn->oøíznout.left = GetRealVal(word);
			load->ifile >> word;
			btn->oøíznout.top = GetRealVal(word);
			load->ifile >> word;
			btn->oøíznout.right = GetRealVal(word);
			load->ifile >> word;
			btn->oøíznout.bottom = GetRealVal(word);
		}
		
		temp = "druh:";
		if (temp == word)
		{
			load->ifile >> word;
			btn->kind = atoi(word.c_str());
		}
		
		temp = "RS:";									//red shade
		if (temp == word)
		{
			load->ifile >> word;
			btn->RS = (float)atoi(word.c_str())/100;
		}
		
		temp = "GS:";
		if (temp == word)
		{
			load->ifile >> word;
			btn->GS = (float)atoi(word.c_str())/100;
		}
		
		temp = "BS:";
		if (temp == word)
		{
			load->ifile >> word;
			btn->BS = (float)atoi(word.c_str())/100;
		}
		
		temp = "VS:";									//alfa
		if (temp == word)
		{
			load->ifile >> word;
			btn->VS = (float)atoi(word.c_str())/100;
		}
		
		temp = "dìlitelw:";
		if (temp == word)
		{
			load->ifile >> word;
			btn->dividerw = (float)atoi(word.c_str())/100;
		}
		
		temp = "dìlitelh:";
		if (temp == word)
		{
			load->ifile >> word;
			btn->dividerh = (float)atoi(word.c_str())/100;
		}
		
		temp = "VS:";
		if (temp == word)
		{
			load->ifile >> word;
			btn->VS = (float)atoi(word.c_str())/100;
		}
		
		temp = "angle:";
		if (temp == word)
		{
			load->ifile >> word;
			btn->angle = atoi(word.c_str());
		}
		
		temp = "text:";
		if (temp == word)
		{
			Load_Text(&btn->text,load);
		}

		temp = "both:";
		if (temp == word)
		{
			load->ifile >> word;
			btn->bevent[_BOTH].key = symbols(word);
			bevent_load(load,&btn->bevent[_BOTH]);
			word = "";
		}

		temp = "key:";
		if (temp == word)
		{
			load->ifile >> word;
			btn->bevent[_KEY].key = symbols(word);
			bevent_load(load,&btn->bevent[_KEY]);
			word = "";
		}

		temp = "pos:";
		if (temp == word)
		{
			bevent_load(load,&btn->bevent[_POS]);
			word = "";
		}
		
		temp = "y:";
		if (temp == word)
		{
			load->ifile >> word;
			btn->rect.top = atoi(word.c_str());
		}
		
		temp = "change:";
		if (temp == word)
		{
			Load_Change(load,&btn->change);
			word = "";
		}
		
		temp = "w:";
		if (temp == word)
		{
			load->ifile >> word;
			btn->rect.right = atoi(word.c_str());
		}
		
		temp = "h:";
		if (temp == word)
		{
			load->ifile >> word;
			btn->rect.bottom = atoi(word.c_str());
		}
		
		temp = "typ:";
		if (temp == word)
		{
			load->ifile >> word;
			btn->typ = atoi(word.c_str());
		}
		
		temp = "obraz:";
		if (temp == word)
		{
			load->ifile >> word;
			btn->pic = atoi(word.c_str());
		}
	}

}


void bevent_load(LOAD *load,BEVENT *bevent)
{
	string temp;
	string word;
	bevent->active = true;
	bool truth = false;

	while(word != "konec:" && load->ifile.good())
	{
		if (truth == false)
		{
			load->ifile >> word;
		}
		else
			truth = false;
		temp = "clicked:";
		if (temp == word)
		{
			bevent->bkind[CLICKED].active = false;
			bevent->bkind[CLICKED].switched = true;
			bevent->bkind[CLICKED].change = 0;
			load->ifile >> word;
			bevent->bkind[CLICKED].save = atoi(word.c_str());
			load->ifile >> word;
			bevent->bkind[CLICKED].frame = atoi(word.c_str());
			load->ifile >> word;
			if (atoi(word.c_str()) != 0)
				bevent->bkind[CLICKED].change = atoi(word.c_str());
		}

		temp = "once:";
		if (temp == word)
		{
			bevent->bkind[ONCE].change = 0;
			bevent->bkind[ONCE].active = false;
			bevent->bkind[ONCE].switched = true;
			load->ifile >> word;
			bevent->bkind[ONCE].save = atoi(word.c_str());
			load->ifile >> word;
			bevent->bkind[ONCE].frame = atoi(word.c_str());
			load->ifile >> word;
			if (atoi(word.c_str()) != 0)
				bevent->bkind[ONCE].change = atoi(word.c_str());
			else
				truth = true;
		}

	}


}


void Load_Image(IMAGE *image,LOAD *load)
{
	string temp;
	string word;
	wchar_t			Temp[MAX_PATH];
	load->ifile >> word;
	image->address = word;
	load->ifile >> word;
	image->cols = atoi(word.c_str());
	load->ifile >> word;
	image->rows = atoi(word.c_str());
	load->ifile >> word;
	image->w = atoi(word.c_str());
	load->ifile >> word;
	image->h = atoi(word.c_str());
	image->chos = 0;
	image->index = CreateOpenGLPIC(0, image);

	mbstowcs(Temp,image->address.c_str(),MAX_PATH);
}


int translate(string word)
{
	if (word == "lbutton")
		return VK_LBUTTON;

}


short symbols(string word)
{
	if (word == "lbutton")
		return 0;


	return -1;
}


void Load_Text(TEXT *text,LOAD *load)
{
	string word;
	string temp;
	text->before = false;

	while (load->ifile.good() && word != "konec:")
	{
		load->ifile >> word;

		temp = "write:";
		if (temp == word)
		{
			load->ifile >> word;
			
			if (word.at(0) == '#')
				text->text = Texts(word,load->lang);
			else
				text->text = Text_modify(word);

		}

		temp = "za:";
		if (temp == word)
		{
			load->ifile >> word;
			text->before = atoi(word.c_str());

		}

		temp = "druh:";
		if (temp == word)
		{
			load->ifile >> word;
			text->kind = atoi(word.c_str());

		}

		temp = "x:";
		if (temp == word)
		{
			load->ifile >> word;
			text->meas.left = atoi(word.c_str());

		}

		temp = "y:";
		if (temp == word)
		{
			load->ifile >> word;
			text->meas.top = atoi(word.c_str());

		}

		temp = "w:";
		if (temp == word)
		{
			load->ifile >> word;
			text->meas.right = atoi(word.c_str());

		}

		temp = "h:";
		if (temp == word)
		{
			load->ifile >> word;
			text->meas.bottom = atoi(word.c_str());

		}

		temp = "size:";
		if (temp == word)
		{
			load->ifile >> word;
			text->size = atoi(word.c_str());

		}

		temp = "size_w:";
		if (temp == word)
		{
			load->ifile >> word;
			text->size_w = atoi(word.c_str());

		}

		temp = "red:";
		if (temp == word)
		{
			load->ifile >> word;
			text->red = atoi(word.c_str());

		}

		temp = "green:";
		if (temp == word)
		{
			load->ifile >> word;
			text->green = atoi(word.c_str());

		}

		temp = "blue:";
		if (temp == word)
		{
			load->ifile >> word;
			text->blue = atoi(word.c_str());

		}


	}



}


string Text_modify(string text)
{
	int cnt = NULL;
	while (cnt < text.length())
	{
		if (text.at(cnt) == '_')
			text.replace(cnt, 1, " ");

		if (text.at(cnt) == '~')
			text.replace(cnt, 1, "\n");
		cnt++;
	}

	return text;
}


void Load_Change(LOAD *load,CHANGE *change)
{
	string temp;
	string word;

	change->tect.left = -1;
	change->kind = -1;

	while(load->ifile.good() && word != "stop:")
	{
		load->ifile >> word;

		temp = "text_vypiš:"; 
		if (temp == word)
		{
			load->ifile >> word;
			change->text = Text_modify(word);
		}

		temp = "text_x:"; 
		if (temp == word)
		{
			load->ifile >> word;
			change->tect.left = atoi(word.c_str());
		}

		temp = "text_r:"; 
		if (temp == word)
		{
			load->ifile >> word;
			change->t_r = atoi(word.c_str());
		}

		temp = "text_g:"; 
		if (temp == word)
		{
			load->ifile >> word;
			change->t_g= atoi(word.c_str());
		}

		temp = "text_b:"; 
		if (temp == word)
		{
			load->ifile >> word;
			change->t_b = atoi(word.c_str());
		}

		temp = "text_s:"; 
		if (temp == word)
		{
			load->ifile >> word;
			change->t_s = atoi(word.c_str());
		}

		temp = "text_sw:"; 
		if (temp == word)
		{
			load->ifile >> word;
			change->t_sw = atoi(word.c_str());
		}

		temp = "text_bef:"; 
		if (temp == word)
		{
			load->ifile >> word;
			change->t_bef = atoi(word.c_str());
		}

		temp = "text_y:"; 
		if (temp == word)
		{
			load->ifile >> word;
			change->tect.top = atoi(word.c_str());
		}

		temp = "text_w:"; 
		if (temp == word)
		{
			load->ifile >> word;
			change->tect.right = atoi(word.c_str());
		}

		temp = "text_h:"; 
		if (temp == word)
		{
			load->ifile >> word;
			change->tect.bottom = atoi(word.c_str());
		}

		temp = "druh:";
		if (temp == word)
		{
			load->ifile >> word;
			change->kind = atoi(word.c_str());
		}

		temp = "v:";
		if (temp == word)
		{
			load->ifile >> word;
			change->in = atoi(word.c_str());
		}

		temp = "který:";
		if (temp == word)
		{
			load->ifile >> word;
			change->which = atoi(word.c_str());
		}


	}
}

string Texts(string word,string lang)
{
	ifstream ifile;

	short which = atoi(word.substr(1,word.length()-1).c_str());

	string name = LANGS_ADDR;
	name += lang;
	name += TEXTS;

	ifile.open(name);

	int cnt = 0;

	do
	{
		getline(ifile,word);
		cnt++;

	}while (cnt < which + 1 && ifile.good()); 

	if (cnt < which + 1 || word == " ")
		return "";

	return word;
}


double GetRealVal(string word)
{

	return GetRealVal(word,WIN_WID);
}


double GetRealVal(string word,short val)
{
	switch (word[word.length() - 1])
	{
		case '%':
		{
			return (double)atoi(word.substr(0, word.length() - 1).c_str()) / 100;
		}
		break;
		case 'v':
		{
			return (double)atoi(word.substr(0, word.length() - 1).c_str()) / val;
		}
		case 'W':
		{
			return (double)WIN_WID*atoi(word.substr(0, word.length() - 1).c_str()) / 100;
		}
		break;
		case 'H':
		{
			return (double)WIN_HEI*atoi(word.substr(0, word.length() - 1).c_str()) / 100;
		}
		break;
	}

	return atoi(word.c_str());
}


void LoadTxtBar(ifstream *ifile,TXTBAR *txtbar)
{
	string word = "";

	txtbar->active = 123;
	txtbar->drect.left = 0;
	txtbar->drect.right = WIN_WID;
	txtbar->drect.top = WIN_HEI-150;
	txtbar->drect.bottom = 150;

	txtbar->RS = 1.0;
	txtbar->GS = 1.0;
	txtbar->BS = 1.0;
	txtbar->VS = 1.0;

	while (word != "stop:")
	{
		*ifile >> word;

		if (word == "x:")
		{
			*ifile >> word;
			txtbar->drect.left = GetRealVal(word.c_str());
		}

		if (word == "y:")
		{
			*ifile >> word;
			txtbar->drect.top = GetRealVal(word.c_str());
		}

		if (word == "w:")
		{
			*ifile >> word;
			txtbar->drect.right = GetRealVal(word.c_str());
		}

		if (word == "h:")
		{
			*ifile >> word;
			txtbar->drect.bottom = GetRealVal(word.c_str());
		}

		if (word == "RS:")
		{
			*ifile >> word;
			txtbar->RS = (float)atoi(word.c_str()) / 100;
		}

		if (word == "GS:")
		{
			*ifile >> word;
			txtbar->GS = (float)atoi(word.c_str()) / 100;
		}

		if (word == "BS:")
		{
			*ifile >> word;
			txtbar->BS = (float)atoi(word.c_str()) / 100;
		}

		if (word == "VS:")
		{
			*ifile >> word;
			txtbar->VS = (float)atoi(word.c_str()) / 100;
		}
	}

}