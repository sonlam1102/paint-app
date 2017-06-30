#pragma once
class C_Regtangle
{
public:
	C_Regtangle();
	~C_Regtangle();
	void DrawRectangle(CDC *pDC, CPoint m_point_s, CPoint m_point_f, COLORREF color);
};

