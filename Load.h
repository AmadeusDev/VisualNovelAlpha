#include "odkazy.h"

void Saves_Load(LOAD *load,SAVES *save);
void pole_load(LOAD *load,BUTTON *btn);
void Load_sets(SETS *set,LOAD *load);
void Load_Text(TEXT *text,LOAD *load);
void Load_Image(IMAGE *image,LOAD *load);;
short symbols(string word);
int translate(string word); 
string Text_modify(string text);
string Text_modify(string text, bool reverse);
void LoadFont(LOAD *load);
string Texts(string word, string lang);
void LoadTxtBar(ifstream *ifile, TXTBAR *txtbar);
