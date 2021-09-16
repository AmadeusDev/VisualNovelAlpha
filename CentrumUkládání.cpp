#include "classes.h"


void CentrumUkládáníANaèítání::Uložení(GAME *game)
{
	PLAYER *player = &game->games.data.player;
	INGAME	*data = &game->games.data;
	string address;
	lang = game->games.language;

	address += SVS_ADDR;

	address += player->name;
	addr = address;
	CreateDirectory(addr.c_str(), NULL);
	address += ".txt";
	UložitIndex(game, address);
	Game = game;
	UložitStav();
}

void CentrumUkládáníANaèítání::UložitStav()
{
	string Addr = addr;
	Addr += "/";
	if (Data.flags.StoryAddress == "")
	{
		Addr += "main";
		CreateDirectory(Addr.c_str(), NULL);
		Addr += "/";
	}
	else
	{
		Addr += Data.flags.StoryAddress;
		CreateDirectory(Addr.c_str(), NULL);
		Addr += "/";
	}
	Addr += "index.txt";
	UložitIndex(Game, Addr);
}

void CentrumUkládáníANaèítání::UložitIndex(GAME *game, string Addr)
{
	ofstream ofile;
	INGAME *data = &game->games.data;

	ofile.open(Addr);

	ofile.clear();

	ofile << "language: " << game->games.language << endl;

	ofile << "story: " << convert(data->story.coor.file) << " " << convert(data->story.coor.folder) << " "
		<< convert(data->player.story) << endl;

	ofile << "persons: " << convert(data->persons.coor.file) << " " << convert(data->persons.coor.folder) << endl;

	ofile << "maps: " << convert(data->map.coor.file) << " " << convert(data->map.coor.folder) << " "
		<< convert(data->player.map) << endl;

	if (Data.flags.StoryAddress == "")
		ofile << "NameOfBook: main" << endl;
	else
		ofile << "NameOfBook: " << Data.flags.StoryAddress << endl;

	ofile.close();
}