#include <stdio.h>
#include <iostream>
#include <ctime>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5\allegro_primitives.h>

using namespace std;

const float FPS = 60;
const int SCREEN_W = 800;
const int SCREEN_H = 800;
const int BOUNCER_SIZE = 32;
enum {RED, GREEN, YELLOW, BLUE};

int main(int argc, char** argv)
{
	srand(time(NULL));
	int pattern[4] = { 0, 0, 0, 0 };
	int order[4] = { 0, 0, 0, 0 };
	int num = 0;
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;
	ALLEGRO_BITMAP* bouncer = NULL;
	int xpos = SCREEN_W / 2;
	int ypos = SCREEN_H / 2;
	int counter = 0;
	int clicker = -1;
	bool drawCircle = false;
	bool redraw = true;
	bool click = false;
	bool same = true;
	

	for (int i = 0; i < 4; i++) {
		pattern[i] = rand() % 4;
		cout << pattern[i] << endl;
	}
	

	al_init();
	al_install_mouse();
	al_init_primitives_addon();
	timer = al_create_timer(1.0 / FPS);
	display = al_create_display(SCREEN_W, SCREEN_H);


	al_set_target_bitmap(al_get_backbuffer(display));
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_start_timer(timer);

	while (1)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			redraw = true;
			if (clicker == 4) {
				clicker = -1;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
			ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {

			xpos = ev.mouse.x;
			ypos = ev.mouse.y;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			drawCircle = true;
			clicker++;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			drawCircle = false;
		}

		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;


			if(counter < 1){
			
				for (int i = 0; i < 4; i++) {

					if (pattern[i] == RED) {
						al_draw_filled_rectangle(0, 0, 400, 400, al_map_rgb(250, 100, 100));
						al_flip_display();
						al_rest(.5);
						al_clear_to_color(al_map_rgb(0, 0, 0));
						al_flip_display();
						al_rest(.1);
					}
					if (pattern[i] == GREEN) {
						al_draw_filled_rectangle(400, 400, 0, 800, al_map_rgb(100, 250, 100));
						al_flip_display();
						al_rest(.5);
						al_clear_to_color(al_map_rgb(0, 0, 0));
						al_flip_display();
						al_rest(.1);
					}
					if (pattern[i] == YELLOW) {
						al_draw_filled_rectangle(400, 400, 800, 0, al_map_rgb(100, 100, 250));
						al_flip_display();
						al_rest(.5);
						al_clear_to_color(al_map_rgb(0, 0, 0));
						al_flip_display();
						al_rest(.1);
					}
					if (pattern[i] == BLUE) {
						al_draw_filled_rectangle(400, 400, 800, 800, al_map_rgb(250, 250, 100));
						al_flip_display();
						al_rest(.5);
						al_clear_to_color(al_map_rgb(0, 0, 0));
						al_flip_display();
						al_rest(.1);
					}

					if (i == 3) {
						break;
					}
				}
				counter++;
				//cout << "counter " << counter << endl;

			}

			

			al_clear_to_color(al_map_rgb(0, 0, 0));
			if (drawCircle == true && xpos < 400 && ypos < 400) {
				al_draw_filled_rectangle(0, 0, 400, 400, al_map_rgb(250, 100, 100));
				click = true;
			}
			else if (drawCircle == true && xpos < 400 && ypos > 400) {
			al_draw_filled_rectangle(400, 400, 0, 800, al_map_rgb(100, 250, 100));
			click = true;
			}
			else if (drawCircle == true && xpos > 400 && ypos < 400) {
				al_draw_filled_rectangle(400, 400, 800, 0, al_map_rgb(100, 100, 250));
				click = true;
			}
			else if (drawCircle == true && xpos > 400 && ypos > 400) {
				al_draw_filled_rectangle(400, 400, 800, 800, al_map_rgb(250, 250, 100));
				click = true;
			}
			al_flip_display();
			if (!same) {
				break;
			}
		}
	}

	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}
