#pragma once

#ifndef MA_H

#define MA_H

/*!
 * \file molto-allegro.h
 *
 * \author Paweł J. Wal <pjw@paweljw.eu>
 */
#include <vector>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include "renderer.h"
using namespace std;

/*! Simple function pointer definition for later use in callbacks. */
typedef int (*fptr)(void*);

/*! Menu states. Extendable if needed. */
enum MENU_STATE
{
	MENU_CLOSED,
	MENU_OPEN
};

/*! Function checking whether points lay within a rectangle. */
extern bool pointInRectangle(float, float, float, float, float, float);

/*!
 * \class MenuElem
 *
 * \brief Basic clickable element of a menu
 */
class MenuElem
{
	/*! Name tag. */
	string name;
	/*! Callback function pointer. */
	fptr callback;
	/*! Argument payload pointer. */
	void* args;
	/*! Active flag. */
	bool active;
public:
	MenuElem(string, fptr, void*);
//	MenuElem(string, fptr, void*, bool);
	void click();	
	bool isActive();
	void activate();
	void deactivate();
	string getName();
};

/*!
 * \class MenuTopElem
 *
 * \brief Top element of a given menu - names shown in top menu bar.
 *
 * \author Paweł J. Wal <pjw@paweljw.eu>
 */
class MenuTopElem
{
	/*! Name tag. */
	string name;
	/*! X rectangle coordinates. */
	float x1, x2;
	/*! Y rectangle coordinates. */	
	float y1, y2;
public:
	/*! All elements of the category. */
	vector<MenuElem> elems;
	MenuTopElem(string);
	void addElem(string, fptr, void*);
	string getName();
	void setPos(float, float, float, float);
	void getPos(float&, float&, float&, float&);
};

/*!
 * \class Menu
 *
 * \brief Main class for menu control and drawing, focused around the concept of a menu as a state machine.
 *
 * \author Paweł J. Wal <pjw@paweljw.eu>
 */
class Menu
{
	vector<MenuTopElem> elems;
	bool shown;
	float x1, x2;
	float y1, y2;
	int screen_w;
	int screen_h;
	void setPos(float, float, float, float);
	MENU_STATE state;
	int openIx;
	int hitBoxW;
	Renderer* r;
public:
	void addElem(string);
	void getPos(float&, float&, float&, float&);
	Menu(Renderer*);
	void draw();
	MenuTopElem* element(const char*);
	bool click(float, float);
};

#endif
