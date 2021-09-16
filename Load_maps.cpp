#include "Load.h"
void Loading(MAPS *map,LOAD *load);
void LoadingMap(MAP *map,LOAD *load);

bool Load_maps(MAPS *maps,string jazyk)
{
	string address;
	LOAD load;

	address += LANGS_ADDR;
	address += convert(maps->coor.folder);
	address += "/m";
	address += convert(maps->coor.file);
	address += ".txt";
	
	load.ifile.open(address);

	if (!load.ifile.is_open())
	{
		address += " cannot be loaded";
		MessageBox(NULL,address.c_str(),"error",MB_OK);
		return false;
	}


	Loading(maps,&load);
	return true;
}

void Loading(MAPS *map,LOAD *load)
{
	string temp;
	string word;
	
	while (load->ifile.good())
	{
		load->ifile >> word;
		
		if (word == "map:")
		{
			load->ifile >> word;
			LoadingMap(&map->map[atoi(word.c_str())],load);
		}

	}

}


void LoadingMap(MAP *map,LOAD *load)
{
	string word;

	while (word != "konec:")
	{
		load->ifile >> word;


		if (word == "/*")
			while (word != "*/")
				load->ifile >> word;

		if (word == "sound:")
		{
			load->ifile >> word;
			map->sound = word;
		}

		if (word == "image:")
		{
			load->ifile >> word;
			map->image.address = word;
			load->ifile >> word;
			map->image.cols = atoi(word.c_str());
			load->ifile >> word;
			map->image.rows = atoi(word.c_str());
			load->ifile >> word;
			map->image.w = atoi(word.c_str());
			load->ifile >> word;
			map->image.h = atoi(word.c_str());
			map->image.chos = 1;
			map->image.index = CreateOpenGLPIC(1, &map->image);

		}

		if (word == "pozad�:")
		{
			load->ifile >> word;
			map->pozad�.address = word;
			map->pozad�.chos = 4;
			map->pozad�.index = CreateOpenGLPIC(4, word);
		}
		if ("O��znoutObr�zek:" == word)
		{
			load->ifile >> word;
			map->o��znout.left = GetRealVal(word);
			load->ifile >> word;
			map->o��znout.top = GetRealVal(word);
			load->ifile >> word;
			map->o��znout.right = GetRealVal(word);
			load->ifile >> word;
			map->o��znout.bottom = GetRealVal(word);
		}

		if (word == "rozlo�en�:")
		{
			load->ifile >> word;
			map->pozad�.w = atoi(word.c_str());
			load->ifile >> word;
			map->pozad�.h = atoi(word.c_str());
			map->pozad�.cols = 1;
			map->pozad�.rows = 1;
		}

		if (word == "object:")
		{
			load->ifile >> word;
			pole_load(load,&map->btn[atoi(word.c_str())]);
			word = "";
		}

		if (word == "save:")
		{
			load->ifile >> word;
			map->save = atoi(word.c_str());
		}

		if (word == "coor:")
		{
			load->ifile >> word;
			map->SvCoor.folder = atoi(word.c_str());
			load->ifile >> word;
			map->SvCoor.file = atoi(word.c_str());
		}

	}

}