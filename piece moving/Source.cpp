#define _CRT_SECURE_NO_WARNINGS
#include<allegro5\allegro5.h>
#include<allegro5\allegro_native_dialog.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5\allegro_image.h>
#include<allegro5\allegro_audio.h>
#include<allegro5\allegro_acodec.h>
#include<cmath>
#include<iostream>
#include<string>
#include"mappy_A5.h"
#include"Collectables.h"
#include <string>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

#define ScreenWidth 1000	//dimensions of the display screen
#define ScreenHeight 700
#define mapHght 4736
#define itemSize 5
using namespace std;

int hrH, hrL, minL, minH, secL, secH ;	  // time variables
int top, bottom, left, right;
int score = 0;

bool dlay = false;

enum menuItems { nGame, lGame, options, credits, Exit }; //enumerations which assist in scrolling through the menue

void Next_Part_Draw(int xx, int yy, int xoff, int yoff, COLLECTABLES *Album[3][5], int &score); //decleration of the function for displaying the coin pictures on the display screen
void Initialize_with_pics(COLLECTABLES *Album[3][5]); //decleration of the function that initializes the COLLECTABLES array
void TimeElapse();
void DrawTitles(int);
int clickLink(int);
void DrawImage();
void Game(); // Game function
void Credit();
string Draw1(int increment);
int main()
{

	const float FPS = 60.0;

	if (!al_init())
	{
		al_show_native_message_box(NULL, "Error", "Error", "Cannot initialize Allegro.", NULL, NULL);
		return -1;
	}

	//Initialization and the setting of the display
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	ALLEGRO_DISPLAY *display = al_create_display(ScreenWidth, ScreenHeight);
	al_set_window_title(display, " The Maze Runner");

	if (!display)	//checks if display was set properly
	{
		al_show_native_message_box(NULL, "Error", "Error", "Cannot create display.", NULL, NULL);
		return -1;
	}

	//Initialization of the keyboard and neccesary addons
	al_init_primitives_addon();
	al_install_keyboard();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();

	if (MapLoad("background2.FMP", 1)) // loads and checks checks if maze was loaded properly
		return -5;

	ALLEGRO_BITMAP *backImage = al_load_bitmap("image1.png"); //manue background image
	ALLEGRO_TIMER *timer = al_create_timer(1.0f / FPS);	//timer synchronizes the button presses and the scrolling through the menue
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue(); //queue for keeping track of the events that occure during the display of the main manue

	//registration of the event sources into the que so that they can be detected when they occure
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));

	bool done = false, draw = true;
	int counter = nGame;

	//al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);

	al_start_timer(timer);	//start time to synchronize the updating of the creen and the button pressed

	while (!done)
	{
		hrH = 0, hrL = 0, minL = 0, minH = 0, secL = 0, secH = 0;

		ALLEGRO_EVENT ev; //this object is sort of responsible for recoarding each event that occurrs int the main manue into the queue
		al_wait_for_event(event_queue, &ev);

/******************************************************************SCROLLING THROUGH THE MAMENU*******************************************************************************/
		//This part is respnsible for scrolling through the menue through the recording of the key press events which also results in the execution of the relevent if statements
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			done = true;

		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			draw = true;
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
			{
				if (counter > nGame)
					counter--;
				break;
			}
			case ALLEGRO_KEY_DOWN:
			{
				if (counter < Exit)
					counter++;
				break;
			}
			case ALLEGRO_KEY_ENTER:
			{
				if (clickLink(counter) == nGame)
				{
					DrawImage();	 //pressing Enter at the new game starts the game

						Game();
					break;
						
				}
				else if (clickLink(counter) == credits)
				{
					Credit();
					break;
				}
				else if (clickLink(counter) == Exit)
					done = true;
				break;
			}
			draw = false;
			}
		}

		if (draw)
		{
			draw = false;
			al_draw_bitmap(backImage, 0, 0, NULL);
			DrawTitles(counter);

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}

	}
	/***********************************************************************************************************************************************************************************************/
	//Destroy the pointers after use to prevent memory leaks
	MapFreeMem();
	al_destroy_display(display);
	al_destroy_bitmap(backImage);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);

	return 0;
}

