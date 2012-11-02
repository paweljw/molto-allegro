#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <string>
using namespace std;

class Allegro5_Renderer
{
	ALLEGRO_DISPLAY *display;
	ALLEGRO_BITMAP *drawBmp;
public:
	Allegro5_Renderer(ALLEGRO_DISPLAY*);

	int getDisplayWidth();
	int getDisplayHeight();
	
	void initEnv();

	void paint();

	void clearToColor(int);
	void drawRectangle(float, float, float, float, int); // x, y, x, y, line_color
	void drawFilledRectangle(float, float, float, float, int); // x, y, x, y, fill_color
	void drawLine(float, float, float, float, int); // x, y, x, y, line_color
	void drawText(float, float, string, TEXT_ALIGN);
}
