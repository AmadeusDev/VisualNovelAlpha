#include "Load.h"


void Items_load(LOAD *load,ITEMS *items)
{
	string temp;
	string word;

	while (load->ifile.good())
	{
		load->ifile >> word;

		temp = "item:";
		if (word == temp)
		{
			load->ifile >> word;

		}


	}



}


void Item_Load(LOAD *load,ITEM *item)
{
	string temp;
	string word;


	while (word != "konec:")
	{
		load->ifile >> word;

		temp = "name:";
		if (word == temp)
		{
			load->ifile >> word;
			item->name = word;

		}


	}


}