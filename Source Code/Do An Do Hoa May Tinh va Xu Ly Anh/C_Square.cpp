#include "stdafx.h"
#include "C_Square.h"
#include "C_Regtangle.h"

C_Square::C_Square()
{
}
C_Square::~C_Square()
{
}
void C_Square::Draw_Square(CDC *pDC, CPoint m_point_s, CPoint m_point_f, COLORREF color)
{
	C_Regtangle *p1 = new C_Regtangle;
	CPoint m_point_bot;
	if (m_point_s.x < m_point_f.x)
	{
		if (m_point_s.y < m_point_f.y)
		{
			m_point_bot =CPoint(m_point_f.x, m_point_f.x - m_point_s.x + m_point_s.y);
			p1->DrawRectangle(pDC, m_point_s, m_point_bot, color);
		}			
		else
		{
			CPoint m_point_bot(m_point_f.x, m_point_s.x - m_point_f.x  + m_point_s.y);
			p1->DrawRectangle(pDC, m_point_s, m_point_bot, color);
		}
	}
	else
	{
		if (m_point_s.y < m_point_f.y)
		{
			CPoint m_point_bot(m_point_f.x, m_point_s.x - m_point_f.x + m_point_s.y);
			p1->DrawRectangle(pDC, m_point_s, m_point_bot, color);
		}
		else
		{
			m_point_bot = CPoint(m_point_f.x, m_point_f.x - m_point_s.x + m_point_s.y);
			p1->DrawRectangle(pDC, m_point_s, m_point_bot, color);
		}
	}
	delete p1;
}
