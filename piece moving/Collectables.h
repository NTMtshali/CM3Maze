#ifndef	COLLECTABLES_H
#define COLLECTABLES_H

#include<allegro5/allegro5.h>
#include<allegro5\allegro_image.h>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5\allegro_font.h>
#include<string>
#include"mappy_A5.h"

/*COLLECTABLES ARRAY sekeleton*/

class COLLECTABLES
{
private:
	ALLEGRO_BITMAP *image[9][9]; //Store coin images
	bool ImageState[9][9];	  //Store Boolean state for each image
	bool keep_printed = false;

	//bounds to decide where on the maze the the coin pictures are to be
	int Lower_x;
	int Higher_x;
	int Lower_y;
	int Higher_y;

public:
	COLLECTABLES(int, int);
	~COLLECTABLES();
	void setStatesAndImages_Array(); //Initializes the image array and the bool array.
	ALLEGRO_BITMAP *GetImage(int, int);		 //returns an image from the image array
	bool GetImageState(int, int);			 //returns the the state of an image from the ImageState array
	void modify_ImageState(int, int);		   //changes the state of the image in the ImageState array during collision
	void modify_keep_printed();				   //allows for the images array to remain printed after it has been printed once
	bool Get_keep_printed_state();		//returns the state of keep_printed
	void PrintPictures(int, int, int, int, int &);
	bool Collision(int, int, int &, int &, int &);//  Checks for collisions, and updates the score and the ImageStates array for the coin picture that collided with the player
	void Set_x_Bounds(int);			//sets the x bounds to decide in which section of the map to print the array of the coin pictures
	void Set_y_Bounds(int);			 //sets the y bounds to decide in which section of the map to print the array of the coin pictures
	bool CheckIfWithinBounds(int, int);	  //checks if the offsets of the map are within the bounds for the printing of the relevent array of pictures
	void Draw1(); // updates the time
};

#endif
