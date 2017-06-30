#pragma once

#define Round(a) int(a+0.5)

class C_Line
{
public:
	C_Line();
	~C_Line();
	void DrawLine(CDC *pDC, CPoint m_point_s, CPoint m_point_f,COLORREF cCurrentColor);
	
};

