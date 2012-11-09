#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "ma/molto-allegro.h"
#include "ma/allegro5_renderer.h"

using namespace std;

#define PI 3.14159265;

const int SCREEN_W = 640;
const int SCREEN_H = 480;

const int MENU_H = 25;

int TRYB = 0;
ALLEGRO_FONT *font;

struct punkt3d
{
	float x;
	float y;
	float z;
};

struct punkt2d
{
	float x;
	float y;
};

int wyjscie(void* a)
{
	exit(EXIT_SUCCESS);
}

int setTryb(void* a)
{
	int *w = (int*)a;
	TRYB = *w;
	return 0;
}

punkt2d rzutTales(punkt3d p)
{
	float focus = 200;
	float corx = 320;
	float cory = 240;

	punkt2d p1;

	float z = (p.z/(float)0x100) + 1.0f;

	cout << "Point: " << p.x + 1.0f << ", " << p.y + 1.0f << endl;

	p1.x = (SCREEN_W / 2.0f) * ((p.x / z) + 1);
	p1.y = MENU_H + ((SCREEN_H - MENU_H) / 2.0f) * ((p.y / z) + 1);

	return p1;
}

void writeStatus(string s)
{
	al_draw_filled_rectangle(0, 470, 640, 480, al_map_rgb(30,30,30));
	al_draw_text(font, al_map_rgb(255,255,255), 640, 470, ALLEGRO_ALIGN_RIGHT, s.c_str());
}


int funkcja1()
{
	punkt2d p1, p2, p3, p4;

	p1.x = 50;
	p1.y = 50;
	
	p2.x = 600;
	p2.y = 400;

	p3.x = 600;
	p3.y = 50;

	p4.x = 50;
	p4.y = 400;

	al_draw_line(p1.x, p1.y, p2.x, p2.y, al_map_rgb(0, 255, 0), 1);
	al_draw_line(p3.x, p3.y, p4.x, p4.y, al_map_rgb(0, 255, 0), 1);
	al_flip_display();

	float delta = (p2.x-p1.x)*(p3.y-p4.y)-(p3.x-p4.x)*(p2.y-p1.y);
	
	if(delta != 0)
	{
		float deltaMi = (p3.x - p1.x)*(p3.y-p4.y)-(p3.x-p4.x)*(p3.y-p1.y);
		float mi = deltaMi / delta;

		float x = (1-mi)*p1.x + mi*p2.x;
		float y = (1-mi)*p1.y + mi*p2.y;

		char buf[256];
		sprintf(buf, "Cross point: %.1f x %.1f", x, y);
		writeStatus((string)buf);
	}
	return 0;
}

int funkcja2()
{
	punkt2d p1, p2, p3, p4;

	p1.x = 50;
	p1.y = 50;
	
	p2.x = 600;
	p2.y = 400;

	p3.x = 600;
	p3.y = 50;

	p4.x = 50;
	p4.y = 400;

	al_draw_line(p1.x, p1.y, p2.x, p2.y, al_map_rgb(0, 255, 0), 1);
	al_draw_line(p3.x, p3.y, p4.x, p4.y, al_map_rgb(0, 255, 0), 1);
	al_flip_display();

	float delta = (p2.x-p1.x)*(p3.y-p4.y)-(p3.x-p4.x)*(p2.y-p1.y);
	
	if(delta != 0)
	{
		float deltaMi = (p3.x - p1.x)*(p3.y-p4.y)-(p3.x-p4.x)*(p3.y-p1.y);
		float mi = deltaMi / delta;

		float x = (1-mi)*p1.x + mi*p2.x;
		float y = (1-mi)*p1.y + mi*p2.y;

		cout << x << "x" << y << endl;

		// dlugosc a, b, c
		float a1 = p1.x-x;
		float a2 = p1.y-y;

		float a = sqrt(a1*a1+a2*a2);

		float b1 = p3.x-x;
		float b2 = p3.y-y;

		float b = sqrt(b1*b1+b2*b2);

		float c1 = p1.x-p3.x;
		float c2 = p1.y-p3.y;

		float c = sqrt(c1*c1+c2*c2);

		float alfa = atan( (( -(c*c) + a*a + b*b ) / (2*a*b)) );
		alfa *= 180/PI;

		if(alfa < 0) alfa = -1*alfa + 90;

		char buf[256];
		sprintf(buf, "Triangle %.1f, %.1f, %.1f : alpha %.1f", a, b, c, alfa);

		writeStatus((string)buf);

	}
}

