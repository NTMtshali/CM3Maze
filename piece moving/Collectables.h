#ifndef	COLLECTABLES_H
#define COLLECTABLES_H

#include<allegro5/allegro5.h>
#include<allegro5\allegro_image.h>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5\allegro_font.h>
#include<string>
#include"mappy_A5.h"
class COLLECTABLES
{
private:
	ALLEGRO_BITMAP *image[9][9];
	bool ImageState[9][9];
	bool keep_printed = false;
	int Lower_x;
	int Higher_x;
	int Lower_y;
	int Higher_y;

public:
	COLLECTABLES(int, int);
	~COLLECTABLES();
	void setStatesAndImages_Array();
	ALLEGRO_BITMAP *GetImage(int, int);
	bool GetImageState(int, int);
	void modify_ImageState(int, int);
	void modify_keep_printed();
	bool Get_keep_printed_state();
	void PrintPictures(int, int, int, int, int &);
	bool Collision(int, int, int &, int &, int &);
	void Set_x_Bounds(int);
	void Set_y_Bounds(int);
	bool CheckIfWithinBounds(int, int);
	void Draw1();
};

#endif
