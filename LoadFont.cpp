#include "Load.h"

void LoadFont(LOAD *load)
{
	string word;
	int count = 0;

	while (load->ifile.good() && count < FNT_CNT)
	{
		load->ifile >> word;

		if (word == "font:")
		{
			load->ifile >> word;
			Data.font[count].name = word;
			load->ifile >> word;
			Data.font[count].image.address = word;
			load->ifile >> word;
			Data.font[count].image.cols = atoi(word.c_str());
			load->ifile >> word;
			Data.font[count].image.rows = atoi(word.c_str());
			load->ifile >> word;
			Data.font[count].image.w = atoi(word.c_str());
			load->ifile >> word;
			Data.font[count].image.h = atoi(word.c_str());
			Data.font[count].image.index = CreateOpenGLPIC(3, &Data.font[count].image);
			Data.font[count].image.chos = 3;
			count++;
		}

		if (word == "VP:")
		{
			count--;
			load->ifile >> word;
			short val = atoi(word.c_str());
			load->ifile >> word;
			if (word == "-")
			{
				load->ifile >> word;
				short val2 = atoi(word.c_str());
				load->ifile >> word;
				double val3 = GetRealVal(word,Data.font[count].image.w);
				for (; val <= val2; val++)
					Data.font[count].W[val] = val3;
			}
			else if ( word == "=")
			{
				double Val = (double)val / Data.font[count].image.w;
				load->ifile >> word;
				while (word != ";")
				{
					load->ifile >> word;
					Data.font[count].W[atoi(word.c_str())] = Val;
				}
			}
			else
				Data.font[count].W[val] = GetRealVal(word.c_str(),Data.font[count].image.w);
			count++;
		}
	}
}

