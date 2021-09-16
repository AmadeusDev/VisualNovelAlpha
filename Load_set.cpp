#include "Load.h"
void Load_set(SET *set,LOAD *load);

void Load_sets(SETS *set,LOAD *load)
{
	string temp;
	string word;
	short	id;


	while (load->ifile.good())
	{
		load->ifile >> word;
		temp = "set:";
		if (temp == word)
		{
			load->ifile >> word;
			id = atoi(word.c_str());
			Load_set(&set->set[id],load);
		}

	}


}

void Load_set(SET *set,LOAD *load)
{
	string temp;
	string word;
	short id;
	
	Proèista(set->btn,BTN_CNT);

	while (word != "konec:")
	{
		load->ifile >> word;

		if (word == "/*")
			while (word != "*/")
				load->ifile >> word;

		temp = "image:";
		if (temp == word)
		{
			Load_Image(&set->image,load);
		}

		temp = "pole:";
		if (temp == word)
		{
			load->ifile >> word;
			id = atoi(word.c_str());
			pole_load(load,&set->btn[id]);
			word = "";
		}
		
		temp = "frame:";
		if (temp == word)
		{
			load->ifile >> word;
			set->frame = atoi(word.c_str());
		}
		
		temp = "save:";
		if (temp == word)
		{
			load->ifile >> word;
			set->save = atoi(word.c_str());

		}
		
		temp = "x:";
		if (temp == word)
		{
			load->ifile >> word;
			set->rect.left = atoi(word.c_str());

		}
		
		temp = "y:";
		if (temp == word)
		{
			load->ifile >> word;
			set->rect.top = atoi(word.c_str());

		}
		
		temp = "w:";
		if (temp == word)
		{
			load->ifile >> word;
			set->rect.right = atoi(word.c_str());

		}
		
		temp = "h:";
		if (temp == word)
		{
			load->ifile >> word;
			set->rect.bottom = atoi(word.c_str());

		}
		
		temp = "druh:";
		if (temp == word)
		{
			load->ifile >> word;
			set->kind = atoi(word.c_str());

		}

	}




}