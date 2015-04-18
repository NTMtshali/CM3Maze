#include<allegro5/allegro5.h>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_primitives.h>
#include<iostream>

#define screanWidth 1366
#define screenHieght 768

int main()
{
	if (!al_init())
	{
		al_show_native_message_box(NULL, NULL, NULL, "ERROR IN ALLEGRO 5", NULL, NULL);
		return -1;
	}
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	ALLEGRO_DISPLAY *display = al_create_display(screanWidth, screenHieght);
	al_set_window_position(display, 200, 100);
	al_set_window_title(display, "The MAZE");

	if (!display)
	{
		al_show_native_message_box(display, "The MAZE", "ERROR", "The maze game could not start", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	
	al_init_primitives_addon();
	al_install_keyboard();

	ALLEGRO_COLOR something = al_map_rgb(60, 120, 208);
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	bool done = false;
	int x = 10, y = 10;
	int speed = 5;
	// int state = NULL;

	while (!done)
	{
		ALLEGRO_EVENT buttonPress;
		al_wait_for_event(event_queue, &buttonPress);

		if (buttonPress.type = ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (buttonPress.keyboard.keycode)
			{
			case ALLEGRO_KEY_DOWN:
				y += speed;
				break;
			case ALLEGRO_KEY_UP:
				y -= speed;
				break;
			case ALLEGRO_KEY_RIGHT:
				x += speed;
				break;
			case ALLEGRO_KEY_LEFT:
				x -= speed;
				break;
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}
		al_draw_circle(x, y,10, something, 2.0);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	return 0;
}