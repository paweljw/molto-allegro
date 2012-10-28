#include <vector>
#include <string>
#include <allegro5/allegro.h>
#include <iostream>

#include "../src/molto-allegro.h"

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

	Menu *m = new Menu(display);

	m->addElem(string("Test"));
	m->addElem(string("Testowy 2"));	
	m->addElem(string("Kolejny"));
	m->addElem(string("Czy one rosną?"));

	m->draw(display);

	al_flip_display();

	while(true)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(q, &ev);

		if(ev.type == ALLEGRO_EVENT_KEY_UP)
			if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				break;

		if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) 
		{
      		float x = ev.mouse.x;
			float y = ev.mouse.y;

			m->click(x, y);
		}
	}

	return 0;
}