void DrawTitles(int opt)
{
	std::string Items[itemSize] = { "New Game", "Load Game", "Options", "Credits", "Exit" };

	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_FONT *font = al_load_font("font1.ttf", 30, NULL);
	ALLEGRO_COLOR Blue = al_map_rgb(44, 117, 255);
	ALLEGRO_COLOR White = al_map_rgb(255, 255, 255);


	int y = ScreenHeight / 2.0 - 5 * al_get_font_line_height(font) / 2.0;

	for (int i = 0; i < itemSize; i++)
	{
		int x = ScreenWidth / 2.0 - al_get_text_width(font, Items[i].c_str()) / 2.0;

		if (opt == i)
			al_draw_text(font, White, x, y, NULL, Items[i].c_str());
		else
			al_draw_text(font, Blue, x, y, NULL, Items[i].c_str());
		y += al_get_font_line_height(font) + 10;

	}

	//al_destroy_font(font);
}

int clickLink(int item)
{
	if (item == nGame)
		return nGame;
	else if (item == lGame)
		return lGame;
	else if (item == options)
		return options;
	else if (item == credits)
		return credits;
	else if (item == Exit)
		return Exit;
}

void DrawImage()
{
	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_BITMAP *image2 = al_load_bitmap("image2.png");
	ALLEGRO_FONT *font = al_load_font("font1.ttf", 30, NULL);
	ALLEGRO_COLOR Blue = al_map_rgb(44, 117, 255);
	ALLEGRO_COLOR White = al_map_rgb(255, 255, 255);

	al_draw_bitmap(image2, 0, 0, NULL);

	float x = ScreenWidth / 2 - al_get_text_width(font, "The Maze Runners") / 2;
	float y = ScreenHeight - 2 * al_get_font_line_height(font);

	al_draw_text(font, al_map_rgb(255, 0, 0), x, y, NULL, "The Maze Runners");

	al_flip_display();
}

