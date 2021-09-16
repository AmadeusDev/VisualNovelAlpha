#include "odkazy.h"
void EnableOpenGL(HWND hWnd, HDC * hDC, HGLRC * hRC);

int CreateOpenGLPIC(int chos, IMAGE *image)
{
	return CreateOpenGLPIC(chos, image->address, image->cols, image->rows, image->w, image->h);
}

int CreateOpenGLPIC(int chos, string address)
{
	return CreateOpenGLPIC(chos, address, 1, 1, 0, 0);
}

int CreateOpenGLPIC(int chos, string address, int cols, int rows, int w, int h)
{
	OPENGL *opengl;
	int index;
	switch (chos)
	{
		case 0:
		{
			index = Data.opengl.menus;
			opengl = &Data.opengl.menu[Data.opengl.menus];
			Data.opengl.menus++;
		}
		break;

		case 1:
		{
			index = Data.opengl.buttons;
			opengl = &Data.opengl.button[index];
			Data.opengl.buttons++;
		}
		break;

		case 2:
		{
			index = Data.opengl.saves;
			opengl = &Data.opengl.save[index];
			Data.opengl.saves++;
		}
		break;

		case 3:
		{
			index = Data.opengl.fonts;
			opengl = &Data.opengl.font[index];
			Data.opengl.fonts++;
		}
		break;

		case 4:
		{
			index = Data.opengl.maps;
			opengl = &Data.opengl.map[index];
			Data.opengl.maps++;
		}
		break;

		default:
			return -1;
	}
	HBITMAP hBmp = (HBITMAP)LoadImage(NULL, address.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	BITMAP bmp;

	opengl->address = address;

	GetObject(hBmp, sizeof(bmp), &bmp);

	opengl->W = bmp.bmWidth;
	opengl->H = bmp.bmHeight;

	if (w + h)
	{
		opengl->w = w;
		opengl->h = h;
	}
	else
	{
		opengl->w = opengl->W;
		opengl->h = opengl->H;
	}

	opengl->cols = cols;
	opengl->rows = rows;

	return index;
}


void LoadOpenGL(UNIVERSAL *access)
{
	EnableOpenGL(access->wnd.hwnd, &access->graph.buffer, & access->graph.hRC);
}

void EnableOpenGL(HWND hWnd, HDC * hDC, HGLRC * hRC)
{
	PIXELFORMATDESCRIPTOR pfd;
	int format;
	*hDC = GetDC(hWnd);

	// get the device context (DC)
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);                        // Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);                   // Black Background
	glClearDepth(1.0f);                         // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);                        // Enables Depth Testing
	glDepthFunc(GL_LEQUAL);                         // The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // Really Nice Perspective Calculations

	ZeroMemory(&pfd, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	format = ChoosePixelFormat(*hDC, &pfd);
	SetPixelFormat(*hDC, format, &pfd);

	*hRC = wglCreateContext(*hDC);
	wglMakeCurrent(*hDC, *hRC);
}

// Disable OpenGL

void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC)
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	ReleaseDC(hWnd, hDC);
}


void LoadTexture(OPENGL *opengl)
{
	int width, height;
	BYTE * data;
	BYTE * SuperData;
	FILE * file;
	opengl->W = 0;
	opengl->H = 0;


	if (opengl->address.substr(opengl->address.length() - 3, 3) == "bmp")
	{
		data = SOIL_load_image(opengl->address.c_str(), &opengl->W, &opengl->H, NULL, SOIL_LOAD_RGB);

		width = opengl->W;
		height = opengl->H;
		SuperData = (BYTE*)malloc(width * height * 4);
		int count = height - 1;
		for (int i = 0; i < height; i++)
		{

			for (int x = 0; x < width; x++)
			{
				int index = (count*width + x) * 3;
				int superIndex = (i*width + x) * 4;
				SuperData[superIndex] = data[index];
				SuperData[superIndex + 1] = data[index + 1];
				SuperData[superIndex + 2] = data[index + 2];
				if (data[index] + data[index + 1] + data[index + 2] == 0)
					SuperData[superIndex + 3] = 0;
				else
					SuperData[superIndex + 3] = 255;
			}
			count--;
		}

		opengl->index = 0;

		glGenTextures(1, &opengl->index);
		glBindTexture(GL_TEXTURE_2D, opengl->index);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, SuperData);
		free(data);
		free(SuperData);
	}
	else
	{
		opengl->index = SOIL_load_OGL_texture(opengl->address.c_str(),0,0,SOIL_FLAG_INVERT_Y);
	}
}