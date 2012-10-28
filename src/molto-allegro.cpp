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
#include <stdlib.h>
#include <time.h>

#include "molto-allegro.h"
using namespace std;

/*! Menu height. */
#define MENU_HT 25

/*!
 * \brief Checks whether point is within a rectangle.
 */
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
	cout << screen_w << "x" << screen_h << endl;

	state = MENU_CLOSED;
	hitBoxW = 0;
}

/*!
 * \brief Click event for menu class.
 *
 * \param x X coordinate of mouse during click.
 * \param y Y coordinate of mouse during click.
 */
bool Menu::click(float x, float y)
{
	float tx1, tx2, ty1, ty2;

	for(unsigned int i=0;i<elems.size();i++)
	{
		elems.at(i).getPos(tx1, ty1, tx2, ty2);
		cout << x1 << "," << y1 << " " << x2 << "," << y2 << endl;
		if(pIR(tx1, ty1, tx2, ty2, x, y))
		{
			state = MENU_OPEN;
			openIx = i;
			cout << openIx << " got clicked" << endl;
			return true;
		}
	}

	// no top level menus have been hit; are we open?
	
	if(state == MENU_OPEN)
	{
		// we check rectangle with:
		// x1 = openIx's x1
		// y1 = MENU_HT
		// x2 = openIx's number of elements times MENU_HT
		// y2 = hitBoxW

		elems.at(openIx).getPos(tx1, ty1, tx2, ty2);		

		for(unsigned int i=0;i<elems.at(openIx).elems.size();i++)
		{
			if(pIR(tx1, MENU_HT * (i+1), tx1 + hitBoxW, MENU_HT * (i+2), x, y))
			{
				elems.at(openIx).elems.at(i).click();
				state = MENU_CLOSED;
				return true;
			}
		}	
	} 

	if(state == MENU_OPEN)
	{
		// Click was outside an open menu; default behavior should be close.
		state = MENU_CLOSED;
		cout << "Menu got closed." << endl;
	}

	return false;
}		

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
	cout << "Going draw" << endl;

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

	// Step two: drawing currently open menu
	if(state == MENU_OPEN)
	{
		int height = 0; // base height

		height += elems.at(openIx).elems.size()*MENU_HT;
			
		cout << "Draw height " << height << endl;

		float tx1, tx2, ty1, ty2;
		elems.at(openIx).getPos(tx1, ty1, tx2, ty2);		
		cout << x2 << "," << y2 << endl;

		if(height == 0)
		{
			// empty menu!
			height = MENU_HT;
			int longest = 30 + al_get_text_width(font, "- Empty -") + tx1;
			al_draw_filled_rectangle(tx1, MENU_HT-2, longest, height+MENU_HT, al_map_rgb(255, 255, 240));

			al_draw_line(longest, MENU_HT-2, longest, MENU_HT*2, al_map_rgb(0x66, 0x66, 0x66), 1);
			al_draw_line(tx1, height+MENU_HT, longest, MENU_HT*2, al_map_rgb(0x66, 0x66, 0x66), 1);	

			al_draw_text(font, al_map_rgb(0x66, 0x66, 0x66), tx1+10, MENU_HT*1+2, ALLEGRO_ALIGN_LEFT, "- Empty -");		
		} else {


			unsigned int mSize = 0;
			int mInt  = 0;
	
			for(unsigned int i=0; i<elems.at(openIx).elems.size(); i++)
			{
				if(elems.at(openIx).elems.at(i).getName().length() > mSize) 
				{
					mSize = elems.at(openIx).elems.at(i).getName().length();
					mInt  = i;
				} 
			}

			int longest = 30 + al_get_text_width(font, elems.at(openIx).elems.at(mInt).getName().c_str());
			hitBoxW = longest;
			al_draw_filled_rectangle(tx1, MENU_HT-2, tx1 + longest, height+MENU_HT, al_map_rgb(255, 255, 240));

			for(unsigned int i=0; i<elems.at(openIx).elems.size(); i++)
			{
				ALLEGRO_COLOR col;
				MenuElem menel = elems.at(openIx).elems.at(i);
				col = (menel.isActive() ? al_map_rgb(0, 0, 0) : al_map_rgb(0x66, 0x66, 0x66));
				al_draw_text(font, col, tx1+10, MENU_HT*(i+1)+2, ALLEGRO_ALIGN_LEFT, menel.getName().c_str());
			}

			al_draw_line(longest, MENU_HT-2, tx1 + longest, MENU_HT * ( elems.at(openIx).elems.size()+1), al_map_rgb(0x66, 0x66, 0x66), 1);
			al_draw_line(tx1, height+MENU_HT, tx1 + longest, MENU_HT * ( elems.at(openIx).elems.size()+1), al_map_rgb(0x66, 0x66, 0x66), 1);
		}
	}
}

