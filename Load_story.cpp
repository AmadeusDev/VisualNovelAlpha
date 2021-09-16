#include "Load.h"
void LoadSummon(CONJURE *person,ifstream *ifile);
void StoryPartLoad(STORY *story,LOAD *load);
void LoadAnswer(ODPOVÌÏ *answer,ifstream *ifile,LOAD *load);


bool StoryLoad(UNIVERSAL *access,STORYLINE *storyline,string lang)
{
	string address;
	string word;
	LOAD load;
	address = LANGS_ADDR;
	address += convert(storyline->coor.folder);
	address += "/";
	address += "s";
	address += convert(storyline->coor.file);
	address += ".txt";

	load.lang = lang;
	load.ifile.open(address);

	for (int a = 0; a < STR_CNT; a++)
		storyline->story[a].Changed = false;

	if (!load.ifile.is_open())
	{
		address += " cannot be loaded";
		MessageBox(NULL,address.c_str(),"error",MB_OK);
		return false;
	}

	while (load.ifile.good())
	{
		load.ifile >> word;


		if (word == "/*")
			while (word != "*/")
				load.ifile >> word;

		if (word == "story:")
		{
			load.ifile >> word;
			StoryPartLoad(&storyline->story[atoi(word.c_str())],&load);

		}
	}
}

void StoryPartLoad(STORY *story,LOAD *load)
{
	string word;

	story->frames.frame = -1;
	story->frames.save = -1;
	story->frames.active = 0;
	story->OdpCnt = 0;
	story->conjure.active = false;
	story->NextMap.jo = false;
	story->NextMap.map = 0;
	story->NextMap.nové = false;
	story->NextMap.coor.file = 0;
	story->NextMap.coor.folder = 0;
	story->FrameCoor.file = -1;
	story->FrameCoor.folder = -1;
	story->frame = -1;
	story->save = -1;

	bool Nxt = false;

	while (word != "konec:" && load->ifile.good())
	{
		
		if (word == "/*")
			while (word != "*/")
				load->ifile >> word;

		if (Nxt == true)
			Nxt = false;
		else
			load->ifile >> word;
		
		if (word == "/*")
			while (word != "*/")
				load->ifile >> word;

		if (word == "sound:")
		{
			load->ifile >> word;
			story->sound = word;
		}

		if (word == "frame:")
		{
			load->ifile >> word;
			story->frame = atoi(word.c_str());
		}

		if (word == "frame_load:")
		{
			load->ifile >> word;
			story->FrameCoor.folder = atoi(word.c_str());
			load->ifile >> word;
			story->FrameCoor.file = atoi(word.c_str());
		}

		if (word == "txtbar:")
		{
			LoadTxtBar(&load->ifile, &story->txtbar);
		}

		if (word == "coor:")
		{
			load->ifile >> word;
			story->coor.folder = atoi(word.c_str());
			load->ifile >> word;
			story->coor.file = atoi(word.c_str());
		}

		if (word == "naèíst_mapu:")
		{
			story->NextMap.jo = true;
			load->ifile >> word;
			story->NextMap.map = atoi(word.c_str());
			load->ifile >> word;
			if (word.at(0) < '0' || word.at(0) > '9')
			{
				Nxt = true;
				continue;
			}
			story->NextMap.nové = true;
			story->NextMap.coor.folder = atoi(word.c_str());
			load->ifile >> word;
			story->NextMap.coor.file = atoi(word.c_str());
		}

		if (word == "map:")
		{
			load->ifile >> word;
			story->conds.map = atoi(word.c_str());
		}

		if (word == "druh:")
		{
			load->ifile >> word;
			story->kind = atoi(word.c_str());
		}

		if (word == "save:")
		{
			load->ifile >> word;
			story->frames.active = true;
			story->save = atoi(word.c_str());
		}

		if (word == "NaèístSave:")
		{
			load->ifile >> word;
			story->SaveCoor.folder = atoi(word.c_str());
			load->ifile >> word;
			story->SaveCoor.file = atoi(word.c_str());
		}

		if (word == "person:")
		{
			story->conjure.active = true;
			LoadSummon(&story->conjure,&load->ifile);
		}

		if (word == "text:")
		{
			Load_Text(&story->text,load);
		}

		if (word == "answer:")
		{
			LoadAnswer(&story->odpovìï[story->OdpCnt],&load->ifile,load);
			story->OdpCnt++;
		}

	}


}


void LoadSummon(CONJURE *person,ifstream *ifile)
{
	string word;

	while (word != "konec:")
	{
		*ifile >> word;

		if (word == "id:")
		{
			*ifile >> word;
			person->id = atoi(word.c_str());
		}

		if (word == "frame:")
		{
			*ifile >> word;
			person->frame = atoi(word.c_str());
		}

		if (word == "rect:")
		{
			*ifile >> word;
			person->rect.left = atoi(word.c_str());
			*ifile >> word;
			person->rect.top = atoi(word.c_str());
			*ifile >> word;
			person->rect.right = atoi(word.c_str());
			*ifile >> word;
			person->rect.bottom = atoi(word.c_str());
		}

		if (word == "coor:")
		{
			*ifile >> word;
			person->coor.folder = atoi(word.c_str());
			*ifile >> word;
			person->coor.file = atoi(word.c_str());
		}

		if (word == "save:")
		{
			*ifile >> word;
			person->save = atoi(word.c_str());
		}

		if (word == "cond:")
		{
			*ifile >> word;
			person->condition = atoi(word.c_str());
		}



	}


}

void LoadAnswer(ODPOVÌÏ *answer,ifstream *ifile,LOAD *load)
{
	string word;



	while (word != "konec:")
	{
		*ifile >> word;

		if (word == "text:")
		{
			Load_Text(&answer->text,load);
		}

		if (word == "next:")
		{
			*ifile >> word;
			answer->next = atoi(word.c_str());
		}

		if (word == "story:")
		{
			*ifile >> word;
			answer->story = atoi(word.c_str()); 
		}

		if (word == "person:")
		{
			*ifile >> word;
			answer->charakters = atoi(word.c_str()); 
		}

		if (word == "frames:")
		{
			*ifile >> word;
			answer->frames = atoi(word.c_str()); 
		}

	}


}