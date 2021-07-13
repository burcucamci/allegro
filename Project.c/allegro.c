#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char**argv) {

	srand(time(NULL));//random atmak için 
	al_init_primitives_addon();//sekiller için (kare,daire vs)
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	al_init();
	al_install_keyboard();
	al_install_mouse();


	display = al_create_display(800, 800);

	queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 50); // saniyede 10 defa gelecek þekilde ayarladýk 
	al_start_timer(timer);

	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));

	//beyaz olan hareket cubugunda mouse un görünmemesi için 
	al_hide_mouse_cursor(display);



	int x = 0, y = 0;// acýk yesilin koord.
	int syh1x = 0, syh1y = 0, syh2x = 0, syh2y = 0;//siyah kutularýn koordinatlarý
	int dairex = 0, dairey = 0;// sol alt beyaz daire 
	int t1x = 0, t2x = 0, t1y = 0, t2y = 0;//ortadaki turuncu kutu için 
	int kx = 0, ky = 0;//turuncu üstündeki beyaz
	int tdx = 0, tdy = 0;//turuncu yuvarlak
	int bsx = 0, bsy = 0;//büyük siyah top
	int sx = 0, sy = 0;//sarý kutu
	int ssx = 0, ssy = 0;//sari üstündeki siyah 
	int ss2x = 0, ss2y = 0;



	int width = 218;
	int height = 100;

	int hx = width;
	int hy = height;

	int pos_x = width / 2;
	int pos_y = height / 2;




	hx = rand() % 218;
	hy = rand() % 100;

	float angTomouse = atan2(pos_y - hy, pos_x - hx);
	float ballspeed = 4.0;
	angTomouse += (rand() % 80) + 1000;
	float move_x = cos(angTomouse) * ballspeed;
	float move_y = sin(angTomouse) * ballspeed;


	while (1) {
		ALLEGRO_EVENT ev; // herhangi bir event geldigi zaman bu degiþken üzerine alýyoruz 
		al_wait_for_event(queue, &ev);

		al_clear_to_color(al_map_rgb(46, 139, 87));// arka plan rengi

		al_draw_filled_rectangle(x + 300, y + 100, x + 530, y + 700, al_map_rgb(0, 255, 127));

		al_draw_filled_rectangle(syh1x + 700, syh1y + 750, syh1x + 800, syh1y + 700, al_map_rgb(0, 0, 0));

		al_draw_filled_rectangle(syh2x + 100, syh2y + 750, syh2x, syh2y + 700, al_map_rgb(0, 0, 0));

		al_draw_filled_circle(dairex + 30, dairey + 723, 13, al_map_rgb(255, 255, 255));//beyaz top

		al_draw_filled_rectangle(t1x + 380, t1y + 600, t2x + 440, t2y + 640, al_map_rgb(244, 164, 96));

		//al_draw_filled_circle(kx + 410, ky + 620, 9, al_map_rgb(255, 255, 255));// hareket eden beyaz top

		al_draw_filled_circle(tdx + 410, tdy + 200, 20, al_map_rgb(244, 164, 96));


		al_draw_filled_rectangle(sx + 715, sy + 710, sx + 735, sy + 740, al_map_rgb(249, 209, 9));

		al_draw_filled_circle(ssx + 725, ssy + 720, 5, al_map_rgb(0, 0, 0));

		al_draw_filled_rectangle(ss2x + 720, ss2y + 738, ss2x + 730, ss2y + 730, al_map_rgb(0, 0, 0));

		al_draw_filled_circle(bsx + 410, bsy + 200, 15, al_map_rgb(0, 0, 0));

		al_draw_filled_circle(hx + 310, hy + 520, 9, al_map_rgb(255, 255, 255));


		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			true;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			pos_x = ev.mouse.x;
			pos_y = ev.mouse.y;
		}
		al_draw_filled_rectangle(pos_x, pos_y, pos_x + 30, pos_y + 15, al_map_rgb(255, 255, 255));


		hx = hx + move_x;
		hy = hy + move_y;


		if (hx >= width || hx < 0) {

			move_x *= -1;



			if (hy >= height || hy < 0) {

				move_y *= -1;

				if (move_x > 0.3 || move_x < -0.3) {
					if (move_x > 0)
						move_x -= 0.5;

					else if (move_x < 0)
						move_x += 0.5;

				}
				else
					move_x = 0.0;

				if ((move_y < 0.5 && move_y > -0.5) || (move_y > -0.5 && move_y < -0.5))

					move_y = 0;
			}

			if (move_y > 0.0)
				move_y += 0.5;

			else if (move_y < 0.0)
				move_y += 0.7;


			if (move_x > 0)
				move_x -= 0.015;

			else if (move_x < 0)
				move_x += 0.015;
		}




		al_flip_display();

		if (abs(hx - 410) <= 15 && abs(hy - 200) <= 15)
		{


			return 0;

		}

	}


	system("pause");
	al_destroy_display(display);
	al_destroy_event_queue(queue);

	return 0;
}
