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
}