/*************************************************************************************ACTUAL GAME FUNCTION********************************************************************/
void Game()
{
	
	enum Direction { UP, LEFT, DOWN, RIGHT };
	bool draw = false, active = false;
	float speed = 10;
	int xoff = 0;					 //xoff and yoff can be thought of as the coordinates of the player on the maze and also as the offsets of the maze reletive to the display screen
	int yoff = 384;
	int xx = 0;						 //xx and yy of are the coin picture offsets reletive to the display screen
	int yy = 0;
	const float FPS = 60.0;		 //constant for the timer used for updating the display
	int dir = UP, sourceX = 64, sourceY = 0;

	//Installation and initialization of the keyboard, sound and image, font addons.
	al_install_keyboard();
	al_init_image_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	al_reserve_samples(1);
	//Creation and initialization of the graphics
	ALLEGRO_BITMAP *Trophy = al_load_bitmap("trophy.png");
	ALLEGRO_SAMPLE *soundEffect = al_load_sample("Footsteps.wav");
	ALLEGRO_FONT *font = al_load_font("font1.ttf", 30, NULL);
	ALLEGRO_BITMAP *player = al_load_bitmap("USE.png");

	ALLEGRO_KEYBOARD_STATE keyState; //used to check which key was pressed
	ALLEGRO_EVENT_QUEUE *events = al_create_event_queue(); //created to hold events that occure and to allow them to be executed synchronously
	ALLEGRO_TIMER *timer = al_create_timer(1/FPS);// created to allow for a smooth update of the screen after each event 
	

	ALLEGRO_COLOR grass = al_map_rgb(44, 117, 255);
	BLKSTR *Tile1, *Tile2;
	
	COLLECTABLES *Album[3][5];		//decleration and initialization of the COLLECTABLES array which contains the coin pictures
	Initialize_with_pics(Album);

	//registration of event sources so that they can be detected when they occure
	al_register_event_source(events, al_get_keyboard_event_source());
	al_register_event_source(events, al_get_timer_event_source(timer));
	bool isActive = false; // used as the while condition and allows to game to exit when escape is pressed

	al_start_timer(timer);
	while (!isActive)
	{

		ALLEGRO_EVENT ev;
		al_wait_for_event(events, &ev);
		al_get_keyboard_state(&keyState);

		if ((ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) || (hrL >= 3)) 
		{
			isActive = true;
		}

		else if (ev.type == ALLEGRO_EVENT_TIMER)			//when the timer ticks, the relevent 'if statement' executes
		{
			active = true;
			if (al_key_down(&keyState, ALLEGRO_KEY_UP))			//if key UP is pressed, do the following
			{
				yoff -= speed;				 //offset the map and the displayed coin pictures, opposint to pressed direction
				yy -= speed;
				dir = UP;
				if (yoff < 0)			//if the yoff is negetive, set it to zero so that during the display the dark part of the background will not show
					yoff = 0;



				Tile1 = MapGetBlockInPixels(xoff, yoff);			//get the block where the top left point of the player photo will lie
				Tile2 = MapGetBlockInPixels(xoff + 25, yoff);		 //get the block where the top right point of the player photo will lie

				if (Tile1->tl || Tile2->tl)			//If the top left and/or the top right point of the photo lie on the forbidden block
				{									//undo the above decrementation. This also prevents the coin picture from moving into forbidden region
					yoff = yoff + speed;
					yy = yy + speed;
				}
				al_play_sample(soundEffect, 0.5, 0.0, 2.5, ALLEGRO_PLAYMODE_ONCE, 0);
			}
			else if (al_key_down(&keyState, ALLEGRO_KEY_DOWN))		   // if key DOWN is pressed, do the following:
			{
				yoff += speed;										  //offset the map and the displayed coin pictures, opposint to pressed direction
				yy += speed;
				dir = DOWN;

				if (yoff>mapHght - ScreenHeight)						 //this prevents the dark part at the bottom of the background from showing
					yoff = mapHght - ScreenHeight;

				Tile1 = MapGetBlockInPixels(xoff, yoff + 44);			  //get the block where the bottom left point of the player photo lies
				Tile2 = MapGetBlockInPixels(xoff + 25, yoff + 44);			//get the block where the bottom right point of the player photo lies

				if (Tile1->tl || Tile2->tl)									  //if the bottom left and/or right point of the playert lie on the forbidden block, undo the above incrementations.
				{																  //This also prevents the coin picture from moving into forbidden region
					yoff = yoff - speed;
					yy = yy - speed;
				}
				al_play_sample(soundEffect, 0.5, 0.0, 2.5, ALLEGRO_PLAYMODE_ONCE, 0);   //play sound after each movement
			}
			else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))				 //if key UP is pressed, do the	the follwing:
			{
				xoff -= speed;
				xx -= speed;												 //offset the map and the displayed coin picures , opposite to the direction of the pressed button

				dir = LEFT;
				if (xoff < 0)												//this prevents the dark part at the far left of the map from showing
				{
					xoff = 0;
					xx = 0;
				}

				Tile1 = MapGetBlockInPixels(xoff, yoff);					 //get the block where the top left point of the player photo lies
				Tile2 = MapGetBlockInPixels(xoff, yoff + 44);				  //get the block where the bottom left of the phot lies
				if (Tile1->tl || Tile2->tl)
				{
					xoff = xoff + speed;										  //if the top left and/or bottom right point of the playert lie on the forbidden block, undo the above incrementations.
					xx = xx + speed;												//This also prevents the coin picture from moving into forbidden region
				}

				al_play_sample(soundEffect, 0.5, 0.0, 2.5, ALLEGRO_PLAYMODE_ONCE, 0);
			}
			else if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
			{
				xoff += speed;	//offset the maze and the displayed coins in the direction opposite the pressed button
				xx += speed;
				dir = RIGHT;

				if (xoff == 300)
				{
					//al_show_native_message_box(displays, "WINNER", "MAZE", "YOU SOLVED THE MAZE", NULL, NULL);
					//al_draw_text(font, grass, xf, yf, ALLEGRO_ALIGN_CENTER, "WIN");
				}

				Tile1 = MapGetBlockInPixels(xoff + 25, yoff); //get the block where the top right point of the player photo will lies
				Tile2 = MapGetBlockInPixels(xoff + 25, yoff + 40);   //get the block where the bottom right point of the player photo lies
				if (Tile1->tl || Tile2->tl)
				{
					xoff = xoff - speed;
					xx = xx - speed;
				}
				al_play_sample(soundEffect, 0.5, 0.0, 2.5, ALLEGRO_PLAYMODE_ONCE, 0);

			}
			///else if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
				//isActive == true;
			else
				active = false;

		if (active)
			sourceX += al_get_bitmap_width(player) / 9;
		else
			sourceX = 64;

		if (sourceX >= al_get_bitmap_width(player))
			sourceX = 0;

		sourceY = dir;

		draw = true;

		}

		if (draw)
		{		//updating the maze, player, coin picture position and the time
			if (hrL >= 2)
			{
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_textf(font, grass, ScreenWidth / 2, ScreenHeight / 2, ALLEGRO_ALIGN_CENTER, "Gameover", score);
				al_draw_text(font, grass, ScreenWidth / 2, (ScreenHeight / 2) + 300, ALLEGRO_ALIGN_CENTER, "You Ran out of Time");

			}

			else if (xoff >= 7040)
			{
				//al_show_native_message_box(displays, "WINNER", "MAZE", "YOU SOLVED THE MAZE", NULL, NULL);
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_bitmap(Trophy, 0, 0, NULL);
				al_draw_text(font, grass, ScreenWidth / 2, (ScreenHeight / 2) - 300, ALLEGRO_ALIGN_CENTER, "CONGRATULATIONS YOU HAVE SOLVED THE MAZE");
				if (score >= 200)
				{
					al_draw_textf(font, grass, ScreenWidth / 2, ScreenHeight / 2, ALLEGRO_ALIGN_CENTER, "HIGHSCORE : %i", score);
					al_draw_text(font, grass, ScreenWidth / 2, (ScreenHeight / 2) + 300, ALLEGRO_ALIGN_CENTER, "YOU QUALIFY TO BE A RUNNER");
				}
				else
				{
					al_draw_text(font, grass, ScreenWidth / 2, ScreenHeight / 2, ALLEGRO_ALIGN_CENTER, "YOU STILL NEED TO WORK ON YOUR COLLECTING SKILLS");
					al_draw_textf(font, grass, ScreenWidth / 2, (ScreenHeight / 2) + 300, ALLEGRO_ALIGN_CENTER, "SCORE : %i", score);
				}

			}
			else
			{

				MapDrawBG(xoff - 18, yoff - 20, 0, 0, ScreenWidth, ScreenHeight);

				al_draw_bitmap_region(player, sourceX, dir*al_get_bitmap_height(player) / 4, 64, 64, 0, 0, NULL);
				Next_Part_Draw(xx, yy, xoff, yoff, Album, score);
				al_draw_textf(font, al_map_rgb(255, 0, 0), 400, 30, NULL, "SCORE %i", score);
				al_draw_text(font, al_map_rgb(0, 0, 255), 800, 30, NULL, Draw1(1).c_str());
			}
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

}


