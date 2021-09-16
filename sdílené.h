#include "struktury.h"
string convert(double num);
void startPnt(GRAPH *graph);
void Paint_element(UNIVERSAL *access, GRAPH *graph, IMAGE *simage, HDC hdc, string address, DRECT *drect, short x, short y, short w, short h);
void OpenGLTurboKreslení(UNIVERSAL *, GRAPH *, IMAGE *, HDC, string, DRECT *, short, short, short, short);
void Keys_detect(HWND hwnd,KEYS *keys);
bool Rect_get(RECT *rect,POINT *p);
void buttonClicked(UNIVERSAL *access,BUTTON btn[],short count,KEYS *keys);
void buttonDraw(UNIVERSAL *access,BUTTON btn[],short count,GRAPH *graph,IMAGE *image,SAVES save[]);
void Text_Draw(HDC hdc,TEXT *text,RECT *rect);
void Frames(UNIVERSAL *access,FRAMES *frames,SAVES saves[],RECT *rect);
void MenuFrames(UNIVERSAL *access,BUTTON btn[],short count,SAVES save[]);
void ChangeStory(UNIVERSAL *access,PLAYER *player,STORYLINE *storyline,int imma);
void Load_Graph(FRAME *frame,GRAPH *graph);
string findword(string text,int &pos);
void Proèista(BUTTON btn[],int count);
bool PlaySoundFile(UNIVERSAL *access,string file);
void ChangeFrame(FRAMES *frames,short id);

DWORD WINAPI Texter(LPARAM lParameter);
DWORD WINAPI Loader(LPARAM lParam);
DWORD WINAPI Timer(LPARAM lParam);

bool startGame(UNIVERSAL *access,MENU *menu);
bool Load_maps(MAPS *maps,string jazyk);
bool StoryLoad(UNIVERSAL *access,STORYLINE *storyline,string lang);
void AbsStartGame(UNIVERSAL *access, GAMES *game);
bool Load_Svs(UNIVERSAL *access,SAVES *save,COOR *coor);
bool Load_Peer(UNIVERSAL *access,PERSONS *persons,string language); 
void LoadSaveInners(ifstream *ifile, string *lang, INGAME *data, string *word);


double GetRealVal(string word);
double GetRealVal(string word,short val);
void PostChanges(BUTTON *btn);
void GLDrawText(TEXT *text, RECT *rect);
