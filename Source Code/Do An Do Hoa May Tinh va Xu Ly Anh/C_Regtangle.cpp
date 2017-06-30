#include "stdafx.h"
#include "C_Regtangle.h"
#include "C_Line.h"

C_Regtangle::C_Regtangle()
{
}
C_Regtangle::~C_Regtangle()
{
}
void C_Regtangle::DrawRectangle(CDC *pDC, CPoint m_point_s, CPoint m_point_f ,COLORREF color)
{
	C_Line *p1 = new C_Line();
	p1->DrawLine(pDC, CPoint(m_point_s.x, m_point_s.y), CPoint(m_point_f.x, m_point_s.y), color);
	p1->DrawLine(pDC, CPoint(m_point_s.x, m_point_s.y), CPoint(m_point_s.x, m_point_f.y), color);
	p1->DrawLine(pDC, CPoint(m_point_s.x, m_point_f.y), CPoint(m_point_f.x, m_point_f.y), color);
	p1->DrawLine(pDC, CPoint(m_point_f.x, m_point_s.y), CPoint(m_point_f.x, m_point_f.y), color);
	delete p1;
}