void funkcja3()
{
	punkt3d p1, p2, p3, p4;

	p1.x = -0.5;
	p1.y = -0.5;
	p1.z = 100;

	p2.x = 0.5;
	p2.y = -0.5;
	p2.z = 0;

	p3.x = 0.5;
	p3.y = 0.5;
	p3.z = 0;

	p4.x = -0.5;
	p4.y = 0.5;
	p4.z = 100;

	// punkty linii
	punkt3d pl1, pl2;

	pl1.x = -0.5f; pl1.y = 0.5f; pl1.z = 0.0f;
	pl2.x = 1.0; pl2.y = -1.0; pl2.z = 150;

	al_clear_to_color(al_map_rgb(0,0,0));

	punkt2d p12, p22, p32, p42;

	p12 = rzutTales(p1);
	p22 = rzutTales(p2);
	p32 = rzutTales(p3);
	p42 = rzutTales(p4);

	al_draw_line(p12.x, p12.y, p22.x, p22.y, al_map_rgb(0, 255, 0), 1);
	al_draw_line(p22.x, p22.y, p32.x, p32.y, al_map_rgb(0, 255, 0), 1);
	al_draw_line(p32.x, p32.y, p42.x, p42.y, al_map_rgb(0, 255, 0), 1);
	al_draw_line(p42.x, p42.y, p12.x, p12.y, al_map_rgb(0, 255, 0), 1);

	punkt2d pl12, pl22;

	pl12 = rzutTales(pl1);
	pl22 = rzutTales(pl2);

	cout << pl12.x << "x" << pl12.y << ", " << pl22.x << "x" << pl22.y << endl;

	al_draw_line(pl12.x, pl12.y, pl22.x, pl22.y, al_map_rgb(255, 0, 0), 1);

	al_flip_display();
}

int funkcja4()
{
	// where blue = 00

	int Y_OFF = 188;
	int X_OFF = 64;

	for(int i=0;i<128;i++) // x
		for(int j=0;j<128;j++)
		{
			al_draw_pixel(X_OFF + i, Y_OFF + j, al_map_rgb(0x0, i*2, j*2));
		}

	X_OFF += 128;

	for(int i=0;i<128;i++) // x
		for(int j=0;j<128;j++)
		{
			al_draw_pixel(X_OFF + i, Y_OFF + j, al_map_rgb(i*2, 255, j*2));
		}

	X_OFF += 128;

	for(int i=0;i<128;i++) // x
		for(int j=0;j<128;j++)
		{
			al_draw_pixel(X_OFF + i, Y_OFF + j, al_map_rgb(255, (255 - i*2), j*2));
		}

	Y_OFF -= 128;

	for(int i=0;i<128;i++) // x
		for(int j=0;j<128;j++)
		{
			al_draw_pixel(X_OFF + i, Y_OFF + j, al_map_rgb(j*2, (255 - i*2), 0x0));
		}

	Y_OFF += 0x100;


	for(int i=0;i<128;i++) // x
		for(int j=0;j<128;j++)
		{
			al_draw_pixel(X_OFF + i, Y_OFF + j, al_map_rgb((255 - j*2), (255 - i*2), 255));
		}


	Y_OFF -= 128;

	X_OFF += 128;

	for(int i=0;i<128;i++) // x
		for(int j=0;j<128;j++)
		{
			al_draw_pixel(X_OFF + i, Y_OFF + j, al_map_rgb((255 - i*2), 0, j*2));
		}

	return 0;
}



using namespace std;

int main()
{
	al_init();
	
	ALLEGRO_DISPLAY* display = al_create_display(640, 480);
	ALLEGRO_EVENT_QUEUE *q;

	q = al_create_event_queue();

	al_install_keyboard();
	al_register_event_source(q, al_get_keyboard_event_source());

	al_install_mouse();
	al_register_event_source(q, al_get_mouse_event_source());

	al_init_primitives_addon();
	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon();// initialize the ttf (True Type Font) addon

    font = al_load_ttf_font("dvs.ttf",10,0 );

	Allegro5_Renderer *renderer = new Allegro5_Renderer(display);

	Menu *m = new Menu(renderer);

	m->addElem(string("Obliczenia"));
	m->addElem(string("Kolory"));

	int lTryb1 = 1, lTryb2 = 2, lTryb3 = 3, lTryb4 = 4;

	m->element("Obliczenia")->addElem("Punkt przecięcia", setTryb, (void*)&lTryb1);
	m->element("Obliczenia")->addElem("Kąt", setTryb, (void*)&lTryb2);
	m->element("Obliczenia")->addElem("Prosta i płaszczyzna", setTryb, (void*)&lTryb3);

	m->element("Kolory")->addElem("Schemat kolorów RGB", setTryb, (void*)&lTryb4);

	m->element("Obliczenia")->addElem("Koniec", wyjscie, (void*)NULL);

	m->draw();

	al_flip_display();

	while(true)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(q, &ev);

		al_set_target_bitmap(al_get_backbuffer(display));
		


		if(ev.type == ALLEGRO_EVENT_KEY_UP)
			if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				break;

		if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) 
		{
      		float x = ev.mouse.x;
			float y = ev.mouse.y;

			if(m->click(x, y))
			{
				al_clear_to_color(al_map_rgb(0,0,0));

				switch(TRYB)
				{
					case 1: funkcja1(); break;
					case 2: funkcja2(); break;
					case 3: funkcja3(); break;
					case 4: funkcja4(); break;
				}

				m->draw();
			} else {
				if(TRYB == 4)
				{
					
					
					ALLEGRO_COLOR c;
					c = al_get_pixel(al_get_target_bitmap(), x, y);
					float r, g, b;
					al_unmap_rgb_f(c, &r, &g, &b);

					r *= 256; g *= 256; b *= 256;
					char buf[256];
			
					sprintf(buf, "Color at click: %.0f,%.0f,%.0f", r, g, b);
					writeStatus((string)buf);
				}
			}
					
		}


		al_flip_display();
	}

	return 0;
}
