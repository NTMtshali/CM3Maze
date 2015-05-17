	
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
  //
#define ScreenWidth 1000
#define ScreenHeight 700
#define mapHght 4736
#define itemSize 5
using namespace std;
 
int hrH, hrL, minL, minH, secL, secH ;	  // time variables
bool dlay = false;

int top, bottom, left, right;
enum menuItems { nGame, lGame, options, credits, Exit };
int score=0;
void Next_Part_Draw(int xx, int yy, int xoff, int yoff, COLLECTABLES *Album[3][5], int &score);
void Initialize_with_pics(COLLECTABLES *Album[3][5]);
void TimeElapse();

void DrawTitles(int);
int clickLink(int);
void DrawImage();
void Game();
void Credit();

string Draw1(int increment);
//ALLEGRO_DISPLAY *display = al_create_display(ScreenWidth, ScreenHeight);
int main()
{

	const float FPS = 60.0;

	if (!al_init())
	{
		al_show_native_message_box(NULL, "Error", "Error", "Cannot initialize Allegro.", NULL, NULL);
		return -1;
	}

	al_set_new_display_flags(ALLEGRO_WINDOWED);
	ALLEGRO_DISPLAY *display = al_create_display(ScreenWidth, ScreenHeight);
	al_set_window_title(display, " The Maze Runner");

	if (!display)
	{
		al_show_native_message_box(NULL, "Error", "Error", "Cannot create display.", NULL, NULL);
		return -1;
	}


	al_init_primitives_addon();
	if (MapLoad("background2.FMP", 1))
		return -5;

	al_install_keyboard();
	al_install_mouse();

	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();


	ALLEGRO_BITMAP *backImage = al_load_bitmap("image1.png");
	ALLEGRO_TIMER *timer = al_create_timer(1.0f / FPS);
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	//ALLEGRO_KEYBOARD_STATE keyState;

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));

	bool done = false, draw = true;
	int counter = nGame;

	//al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);

	al_start_timer(timer);

	while (!done)
	{
		hrH = 0, hrL = 0, minL = 0, minH = 0, secL = 0, secH = 0;

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		//al_get_keyboard_state(&keyState);

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
					DrawImage();

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
	//al_rest(2);
	//al_destroy_bitmap(image2);
	//al_destroy_font(font);
}


void Game()
{

	enum Direction { UP, LEFT, DOWN, RIGHT };
	bool draw = false, active = false;
	float speed = 10;
	int xoff = 0;					 //10, 384
	int yoff = 384;
	int xx = 0;
	int yy = 0;
	const float min = 60;
	int dir = UP, sourceX = 64, sourceY = 0;

	al_install_keyboard();
	al_init_image_addon();
	al_install_audio();
	al_init_acodec_addon();
	


	ALLEGRO_BITMAP *Trophy = al_load_bitmap("trophy.png");


	ALLEGRO_SAMPLE *soundEffect = al_load_sample("Footsteps.wav");
	al_reserve_samples(1);

	ALLEGRO_FONT *font = al_load_font("font1.ttf", 30, NULL);
	ALLEGRO_BITMAP *player = al_load_bitmap("USE.png");
	ALLEGRO_BITMAP *player2 = al_load_bitmap("WALL.png");
	//ALLEGRO_DISPLAY *displays = al_create_display(ScreenWidth, ScreenHeight);

	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_KEYBOARD_STATE keyState;
	ALLEGRO_EVENT_QUEUE *events = al_create_event_queue();
	ALLEGRO_TIMER *timer = al_create_timer(1/60.0);
	

	ALLEGRO_COLOR grass = al_map_rgb(44, 117, 255);

	BLKSTR *Tile1, *Tile2;
	COLLECTABLES *Album[3][5];

	al_register_event_source(events, al_get_keyboard_event_source());
	al_register_event_source(events, al_get_timer_event_source(timer));



	bool isActive = false;



	Initialize_with_pics(Album);
	al_start_timer(timer);

	while (!isActive)
	{

		ALLEGRO_EVENT ev;
		al_wait_for_event(events, &ev);
		al_get_keyboard_state(&keyState);

		if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE || hrL >= 1) 
		{
			isActive = true;



			/*al_destroy_timer(timer);
			al_destroy_bitmap(player);
			al_destroy_sample(soundEffect);
			al_destroy_event_queue(events);*/


		}

		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			active = true;
			if (al_key_down(&keyState, ALLEGRO_KEY_UP))
			{
				yoff -= speed;
				yy -= speed;
				dir = UP;
				if (yoff < 0)
					yoff = 0;



				Tile1 = MapGetBlockInPixels(xoff, yoff);
				Tile2 = MapGetBlockInPixels(xoff + 25, yoff);

				if (Tile1->tl || Tile2->tl)
				{
					yoff = yoff + speed;
					yy = yy + speed;
				}
				al_play_sample(soundEffect, 0.5, 0.0, 2.5, ALLEGRO_PLAYMODE_ONCE, 0);
			}
			else if (al_key_down(&keyState, ALLEGRO_KEY_DOWN))
			{
				yoff += speed;
				yy += speed;
				dir = DOWN;

				if (yoff>mapHght - ScreenHeight)
					yoff = mapHght - ScreenHeight;

				Tile1 = MapGetBlockInPixels(xoff, yoff + 44);
				Tile2 = MapGetBlockInPixels(xoff + 25, yoff + 44);
				if (Tile1->tl || Tile2->tl)
				{
					yoff = yoff - speed;
					yy = yy - speed;
				}
				al_play_sample(soundEffect, 0.5, 0.0, 2.5, ALLEGRO_PLAYMODE_ONCE, 0);
			}
			else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
			{
				xoff -= speed;
				xx -= speed;

				dir = LEFT;
				if (xoff < 0)
				{
					xoff = 0;
					xx = 0;
				}

				Tile1 = MapGetBlockInPixels(xoff, yoff);
				Tile2 = MapGetBlockInPixels(xoff, yoff + 44);
				if (Tile1->tl || Tile2->tl)
				{
					xoff = xoff + speed;
					xx = xx + speed;
				}

				al_play_sample(soundEffect, 0.5, 0.0, 2.5, ALLEGRO_PLAYMODE_ONCE, 0);
			}
			else if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
			{
				xoff += speed;
				xx += speed;
				dir = RIGHT;

				if (xoff == 300)
				{
					//al_show_native_message_box(displays, "WINNER", "MAZE", "YOU SOLVED THE MAZE", NULL, NULL);
					//al_draw_text(font, grass, xf, yf, ALLEGRO_ALIGN_CENTER, "WIN");
				}

				Tile1 = MapGetBlockInPixels(xoff + 25, yoff);
				Tile2 = MapGetBlockInPixels(xoff + 25, yoff + 40);
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
		{

			if (xoff >= 7040)
			{
				//al_show_native_message_box(displays, "WINNER", "MAZE", "YOU SOLVED THE MAZE", NULL, NULL);
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_bitmap(Trophy, 0, 0, NULL);
				al_draw_text(font, grass, ScreenWidth / 2, (ScreenHeight / 2) - 300, ALLEGRO_ALIGN_CENTER, "CONGRATULATIONS YOU HAVE SOLVED THE MAZE");
				int x = 900;
				if (score >= 800)
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