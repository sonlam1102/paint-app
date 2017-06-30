#include "stdafx.h"
#include "C_Line.h"


C_Line::C_Line()
{
}
C_Line::~C_Line()
{
}
void C_Line::DrawLine(CDC *pDC, CPoint m_point_s, CPoint m_point_f, COLORREF cCurrentColor)  //Bresenham Algorithm
{
	int dy = abs(m_point_f.y - m_point_s.y);
	int dx = abs(m_point_f.x - m_point_s.x);
	int x, y, p;
	int c;
	int f_x, f_y;

	p = dx - dy;

	x = m_point_s.x;
	y = m_point_s.y;

	f_x = 1;
	f_y = 1;

	if (m_point_f.x - m_point_s.x < 0)
		f_x = -f_x;
	if (m_point_f.y - m_point_s.y < 0)
		f_y = -f_y;

	pDC->SetPixel(x, y, cCurrentColor);
	if (m_point_s.x == m_point_f.x)
	{
		for (int i = m_point_s.y; i < m_point_f.y; i++)
		{
			y += f_y;
			pDC->SetPixel(x, y, cCurrentColor);
		}
	}
	else
		if (m_point_s.y == m_point_f.y)
		{
			for (int i = m_point_s.x; i < m_point_f.x; i++)
			{
				x += f_x;
				pDC->SetPixel(x, y, cCurrentColor);
			}
		}

	if (m_point_s.x != m_point_f.x && m_point_s.y != m_point_f.y)
	{
		while (1)
		{
			if (x == m_point_f.x && y == m_point_f.y)
				break;
			c = 2 * p;
			if (c > -dy)
			{
				p = p - dy;
				x = x + f_x;
			}
			if (c < dx)
			{
				p = p + dx;
				y = y + f_y;
			}
			pDC->SetPixel(x, y, cCurrentColor);
		}
	}
}