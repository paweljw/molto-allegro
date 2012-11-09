#include <vector>
#include <string>
#include <allegro5/allegro.h>
#include <iostream>

#include "../src/molto-allegro.h"

int dummy(void* arg)
{
	int *wejscie = (int*)(arg);

	cout << "Callback called; you weren't home." << *wejscie << endl;
	*(wejscie) = 11;
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

	Menu *m = new Menu(display);

	m->addElem(string("Test"));
	m->addElem(string("Test 2"));	
	m->addElem(string("Test 3"));

	int param;
	param = 10;

	m->element("Test")->addElem("Testowa opcja", dummy, (void*)&param);



	m->element("Test")->addElem("Testowa opcja 1", dummy, (void*)&param);
	m->element("Test")->addElem("Testowa opcja 2", dummy, (void*)&param);
	m->element("Test")->addElem("Testowa opcja 3", dummy, (void*)&param);
	m->element("Test")->addElem("Testowa opcja 4", dummy, (void*)&param);

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

			al_set_target_bitmap(al_get_backbuffer(display));
			al_clear_to_color(al_map_rgb(0,0,0));

			m->click(x, y);
			m->draw(display);

			al_flip_display();
			
		}
	}

	return 0;
}
