#include "stdafx.h"
#include "C_Elip.h"


C_Elip::C_Elip()
{
}
C_Elip::~C_Elip()
{
}
void C_Elip::DrawElip(CDC *pDC, CPoint point_s, CPoint point_f, COLORREF color)  //MidPoint Algorithm
{
	int a, b;
	a = abs((point_f.x - point_s.x)/2);
	b = abs((point_f.y - point_s.y)/2);

	CPoint midPoint;
	midPoint.x = (int)(point_s.x + point_f.x) / 2;
	midPoint.y = (int)(point_s.y + point_f.y) / 2;

	int x, y;
	double k1, k2, P;
	x = 0; 
	y = b;
	k1 = (double)(b*b) / (a*a);
	k2 = (double)1 / k1;
	P = 2 * k1 - (2 * b) + 1;
	while (k1*(double)x / y <= 1) 
	{
		setpixel6(pDC, midPoint.x, midPoint.y, x, y, color);
		if (P < 0) P += 2 * k1*(2 * x + 3);
		else 
		{
			P += 2 * k1*(2 * x + 3) + 4 * (1 - y);
			y--;
		}
		x++;
	}

	x = a; 
	y = 0;
	P = 2 * k2 - 2 * a + 1;
	while (k2*(double)y / x <= 1) 
	{
		setpixel6(pDC, midPoint.x, midPoint.y, x, y, color);
		if (P < 0) P += 2 * k2*(2 * y + 3);
		else 
		{
			P += 2 * k2*(2 * y + 3) + 4 * (1 - x);
			x--;
		}
		y++;
	}

	

}
void C_Elip::setpixel6(CDC *pDC, int xc, int yc, int x, int y, int color)
{
	pDC->SetPixel(xc + x, y + yc, color);
	pDC->SetPixel(xc - x, y + yc, color);
	pDC->SetPixel(xc - x, yc - y, color);
	pDC->SetPixel(xc + x, yc - y, color);
}
