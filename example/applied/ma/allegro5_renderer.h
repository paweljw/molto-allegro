#pragma once

#ifndef A5RH

#define A5RH

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>
#include "renderer.h"
using namespace std;

class Allegro5_Renderer : public Renderer
{
	ALLEGRO_DISPLAY *display;
	ALLEGRO_BITMAP *drawBmp;
	ALLEGRO_FONT *font;

	void initEnv(); //
	void loadFont(int); //

	ALLEGRO_COLOR colorTranslate(int); //
public:
	Allegro5_Renderer(ALLEGRO_DISPLAY*); //

	int getDisplayWidth(); //
	int getDisplayHeight(); //
	
	void paintToDisplay(); //

	void clearToColor(int);

	void drawRectangle(float, float, float, float, int, int); // x, y, x, y, line_color, line_width
	void drawFilledRectangle(float, float, float, float, int); // x, y, x, y, fill_color
	void drawLine(float, float, float, float, int, int); // x, y, x, y, line_color
	void drawText(float, float, string, TEXT_ALIGN, int);
	int getTextWidth(string);
};

#endif
