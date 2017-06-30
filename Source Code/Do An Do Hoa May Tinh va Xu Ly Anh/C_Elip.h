#pragma once
#ifndef _ELIP_H_
#define _ELIP_H_
class C_Elip
{
public:
	C_Elip();
	~C_Elip();
	void DrawElip(CDC *pDC, CPoint m_point_s, CPoint m_point_f, COLORREF color);
	//void Set8Pixel(CDC *pDC, CPoint m_point, int a, int b, COLORREF color);
	void setpixel6(CDC *pDC, int xc, int yc, int x, int y, int color);
};

#endif