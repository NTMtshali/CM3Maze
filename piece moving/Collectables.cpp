#include "Collectables.h"
#include<string>
#include <iostream>
//COLLECTABLES member definitions
using namespace std;

COLLECTABLES::COLLECTABLES(int i, int j) //Constructer initializes the data members
{
	setStatesAndImages_Array();
	Set_x_Bounds(i);
	Set_y_Bounds(j);
}

void COLLECTABLES::setStatesAndImages_Array() // initializes the ImageStates array and the image array 
{
	for (int k = 0; k < 9; k++)
	{
		for (int t = 0; t < 9; t++)
		{
			image[k][t] = al_load_bitmap("Coin.bmp");
			al_convert_mask_to_alpha(image[k][t], al_map_rgb(255, 255, 255));
			ImageState[k][t] = true;
		}
	}
}

void COLLECTABLES::Set_x_Bounds(int i) // sets the x bounds for displaying the coin pictures at a certain region of the maze.
{
	Lower_x = 1280 * i;
	Higher_x = 1280 * (i + 1);
}
void COLLECTABLES::Set_y_Bounds(int i)	// sets the x bounds for displaying the coin pictures at a certain region of the maze.
{
	Lower_y = 1280 * (i);
	Higher_y = 1280 * (i + 1);
}
ALLEGRO_BITMAP *COLLECTABLES::GetImage(int j, int i) // returns a coin image from the Image array
{
	return image[j][i];
}

bool COLLECTABLES::GetImageState(int j, int i) //returns the image state of an image from that ImageState array at a position corresponding to that in the image array
{
	return ImageState[j][i];
}

void COLLECTABLES::modify_ImageState(int j, int i)// Assists during collision by changing the state of an image in the Image array so that it won't be displayed after being captured
{
	ImageState[j][i] = false;
}
bool COLLECTABLES::Get_keep_printed_state() // returns the state of the keep_printed to check whether to keep an array of images printed or not
{
	return keep_printed;
}
void COLLECTABLES::modify_keep_printed() //changes keep printed. Assists in keeping the Image array pictures on the display after being printed once
{
	keep_printed = true;
}

bool COLLECTABLES::CheckIfWithinBounds(int xoff, int yoff) //checks whether the maze has offset enough for display of the image array
{
	if ((Lower_x <= xoff && xoff <= Higher_x) && (Lower_y <= yoff && yoff <= Higher_y))
	{
		return true;
	}
	else
		return false;
}

void COLLECTABLES::PrintPictures(int xx, int yy, int xoff, int yoff, int &score)// Handles the display of pictures and partially handles collisions
{
	if (CheckIfWithinBounds(xoff, yoff) || this->Get_keep_printed_state()) //if not within bounds or if image array hasn't been displayed atleast  onec, do nothing.
	{
		int i = 0, j = 0; // assist in the iteration through the ImageState and Image array.
		int px = 128;
		for (j; j < 9; j++)
		{
			for (i; i < 9; i++)
			{
				while (Collision((Lower_x + px*(i + 1) - xx), Lower_y + px*j - yy + 20, i, j, score)) //while the picture has not been captured....
				{

				}
				BLKSTR *Checkblock = MapGetBlockInPixels(Lower_x + px*(i + 1), Lower_y + 384 + px*j); //....get the maze block where it will be displayed.

				if (!Checkblock->tl)	//If this maze block is forbidden, don't display the block. Look for another image to display at non-forbidden block
				{

					if (i < 9 && this->GetImageState(j, i)) //Provided the maze block is not forbidden, if the block is already captured(ImageState is false), don't display the block.
					{									//Collision might increment i to be >9, so this prevents the printing of a picture thats out of the array bounds

						al_draw_bitmap(this->GetImage(j, i), Lower_x + px*(i + 1) - xx + 18, Lower_y + px*j - yy + 20, 0);

					}
				}
			}
			i = 0;
		}
		this->modify_keep_printed(); //since the images array has been displayed once, keep it on the maze.
	}
}

bool COLLECTABLES::Collision(int coin_x, int coin_y, int &i, int &j, int &score) // Takes care of collisions between the picture and the player
{
	if ((0 <= coin_x) && (coin_x <= 65) && (-20 <= coin_y) && (coin_y <= 70)) //if the picture is in the player region.....
	{

		if (i < 9)
		{
			if (this->GetImageState(j, i))
			{
				score++;			//.....mark it as a capture....
			}
			this->modify_ImageState(j, i); //..and change the image state of this image so that it will not be displaye again
			i++;
			return true;
		}
	}
	else if ((-30 <= coin_x) && (coin_x <= 0) && (0 <= coin_y) && (coin_y <= 70)) //Works the same way as the previous 'if statement'
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