#include "Load.h"

bool Load_Svs(UNIVERSAL *access,SAVES *save,COOR *coor)
{
	string address;
	LOAD load;

	address = LANGS_ADDR;
	address += convert(coor->folder);
	address += "/";
	address += "f";
	address += convert(coor->file);
	address += ".txt";

	load.lang = access->game.games.language;
	load.ifile.open(address);

	if (!load.ifile.is_open())
	{
		address += " cannot be loaded";
		MessageBox(NULL,address.c_str(),"error",MB_OK);
		return false;
	}

	Saves_Load(&load,save);

	save->coor.file = coor->file;
	save->coor.folder = coor->folder;
	return true;
}