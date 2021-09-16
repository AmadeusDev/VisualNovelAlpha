#include "odkazy.h"
OPENGL *Chos(int type, int which);

void InitGL(UNIVERSAL *access)
{
	static bool once = false;
	if (!once)
		LoadOpenGL(access);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	once = true;
}


void OpenGLTurboKreslení(UNIVERSAL *access, GRAPH *graph, IMAGE *simage, HDC hdc, string address, DRECT *oøíznout, short x, short y, short w, short h)
{
	OPENGL *opengl = Chos(simage->chos,simage->index);
	

	double txtureW;
	double txtureH;
	double TX;
	double TY;

	double W2 = WIN_WID / 2;
	double H2 = WIN_HEI / 2;

	double W = w / W2;
	double H = h / H2;

	double X = (x - W2) / W2;
	double Y = ((H2 - y) / H2) - H;
	
	if (opengl->index > 1000000000)
	{
		glEnable(GL_TEXTURE_2D);
		LoadTexture(opengl);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		opengl->MáObrázek = true;
	}


	if (oøíznout == NULL)
	{
		TX = 0;
		TY = 0;
		txtureW = 1.0;
		txtureH = 1.0;
	}
	else
	{
		if (oøíznout->left > 1)
			TX = (double)oøíznout->left / opengl->W;
		else
			TX = oøíznout->left;

		if (oøíznout->top > 1)
			TY = (double)oøíznout->top / opengl->H;
		else
			TY = oøíznout->top;

		if (oøíznout->right > 1)
			txtureW = (double)oøíznout->right / opengl->W;
		else
			txtureW = oøíznout->right;

		if (oøíznout->bottom > 1)
			txtureH = (double)oøíznout->bottom / opengl->H;
		else
			txtureH = oøíznout->bottom;
	}

	if (graph->dividerh == 0)
		graph->dividerh = 1.0;

	if (graph->dividerw == 0)
		graph->dividerw = 1.0;
	
	W *= graph->dividerw;
	H *= graph->dividerh;
	glBindTexture(GL_TEXTURE_2D, opengl->index);
	glBegin(GL_QUADS);
	glColor4f(graph->matrix[0][0], graph->matrix[1][1], graph->matrix[2][2], graph->matrix[3][3]);
	glTexCoord2d(TX, TY); glVertex2d(X, Y);
	glTexCoord2d(txtureW + TX, TY); glVertex2d(X + W, Y);
	glTexCoord2d(txtureW + TX, TY + txtureH); glVertex2d(X + W, Y + H);
	glTexCoord2d(TX, TY + txtureH); glVertex2d(X, Y + H);
	glEnd();
}

OPENGL *Chos(int type, int which)
{
	switch (type)
	{
		case 0:
			return &Data.opengl.menu[which];
			break;

		case 1:
			return &Data.opengl.button[which];
			break;

		case 2:
			return &Data.opengl.save[which];
			break;

		case 3:
			return &Data.opengl.font[which];
			break;

		case 4:
			return &Data.opengl.map[which];
			break;
	}
}

void EndGL(UNIVERSAL *access)
{
	SwapBuffers(access->graph.hdc);
}

void GLDrawText(TEXT *text, RECT *rect)
{
	if (rect == NULL)
	{
		rect = new RECT();
		rect->left = 0;
		rect->top = 0;
		rect->right = 0;
		rect->bottom = 0;
	}

	FONTS *font = &Data.font[0];

	//*
	int hranice[100];
	int PoèetHranic = 0;
	
	int cnt = 0;

	double SZ = (double)text->meas.right / (WIN_WID / 2);

	while (cnt < text->text.length())
	{
		double Celkem = 0;
		int checkpoint = 0;
		while (Celkem < SZ && cnt < text->text.length())
		{
			Celkem += (double)((double)text->size/(WIN_WID/2))*font->W[(unsigned char)text->text.at(cnt)];
			if (text->text.at(cnt) == ' ')
				checkpoint = cnt + 1;
			cnt++;
		}

		if (checkpoint == 0 || Celkem < SZ)
			hranice[PoèetHranic] = cnt;
		else
			hranice[PoèetHranic] = checkpoint;
		PoèetHranic++;
	}
	//*/
	if (Data.opengl.font[0].index > 100000000)
	{
		LoadTexture(&Data.opengl.font[0]);
	}

	double W2 = WIN_WID / 2;
	double H2 = WIN_HEI / 2;

	double W = text->size / W2;
	double H = text->size / H2;

	double X = ((rect->left + text->meas.left) - W2) / W2;
	double Y = ((H2 - (rect->top + text->meas.top)) / H2) - H;

	double TW = (double)Data.font[0].image.w / Data.opengl.font[0].W;
	double TH = (double)Data.font[0].image.h / Data.opengl.font[0].H;

	float RS = (float)(unsigned char)text->red / 255;
	float GS = (float)(unsigned char)text->green / 255;
	float BS = (float)(unsigned char)text->blue / 255;

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_2D, Data.opengl.font[0].index);
	glBlendFunc(GL_SRC_COLOR, GL_ONE);
	glBegin(GL_QUADS);

	int index = 0;
	int poslHranice = 0;

	for (double poèetHranic = 0; poèetHranic < PoèetHranic;
	poèetHranic++)
	{
		double Wplus = 0;
//		MessageBox(NULL, convert(Data.opengl.font[0].index).c_str(), "error", MB_OK);

		while (index < hranice[(int)poèetHranic])
		{
			unsigned char ch = text->text.at(index);
			double	TX = (double)((ch % 16) * Data.font[0].image.w) / (double)Data.opengl.font[0].W ,
					TY = (double)( (16 - (ch / 16) - 1) * Data.font[0].image.h) / (double)Data.opengl.font[0].H;
			
			double x = X + Wplus;
			double y = Y - poèetHranic*H;
			double TrW = TW*Data.font[0].W[ch];
			double Wtr = W*Data.font[0].W[ch];

			glColor4f(RS, GS, BS, (float)2.0);
			glTexCoord2d(TX, TY); glVertex2d(x, y);
			glTexCoord2d(TX + TW, TY); glVertex2d(x + W, y);
			glTexCoord2d(TX + TW, TY + TH); glVertex2d(x + W, y + H);
			glTexCoord2d(TX, TY + TH); glVertex2d(x, y + H);
			Wplus += Wtr;

			index++;
		}
		poslHranice = hranice[(int)poèetHranic];
	}
	glEnd();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	font = NULL;
	//*/
}