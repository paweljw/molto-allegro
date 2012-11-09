#pragma once

#ifndef RENDERER_H

#include <string>
using namespace std;

#define RENDERER_H

enum TEXT_ALIGN
{
	TA_LEFT,
	TA_RIGHT,
	TA_CENTER
};

class Renderer
{
	virtual void initEnv() = 0;
	virtual void loadFont(int) = 0;
public:
	virtual int getDisplayWidth() = 0;
	virtual int getDisplayHeight() = 0;

	virtual void paintToDisplay() = 0;

	virtual void clearToColor(int) = 0;
	virtual void drawRectangle(float, float, float, float, int, int) = 0;
	virtual void drawFilledRectangle(float, float, float, float, int) = 0;
	virtual void drawLine(float, float, float, float, int, int) = 0;
	virtual void drawText(float, float, string, TEXT_ALIGN, int) = 0;

	virtual int getTextWidth(string)=0;
};

#endif
