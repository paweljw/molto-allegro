/*!
 * \file molto-allegro.cpp
 *
 * \author Paweł J. Wal <pjw@paweljw.eu>
 * \date
 */
#include <vector>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>

#include "molto-allegro.h"
using namespace std;

#define MENU_HT 25

bool pIR(float x1, float y1, float x2, float y2, float xp, float yp)
{
	if(xp >= x1 && xp <= x2 && yp >= y1 && yp <= y2) return true;
	return false;
}

/*!
 * \brief Adds top-level elements to menu.
 *
 * \param s Name for element.
 */
void Menu::addElem(string s)
{
	elems.push_back(MenuTopElem(s));
}

/*!
 * \brief Gets the menu rectangle.
 */
void Menu::getPos(float& ex1, float& ey1, float& ex2, float& ey2)
{
	ex1 = x1;
	ex2 = x2;
	ey1 = y1;
	ey2 = y2;
}

/*!
 * \brief Sets the menu rectangle.
 */
void Menu::setPos(float ex1, float ey1, float ex2, float ey2)
{
	x1 = ex1;
	x2 = ex2;
	y1 = ey1;
	y2 = ey2;
}

/*!
 * \brief Constructor. Requires display for getting drawing rectangle size.
 *
 * \param disp Allegro display.
 */
Menu::Menu(ALLEGRO_DISPLAY*& disp)
{
	screen_w = al_get_display_width(disp);
	screen_h = al_get_display_height(disp);

	setPos(0, 0, screen_w, MENU_HT - 2);
	shown = true;

	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	font = al_load_ttf_font("dvs.ttf", MENU_HT/2 + 2, 0);

	menubmp = al_create_bitmap(screen_w, screen_h);

	state = MENU_CLOSED;
}

bool Menu::click(float x, float y)
{
	float x1, x2, y1, y2;

	for(unsigned int i=0;i<elems.size();i++)
	{
		elems.at(i).getPos(x1, y1, x2, y2);
		cout << x1 << "," << y1 << " " << x2 << "," << y2 << endl;
		if(pIR(x1, y1, x2, y2, x, y))
		{
			state = MENU_OPEN;
			openIx = i;
			cout << openIx << " got clicked" << endl;
			return true;
		}
	}

	// no top level menus have been hit; are we open?
	
	/*if(state == MENU_OPEN)
	{
		// we check rectangle with:
		// x1 = openIx's x1
		// y1 = MENU_HT
		// x2 = openIx's number of elements times MENU_HT
		// y2 = openIx's width (???)
	} */ 

	if(state == MENU_OPEN)
	{
		// Click was outside an open menu; default behavior should be close.
		state = MENU_CLOSED;
		cout << "Menu got closed." << endl;
	}

	return false;
}		

/*!
 * \brief Checks whether menu is shown.
 *
 * \return Shown status of menu.
 */
bool Menu::isShown()
{
	return shown;
}

/*!
 * \brief Shows menu.
 */
void Menu::show() { shown = true; }

/*!
 * \brief Hides menu.
 */
void Menu::hide() { shown = false; }

/*!
 * \brief Draws menu to a display.
 *
 * \param display Allegro display.
 */
void Menu::draw(ALLEGRO_DISPLAY* display)
{
	draw();
	al_set_target_bitmap(al_get_backbuffer(display));
	al_draw_bitmap(menubmp, 0,0,0);
}

/*!
 * \brief Draws menu to a bitmap.
 *
 * \param bmp Allegro bitmap.
 */
void Menu::draw(ALLEGRO_BITMAP* bmp)
{
	draw();
	al_set_target_bitmap(bmp);
	al_draw_bitmap(menubmp, 0, 0, 0);
}

/*!
 * \brief Draws the menu to an internal bitmap for later reuse.
 */
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

		// Reset the box for menu element (click hitbox)
		// It could have changed
		elems.at(i).setPos(offset, 0, offset+cw, MENU_HT);
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

void MenuTopElem::getPos(float &ex1, float &ey1, float &ex2, float &ey2)
{
	ex1 = x1; ex2 = x2;
	ey1 = y1; ey2 = y2;
}

void MenuTopElem::setPos(float ex1, float ey1, float ex2, float ey2)
{
	x1 = ex1;
	x2 = ex2;

	y1 = ey1;
	y2 = ey2;
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
