#pragma once
#include "sdílené.h"

class CentrumUkládáníANaèítání
{
private:
	string lang;
	string addr;
	GAME *Game;

public:
	void Uložení(GAME *game);

private:

	void UložitStav();

	void UložitIndex(GAME *game, string Addr);

};