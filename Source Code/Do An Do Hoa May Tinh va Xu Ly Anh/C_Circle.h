#pragma once
#ifndef _CIRCLE_H_
#define _CIRCLE_H_
class C_Circle
{
public:
	C_Circle();
	~C_Circle();
	void DrawCircle(CDC *pDC, CPoint m_point_s, float iR, COLORREF color);
	void Set8Pixel(CDC *pDC, CPoint m_point, int a, int b, COLORREF color);
};

#endif