//Initializes the COLLECTABLES Album array of pointers with COLLECTABLE instances

void Initialize_with_pics(COLLECTABLES *Album[3][5])
{


	for (int k = 0; k < 3; k++)
	{
		for (int t = 0; t < 5; t++)
		{
			Album[k][t] = new COLLECTABLES(t, k);
		}
	}

}
//Responsible for calling the function PrintPicture of each instance to display that instances array of pictures at the relevent section of background
void Next_Part_Draw(int xx, int yy, int xoff, int yoff, COLLECTABLES *Album[3][5], int &score)
{
	for (int k = 0; k < 3; k++)
	{
		for (int t = 0; t < 5; t++)
		{
			Album[k][t]->PrintPictures(xx, yy, xoff, yoff, score);
			
		}
	}
	
}


string Draw1(int increment)
{
	ALLEGRO_FONT *font = al_load_font("font1.ttf", 30, NULL);
	string timeH[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
		

		if (secL >= 9)
		{
			secL = 0;
			secH++;
		}
		else if (secH >= 6)
		{
			secH = 0;
			minL++;
		}

		if (minL >= 9)
		{
			minL = 0;
			minH++;
		}
		else if (minH >= 6)
		{
			minH = 0;
			hrL++;
		}

		if (hrL >= 2)
		{
			increment = 0;
			secL = 0;
		}

		secL += increment;

		return (timeH[hrH] + timeH[hrL] + ":" + timeH[minH] + timeH[minL] + ":" + timeH[secH] + timeH[secL]);

}	

void Credit()
{

	al_init_font_addon();
	al_init_ttf_addon();


	ALLEGRO_BITMAP *Trophy = al_load_bitmap("trophy.png");
	ALLEGRO_FONT *font = al_load_font("font1.ttf", 30, NULL);
	ALLEGRO_COLOR Blue = al_map_rgb(44, 117, 255);
	ALLEGRO_COLOR White = al_map_rgb(255, 255, 255);


	int y = ScreenHeight / 2.0 - 5 * al_get_font_line_height(font) / 2.0;
	int x = ScreenWidth / 2.0 - al_get_text_width(font,"SCORE %i") / 2.0;
	
	al_draw_bitmap(Trophy, 0, 0, NULL);

	al_draw_textf(font, al_map_rgb(44, 117, 255), ScreenWidth / 2, ScreenHeight / 2, ALLEGRO_ALIGN_CENTER, "MAXIMUM POINTS   %i", 800);
	

	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_rest(3);

}