#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <string>
#include "renderer.h"
#include "allegro5_renderer.h"

Allegro5_Renderer::Allegro5_Renderer(ALLEGRO_DISPLAY *d)
{
	initEnv();

	display = d;
	drawBmp = al_create_bitmap(getDisplayWidth(), getDisplayHeight());

	loadFont();
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

void Allegro5_Renderer::paintToBitmap(ALLEGRO_BITMAP* bmp)
{
	al_set_target_bitmap(bmp);
	al_draw_bitmap(drawBmp, 0, 0, 0);
}
