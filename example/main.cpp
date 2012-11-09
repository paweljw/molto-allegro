#include <vector>
#include <string>
#include <allegro5/allegro.h>
#include <iostream>

#include "../src/molto-allegro.h"
#include "../src/allegro5_renderer.h"

int dummy(void* arg)
{
	int *input = (int*)(arg);

	cout << "Callback called, said " << *input << endl;
	*(input) += 1;
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

	Allegro5_Renderer* renderer = new Allegro5_Renderer(display);

	Menu *m = new Menu(renderer);

	m->addElem(string("Test"));
	m->addElem(string("Test 2"));	
	m->addElem(string("Test 3"));

	int param;
	param = 10;

	m->element("Test")->addElem("Test button 1", dummy, (void*)&param);
	m->element("Test")->addElem("Test button 2", dummy, (void*)&param);
	m->element("Test")->addElem("Test button 3", dummy, (void*)&param);
	m->element("Test")->addElem("Test button 4", dummy, (void*)&param);

	m->draw();

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

			if(m->click(x, y))
				cout << "New param value: " << param << endl;

			m->draw();

			al_flip_display();
			
		}
	}

	return 0;
}
