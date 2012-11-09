#ifndef A5R_H

#define A5R_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>
#include "allegro5_renderer.h"

Allegro5_Renderer::Allegro5_Renderer(ALLEGRO_DISPLAY *d)
{
	initEnv();

	display = d;
	drawBmp = al_create_bitmap(getDisplayWidth(), getDisplayHeight());

	loadFont(15);
}

void Allegro5_Renderer::initEnv()
{
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
}

void Allegro5_Renderer::loadFont(int ht)
{
	font = al_load_ttf_font("dvs.ttf", ht, 0);
}

int Allegro5_Renderer::getDisplayWidth()
{
	return (int)al_get_display_width(display);
}

int Allegro5_Renderer::getDisplayHeight()
{
	return (int)al_get_display_height(display);
}

void Allegro5_Renderer::paintToDisplay()
{
	al_set_target_bitmap(al_get_backbuffer(display));
	al_draw_bitmap(drawBmp, 0, 0, 0);
}

ALLEGRO_COLOR Allegro5_Renderer::colorTranslate(int hex)
{
	int r, g, b, a;

    r = (hex & 0xFF000000) >> 24;
    g = (hex & 0x00FF0000) >> 16;
    b = (hex & 0x0000FF00) >> 8;
    a = (hex & 0x000000FF);

	return al_map_rgba(r,g,b,a);
}

void Allegro5_Renderer::clearToColor(int hex)
{
	al_set_target_bitmap(drawBmp);
	al_clear_to_color(colorTranslate(hex));
}

void Allegro5_Renderer::drawRectangle(float x1, float y1, float x2, float y2, int hex, int lw)
{
	al_set_target_bitmap(drawBmp);
	ALLEGRO_COLOR lineColor = colorTranslate(hex);
	al_draw_rectangle(x1, y1, x2, y2, lineColor, lw);
}

void Allegro5_Renderer::drawFilledRectangle(float x1, float y1, float x2, float y2, int hex) // x, y, x, y, fill_color
{
	al_set_target_bitmap(drawBmp);
	ALLEGRO_COLOR lineColor = colorTranslate(hex);
	al_draw_filled_rectangle(x1, y1, x2, y2, lineColor);
}

void Allegro5_Renderer::drawLine(float x1, float y1, float x2, float y2, int hex, int lw)
{
	al_set_target_bitmap(drawBmp);
	ALLEGRO_COLOR lineColor = colorTranslate(hex);
	al_draw_line(x1, y1, x2, y2, lineColor, lw);
}

void Allegro5_Renderer::drawText(float x, float y, string s, TEXT_ALIGN ta, int hex)
{
	ALLEGRO_COLOR tColor = colorTranslate(hex);

	switch(ta) {
		case TA_LEFT: al_draw_text(font, tColor, x, y, ALLEGRO_ALIGN_LEFT, s.c_str()); break;
		case TA_RIGHT: al_draw_text(font, tColor, x, y, ALLEGRO_ALIGN_RIGHT, s.c_str()); break;
		case TA_CENTER: al_draw_text(font, tColor, x, y, ALLEGRO_ALIGN_CENTRE, s.c_str()); break;
	}
}

int Allegro5_Renderer::getTextWidth(string s)
{
	return al_get_text_width(font, s.c_str());
}

#endif


