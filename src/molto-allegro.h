/*!
 * \file molto-allegro.h
 *
 * \author Paweł J. Wal <pjw@paweljw.eu>
 * \date
 */
#include <vector>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
using namespace std;

typedef int (*fptr)();

enum MENU_STATE
{
	MENU_CLOSED,
	MENU_OPEN
};

extern bool pointInRectangle(float, float, float, float, float, float);

/*!
 * \class MenuTopElem
 *
 * \brief Top element of a given menu - names shown in top menu bar.
 *
 * \author [your name]
 * \date
 */
class MenuTopElem
{
	string name;
//	vector<MenuElem> elems;
	bool _open;
	float x1, x2;
	float y1, y2;

public:
	MenuTopElem(string);
	void addElem(string);
	void open();
	void close();
	bool isOpen();
	string getName();
	void setPos(float, float, float, float);
	void getPos(float&, float&, float&, float&);
};

/*!
 * \class Menu
 *
 * \brief Main class for menu control and drawing, focused around the concept of a menu as a state machine.
 *
 * \author [your name]
 * \date
 */
class Menu
{
	vector<MenuTopElem> elems;
	bool shown;
	float x1, x2;
	float y1, y2;
	int screen_w;
	int screen_h;
	ALLEGRO_BITMAP* menubmp;
	ALLEGRO_FONT *font;
	void draw();
	void setPos(float, float, float, float);
	MENU_STATE state;
	int openIx;
public:
	void addElem(string);
	void getPos(float&, float&, float&, float&);
	Menu(ALLEGRO_DISPLAY*&);
	bool isShown();
	void show();
	void hide();
	void draw(ALLEGRO_DISPLAY*);
	void draw(ALLEGRO_BITMAP*);
	MenuTopElem operator[](string);
	bool click(float, float);
};



/*!
 * \class MenuElem
 *
 * \brief Basic clickable element of a menu
 * \date
 */
/*

class MenuElem
{
	string name;
	fptr callback;
	bool active;
public:
	MenuElem(string);	
	isActive();
};

*/