/*!
 * \brief Returns name of a MenuElem.
 *
 * \return Element's name.
 */
string MenuElem::getName() { return name; }

/*!
 * \brief Returns MenuTopElem by name.
 *
 * \param cs name of element to be found.
 * \return MenuTopElem* of given name.
 */
MenuTopElem* Menu::element(const char *cs)
{
	string s(cs);

	for(unsigned int i=0; i < elems.size(); i++)
	{
		if(elems[i].getName() == s) return &elems[i];
	}
	return &elems[0];
}

/*!
 * \brief Get rectangle coordinates of a MenuTopElem.
 *
 * \param[out] ex1 top left corner of rectangle
 * \param[out] ey1 top left corner of rectangle
 * \param[out] ex2 bottom right corner of rectangle
 * \param[out] ey2 bottom right corner of rectangle
 */
void MenuTopElem::getPos(float &ex1, float &ey1, float &ex2, float &ey2)
{
	ex1 = x1; ex2 = x2;
	ey1 = y1; ey2 = y2;
}

/*!
 * \brief Sets rectangle coordinates of a MenuTopElem.
 *
 * \param ex1 top left corner of rectangle
 * \param ey1 top left corner of rectangle
 * \param ex2 bottom right corner of rectangle
 * \param ey2 bottom right corner of rectangle
 */
void MenuTopElem::setPos(float ex1, float ey1, float ex2, float ey2)
{
	x1 = ex1;
	x2 = ex2;

	y1 = ey1;
	y2 = ey2;
}

/*!
 * \brief Get name of a MenuTopElem.
 */
string MenuTopElem::getName()
{
	return name;
}

/*!
 * \brief Constructor of a MenuTopElem using a string.
 * 
 * \param s Name to be set.
 */
MenuTopElem::MenuTopElem(string s)
{
	name = s;
}

/*!
 * \brief Add a button to a top menu element (category).
 * 
 * \param s String for name.
 * \param f Pointer to a callback function
 * \param a Callback argument payload.
 */
void MenuTopElem::addElem(string s, fptr f, void* a)
{
	elems.push_back(MenuElem(s,f,a));
}

/*!
 * \brief MenuElem constructor.
 *
 * \param s String for name.
 * \param f Pointer to a callback function
 * \param a Callback argument payload.
 */
MenuElem::MenuElem(string s, fptr f, void* a)
{
	name = s;
	callback = f;
	args = a;
	active = true;
}

/*
MenuElem::MenuElem(string s, fptr f, void* a, bool b)
{
	name = s;
	callback = f;
	args = a;
	active = b;
}*/

/*!
 * \brief MenuElem click event.
 *
 */
void MenuElem::click()
{
	callback(args);
}

/*!
 * \brief Check whether MenuElem is active (clickable).
 *
 * \return Boolean active.
 */
bool MenuElem::isActive()
{
	return active;
}

/*!
 * \brief Activate a MenuElem.
 */
void MenuElem::activate()
{
	active = true;
}


/*!
 * \brief Deactivate a MenuElem.
 */
void MenuElem::deactivate()
{
	active = false;
}
