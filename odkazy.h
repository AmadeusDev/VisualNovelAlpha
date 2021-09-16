#include "classes.h"
short Load(UNIVERSAL *access,char *folder_name);
void Proc(UNIVERSAL *access);
void graph_load(UNIVERSAL *access);
void Basics_Setup(UNIVERSAL *access);
void menu(UNIVERSAL *access,MENUS *menu);
void Sanime(UNIVERSAL *access,BUTTON anime[]);
void Game(UNIVERSAL *access,GAMES *games);
void LoadOpenGL(UNIVERSAL *access);
void LoadTexture(OPENGL *);
void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC);
void EnableOpenGL(HWND hWnd, HDC * hDC, HGLRC * hRC);
void InitGL(UNIVERSAL *access);
void EndGL(UNIVERSAL *access);
int CreateOpenGLPIC(int, string, int, int, int, int);
int CreateOpenGLPIC(int, string);
int CreateOpenGLPIC(int, IMAGE *);