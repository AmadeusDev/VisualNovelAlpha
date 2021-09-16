#include "Load.h"

void PersonLoading(PERSON *person,LOAD *load);

bool Load_Peer(UNIVERSAL *access,PERSONS *persons,string language)
{
	string address;
	string word;
	LOAD load;

	address = LANGS_ADDR;
	address += convert(persons->coor.folder);
	address += "/";
	address += "p";
	address += convert(persons->coor.file);
	address += ".txt";

	load.lang = language;
	load.ifile.open(address);

	if (!load.ifile.is_open())
	{
		address += " cannot be loaded";
		MessageBox(NULL,address.c_str(),"error",MB_OK);
		return false;
	}

	while (load.ifile.good())
	{
		load.ifile >> word;


		if (word == "person:")
		{
			load.ifile >> word;
			PersonLoading(&persons->person[atoi(word.c_str())],&load);

		}

	}

	return true;

}


void PersonLoading(PERSON *person,LOAD *load)
{
	string word;

	while (word != "konec:")
	{
		load->ifile >> word;
		if  (word == "image:")
		{
			load->ifile >> word;
			Load_Image(&person->image[atoi(word.c_str())],load);
		}

		if (word == "sex:")
		{
			load->ifile >> word;
			person->sex = atoi(word.c_str());

		}

		if (word == "name:")
		{
			load->ifile >> word;
			person->name = Text_modify(word);

		}

		if (word == "age:")
		{
			load->ifile >> word;
			person->age = atoi(word.c_str());

		}
		if (word == "save:")
		{
			load->ifile >> word;
			person->frame.save = atoi(word.c_str());
		}
	}



}