#include <vector>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
using namespace std;

typedef int (*fptr)();

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
};

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
public:
	void addElem(string);
	void getPos(float&, float&, float&, float&);
	void setPos(float, float, float, float);
	Menu(ALLEGRO_DISPLAY*&);
	bool isShown();
	void show();
	void hide();
	void draw(ALLEGRO_DISPLAY*);
	void draw(ALLEGRO_BITMAP*);
	void draw();
	MenuTopElem operator[](string);
//	const MenuTopElem operator[](string);
};




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
