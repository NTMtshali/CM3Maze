#include "Collectables.h"
#include<string>
#include <iostream>

using namespace std;

COLLECTABLES::COLLECTABLES(int i, int j)
{
	setStatesAndImages_Array();
	Set_x_Bounds(i);
	Set_y_Bounds(j);
}

void COLLECTABLES::setStatesAndImages_Array()
{
	for (int k = 0; k < 9; k++)
	{
		for (int t = 0; t < 9; t++)
		{
			image[k][t] = al_load_bitmap("Coin.bmp");
			al_convert_mask_to_alpha(image[k][t],al_map_rgb(255, 255, 255));
			ImageState[k][t] = true;
		}
	}
}

void COLLECTABLES::Set_x_Bounds(int i)
{
	Lower_x = 1280 * i;
	Higher_x = 1280 * (i + 1);
}
void COLLECTABLES::Set_y_Bounds(int i)
{
	Lower_y = 1280 * (i);
	Higher_y = 1280 * (i + 1);
}
ALLEGRO_BITMAP *COLLECTABLES::GetImage(int j, int i)
{
	return image[j][i];
}

bool COLLECTABLES::GetImageState(int j, int i)
{
	return ImageState[j][i];
}

void COLLECTABLES::modify_ImageState(int j, int i)
{
	ImageState[j][i] = false;
}
bool COLLECTABLES::Get_keep_printed_state()
{
	return keep_printed;
}
void COLLECTABLES::modify_keep_printed()
{
	keep_printed = true;
}

bool COLLECTABLES::CheckIfWithinBounds(int xoff, int yoff)
{
	if ((Lower_x <= xoff && xoff <= Higher_x) && (Lower_y <= yoff && yoff <= Higher_y))
	{
		return true;
	}
	else
		return false;
}

void COLLECTABLES::PrintPictures(int xx, int yy, int xoff, int yoff, int &score)
{
	if (CheckIfWithinBounds(xoff, yoff) || this->Get_keep_printed_state())
	{
		int i = 0, j = 0;
		int px = 128;
		for (j; j < 9; j++)
		{
			for (i; i < 9; i++)
			{
				while (Collision((Lower_x + px*(i + 1) - xx), Lower_y + px*j - yy + 20, i, j, score))
				{
				
				}
				BLKSTR *Checkblock = MapGetBlockInPixels(Lower_x + px*(i + 1), Lower_y + 384 + px*j);

				if (!Checkblock->tl)
				{

					if ((i < 9) && this->GetImageState(j, i))
					{
						al_draw_bitmap(this->GetImage(j, i), Lower_x + px*(i + 1) - xx + 18, Lower_y + px*j - yy + 20, 0);

					}
				}
			}
			i = 0;
		}
		this->modify_keep_printed();
	}
}

bool COLLECTABLES::Collision(int coin_x, int coin_y, int &i, int &j,int &score)
{
	if ((0 <= coin_x) && (coin_x <= 65) && (0 <= coin_y) && (coin_y <= 70))
	{

		if (i < 9)
		{
			if (this->GetImageState(j, i))
			{
				score++;
			}
			this->modify_ImageState(j, i);
			i++;
			return true;
		}
	}
	else if ((-30 <= coin_x) && (coin_x <= 0) && (0 <= coin_y) && (coin_y <= 70))
	{

		if (i < 9)
		{
			if (this->GetImageState(j, i))
			{
				score++;
			}
			this->modify_ImageState(j, i);
			i++;
			return true;
		}
	}
	return false;
}

void COLLECTABLES::Draw1()
{	
	ALLEGRO_DISPLAY *display = al_create_display(1000, 700);
	ALLEGRO_FONT *font = al_load_font("font1.ttf", 30, NULL);
	string timeL[10] = { "00", "01", "02", "03", "04", "05", "06", "07", "08", "09" };
	string timeH[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

	int time = 0, minL = 2, minH = 0, secL = 9, secH = 5;

	while (minL >= 0)
	{
		string TIME, Min, Sec;

		if (secL == 0)
		{
			secL = 9;
			secH--;
		}

		if (secH == 0)
		{
			secH = 5;
			secL = 9;
			minL--;
		}

		else
		{
			secL--;
		}

		TIME = timeH[minH] + timeH[minL] + ":" + timeH[secH] + timeH[secL];

		al_rest(0.5);


		al_draw_text(font, al_map_rgb(255, 0, 0), 800, 50, NULL, TIME.c_str());

	}
}