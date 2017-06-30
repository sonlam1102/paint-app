#include"Screen.h"

const int width = 1288;
const int height = 604;
Screen::Screen()
{
	scr = new COLORREF*[width];
	for (int i = 0; i < width; i++)
		scr[i] = new COLORREF[height];
}
void Screen::getScreen(CDC *pDC)
{
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
			scr[i][j] = pDC->GetPixel(i, j);
}
void Screen::setScreen(CDC *pDC)
{
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
			pDC->SetPixel(i, j, scr[i][j]);
}
void Screen::release()
{
	for (int i = 0; i < width; i++)
			delete[] scr[i];
	delete[]scr;
}