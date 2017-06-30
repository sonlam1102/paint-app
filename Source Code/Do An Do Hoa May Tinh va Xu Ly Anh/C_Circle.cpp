#include "stdafx.h"
#include "C_Circle.h"
C_Circle::C_Circle()
{
}
C_Circle::~C_Circle()
{
}
void C_Circle::DrawCircle(CDC *pDC, CPoint m_point_s, float iR, COLORREF color)  //MidPoint Algorithm
{
	int x = 0, y = iR;
	int d = 1 - iR;
	Set8Pixel(pDC, m_point_s, x, y, color);

	while (x<y)
	{
		if (d<0)
			d += 2 * x + 3;
		else
		{
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
		Set8Pixel(pDC, m_point_s, x, y, color);
	}
}
void C_Circle::Set8Pixel(CDC *pDC, CPoint m_point, int a, int b, COLORREF color)
{
	pDC->SetPixel(m_point.x + a, m_point.y + b, color);
	pDC->SetPixel(m_point.x - a, m_point.y + b, color);
	pDC->SetPixel(m_point.x - a, m_point.y - b, color);
	pDC->SetPixel(m_point.x + a, m_point.y - b, color);
	pDC->SetPixel(m_point.x + b, m_point.y + a, color);
	pDC->SetPixel(m_point.x - b, m_point.y + a, color);
	pDC->SetPixel(m_point.x - b, m_point.y - a, color);
	pDC->SetPixel(m_point.x + b, m_point.y - a, color);
}
