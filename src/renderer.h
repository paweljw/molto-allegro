#ifndef RENDERER_H

#define RENDERER_H

enum TEXT_ALIGN
{
	TA_LEFT,
	TA_RIGHT,
	TA_CENTER,
	TA_JUSTIFY
};

class Renderer
{
public:
	virtual int getDisplayWidth() = 0;
	virtual int getDisplayHeight() = 0;

	virtual void initEnv();

	virtual void paintToDisplay();
	virtual void paintToBitmap();

	virtual void clearToColor();
	virtual void drawRectangle();
	virtual void drawFilledRectangle();
	virtual void drawLine();
	virtual void drawText();
	virtual void loadFont();
}

#endif
