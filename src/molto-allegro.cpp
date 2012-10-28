#include <vector>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>

#include "molto-allegro.h"
using namespace std;

void Menu::addElem(string s)
{
	elems.push_back(MenuTopElem(s));
}

void Menu::getPos(float& ex1, float& ey1, float& ex2, float& ey2)
{
	ex1 = x1;
	ex2 = x2;
	ey1 = y1;
	ey2 = y2;
}


void Menu::setPos(float ex1, float ey1, float ex2, float ey2)
{
	x1 = ex1;
	x2 = ex2;
	y1 = ey1;
	y2 = ey2;
}


Menu::Menu(ALLEGRO_DISPLAY*& disp)
{
	screen_w = al_get_display_width(disp);
	screen_h = al_get_display_height(disp);

	setPos(0, 0, screen_w, 23);
	shown = true;

	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	font = al_load_ttf_font("dvs.ttf", 14, 0);

	menubmp = al_create_bitmap(screen_w, screen_h);
}

bool Menu::isShown()
{
	return shown;
}

void Menu::show() { shown = true; }

void Menu::hide() { shown = false; }

void Menu::draw(ALLEGRO_DISPLAY* display)
{
	draw();
	al_set_target_bitmap(al_get_backbuffer(display));
	al_draw_bitmap(menubmp, 0,0,0);
}

void Menu::draw(ALLEGRO_BITMAP* bmp)
{
	// stub
}

// the function for drawing all of menu
void Menu::draw()
{
	al_set_target_bitmap(menubmp);
	al_clear_to_color(al_map_rgba(0,0,0,0));

	al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(255, 255, 240));
	al_draw_line(x1, y2, x2, y2, al_map_rgb(0x66, 0x66, 0x66), 2);

	int offset = 0;
	
	for(unsigned int i=0; i < elems.size(); i++)
	{
		string buf;
		buf = elems.at(i).getName();

		int cw = al_get_text_width(font, buf.c_str()) + 20;

		al_draw_text(font, al_map_rgb(0, 0, 0), offset+cw/2, 3, ALLEGRO_ALIGN_CENTRE, buf.c_str());

		offset += cw;
	}
}

MenuTopElem Menu::operator[](string s)
{
	for(unsigned int i=0; i < elems.size(); i++)
	{
		if(elems[i].getName() == s) return elems[i];
	}
	return elems[0];
}

// MenuTopElem

void MenuTopElem::setPos(float ex1, float ey1, float ex2, float ey2)
{
	x1 = ex1;
	x2 = ex2;

	y1 = ex1;
	y2 = ex2;
}

string MenuTopElem::getName()
{
	return name;
}

void MenuTopElem::open()
{
	_open = true;
}

void MenuTopElem::close()
{
	_open = false;
}

MenuTopElem::MenuTopElem(string s)
{
	name = s;
	_open = false;
}

void MenuTopElem::addElem(string s)
{
//	elems.push_back(MenuElem(s));
// stub
}

bool MenuTopElem::isOpen()
{
	return _open;
}
