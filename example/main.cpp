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

	Menu *m = new Menu(display);

	m->addElem(string("Test"));
	m->addElem(string("Testowy 2"));	
	m->addElem(string("Kolejny"));
	m->addElem(string("Czy one rosną?"));

	m->draw(display);

	al_flip_display();

	al_rest(3.0);

	return 0;
}
